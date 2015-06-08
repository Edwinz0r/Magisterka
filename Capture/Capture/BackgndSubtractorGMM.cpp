//BackgndSubtractorGMM.cpp
// BackgndSubtractorGMM class definitions
// author: Tomasz Wieczorek

#include "stdafx.h"
using namespace cv;

BackgndSubtractorGMM::BackgndSubtractorGMM(Recorder& _cap): 
	BackgndSubtractor(_cap)
{
	
}

int BackgndSubtractorGMM::extractFg(){
	
	
	Mat currFrame;

	//try{
		mRecorder.getFrame(currFrame);
//	}catch(...){ throw;}

	if (currFrame.empty()) return -2;

	cvtColor(currFrame, currFrame, CV_BGR2GRAY);
	
	MOG(currFrame, mFgMask);
	threshold(mFgMask,mFgMask,defines::BGND_SUBTRACTOR_THRESHOLD,255,CV_THRESH_BINARY);



	Mat element = getStructuringElement( MORPH_ELLIPSE,
                                       Size( 3, 3 ),
                                       Point( 1, 1 ) );
	dilate( mFgMask, mFgMask, element );  
	erode( mFgMask, mFgMask, element );
	
	//adaptiveThreshold(mFgMask,mFgMask,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,5,5);
	if(mShowFlag){
		cvtColor(mFgMask, mFgMask, CV_GRAY2BGR);
		imshow("Mask", mFgMask);
		waitKey(0);
	}
	return 0;
}
