//Recorder.h
// Recorder class declarations



#ifndef _RECORDER_H
#define _RECORDER_H
#include "stdafx.h"
#include <mutex>
//using namespace cv;
class Recorder {

private:
	cv::VideoCapture cap;
	cv::Mat frame;
	std::mutex mtxFrame;

	virtual inline bool existsTest(const std::string & );
	virtual cv::Scalar countMovingPixels(cv::Mat &, cv::Mat &, cv::Mat &, cv::Mat & );
public:
	Recorder();
	Recorder(int);
	Recorder(std::string);
	Recorder(Recorder&);

	bool mtxTryLock(){ return mtxFrame.try_lock();};
	void mtxLock(){ mtxFrame.lock();};
	void mtxUnlock(){ mtxFrame.unlock();};

	cv::Mat & getFrame(cv::Mat&);
		
	int captureMovement();

};

#endif