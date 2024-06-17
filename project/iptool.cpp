#include "../iptools/core.h"
#include <string.h>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt;
	FILE *fp;
	int x, y, sx, sy, numROI;
	char str[MAXLEN];
	char infile[MAXLEN];
	char outfile[MAXLEN];
	char *pch;
	
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	while(fgets(str,MAXLEN,fp) != NULL) {
		pch = strtok(str, " ");
		strcpy(infile, pch);

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		cv::Mat I = cv::imread(infile);
		cv::Mat I2;

		if( I.empty()) {
			cout << "Could not open or find the image: " << infile << endl;
			return -1;
		}

		I2 = I.clone();

		pch = strtok(NULL, " ");
		numROI = atoi(pch);

		for(int num = 0; num < numROI; num++)
		{
			pch = strtok(NULL, " ");
			x = atoi(pch);
			pch = strtok(NULL, " ");
			y = atoi(pch);
			pch = strtok(NULL, " ");
			sx = atoi(pch);
			pch = strtok(NULL, " ");
			sy = atoi(pch);

			pch = strtok(NULL, " ");
			if (strncasecmp(pch,"gray",4)==0) {
				utility::gray(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"blur_avg",8)==0) {
				pch = strtok(NULL, " ");
				utility::avgblur(I, I2, atoi(pch), x, y, sx, sy);
			}
			else if (strncasecmp(pch,"binarize",8)==0) {
				utility::binarize(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"sobel3",6)==0) {
				utility::sobel3(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"sobel5",6)==0) {
				utility::sobel5(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"coloredge",9)==0) {
				pch = strtok(NULL, " "); 
				utility::coloredge(I, I2, atoi(pch), x, y, sx, sy);
			}
			else if (strncasecmp(pch,"binaryedge",10)==0) { 
				pch = strtok(NULL, " "); 
				int thres = atoi(pch);
				pch = strtok(NULL, " "); 
				int angle = atoi(pch);
				utility::binaryedge(I, I2, thres, angle, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"cannycv",7)==0) {
				utility::cannycv(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"histoeq",7)==0) {
				utility::histoeq(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"cannyhisto",10)==0) {
				utility::cannyhisto(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"otsucv",6)==0) {
				utility::otsucv(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"otsuhisto",9)==0) {
				utility::otsuhisto(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"QRcode",6)==0) {
				utility::QRcode(I, I2, x, y, sx, sy);
			}
			else if (strncasecmp(pch,"QRcodqul",8)==0) {
				utility::QRcodqul(I, I2, x, y, sx, sy);
			}
			else {
				printf("No function: %s\n", pch);
				continue;
			}
		}

		cv::imwrite(outfile, I2);
	}
	fclose(fp);
	return 0;
}
