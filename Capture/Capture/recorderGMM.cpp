//recorderGMM.cpp
// RecorderGMM class definitions
// author: Tomasz Wieczorek

#include "stdafx.h"
using namespace cv;

RecorderGMM::RecorderGMM(): Recorder(0){

	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

RecorderGMM::RecorderGMM(int mod): Recorder(mod){
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

RecorderGMM::RecorderGMM(std::string filename): Recorder(filename){
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

 int RecorderGMM::capture(){

	 if(!cap.isOpened())  // check if we succeeded
	 {
		 std::cout<<"Nie dziala polaczenie z kamera"<<std::endl;
		 return -1;
	 }

	 Mat currFrame, prevFrame, nextFrame, currFrameRGB, fgMask;
	 Mat bgnd, temp;
	 const short int _2sec = 60;
	 // pMOG = createbgndgroundSubtractorMOG();
	 
	 bool movement=false;
	 Scalar amountOfMovPix;

	 VideoWriter mov,mask;
	 Size frS(768,576);
	 char filename1[20],filename2[20];
	 int a=1,b=1,film_limit=1,j=0;
	 cap>>prevFrame;
	 cvtColor(prevFrame, prevFrame, CV_BGR2GRAY);
	 cap>>currFrame;
	 cvtColor(currFrame, currFrame, CV_BGR2GRAY);

	 for(;;)
	 {

		 cap >> nextFrame; // get a new frame from camera

		 if (nextFrame.empty()) break;
		 cvtColor(nextFrame, nextFrame, CV_BGR2GRAY);
		 //absdiff(currFrame_gray, prevFrame , d1);

		 amountOfMovPix=countMovingPixels(nextFrame, currFrame, prevFrame,fgMask);
		 imshow("stream",currFrame);

		 currFrame.copyTo(prevFrame);
		 nextFrame.copyTo(currFrame);
		 if(waitKey(30) >= 0) break;

		 // Nagrywanie filmu
		 if( *(amountOfMovPix.val) > 70000)
		 {

			 // Inicjalizacja plikow zapisu filmow
			 sprintf(filename1,"movement_%d.avi",a);
			 while(existsTest(filename1))
			 {
				 a++;
				 sprintf(filename1,"movement_%d.avi",a);
			 }
			 mov.open(filename1, Def::CODEC, 24 ,frS); //CV_FOURCC('X','V','I','D')
			 movement=true;
			             sprintf(filename2,"mask_%d.avi",b);
			             while(existsTest(filename2))
			             {
			                 b++;
			                 sprintf(filename2,"mask_%d.avi",b);
			             }
			             mask.open(filename2,Def::CODEC,24,frS); //
			 // ------------------------------------------

			 j=0;

			 while(movement)
			 {

				 cap >> nextFrame; // get a new frame from camera
				 if (nextFrame.empty()) break;
				 cvtColor(nextFrame, nextFrame, CV_BGR2GRAY);
				 amountOfMovPix=countMovingPixels(nextFrame, currFrame, prevFrame, fgMask);

				 imshow("stream",currFrame);               
				 cvtColor(currFrame, currFrameRGB, CV_GRAY2BGR);

				 mov<<currFrameRGB;
				  mask<<fgMask;

				 currFrame.copyTo(prevFrame);
				 nextFrame.copyTo(currFrame);
				 if(waitKey(30) >= 0) break;
				 j++;
				 if( *(amountOfMovPix.val) > 30000) j=0;
				 if (j > _2sec) movement=false;
			 }
			 a++;
			 b++;
			 film_limit++;
		 }


		 if(film_limit>300) break;
	 }
	 return 0;  
 }





