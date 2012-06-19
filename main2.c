#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <cv.h>


void binaryThreshold (IplImage *img) {
	uchar* ptr = NULL;
	int x, y;
	
	//Noise removal and conversion to a binary image
	for(y = 0; y < img->height; y++){
		ptr = (uchar *)(img->imageData + y*img->widthStep);
		for(x = 0; x < img->width; x++){
			if((int)ptr[x] > 150)
				ptr[x] = 255;
			else
				ptr[x] = 0;
		}
	}
}

void morphologicFilter(IplImage *img, int type){
	IplConvKernel* kernel;
	
	switch (type) {
	case 0:
	  cvDilate(img, img, kernel, 1);
	  break;
	case 1:
	  cvErode(img, img, kernel, 1);
	  break;
	case 2:
	  cvMorphologyEx(img,img,0,kernel,CV_MOP_OPEN,1);
	  break;
	case 3:
	  cvMorphologyEx(img,img,0,kernel,CV_MOP_CLOSE,1);
	  break;
	default:
	  cvErode(img, img, kernel, 1);
	  break;
	}
	
}

int main(int argc, char** argv)
{
	IplImage  *img, *img1, *imgChar, *tmp_resize, *tmp_resize1, *imgChar1, *img2;
	IplImage  *tpl, *tpl1;
	IplImage  *res, *resT, *resT1;
	CvPoint   minloc, maxloc, minloc1, maxloc1;
	double    minval, maxval, minval1, maxval1;
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq     *contour;
	CvSeq	  *contourLow;
	CvRect     boundingBox;
	int i, valueRes, valueRes1;

	//cvNamedWindow("template", CV_WINDOW_AUTOSIZE);

	/* check for arguments */
	if(argc < 2) {
		fprintf(stderr, "Usage: template_match <reference> <template>\n");
		return 1;
	}

	/* load reference image */
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	/* always check */
	if(img == 0) {
		printf("Cannot load file %s!\n", argv[1]);
		return 1;
	}

	/* load template image */
	//tpl = cvLoadImage(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	tpl = cvLoadImage("picture1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	tpl1 = cvLoadImage("picture2.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	/* always check */
	if(tpl == 0) {
		printf("Cannot load file %s!\n", argv[2]);
		return 1;
	}
	
	
	img2 = cvCloneImage(img);
	cvSmooth(img, img, CV_GAUSSIAN, 3, 0, 0, 0);
	//binaryThreshold(img);
	cvThreshold( img, img, 150, 255, CV_THRESH_BINARY_INV );
	//morphologicFilter(img, 3);
	img1 = cvCloneImage(img);
	
	//cvFindContours(img1, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
	//Search countours in preprocesed image
	cvFindContours( img1, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0) );
	//Optimize contours, reduce points
	contourLow = cvApproxPoly(contour, sizeof(CvContour), storage,CV_POLY_APPROX_DP,1,1);
	
	for( ; contourLow != 0; contourLow = contourLow->h_next ) {
		printf("contourLow find\n");
		boundingBox = cvBoundingRect(contourLow, 0);
		imgChar = cvCloneImage(img2);
		imgChar1 = cvCloneImage(img2);
		cvSetImageROI(imgChar, boundingBox);
		cvSetImageROI(imgChar1, boundingBox);
		cvRectangle(img, cvPoint(boundingBox.x, boundingBox.y), cvPoint(boundingBox.x + boundingBox.width, boundingBox.y + boundingBox.height), CV_RGB(255, 255, 255), 1, 0, 0);
		
		tmp_resize = cvCreateImage(cvSize(boundingBox.width, boundingBox.height), tpl->depth, tpl->nChannels);
		tmp_resize1 = cvCreateImage(cvSize(boundingBox.width, boundingBox.height), tpl1->depth, tpl1->nChannels);
		cvResize(tpl, tmp_resize, CV_INTER_LINEAR);
		cvResize(tpl1, tmp_resize1, CV_INTER_LINEAR);
		
		
		resT = cvCreateImage(cvSize(boundingBox.width - tmp_resize->width + 1, boundingBox.height - tmp_resize->height + 1), IPL_DEPTH_32F, 1);
		cvZero(resT);
		cvMatchTemplate(imgChar, tmp_resize, resT,  CV_TM_CCORR);
		cvMinMaxLoc(resT, &minval, &maxval, &minloc, &maxloc, 0);
		
		valueRes = maxval;
		valueRes1 = 6;
		printf("result1: %f\n", maxval);
		
		
		
		resT1 = cvCreateImage(cvSize(boundingBox.width - tmp_resize1->width + 1, boundingBox.height - tmp_resize1->height + 1), IPL_DEPTH_32F, 1);
		cvZero(resT1);
		cvMatchTemplate(imgChar1, tmp_resize1, resT1,  CV_TM_CCORR);
		cvMinMaxLoc(resT1, &minval1, &maxval1, &minloc1, &maxloc1, 0);
		
		
		//cvShowImage("template", tmp_resize);
		
		if(maxval1 > valueRes) {
			valueRes = maxval1;
			valueRes1 = 2;
		}
		
		printf("result2: %f\n", maxval1);
		
		printf("final result: %i\n", valueRes1);
		
		break;
	}
	
	
	//cvSaveImage("test.jpg", img, 0);
	
	CvSize size = cvSize(
	img->width  - tpl->width  + 1,
	img->height - tpl->height + 1
	);

	// create new image for template matching computation 
	res = cvCreateImage(size, IPL_DEPTH_32F, 1);
	
	/*
	// choose template matching method to be used 
	cvMatchTemplate(img, tpl, res, CV_TM_SQDIFF);
	//cvMatchTemplate(img, tpl, res, CV_TM_SQDIFF_NORMED);
	//cvMatchTemplate(img, tpl, res, CV_TM_CCORR); //Do not use
	//cvMatchTemplate(img, tpl, res, CV_TM_CCORR_NORMED); //Do not use
	//cvMatchTemplate(img, tpl, res, CV_TM_CCOEFF); //Do not use
	//cvMatchTemplate(img, tpl, res, CV_TM_CCOEFF_NORMED);

	cvMinMaxLoc(res, &minval, &maxval, &minloc, &maxloc, 0);

	// draw red rectangle 
	cvRectangle(img, cvPoint(minloc.x, minloc.y), cvPoint(minloc.x + tpl->width, minloc.y + tpl->height), CV_RGB(255, 0, 0), 1, 0, 0);  */

	/* display images */
	//cvNamedWindow("reference", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("template", CV_WINDOW_AUTOSIZE);
	//cvShowImage("reference", img);
	//cvShowImage("imgChar", imgChar);
	//cvShowImage("template", tpl);
	/* wait until user press a key to exit */
	//cvWaitKey(0);

	/* free memory */
	//cvDestroyWindow("reference");
	//cvDestroyWindow("template");
	cvReleaseImage(&img);
	cvReleaseImage(&tpl);
	cvReleaseImage(&res);

	return 0;
}
