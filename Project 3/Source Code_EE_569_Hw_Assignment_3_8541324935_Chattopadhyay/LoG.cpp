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
const int N = 5;
unsigned char Imagedata[size1][size2][BytesPerPixel];
const int x = N / 2;
const int new_rows = size1 + (2 * x);
const int new_col = size2 + (2 * x);
unsigned char Imagedatanew[new_rows][new_col][BytesPerPixel];
unsigned char ImagedataGray[new_rows][new_col];
unsigned char NewImagedata[size1][size2];
unsigned char ternary[size1][size2];
unsigned char zerocross[size1][size2];
int location[size1*size2][2];
int hist[1][256]={0};
int cumhist[1][256]={0};

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
	int kneepoint1 = 0 , kneepoint2 = 0;

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

    // Application of LoG Filter
    double mag;
    double image_grad[size1][size2];

    for(i=(N-1)/2; i<size1+(N-1)/2; i++)
    {
		for(j=(N-1)/2; j<size2+(N-1)/2; j++)
		{
		    mag = (float)ImagedataGray[i-2][j] + (float)ImagedataGray[i-1][j-1] + 2*(float)ImagedataGray[i-1][j] + (float)ImagedataGray[i-1][j+1] + (float)ImagedataGray[i][j-2] + 2*(float)ImagedataGray[i][j-1] -16*(float)ImagedataGray[i][j] + 2*(float)ImagedataGray[i][j+1] + (float)ImagedataGray[i][j+2] + (float)ImagedataGray[i+1][j-1] + 2*(float)ImagedataGray[i+1][j] + (float)ImagedataGray[i+1][j+1] + (float)ImagedataGray[i+2][j];
            image_grad[i-(N-1)/2][j-(N-1)/2] = mag;
		}
	}

	// Normalize the gradient
    double min_val = image_grad[0][0];
    double max_val = image_grad[0][0];

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
		}
	}

	// Getting the histogram
	for(i=0; i<size1; i++)
    {
        for(j=0; j<size2; j++)
        {
            hist[0][(int)NewImagedata[i][j]]= hist[0][(int)NewImagedata[i][j]]+1;
        }
    }

    //Getting the kneepoints from the cumulative histogram
    for(i=0; i<1; i++)
    {
        cumhist[i][0]=hist[i][0];
        for(j=1; j<256; j++)
        {
            cumhist[i][j]=hist[i][j]+cumhist[i][j-1];
        }
    }

    for(j=0;j<256;j++)
    {
        for(i=0;i<1;i++)
        {
            cout<< cumhist[i][j] << ", ";
        }
        cout<<endl;
    }

    for(i=0; i<1; i++)
    {
        for(j=0; j<256; j++)
        {
            if(cumhist[i][j] > (int)7720.05)
            {
                kneepoint1 = j;
                break;
            }
        }
    }

    for(i=0; i<1; i++)
    {
        for(j=0; j<256; j++)
        {

            if(cumhist[i][j] > (int)146680.95)
            {
                kneepoint2 = j;
                break;
            }
        }
    }

    //For ternary map
    for(i=0; i<size1; i++)
    {
		for (j=0; j<size2; j++)
		{
		    if((int)NewImagedata[i][j]<=kneepoint1)
            {
                ternary[i][j] = (unsigned char)64;
            }
            else if((int)NewImagedata[i][j]>kneepoint1 && (int)NewImagedata[i][j]<=kneepoint2)
            {
                ternary[i][j] = (unsigned char)128;
            }
            else
            {
                ternary[i][j] = (unsigned char)192;
            }
		}
    }

    //zero crossing edge map
    int img[size1][size2];
    for(i=0; i<size1; i++)
    {
		for (j=0; j<size2; j++)
		{
		    if((int)ternary[i][j] == 64)
            {
                img[i][j] = -1;
            }
            else if((int)ternary[i][j] == 128)
            {
                img[i][j] = 0;
            }
            else
            {
                img[i][j] = 1;
            }
		}
    }

    for(i=0; i<size1; i++)
    {
		for (j=0; j<size2; j++)
		{
		    zerocross[i][j] = 0;
		}
    }

    for(i=1; i<size1-1; i++)
    {
        for (j=1; j<size2-1; j++)
        {
            if(img[i][j] == 0)
            {
                if(img[i-1][j-1]*img[i+1][j+1]<1)
                {
                    zerocross[i][j] =(unsigned char)255;
                }
                else if(img[i][j-1]*img[i][j+1]<1)
                {
                    zerocross[i][j] =(unsigned char)255;
                }
                else if(img[i+1][j-1]*img[i-1][j+1]<1)
                {
                    zerocross[i][j] =(unsigned char)255;
                }
                else if(img[i+1][j]*img[i-1][j]<1)
                {
                    zerocross[i][j] =(unsigned char)255;
                }
            }
        }
    }

    if (!(file = fopen(argv[2], "wb")))
	{
	cout << "Cannot open file: " << argv[2] << endl;
	exit(1);
	}
	fwrite(zerocross, sizeof(unsigned char), size1*size2*1 , file);
	fclose(file);

	return 0;
}
