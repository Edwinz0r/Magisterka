//recorder.h
// Recorder class declarations

#ifndef _RECORDER_H
#define _RECORDER_H

//using namespace cv;
class Recorder {

protected:
	cv::VideoCapture cap;
	virtual inline bool existsTest(const std::string & );
	virtual cv::Scalar countMovingPixels(cv::Mat &, cv::Mat &, cv::Mat &, cv::Mat &);
public:
	Recorder();
	Recorder(int);
	Recorder(std::string);   
	virtual int capture()=0;

};

#endif