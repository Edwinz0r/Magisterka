//BackgndSubtractor.cpp
// BackgndSubtractor class definitions
// author: Tomasz Wieczorek

#include "stdafx.h"
using namespace cv;

BackgndSubtractor::BackgndSubtractor(Recorder& _cap): 
	mRecorder(_cap),
	mExportMaskFlag(false), 
	mShowFlag(true)
{
	
}

int BackgndSubtractor::extractFg()
{
	return 0;
}





