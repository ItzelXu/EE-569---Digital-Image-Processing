// EE569 Homework Assignment #3
// Date:     March 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <fstream>
#include <algorithm>

using namespace std;

const int BytesPerPixel = 3;
const int size1 = 481, size2 = 321;
const int N = 3;
unsigned char Imagedata[size1][size2][BytesPerPixel];
const int x = N / 2;
const int new_rows = size1 + (2 * x);
const int new_col = size2 + (2 * x);
unsigned char Imagedatanew[new_rows][new_col][BytesPerPixel];
unsigned char ImagedataGray[new_rows][new_col];
unsigned char NewImagedata[size1][size2];
int location[size1*size2][2];

int main(int argc, char *argv[])
{
    // Define file pointer and variables
	FILE *file;

    // Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), size1*size2*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	//Padding

	int i,j,ch;
	int length, breadth, luminosity, intensity;
	float threshold  = 0.10;
	int count, boundary;

	for (ch = 0; ch<BytesPerPixel; ch++)
	{
		for (i = x; i <= size1; i++)
		{
			for (j = x; j <= size2; j++)
			{
				Imagedatanew[i][j][ch] = Imagedata[i - x][j - x][ch];
			}
		}
	}

	//Regenerating the top rows
	for (ch = 0; ch<BytesPerPixel; ch++)
	{
		for (i = 0; i< x; i++)
        {
            for (j = x; j<size2 + x; j++)
            {
                Imagedatanew[i][j][ch] = Imagedatanew[1][j][ch];
            }
        }
	}

	//Regenerating the bottom rows
	for (ch = 0; ch<BytesPerPixel; ch++)
	{
		for (i = size1 + x; i<new_rows; i++)
        {
            for (j = x; j<size2 + x; j++)
            {
                Imagedatanew[i][j][ch] = Imagedatanew[size1][j][ch];
            }
        }
	}

	//Regenerating the left columns
	for (ch = 0; ch<BytesPerPixel; ch++)
	{
		for (i = 0; i<new_rows; i++)
        {
            for (j = 0; j<x; j++)
            {
                Imagedatanew[i][j][ch] = Imagedatanew[i][x][ch];
            }
        }
	}


	//Regenerating the Right column
	for (ch = 0; ch<BytesPerPixel; ch++)
	{
		for (i = 0; i<new_rows; i++)
        {
            for (j = size2 + x; j<new_col; j++)
            {
               Imagedatanew[i][j][ch] = Imagedatanew[i][j - x][ch];
            }
        }
	}

	//Convert to grayscale

	for (i = 0; i<new_rows; i++)
    {
		for (j = 0; j<new_col; j++)
		{
			ImagedataGray[i][j] = 0.21*Imagedatanew[i][j][0] + 0.72*Imagedatanew[i][j][1] + 0.07*Imagedatanew[i][j][2];
		}
    }

    // Application of Sobel Filter
    float gx, gy;
    double mag;
    double image_grad[size1][size2];

    for(i=(N-1)/2; i<size1+(N-1)/2; i++)
    {
		for(j=(N-1)/2; j<size2+(N-1)/2; j++)
		{
		    gx = ((float)ImagedataGray[i-1][j+1] + 2*(float)ImagedataGray[i][j+1] + (float)ImagedataGray[i+1][j+1] - (float)ImagedataGray[i-1][j-1] - 2*(float)ImagedataGray[i][j-1] - (float)ImagedataGray[i+1][j-1])/4;
			gy = ((float)ImagedataGray[i-1][j-1] + 2*(float)ImagedataGray[i-1][j] + (float)ImagedataGray[i-1][j+1] - (float)ImagedataGray[i+1][j-1] - 2*(float)ImagedataGray[i+1][j] - (float)ImagedataGray[i+1][j+1])/4;
            mag = sqrt(gx*gx + gy*gy);
			image_grad[i-(N-1)/2][j-(N-1)/2] = mag;
			//image_grad[i-(N-1)/2][j-(N-1)/2] = gy;
		}
	}

	// Normalize the gradient
    double min_val = image_grad[0][0];
    double max_val = image_grad[0][0];
    int image[size1][size2];

    for(i=0; i<size1; i++)
    {
		for(j=0; j<size2; j++)
        {
			if (image_grad[i][j]>max_val)
			{
				max_val = image_grad[i][j];
			}
			if (image_grad[i][j]<min_val)
			{
				min_val = image_grad[i][j];
			}
		}
	}

	for(i=0; i<size1; i++)
    {
		for (j=0; j<size2; j++)
		{
			NewImagedata[i][j] = (unsigned char)(255*(image_grad[i][j]-min_val)/(max_val-min_val));
			image[i][j] = (int)(255*(image_grad[i][j]-min_val)/(max_val-min_val));
		}
	}

	count = 0;
	for(intensity = 0; intensity<256; intensity++)
    {
        for(length = 0; length<size1; length++)
        {
            for(breadth = 0; breadth<size2; breadth++)
            {
                if(image[length][breadth] == intensity)
                {
                    location[count][0] = length;
                    location[count][1] = breadth;
                    count = count + 1;
                }
            }
        }
    }

    boundary = (int)((1-threshold)*size2*size1);

    for(i=0; i<boundary; i++)
	{
	    // Set 255 to the pixels below threshold
		NewImagedata[location[i][0]][location[i][1]] = (unsigned char)255;
	}
	for(i=boundary; i<size2*size1; i++)
	{
	    // set 0 to the pixels above threshold
		NewImagedata[location[i][0]][location[i][1]] = (unsigned char)0;
	}



    if (!(file = fopen(argv[2], "wb")))
	{
	cout << "Cannot open file: " << argv[2] << endl;
	exit(1);
	}
	fwrite(NewImagedata, sizeof(unsigned char), size1*size2*1 , file);
	fclose(file);

	return 0;
}

