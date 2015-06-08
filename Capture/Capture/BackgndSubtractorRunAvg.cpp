//BackgndSubtractorGMM.cpp
// BackgndSubtractorGMM class definitions
// author: Tomasz Wieczorek

#include "BackgndSubtractorRunAvg.h"
#include <iostream>
#include "stdafx.h"
using namespace cv;

BackgndSubtractorRunAvg::BackgndSubtractorRunAvg(Recorder & _cap, std::string backgndFileName): 
	BackgndSubtractor(_cap),
	mAlpha(0.2)
{
	if(backgndFileName== "")
	{
		mFirstBackgndFromFile=false;
		// TODO
		mRecorder.getFrame(mPrevBackgnd);
	}else{
		mFirstBackgndFromFile=true;
		mRecorder.getFrame(mPrevBackgnd);
		cvtColor(mPrevBackgnd, mPrevBackgnd, CV_BGR2GRAY);
	}
}

void BackgndSubtractorRunAvg::setAlpha(double _alpha)
{
	mAlpha=_alpha;

}
int BackgndSubtractorRunAvg::extractFg(){

	Mat currFrame, currBackgnd, debug;

	mRecorder.getFrame(currFrame);
	cvtColor(currFrame, currFrame, CV_BGR2GRAY);
	mPrevBackgnd.copyTo(debug);
	cvtColor(mPrevBackgnd, mPrevBackgnd, CV_BGR2GRAY);
	
	addWeighted( currFrame, mAlpha, mPrevBackgnd, 1-mAlpha, 0.0, currBackgnd);
	currBackgnd.copyTo(debug);
	absdiff(currFrame, currBackgnd, mFgMask);
	threshold(mFgMask, mFgMask,defines::BGND_SUBTRACTOR_THRESHOLD,255,CV_THRESH_BINARY);
	//adaptiveThreshold(mFgMask,mFgMask,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,5,5);
	if(mShowFlag){
		//cvtColor(mFgMask, mFgMask, CV_GRAY2BGR);
		imshow("Mask", mFgMask);
		waitKey(0);
	}
	//cvtColor(currBackgnd, currBackgnd, CV_BGR2GRAY);
	currBackgnd.copyTo(mPrevBackgnd);
	cvtColor(mPrevBackgnd, mPrevBackgnd, CV_GRAY2BGR);
	return 0;
}
