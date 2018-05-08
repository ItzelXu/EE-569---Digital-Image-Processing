// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>using namespace std;int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 512;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}	// Allocate image data array	unsigned char Imagedata[Size][Size][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int NewSize = 650;
    int length, breadth, channel;
    int xcoord, ycoord, temp;
    unsigned char NewImagedata[NewSize][NewSize][BytesPerPixel];
    float p,q;

    for (length = 0; length<NewSize; length++)
    {
     for(breadth = 0; breadth<NewSize; breadth++)
     {
      for(channel = 0; channel<3; channel++)
      {

       xcoord = length*((float)(Size)/(NewSize));
       ycoord = breadth*((float)(Size)/(NewSize));
       p = (float)length*(Size)/(NewSize) - xcoord;
       q = (float)breadth*(Size)/(NewSize) - ycoord;

       // For last pixel, directly copy pixel intensity for each channel
       if(xcoord==511&&ycoord==511)
				{
					NewImagedata[649][649][channel] = Imagedata[511][511][channel];
					continue;
				}

       // For edge, apply Interpolation formula partially as two terms become 0
       if(xcoord==511&&ycoord!=511)
				{
                    temp = (1-p)*(1-q)*(int)Imagedata[xcoord][ycoord][channel]+p*(1-q)*(int)Imagedata[xcoord][ycoord+1][channel];
                    NewImagedata[length][breadth][channel] = (char)temp;
                    continue;
				}

       // For edge, apply Interpolation formula partially as two terms become 0
       if(ycoord==511&&xcoord!=511)
				{
                    temp = (1-p)*(1-q)*(int)Imagedata[xcoord][ycoord][channel]+p*(1-q)*(int)Imagedata[xcoord+1][ycoord][channel];
                    NewImagedata[length][breadth][channel] = (char)temp;
					continue;
				}
       // Apply Formula for rest of the pixels
       temp = (1-p)*(1-q)*(int)Imagedata[xcoord][ycoord][channel]+q*(1-p)*(int)Imagedata[xcoord][ycoord+1][channel]+p*(1-q)*(int)Imagedata[xcoord+1][ycoord][channel]+p*q*(int)Imagedata[xcoord+1][ycoord+1][channel];
       NewImagedata[length][breadth][channel] = (char)temp;

      }
     }
    }
	// Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(NewImagedata, sizeof(unsigned char), NewSize*NewSize*BytesPerPixel, file);	fclose(file);	return 0;}