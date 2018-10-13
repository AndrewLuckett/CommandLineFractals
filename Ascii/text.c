#include <stdio.h>
#include <math.h>

typedef struct complexnumber {
	double real;
	double imaginary;
} complex;

typedef unsigned int uint;

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

uint fractalAlgo(complex z, complex c, uint cutoffDepth) {
	uint steps = 0;
	for (uint i = 0; i < cutoffDepth; i++) {
		steps++;
		double r = (z.real * z.real) - (z.imaginary * z.imaginary) + c.real;
		double i = (2 * z.real*z.imaginary) + c.imaginary;

		if (r*r + i * i > 4) {
			return steps;
		}

		z.real = r;
		z.imaginary = i;
	}
	return 0; //Is in set
}


void printline(char *lineDat, int size) {
	char lookup[8][2] = { { 15,35 },{ 12,34 },{ 10,91 },{ 8,39 },{ 5,93 },{ 3,46 },{ 2,44 },{ 0,32 } }; //{inValue,outValue}
	for (int i = 0; i < size; i++) {
		char found = 0;
		for (int j = 0; j < sizeof(lookup); j++) {
			if (lineDat[i] == lookup[j][0]) {
				printf("%c", lookup[j][1]);
				found = 1;
			}
		}
		if (found == 0) {
			printf("%c", lineDat[i]+64);
		}
	}
	printf("\n");
}

int main(int argc, char** argv) {
	/*
		d(x,y) : output columns and rows
		c(x,y) : coordinate of centre of drawn fractal
		z(x) : zoom value for drawn fractal
		j(x,y) : julia values (optional, added to instead draw a julia set)
	*/

	int outDimensions[2] = { 60,30 }; //x,y
	double centre[2] = { 0,0 }; //x,y
	double zoom = 1;
	double julia[2];

	for (int i = 0; i < argc; i++) { //set arg values
		printf("%s \n", argv[i]);
	}

	int mathDimension = min(outDimensions[0], outDimensions[1]);

	double pixelwidth = 2 / (mathDimension*zoom); //4x supersample

	for (int y = -outDimensions[1]; y < outDimensions[1]; y+=2) {
		char *linedat = malloc(outDimensions[0]);

		for (int x = -outDimensions[0]; x < outDimensions[0]; x+=2) { //loop for each true 'pixel'
			char out = 0;

			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) { //loop for super sample
					complex inZ = {
						pixelwidth*(x + j) + centre[0],
						pixelwidth*(y + i) + centre[1]
					};
					complex inC = { 0,0 };
					if (fractalAlgo(inC,inZ,1024) == 0) { //fixed cutoff
						out = out + (char) pow(2, 2 * i + j);
					}					
				}
			}
			linedat[(x + outDimensions[0])/2] = out;
		}
		printline(linedat,outDimensions[0]);
	}
}








