#ifndef IDENTIFICATOR_H
#define IDENTIFICATOR_H
#include "stdafx.h"

class Identificator{
private:
	Recorder mRecorder;
	BackgndSubtractorRunAvg mBackgndSubtractor;
public:
	Identificator();
	Identificator(int);
	Identificator(std::string);
	~Identificator();

};

#endif