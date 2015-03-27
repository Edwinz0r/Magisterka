// Capture.cpp : Defines the entry point for the console application.
#include "stdafx.h"

// #include <stdio.h>

using namespace cv;

int main()
{
	RecorderGMM A("movement_13.avi");
	
	return A.capture();

}
