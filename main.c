//#define POSTREQUEST

#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <cv.h>
#include <string.h>
#include "solveMath.h"




int main(int argc, char** argv)
{
	IplImage *img, *imgFilter;
	CvSeq *contour;
	CvMemStorage *storage = cvCreateMemStorage(0);
	template *tpl;
	characterFinal *finalCharact;
	int nbrContour, i;
	char *string = NULL, *result = NULL, *stringEncoded = NULL;
	
	
	
	tpl = loadTemplate();
	

	printf("Content-type: text/plain\n\n");

#ifdef POSTREQUEST
	img = loadImageFromPostRequest();
#else
	img = loadImage();
#endif
	//cvSaveImage("tmp/test.jpg", img, 0);
	
	
	imgFilter = cvCloneImage(img);
	resizeImg(imgFilter);
	
	
	//apply filter
	cvSmooth(imgFilter, imgFilter, CV_GAUSSIAN, 3, 3, 0, 0);
	
	//cvThreshold(imgFilter, imgFilter, 150, 255, CV_THRESH_BINARY_INV);
	cvAdaptiveThreshold(imgFilter, imgFilter, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 101, 1);

	
	morphologicFilter(imgFilter, 2);

	removeNoise(imgFilter);
	
#ifndef POSTREQUEST
	displayImage(imgFilter);
#endif
	
	nbrContour = findContours(imgFilter, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	finalCharact = malloc(sizeof(characterFinal) * nbrContour);
	
	//printf("size: %d\n", nbrContour);
	
	i = 0;
	for( ; contour != 0; contour = contour->h_next ) {
		IplImage *imgRoi;
		character charact;
		CvRect boundingBox = cvBoundingRect(contour, 0);
		//printf("Contour Find\n");
		
		//draw rectangle (for test)
		//cvRectangle(imgFilter, cvPoint(boundingBox.x, boundingBox.y), cvPoint(boundingBox.x + boundingBox.width, boundingBox.y + boundingBox.height), CV_RGB(255, 255, 255), 1, 0, 0);
		
		
		imgRoi = cvCloneImage(imgFilter);
		cvSetImageROI(imgRoi, boundingBox);
		charact = getCharacter(imgRoi, tpl);
		cvReleaseImage(&imgRoi);
			
		
		finalCharact[i].charact = charact;
		finalCharact[i].boundingBox = boundingBox;
		
		
		//displayImage(imgFilter);
		
		i++;
		
		//printf("find: %d\n", i);
	}
	
	sortArrayCharacter(finalCharact, nbrContour);
	string = getString(finalCharact, nbrContour);
	stringEncoded = urlEncoder(string);
	//printCharacter(string);
	//printf("%s\n", stringEncoded);
	result = calculateWithWolframAlpha(stringEncoded);
	free(string);
	printf("%s", result);
	free(result);
	free(stringEncoded);
	
	

	releaseTemplate(tpl);
	cvReleaseImage(&imgFilter);
	cvReleaseImage(&img);
	return 0;
}



