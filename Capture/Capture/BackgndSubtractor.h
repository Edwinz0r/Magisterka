//recorderGMM.cpp
// RecorderGMM class declarations
// author: Tomasz Wieczorek

#include "stdafx.h"

#ifndef BACKGND_SUBTRACTOR_H
#define BACKGND_SUBTRACTOR_H

class BackgndSubtractor{
protected:
//	Recorder rec;
	cv::Mat mFgMask;
	Recorder& mRecorder;
	bool mExportMaskFlag;
	bool mShowFlag;

public:
	BackgndSubtractor(Recorder&);

	virtual int extractFg();
	virtual void getFgMask(const cv::Mat& out){  mFgMask.copyTo(out);};

	virtual void setExport(){mExportMaskFlag = true;};
	virtual void resetExport(){ mExportMaskFlag = false;};
	virtual bool getExport(){return mExportMaskFlag;};

	virtual void setShow(){mShowFlag = true;};
	virtual void resetShow(){ mShowFlag = false;};
	virtual bool getShow(){return mShowFlag;};
//	inline bool exists_test(const std::string &);
//int	capture();

};

#endif