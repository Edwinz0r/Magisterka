
#include "stdafx.h"

Identificator::Identificator():
	mRecorder(0),
	mBackgndSubtractor(mRecorder)
{

}

Identificator::Identificator(int mod):
	mRecorder(mod),
	mBackgndSubtractor(mRecorder)
{

}

Identificator::Identificator(std::string filename):
	mRecorder(filename),
	mBackgndSubtractor(mRecorder)
{

}

Identificator::~Identificator()
{

}

