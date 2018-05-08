// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <math.h>using namespace std;

const int Size = 700;
double temp[Size][Size][3];
double error;
unsigned char NewImagedata[Size][Size][3];

int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 700;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4)
	{		BytesPerPixel = 1; // default is grey image	}	else
	{		BytesPerPixel = atoi(argv[3]);    }	// Allocate image data array	unsigned char Imagedata[Size][Size][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	int length,breadth,channel;

	for(channel = 0; channel<3; channel++)
    {
        for(length = 0; length<Size; length++)
        {
            for(breadth = 0; breadth<Size; breadth++)
            {
                temp[length][breadth][channel] = 1 - ((double)Imagedata[length][breadth][channel]/255);
            }
        }
    }


    for(channel = 0; channel<3; channel++)
    {
        for(length = 0; length<Size; length++)
        {
            for(breadth = 0; breadth<Size; breadth++)
            {
                if (temp[length][breadth][channel]>=0.5)
                {
                    error = temp[length][breadth][channel]-1;
                    NewImagedata[length][breadth][channel] = (unsigned char) 0;
                }
                else
                {
                    error = temp[length][breadth][channel];
                    NewImagedata[length][breadth][channel] = (unsigned char) 255;
                }
                // distribute the error
                if (breadth+1 < Size)
                {
                    temp[length][breadth+1][channel]=temp[length][breadth+1][channel]+error*7/16;
                }
                if (breadth-1 >= 0 && length+1 < Size)
                {
                    temp[length+1][breadth-1][channel]=temp[length+1][breadth-1][channel]+error*3/16;
                }
                if (length+1 < Size)
                {
                    temp[length+1][breadth][channel]=temp[length+1][breadth][channel]+error*5/16;
                }
                if (length+1 < Size && breadth+1 < Size)
                {
                    temp[length+1][breadth+1][channel]=temp[length+1][breadth+1][channel]+error*1/16;
                }
            }
        }
    }
    // Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(NewImagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	return 0;
}
