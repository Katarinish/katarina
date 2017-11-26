#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core.hpp>
#include <opencv/cxcore.h>
#include <stdio.h>
#include <time.h>

int main(int argc,char *argv[]){

   clock_t start, stop, start_t, stopt_t;
   double smthg = 0;
   double shwg = 0;
   double gtng =  0;
   double current = 0;
   int cnt = 0;
   int flag = 0;


   CvCapture *capture = cvCreateCameraCapture(0);
   if (!capture)
   return 0;
   start_t = clock();
   while(1) {
     if (current > 1 ){
       printf("The number of shots per 1s: %i\n", cnt)
     }
     IplImage *frame = cvQueryFrame(capture);
     if(!frame)
       break;
     IplImage *image = cvCloneImage(frame);
     //cvSmooth(frame,image,CV_BLUR,3,3);
     cvSmooth(frame, image, CV_BLUR_NO_SCALE, 3, 3);
	 cvShowImage("test",image);
     char c = cvWaitKey(33);
     if(c == 27)
       break;
   }
   cvReleaseCapture(&capture);
   cvDestroyWindow("test");
}
