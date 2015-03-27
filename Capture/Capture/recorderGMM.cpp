//recorderGMM.cpp
// RecorderGMM class definitions
// author: Tomasz Wieczorek

#include "stdafx.h"

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

	 Mat curr_frame, prev_frame, next_frame, curr_frame_rgb, fgMask;
	 Mat back, prev_back,temp;
	 // pMOG = createBackgroundSubtractorMOG();
	 double alpha=0.2;
	 double beta=1-alpha;
	 bool movement=false;
	 Scalar amount_of_mov_pixels;

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

		 amount_of_mov_pixels=count_moving_pixels(next_frame, curr_frame, prev_frame,fgMask);
		 imshow("stream",curr_frame);

		 curr_frame.copyTo(prev_frame);
		 next_frame.copyTo(curr_frame);
		 if(waitKey(30) >= 0) break;

		 // Nagrywanie filmu
		 if( *(amount_of_mov_pixels.val) > 70000)
		 {

			 // Inicjalizacja plikow zapisu filmow
			 sprintf(filename1,"movement_%d.avi",a);
			 while(exists_test(filename1))
			 {
				 a++;
				 sprintf(filename1,"movement_%d.avi",a);
			 }
			 mov.open(filename1, Def::CODEC, 24 ,frS); //CV_FOURCC('X','V','I','D')
			 movement=true;
			             sprintf(filename2,"mask_%d.avi",b);
			             while(exists_test(filename2))
			             {
			                 b++;
			                 sprintf(filename2,"mask_%d.avi",b);
			             }
			             mask.open(filename2,Def::CODEC,24,frS); //
			 // ------------------------------------------

			 j=0;

			 while(movement)
			 {

				 cap >> next_frame; // get a new frame from camera
				 if (next_frame.empty()) break;
				 cvtColor(next_frame, next_frame, CV_BGR2GRAY);
				 amount_of_mov_pixels=count_moving_pixels(next_frame, curr_frame, prev_frame, fgMask);

				 imshow("stream",curr_frame);               
				 cvtColor(curr_frame, curr_frame_rgb, CV_GRAY2BGR);

				 mov<<curr_frame_rgb;
				  mask<<fgMask;

				 curr_frame.copyTo(prev_frame);
				 next_frame.copyTo(curr_frame);
				 if(waitKey(30) >= 0) break;
				 j++;
				 if( *(amount_of_mov_pixels.val) > 30000) j=0;
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





