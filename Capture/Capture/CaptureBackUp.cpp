// Capture.cpp : Defines the entry point for the console application.
#include "stdafx.h"

// #include <stdio.h>

using namespace cv;

inline bool exists_test(const std::string & name)
{
    if (FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{

    VideoCapture cap(0); // open the default camera
    cap.set(CV_CAP_PROP_FRAME_WIDTH,768);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,576);

    if(!cap.isOpened())  // check if we succeeded
    {
        std::cout<<"Nie dziala polaczenie z kamera"<<std::endl;
        return -1;
    }

    Mat curr_frame, prev_frame, next_frame, curr_frame_rgb, d1,d2,fgMask;
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
        cvtColor(next_frame, next_frame, CV_BGR2GRAY);
            //absdiff(curr_frame_gray, prev_frame , d1);
        absdiff(prev_frame, next_frame, d1);
        absdiff(curr_frame, next_frame, d2);
        bitwise_and(d1, d2, fgMask);

        threshold(fgMask, fgMask,25,255,CV_THRESH_BINARY);

//        addWeighted( curr_frame, alpha, prev_back, beta, 0.0, back);
//        absdiff(curr_frame, back, fgMask);
//        threshold(fgMask, fgMask,30,255,CV_THRESH_BINARY);
        medianBlur(fgMask,fgMask,1);
        amount_of_mov_pixels=sum(fgMask);
        std::cout<<*amount_of_mov_pixels.val<<std::endl;


        imshow("stream",curr_frame);
        cvtColor(fgMask, fgMask, CV_GRAY2BGR);
           //medianBlur(fgMask,fgMask,1);
        imshow("diffrence", fgMask);
        curr_frame.copyTo(prev_frame);
        next_frame.copyTo(curr_frame);
        if(waitKey(30) >= 0) break;

    // Nagrywanie filmu
        if( *(amount_of_mov_pixels.val) > 70000)
    {
            std::cout<<"w ifie"<<std::endl;
        // Inicjalizacja plikow zapisu filmow
            sprintf(filename1,"movement_%d.avi",a);
            while(exists_test(filename1))
            {
                a++;
                sprintf(filename1,"movement_%d.avi",a);
            }
            mov.open(filename1,CV_FOURCC('X','V','I','D'),24,frS); //CV_FOURCC('X','V','I','D')
            movement=true;
//            sprintf(filename2,"mask_%d.avi",b);
//            while(exists_test(filename2))
//            {
//                b++;
//                sprintf(filename2,"mask_%d.avi",b);
//            }
//            mask.open(filename2,CV_FOURCC('X','V','I','D'),24,frS); //
            // ------------------------------------------

            j=0;

            while(movement)
            {


                cap >> next_frame; // get a new frame from camera
                cvtColor(next_frame, next_frame, CV_BGR2GRAY);
                //absdiff(curr_frame_gray, prev_frame , d1);
                absdiff(prev_frame, next_frame, d1);
                absdiff(curr_frame, next_frame, d2);
                bitwise_and(d1, d2, fgMask);

                threshold(fgMask,fgMask,25,255,CV_THRESH_BINARY);
                amount_of_mov_pixels=sum(fgMask);

                imshow("stream",curr_frame);
                cvtColor(fgMask, fgMask, CV_GRAY2BGR);
                //medianBlur(fgMask,fgMask,1);
                imshow("diffrence", fgMask);
                cvtColor(curr_frame, curr_frame_rgb, CV_GRAY2BGR);
                mov<<curr_frame_rgb;
               // mask<<fgMask;

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

//VideoCapture cap(3); // open the default camera
//
//if(!cap.isOpened()) // check if we succeeded
//    std::cout<<"Kamera nie dziala"<<std::endl;
//return -1;
//
//

// the camera will be deinitialized automatically in VideoCapture destructor
//
//return 0;
}
