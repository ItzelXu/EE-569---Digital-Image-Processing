// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>using namespace std;int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size1 = 400;
	int Size2 = 300;
	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		}// Allocate image data array	unsigned char Imagedata[Size1][Size2][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int length,breadth,channel;
	int hist[BytesPerPixel][256]={0};
	int hist1[BytesPerPixel][256]={0};
	float prob[BytesPerPixel][256]={0};
	float cumprob[BytesPerPixel][256]={0};
	int Newcumprob[BytesPerPixel][256]={0};
	unsigned char NewImagedata[Size1][Size2][BytesPerPixel];
	int i,j;
	int ipmin[3] = {0};
	int ipmax[3] = {255};
	int opmin[3] = {0};
	int opmax[3] = {255};
	float slope[3];

    // Make histogram for input image
	for(length = 0; length<Size1; length++)
    {
     for(breadth = 0; breadth<Size2; breadth++)
     {
      for(channel = 0; channel<3; channel++)
      {
	    hist[channel][(int)Imagedata[length][breadth][channel]]= hist[channel][(int)Imagedata[length][breadth][channel]]+1;
      }
     }
    }

    // Display Histogram values
    for(j=0;j<256;j++)
    {
        for(i=0;i<3;i++)
        {
            cout<< hist[i][j] << ", ";
        }
        cout<<j<<", ";
        cout<<endl;
    }

    //Find Minimum and Maximum value of input intensity for transfer function
    for(length = 0; length<Size1; length++)
    {
        for(breadth = 0; breadth<Size2; breadth++)
        {
            for(channel = 0; channel<3; channel++)
            {
               if((int)Imagedata[length][breadth][channel]<ipmin[channel])
               {
                   ipmin[channel] = (int)Imagedata[length][breadth][channel];
               }
               if((int)Imagedata[length][breadth][channel]>ipmax[channel])
               {
                   ipmax[channel] = (int)Imagedata[length][breadth][channel];
               }
            }
        }
    }

    // Find slope of transfer function
    for(i=0; i<3; i++)
    {
        slope[i] = (opmax[i] - opmin[i]) / (1.0 * (ipmax[i] - ipmin[i]));
    }

    // Print the transfer function
    for(i=0; i<3; i++)
    {
     cout << "The transfer function using Method-A for channel "<<i+1<<" is:" << endl;
     cout << "G = " << opmin[i] << " + " << slope[i] << " * (F - " << ipmin[i] << " )" << endl;
    }

    // Find Probability from histogram for each intensity value
    for(i=0;i<3;i++)
    {
     for(j=0;j<256;j++)
     {
       prob[i][j]= (float)hist[i][j]/(Size1*Size2);
     }
    }

    // Find Cumulative probability and make cdf
    for(i=0;i<3;i++)
    {
     cumprob[i][0]=prob[i][0];
     for(j=1;j<256;j++)
     {
       cumprob[i][j]=prob[i][j]+cumprob[i][j-1];
     }
    }

    // Transform Cumulative probability to intensity level
	for(i=0;i<3;i++)
    {
     for(j=0;j<256;j++)
     {
       Newcumprob[i][j]=cumprob[i][j]*255;
     }
    }

    for(j=0;j<256;j++)
    {
        for(i=0;i<3;i++)
        {
            cout<< Newcumprob[i][j] << ", ";
        }
        cout<<endl;
    }

    // Histogram Equalization using Cumulative Probability
	for(length = 0; length<Size1; length++)
    {
     for(breadth = 0; breadth<Size2; breadth++)
     {
      for(channel = 0; channel<3; channel++)
      {
	   NewImagedata[length][breadth][channel]=Newcumprob[channel][(int)Imagedata[length][breadth][channel]];

	  }
	 }
	}

	// Histogram of equalized image
	for(length = 0; length<Size1; length++)
    {
     for(breadth = 0; breadth<Size2; breadth++)
     {
      for(channel = 0; channel<3; channel++)
      {
	    hist1[channel][(int)NewImagedata[length][breadth][channel]]= hist1[channel][(int)NewImagedata[length][breadth][channel]]+1;
      }
     }
    }

    for(j=0;j<256;j++)
    {
        for(i=0;i<3;i++)
        {
            cout<< hist1[i][j] << ", ";
        }
        cout<<endl;
    }

	// Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(NewImagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	return 0;}
