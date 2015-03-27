// recorder.cpp
// Recorder class definitions

#include "stdafx.h"

using namespace cv;


Recorder::Recorder(): cap(0){

	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

Recorder::Recorder(int mod): cap(mod){
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

Recorder::Recorder(std::string filename): cap(filename){
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

 inline bool Recorder::exists_test(const std::string & name){
    if (FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

 Scalar Recorder::count_moving_pixels(Mat & next_frame, Mat & curr_frame, Mat & prev_frame, Mat & fgMask){
		Mat d1,d2;
	
		absdiff(prev_frame, next_frame, d1);
        absdiff(curr_frame, next_frame, d2);
        bitwise_and(d1, d2, fgMask);

        threshold(fgMask, fgMask,25,255,CV_THRESH_BINARY);

//        addWeighted( curr_frame, alpha, prev_back, beta, 0.0, back);
//        absdiff(curr_frame, back, fgMask);
//        threshold(fgMask, fgMask,30,255,CV_THRESH_BINARY);
		cvtColor(fgMask, fgMask, CV_GRAY2BGR);
           //medianBlur(fgMask,fgMask,1);
        imshow("diffrence", fgMask);
        medianBlur(fgMask,fgMask,1);
        return sum(fgMask);
}