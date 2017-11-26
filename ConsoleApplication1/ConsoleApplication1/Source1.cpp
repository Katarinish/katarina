#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/core.hpp>
#include <opencv/cxcore.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {

	clock_t start, stop, start_t, stopt_t;
	double smthg = 0;
	double shwg = 0;
	double gtng = 0;
	double current = 0;
	int cnt = 0;
	int flag = 0;
	int cntflag = 0;

	CvCapture *capture = cvCreateCameraCapture(0);
	if (!capture)
		return 0;
	start_t = clock();
	while (1) {

		start = clock();
		IplImage *frame = cvQueryFrame(capture);
		stop = clock();
		if (!frame)
			break;
		gtng = (double)(stop - start) / CLOCKS_PER_SEC;
		++cnt;

		start = clock();
		IplImage *image = cvCloneImage(frame);
		//cvSmooth(frame,image,CV_BLUR,3,3);
		cvSmooth(frame, image, CV_BLUR_NO_SCALE, 3, 3);
		// cvSmooth(frame, image, CV_BLUR_NO_SCALE, 4, 4);
		stop = clock();
		smthg = (double)(stop - start) / CLOCKS_PER_SEC;

		start = clock();
		cvShowImage("test", image);
		stop = clock();
		shwg = (double)(stop - start) / CLOCKS_PER_SEC;

		stopt_t = clock();
		current = (double)(stopt_t - start_t) / CLOCKS_PER_SEC;
		if (cntflag == 0 && current > 1) {
			printf("The number of shots per 1s %i\n", cnt);
			cntflag = 1;
		}

		if (flag == 0) {
			printf("%.9f %.9f %.9f\n", gtng, smthg, shwg);
			flag = 1;
		}

		char c = cvWaitKey(33);
		if (c == 27)
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("test");
}
