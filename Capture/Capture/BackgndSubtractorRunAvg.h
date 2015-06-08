

#ifndef BACKGND_SUBTRACTOR_RUN _AVG_H
#define BACKGND_SUBTRACTOR_RUN_AVG_H
#include "stdafx.h"
class BackgndSubtractorRunAvg : public BackgndSubtractor{
private:
	cv::Mat mPrevBackgnd;
	bool mFirstBackgndFromFile;
	double mAlpha;
	std::string mFilename;
public:
	BackgndSubtractorRunAvg(Recorder &, std::string ="");
	~BackgndSubtractorRunAvg(){};
	int extractFg();
	void setAlpha(double);
	
};

#endif