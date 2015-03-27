//recorderGMM.cpp
// RecorderGMM class declarations
// author: Tomasz Wieczorek

#include "stdafx.h"

#ifndef RECORDER_GMM_H
#define RECORDER_GMM_H

class RecorderGMM : public Recorder{
private:
	
	

public:
	RecorderGMM();
	RecorderGMM(std::string);
	RecorderGMM(int);
//	inline bool exists_test(const std::string &);
int	capture();

};

#endif