#pragma once
#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>
#include <array> //array 
#include <algorithm> //finding the smallest element in the SSD vector
#include <vector>
#include <math.h>//for squaring
#include <string>//for aesthetics
#include <Windows.h>//also for aesthetics
#include <cstdlib>//used for abs (absolute difference)

using namespace std;

// Input data are provided in .txt format and can be converted to .pgm files for visualization
// Download (free) ImageJ for plotting images in .pgm format
// http://rsb.info.nih.gov/ij/download.html

// Reads .txt file representing an image of R rows and C Columns stored in filename 
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
double* readTXT(char *fileName, int sizeR, int sizeC);

// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns 
// and stores .pgm in filename
// Use Q = 255 for greyscale images and Q=1 for binary images.
void WritePGM(char *filename, vector<double> data, int sizeR, int sizeC, int Q);

class BaseImage 
{
protected:
	//constant integers representing the number of rows and columns in the Wally grey image.
	#define SCOL 36;
	#define SROW 49;
	
public:
	//member functions variable declarations
		vector<vector<double> >sArrCopy;
		int Y = SROW;
		int X = SCOL;
	
		//This function converts the 1d array of wally to a 2d vector to compare
		void convImageS(double* input_data);
private:
	int startingPos = 0;
};

class LargeImage
{
protected:
	//constant integers representing the number of rows and columns in the large cluttered scene image
	#define LROW 768;
	#define LCOL 1024;
public:
	//member functions declarations
	
	vector<vector<double> >lArrCopy;
	int M = LROW;
	int N = LCOL;
	//This function converts the 1d array of the cluttered scene to a 2d vector for comparison
	void convImageL(double* input_data);
private:
	int startingPos = 0;
};
//this class is where the matching of the two images takes place
//the class inherits the variables from the two previous classes.
class MatchImage : public BaseImage, public LargeImage
{
public:
	//SSD is a vector holding each SSD score each time the while loop runs. A vector was chosen as this would around ~700,000 elements 
	//and so allocating memory or using the heap would not be a good idea.
	//The other two vectors (xCoor and yCoor) store the coordinates of the chunk
	//Everytime the while loop runs, the value of SSD and the chunks position in space are pushed back, this therefore means they have the same
	//index.
	vector <int> sumSSD;
	vector <double> xCoor;
	vector <double> yCoor;
	//member functions declarations
	void chunk();
	void findSmallest();
	//private variable declarations
private:
	double temp = 0;
	int xCoords = 0;
	int yCoords = 0;
	int xIncPos = 0;
	int xInc = 0;	
	int yInc = 0;
	int xStartPos = 0;
	int yIncPos = 0;
	int xIncOutput = 0;
	int yIncOutput = 0;
	int yStartPos = 0;
	int counter = 0;
	int sum2 = 0;
	bool finish = false;
	int k = 0;
	double chunkVal = 0;
	double smallVal = 0;
	double preSqr = 0;
	double squared = 0;
	double sum = 0;
	int l = 0;	
	double smallestValIndex = 0;
	int smallestVal = 0;
	double xPosVec = 0;
	double yPosVec = 0;
	int arrCounter = 0;
	vector <double>output;
	
};