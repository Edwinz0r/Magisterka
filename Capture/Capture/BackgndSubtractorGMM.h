#include "stdafx.h"

#ifndef BACKGND_SUBTRACTOR_GMM_H
#define BACKGND_SUBTRACTOR_GMM_H

class BackgndSubtractorGMM : public BackgndSubtractor{
private:
	cv::BackgroundSubtractorMOG2 MOG;
public:
	BackgndSubtractorGMM(Recorder &);
	~BackgndSubtractorGMM(){};
	int extractFg();
	
};

#endif