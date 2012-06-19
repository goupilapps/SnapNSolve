#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <cv.h>
#include <string.h>
#include <ccgi.h>

//#define POSTREQUEST

#define NBRCHARACTERS 1001


typedef enum character            
{
	characterNumber0,
	characterNumber1,
	characterNumber2,
	characterNumber3,
	characterNumber4,
	characterNumber5,
	characterNumber6,
	characterNumber7,
	characterNumber8,
	characterNumber9,
	characterSignPlus
	
} character;


typedef struct template
{
	IplImage *imgTpl;
	character characterTpl;
	
} template;


typedef struct characterFinal
{
	character charact;
	CvRect boundingBox;
	
} characterFinal;




IplImage *loadImageFromPostRequest() {
	IplImage *img = NULL;
	
	CGI_varlist *varlist;
	CGI_value *value;
	
	varlist = CGI_get_all("/tmp/cgi-upload-XXXXXX");
	value = CGI_lookup_all(varlist, "uploadfield");
	
	if (value == 0 || value[1] == 0) {
		printf("No file was uploaded\r\n");
	}
	else {
		printf("Your file \"%s\" was uploaded to my file \"%s\"\r\n",
		    value[1], value[0]);

		// Do something with the file here 
		img = cvLoadImage(value[0], CV_LOAD_IMAGE_GRAYSCALE);

		unlink(value[0]);
	}
	CGI_free_varlist(varlist);
	
	
	return img;
	
}

IplImage *loadImage() {
	IplImage *img = cvLoadImage("picture.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	/* always check */
	if(img == 0) {
		printf("Cannot load source file !\n");
		exit(1);
	}
	
	return img;
}


template* loadTemplate() {
	template *tpl;
	int i = 0;
	char fileName[20];
	tpl = malloc(NBRCHARACTERS * sizeof(template));
	
	
	
	for (i = 0; i < 100; i++) {
		sprintf(fileName, "templates/0/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber0;
	}
	
	
	for (i = 100; i < 200; i++) {
		sprintf(fileName, "templates/1/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber1;
	}
	
	for (i = 200; i < 300; i++) {
		sprintf(fileName, "templates/2/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber2;
	}
	
	for (i = 300; i < 400; i++) {
		sprintf(fileName, "templates/3/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber3;
	}
	
	
	for (i = 400; i < 500; i++) {
		sprintf(fileName, "templates/4/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber4;
	}
	
	for (i = 500; i < 600; i++) {
		sprintf(fileName, "templates/5/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber5;
	}
	
	
	for (i = 600; i < 700; i++) {
		sprintf(fileName, "templates/6/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber6;
	}
	
	
	for (i = 700; i < 800; i++) {
		sprintf(fileName, "templates/7/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber7;
	}
	
	for (i = 800; i < 900; i++) {
		sprintf(fileName, "templates/8/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber8;
	}
	
	for (i = 900; i < 1000; i++) {
		sprintf(fileName, "templates/9/%i.jpg", i);
		tpl[i].imgTpl = cvLoadImage(fileName, CV_LOAD_IMAGE_GRAYSCALE);
		if(tpl[i].imgTpl == 0) {
			printf("error loading template %i.jpg\n", i);
			exit(1);
		}
		tpl[i].characterTpl = characterNumber9;
	}
	
	
	tpl[1000].imgTpl = cvLoadImage("templates/+/+.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[1000].imgTpl == 0) {
		printf("error loading template sign +.jpg\n");
		exit(1);
	}
	tpl[1000].characterTpl = characterSignPlus;
	
	
	
	
	/*
	tpl[1].imgTpl = cvLoadImage("templates/1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[1].imgTpl == 0) {
		printf("error loading template 1.jpg\n");
		exit(1);
	}
	tpl[1].characterTpl = characterNumber1;
	
	
	tpl[2].imgTpl = cvLoadImage("templates/2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[2].imgTpl == 0) {
		printf("error loading template 2.jpg\n");
		exit(1);
	}
	tpl[2].characterTpl = characterNumber2;
	
	
	tpl[3].imgTpl = cvLoadImage("templates/3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[3].imgTpl == 0) {
		printf("error loading template 3.jpg\n");
		exit(1);
	}
	tpl[3].characterTpl = characterNumber3;
	
	
	tpl[4].imgTpl = cvLoadImage("templates/4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[4].imgTpl == 0) {
		printf("error loading template 4.jpg\n");
		exit(1);
	}
	tpl[4].characterTpl = characterNumber4;
	
	
	tpl[5].imgTpl = cvLoadImage("templates/5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[5].imgTpl == 0) {
		printf("error loading template 5.jpg\n");
		exit(1);
	}
	tpl[5].characterTpl = characterNumber5;
	
	
	tpl[6].imgTpl = cvLoadImage("templates/6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[6].imgTpl == 0) {
		printf("error loading template 6.jpg\n");
		exit(1);
	}
	tpl[6].characterTpl = characterNumber6;
	
	
	tpl[7].imgTpl = cvLoadImage("templates/7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[7].imgTpl == 0) {
		printf("error loading template 7.jpg\n");
		exit(1);
	}
	tpl[7].characterTpl = characterNumber7;
	
	
	tpl[8].imgTpl = cvLoadImage("templates/8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[8].imgTpl == 0) {
		printf("error loading template 8.jpg\n");
		exit(1);
	}
	tpl[8].characterTpl = characterNumber8;
	
	
	tpl[9].imgTpl = cvLoadImage("templates/9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if(tpl[9].imgTpl == 0) {
		printf("error loading template 9.jpg\n");
		exit(1);
	}
	tpl[9].characterTpl = characterNumber9;*/
	
	
	return tpl;
}


void morphologicFilter(IplImage *img, int type){
	IplConvKernel* kernel = NULL;
	
	switch (type) {
	case 0:
	  cvDilate(img, img, kernel, 1);
	  break;
	case 1:
	  cvErode(img, img, kernel, 1);
	  break;
	case 2:
	  cvMorphologyEx(img,img,0,kernel, CV_MOP_OPEN, 1);
	  break;
	case 3:
	  cvMorphologyEx(img,img,0,kernel, CV_MOP_CLOSE, 1);
	  break;
	default:
	  cvErode(img, img, kernel, 1);
	  break;
	}
	
}



void releaseTemplate(template *tpl){
	int i;
	
	for(i = 0; i < NBRCHARACTERS; i++) {
		cvReleaseImage(&(tpl[i].imgTpl));
	} 
	
	free(tpl);
}


void displayImage(IplImage *img) {
	cvNamedWindow("reference", CV_WINDOW_AUTOSIZE);
	cvShowImage("reference", img);
	cvWaitKey(0);
	cvDestroyWindow("reference");
}

int findContours(IplImage* imageFilter, CvMemStorage* storage, CvSeq** first_contour, int header_size, int mode, int method, CvPoint offset) {
	
	int nbrContour;
	IplImage *imgContours;
	//CvSeq *contourLow;
	
	imgContours = cvCloneImage(imageFilter);
	nbrContour = cvFindContours(imgContours, storage, first_contour, header_size, mode, method, offset);
	cvReleaseImage(&imgContours);

	
	//memory leak, TO DO remove memory leak
	*first_contour = cvApproxPoly(*first_contour, sizeof(CvContour), storage,CV_POLY_APPROX_DP,1,1);
	
	return nbrContour;
	
}


character getCharacter(IplImage *imgCroped, template *tpl) {
	
	int i;
	CvPoint   minloc, maxloc;
	double    minval, maxval = 0.0, maxMatchValue = 0.0;
	IplImage *tplResise, *resT;
	CvRect boundingBox = cvGetImageROI(imgCroped);
	character charact;
	
	//displayImage(tpl[1].imgTpl);
	for(i = 0; i < NBRCHARACTERS; i++) {
		tplResise = cvCreateImage(cvSize(boundingBox.width, boundingBox.height), (tpl[i].imgTpl)->depth, (tpl[i].imgTpl)->nChannels);
		cvResize(tpl[i].imgTpl, tplResise, CV_INTER_LINEAR);
		
		resT = cvCreateImage(cvSize(boundingBox.width - tplResise->width + 1, boundingBox.height - tplResise->height + 1), IPL_DEPTH_32F, 1);
		cvZero(resT);
		//displayImage(tplResise);
		//cvMatchTemplate(imgCroped, tplResise, resT,  CV_TM_CCORR);
		cvMatchTemplate(imgCroped, tplResise, resT,  CV_TM_CCOEFF);
		
		cvReleaseImage(&tplResise);
		
		cvMinMaxLoc(resT, &minval, &maxval, &minloc, &maxloc, 0);
		cvReleaseImage(&resT);
		//printf("for: %i maxVal: %f\n", i, maxval);
		
		if(maxval > maxMatchValue) {
			maxMatchValue = maxval;
			charact = tpl[i].characterTpl;
		}
	}
	
	return charact;
	
}


void sortArrayCharacter(characterFinal *finalCharact, int size) {
	int i,j;
	characterFinal tmpCharact;
	
	for (i = 0; i < size; i++) {
		for(j = 0; j < size - 1; j++) {
			if(finalCharact[j].boundingBox.x > finalCharact[j + 1].boundingBox.x) {
				tmpCharact = finalCharact[j];
				finalCharact[j] = finalCharact[j + 1];
				finalCharact[j + 1] = tmpCharact;
			}
		}
	}
	
}

void printCharacter(characterFinal *finalCharact, int size) {
	int i;

	
	for(i = 0; i < size; i++) {
		switch(finalCharact[i].charact) 
		{
			case characterNumber0:
				printf("0");
				break;
			case characterNumber1:
				printf("1");
				break;
			case characterNumber2:
				printf("2");
				break;
			case characterNumber3:
				printf("3");
				break;
			case characterNumber4:
				printf("4");
				break;
			case characterNumber5:
				printf("5");
				break;
			case characterNumber6:
				printf("6");
				break;
			case characterNumber7:
				printf("7");
				break;
			case characterNumber8:
				printf("8");
				break;
			case characterNumber9:
				printf("9");
				break;
			case characterSignPlus:
				printf("+");
				break;
			
		}
		//printf("at: %d\n\n", finalCharact[i].boundingBox.x);
	}
	
}

char *replace(const char *src, const char *from, const char *to)
{
   /*
    * Find out the lengths of the source string, text to replace, and
    * the replacement text.
    */
   size_t size    = strlen(src) + 1;
   size_t fromlen = strlen(from);
   size_t tolen   = strlen(to);
   /*
    * Allocate the first chunk with enough for the original string.
    */
   char *value = malloc(size);
   /*
    * We need to return 'value', so let's make a copy to mess around with.
    */
   char *dst = value;
   /*
    * Before we begin, let's see if malloc was successful.
    */
   if ( value != NULL )
   {
      /*
       * Loop until no matches are found.
       */
      for ( ;; )
      {
         /*
          * Try to find the search text.
          */
         const char *match = strstr(src, from);
         if ( match != NULL )
         {
            /*
             * Found search text at location 'match'. :)
             * Find out how many characters to copy up to the 'match'.
             */
            size_t count = match - src;
            /*
             * We are going to realloc, and for that we will need a
             * temporary pointer for safe usage.
             */
            char *temp;
            /*
             * Calculate the total size the string will be after the
             * replacement is performed.
             */
            size += tolen - fromlen;
            /*
             * Attempt to realloc memory for the new size.
             */
            temp = realloc(value, size);
            if ( temp == NULL )
            {
               /*
                * Attempt to realloc failed. Free the previously malloc'd
                * memory and return with our tail between our legs. :(
                */
               free(value);
               return NULL;
            }
            /*
             * The call to realloc was successful. :) But we'll want to
             * return 'value' eventually, so let's point it to the memory
             * that we are now working with. And let's not forget to point
             * to the right location in the destination as well.
             */
            dst = temp + (dst - value);
            value = temp;
            /*
             * Copy from the source to the point where we matched. Then
             * move the source pointer ahead by the amount we copied. And
             * move the destination pointer ahead by the same amount.
             */
            memmove(dst, src, count);
            src += count;
            dst += count;
            /*
             * Now copy in the replacement text 'to' at the position of
             * the match. Adjust the source pointer by the text we replaced.
             * Adjust the destination pointer by the amount of replacement
             * text.
             */
            memmove(dst, to, tolen);
            src += fromlen;
            dst += tolen;
         }
         else /* No match found. */
         {
            /*
             * Copy any remaining part of the string. This includes the null
             * termination character.
             */
            strcpy(dst, src);
            break;
         }
      }
   }
   return value;
}


int main(int argc, char** argv)
{
	IplImage *img, *imgFilter;
	CvSeq *contour;
	CvMemStorage *storage = cvCreateMemStorage(0);
	template *tpl;
	characterFinal *finalCharact;
	int nbrContour, i;
	
	
	
	tpl = loadTemplate();
	

	printf("Content-type: text/plain\n\n");

#ifdef POSTREQUEST
	img = loadImageFromPostRequest();
#else
	img = loadImage();
#endif
	//cvSaveImage("tmp/test.jpg", img, 0);
	
	imgFilter = cvCloneImage(img);
	
	//apply filter
	cvSmooth(imgFilter, imgFilter, CV_GAUSSIAN, 3, 0, 0, 0);
	//cvThreshold(imgFilter, imgFilter, 150, 255, CV_THRESH_BINARY_INV);
	cvAdaptiveThreshold(imgFilter, imgFilter, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 101, 1);
	morphologicFilter(imgFilter, 2);
	
#ifndef POSTREQUEST
	//displayImage(imgFilter);
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
	printCharacter(finalCharact, nbrContour);
	printf("\n");
	//cvSaveImage("test.jpg", imgFilter, 0);
	
	//displayImage(tpl[0].imgTpl);
	
	releaseTemplate(tpl);
	cvReleaseImage(&imgFilter);
	cvReleaseImage(&img);
	return 0;
}



