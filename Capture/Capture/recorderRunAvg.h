#include "stdafx.h"

#ifndef RECORDER_RUNAVG_H
#define RECORDER_RUNAVG_H

class RecorderRunAvg : public Recorder{	
	

public:
	RecorderRunAvg();
	RecorderRunAvg(std::string);
	RecorderRunAvg(int);

int	capture();

};

#endif