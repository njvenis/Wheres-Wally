#include "Header.h"
int main()
{
	// input_data is a pointer to a 1D array of M*N doubles stored in heap. Memory allocation is performed 
	// inside readTXT. readTXT will read an image (in .pgm format) of size MxN and will  store the result in input_data.
	// once you're done with data DO NOT forget to delete the memory as in the end of this main() function


	//*******************************************************************

	//definitions of the large image
	// M is equal to the Y axis
	// N is equal to the X axis
	int M = 768; 
	int N = 1024;
	double* largeInputData = 0;
	cout << endl;
	cout << "*****************************Phase 1: Read in.**************************\n" << endl;
	//A little bit of code to make the program have a nicer UI, does absolutely nothing but add ellipsis to mirror a loading bar.
	string waiting = "";
	for (int i = 0; i < 8; i++)
	{
		cout << waiting;
		Sleep(300);
		waiting += '.';
	}
	//All code to make the UI nicer.
	cout << endl;
	cout << "\n*****************************Phase Complete!**************************" << endl;
	cout << endl;
	cout << "***************************Phase 2: Find Wally.**************************\n" << endl;
	cout << "\n" << "\t\t\t\tWORKING!" << endl;
	cout << "\t\tGrab a brew, this might take a few!(~10 secs)" << endl;
	
	// .pgm image is stored in inputFileName
	char* inputFileName = "Cluttered_scene.txt"; 
	largeInputData = readTXT(inputFileName, M, N);

	//creating a new instance of the class where the matching actually happened.
	//As the match class inherits both the small and large image conversion classes only one call needs to be made (m).
	MatchImage m;
	//convImageL is the cluttered scene.
	//the code provided is used to convert the file from .txt file to 1d array(largeInputData).
	m.convImageL(largeInputData); 


	//*******************************************************************

	//This source code is used to convert the "wally_grey.txt" to its greyscale values, this is then input into a 1d array.
	//text file converted to a 1D double array
	int Y = 36;
	int X = 49;
	double* wally_input = 0;
	char* inputFileNameWally = "Wally_grey.txt";
	wally_input = readTXT(inputFileNameWally, X, Y);

	//the base image class(small imagage of wally) is called. 
	//convImage is a function to convert the 1d array to a 2d array.
	
	//As described earlier m is used to call all classes.
	//as the actual converting classes return nothing (void) nothing is being passed.
	m.convImageS(wally_input);
	m.chunk();
	m.findSmallest();
	//*******************************************************************
	return 0;
	
}

void BaseImage::convImageS(double* input_data)
{
	//the vector defined in the header file is resized to accomodate the 1d array, this is needed to convert the 1d array to a 2d vector
	sArrCopy.resize(Y);
	for (int i = 0; i < Y; ++i)
	{
		sArrCopy[i].resize(X);
	}
	// Value from the 1d is input into the 2d vector using a for loop to increase a 2d index.
	// startingPos is used as a counter, as the input array is 1d and so would need a 1d index increment.
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++)
		{
			sArrCopy[i][j] = input_data[startingPos];
			startingPos++;
		}
	}
}
void LargeImage::convImageL(double* input_data)
{
	//the vector defined in the header file is resized to accomodate the 1d array, this is needed to convert the 1d array to a 2d vector
	lArrCopy.resize(M);
	for (int i = 0; i < M; ++i)
	{
		lArrCopy[i].resize(N);
	}
	// Value from the 1d is input into the 2d vector using a for loop to increase a 2d index.
	// startingPos is used as a counter, as the input array is 1d and so would need a 1d index increment.
	for (int i = 0; i < M; i++)
	{	
		for (int j = 0; j < N; j++)
		{
			lArrCopy[i][j] = input_data[startingPos];
			startingPos++;	
		}
	}
}
void MatchImage::chunk()
{
	// Y = 49 Rows aka Y axis
	// X = 36 Columns aka X axis
	//the vector defined is resized to match the size of the 2d vector of the small wally image, this is so when a chunk of the large image is hard copied
	// it is exactly the size of the small image.
	vector<vector<double> >chunkVec;
	chunkVec.resize(Y);
	for (int i = 0; i < Y; ++i)
	{
		chunkVec[i].resize(X);
	}
	//the while loop for creating a chunk runs while the boolean is set to false, when the chunking process is finished this boolean is set to true and the loop ends.
	while (finish == false)
	{
		//this function is used to calculate the start position on the X and Y axis of the chunk.
		//X and Y are the dimensions of the wally image, this is then just added to the initial position to find the end position.
		xInc = X + xStartPos;
		yInc = Y + yStartPos;
		//This end position or "Inc" is used as the condition of the for loop
		//"startPos" is used as the initial value of where to start the loop, it contains the starting X and Y coords.
		for (int i = yStartPos; i < yInc; i++)
		{
			for (int j = xStartPos; j < xInc; j++)
			{
				chunkVec[l][k] = lArrCopy[i][j];
				k++;
			}
			//As the vector which stores the chunk's X and Y position isnt changing K and L have to be implemented to increase its 2d index everytime the loop runs.
			//K and L are both reset at the end of a loop, this ensures any data stored is overwritten and so memory is freed by not storing every chunk.
			k = 0;
			l++;
		}
		l = 0;
		xStartPos++;
		// everytime the while loop runs 1 is added to the xPosition, it is only when the chunk function reaches the end of the X axis the function increases in Y value.
		//counter++;
		//counter is included for debugging purposes


		//This section of code calculates the sum of squared differences for the chunk in this iteration of the while loop.
		//This for loop is just a standard for loop for looping through the 2d vector's index the size of the small wally image.
		for (int i = 0; i < Y; i++)
		{
			for (int j = 0; j < X; j++)
			{
				//as wally is cut out of his surroundings in the small image but has non-white pixels behind him in the large image you would not get an exact match
				//this if statements fixes that problem as if the current value of the small wally image (sArrCopy) is white (255) the loop should skip this iteration
				//using the continue statement.
				if (sArrCopy[i][j] == 255)
				{
					continue;
				}
				//if the value is not white the SSD should be calculated.
				else {
				preSqr = chunkVec[i][j] - sArrCopy[i][j];
				sum = preSqr * preSqr;
				sum2 = sum2 + sum;
				}
			}
		}
		
		//This if statement checks whether the chunk is at the last position of the X axis.
		//if it is the X starting position is reset and the starting position on the Y axis is increased by one.
		if (xStartPos == ((N - X) + 1))
		{
			xStartPos = 0;
			yStartPos = yStartPos + 1;
		}

		//the SSD value, starting X position, Y position are pushed back into their respective 1D vector, as each shares the same index value it is each to reference each.
		sumSSD.push_back(sum2);
		xCoor.push_back(xStartPos);
		yCoor.push_back(yStartPos);
		sum = 0;
		sum2 = 0;

		//this if statement checks to see if the chunk has reached the last value on the Y axis.
		//if yes the while loops ends.
		if (yStartPos == ((M - Y) + 1))
		{
			finish = true;
		}
		
	}
	//used for a nicer looking UI.
	cout << "\t\t      Chunk separation successful" << endl;
}
//this class is the class that finds the smallest value in the SSD vector, this is the position of wally.
void MatchImage::findSmallest()
	{
		
		//This for loop goes through every value of the SSD vector and checks whether the current value is smaller than the last. This works similiarly to a bubble sort algortihm .. ish.
		//The loop however doesnt return the smallest value but the index of the smallest value, as the X postion and Y position share the same index.
		int ind = 0;
		for (int i = 0; i < sumSSD.size(); ++i)
		{
			if (sumSSD[i] < sumSSD[ind])
				ind = i;
		}
		
		//This sets the varible "PosVec" to the starting X and Y positions of wally.
		xPosVec = xCoor[ind];
		yPosVec = yCoor[ind];

		//this section of code changes the pixel values at certain points to draw a black box around wally.
		//this function is used to calculate the start position on the X and Y axis of wally
		//X and Y are the dimensions of the wally image, this is then just added to the initial position to find the end position.
		xIncOutput = X + xPosVec;
		yIncOutput = Y + yPosVec;
		for (int i = yPosVec; i < yIncOutput; i++)
		{
			for (int j = xPosVec; j < xIncOutput; j++)
			{
				//if the index j (position on the x axis) is equal to the starting X coordinate of wally change the value to 0 (black)
				//OR if the value is equal to the start position +35 (the width of the wally input image) change it also to black.
				if (j == xPosVec || j == (xPosVec + 35))
				{
					lArrCopy[i][j] = 0;
				}
				//if the index i (position on the Y axis) is equal to the starting Y coordinate of wally change the value to 0 (black)
				//OR if the value is equal to the start position +48 (the length of the wally input image) change it also to black.
				if (i == yPosVec || i == (yPosVec + 48))
				{
					lArrCopy[i][j] = 0;
				}
			}

		}

		//convert the 2D vector containing the highlighted wally to a 1d array ready to be output.
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				output.push_back(lArrCopy[i][j]);
			}
		}
		cout << "\n\t\t        WALLY FOUND! Outputting!" << endl;
		/*writes data back to .pgm file stored in outputFileName*/
		char* outputFileName = "FoundWally.pgm";
		/* Use Q = 255 for greyscale images and 1 for binary images.*/
		int Q = 255; 
		WritePGM(outputFileName, output, M, N, Q);
	}

// Read .txt file with image of size RxC, and convert to an array of doubles
double* readTXT(char *fileName, int sizeR, int sizeC)
{
  double* data = new double[sizeR*sizeC];
  int i=0;
  ifstream myfile (fileName);
  if (myfile.is_open())
  {
	 
	while ( myfile.good())
    {
       if (i>sizeR*sizeC-1) break;
		 myfile >> *(data+i);
        //cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
	     i++;                                                             
	}
    myfile.close();
  }

  else cout << "Unable to open file"; 
  //cout << i;

  return data;
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, vector<double> data, int sizeR, int sizeC, int Q)
{

 int i, j;
 unsigned char *image;
 ofstream myfile;

 image = (unsigned char *) new unsigned char [sizeR*sizeC];

 // convert the integer values to unsigned char
 
 for(i=0; i<sizeR*sizeC; i++)
	 image[i]=(unsigned char)data[i];

 myfile.open(filename, ios::out|ios::binary|ios::trunc);

 if (!myfile) {
   cout << "Can't open file: " << filename << endl;
   exit(1);
 }

 myfile << "P5" << endl;
 myfile << sizeC << " " << sizeR << endl;
 myfile << Q << endl;

 myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

 if (myfile.fail()) {
   cout << "Can't write image " << filename << endl;
   exit(0);
 }

 myfile.close();
 cout << "\n             Written to file (FoundWally.pgm) successfully!\n" << endl;
 cout << "***************************** Have a nice day! *****************************" << endl;
 system("pause");
 delete [] image;

}



