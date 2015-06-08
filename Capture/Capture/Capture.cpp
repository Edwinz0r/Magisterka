// Capture.cpp : Defines the entry point for the console application.
#include "stdafx.h"

// #include <stdio.h>

using namespace cv;

int main()
{
	Recorder A("Comp1.avi");
	BackgndSubtractorGMM bgnSub(A);
	bgnSub.setShow();
	try{
		for(int i=0;i<200;++i){
			bgnSub.extractFg();

		}
	}catch(...){std::cout<<"Nie dziala zrodlo"<<std::endl;};

	//system("PAUSE");
	return 0;

}