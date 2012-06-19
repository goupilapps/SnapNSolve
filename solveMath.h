#include <cv.h>


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



struct string {
	char *ptr;
	size_t len;
};



IplImage *loadImageFromPostRequest();
IplImage *loadImage();
template* loadTemplate();
void morphologicFilter(IplImage *img, int type);
void releaseTemplate(template *tpl);
void displayImage(IplImage *img);
int findContours(IplImage* imageFilter, CvMemStorage* storage, CvSeq** first_contour, int header_size, int mode, int method, CvPoint offset);
character getCharacter(IplImage *imgCroped, template *tpl);
void sortArrayCharacter(characterFinal *finalCharact, int size);
void printCharacter(char *string);
char *getString(characterFinal *finalCharact, int size);
char *replace(const char *src, const char *from, const char *to);
char* urlEncoder(char *string);
char* calculateWithWolframAlpha(char *string);
void init_string(struct string *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);
void resizeImg(IplImage *img);
void removeNoise(IplImage *img);







