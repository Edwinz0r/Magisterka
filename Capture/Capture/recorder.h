//recorder.h
// Recorder class declarations

#ifndef _RECORDER_H
#define _RECORDER_H

using namespace cv;
class Recorder {

protected:
	VideoCapture cap;
	virtual inline bool exists_test(const std::string & );
	virtual Scalar count_moving_pixels(Mat &, Mat &, Mat &, Mat &);
public:
	Recorder();
	Recorder(int);
	Recorder(std::string);   
	virtual int capture()=0;
	


};

#endif