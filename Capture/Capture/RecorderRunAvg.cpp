//recorderRunAvg.cpp
// RecorderRunAvg class definitions
// author: Tomasz Wieczorek

#include "stdafx.h"
using namespace cv;
RecorderRunAvg::RecorderRunAvg(): Recorder(0){

	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

RecorderRunAvg::RecorderRunAvg(int mod): Recorder(mod){
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

RecorderRunAvg::RecorderRunAvg(std::string filename): Recorder(filename){
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);
}

 int RecorderRunAvg::capture(){

	 if(!cap.isOpened())  // check if we succeeded
	 {
		 std::cout<<"Nie dziala polaczenie z kamera"<<std::endl;
		 return -1;
	 }

	 Mat curr_frame, prev_frame, next_frame, curr_frame_rgb,fgMask;
	 Mat back, prev_back, temp;
	 // pMOG = createBackgroundSubtractorMOG();
	 double alpha=0.2;
	 double beta=1-alpha;
	 bool movement=false;
	 Scalar amountOfMovPix;

	 VideoWriter mov,mask;
	 Size frS(768,576);
	 char filename1[20],filename2[20];
	 int a=1,b=1,film_limit=1,j=0;
	 cap>>prev_frame;
	 cvtColor(prev_frame, prev_frame, CV_BGR2GRAY);
	 cap>>curr_frame;
	 cvtColor(curr_frame, curr_frame, CV_BGR2GRAY);

	 for(;;)
	 {

		 cap >> next_frame; // get a new frame from camera

		 if (next_frame.empty()) break;
		 cvtColor(next_frame, next_frame, CV_BGR2GRAY);
		 //absdiff(curr_frame_gray, prev_frame , d1);

		 amountOfMovPix=countMovingPixels(next_frame, curr_frame, prev_frame,fgMask);
		 imshow("stream",curr_frame);

		 curr_frame.copyTo(prev_frame);
		 next_frame.copyTo(curr_frame);
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
			 //            sprintf(filename2,"mask_%d.avi",b);
			 //            while(existsTest(filename2))
			 //            {
			 //                b++;
			 //                sprintf(filename2,"mask_%d.avi",b);
			 //            }
			 //            mask.open(filename2,CV_FOURCC('X','V','I','D'),24,frS); //
			

			 j=0;

			 while(movement)
			 {

				 cap >> next_frame; // get a new frame from camera
				 if (next_frame.empty()) break;
				 cvtColor(next_frame, next_frame, CV_BGR2GRAY);
				 amountOfMovPix=countMovingPixels(next_frame, curr_frame, prev_frame,fgMask);

				 imshow("stream",curr_frame);               
				 cvtColor(curr_frame, curr_frame_rgb, CV_GRAY2BGR);

				 mov<<curr_frame_rgb;
				 // mask<<fgMask;

				 curr_frame.copyTo(prev_frame);
				 next_frame.copyTo(curr_frame);
				 if(waitKey(30) >= 0) break;
				 j++;
				 if( *(amountOfMovPix.val) > 30000) j=0;
				 if (j>60) movement=false;
			 }
			 a++;
			 b++;
			 film_limit++;
		 }


		 if(film_limit>300) break;
	 }
	 return 0;  
 }





