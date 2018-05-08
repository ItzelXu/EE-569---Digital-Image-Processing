// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <math.h>using namespace std;

const int Size = 512;
double temp[Size][Size];
double error;

int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 512;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4)
	{		BytesPerPixel = 1; // default is grey image	}	else
	{		BytesPerPixel = atoi(argv[3]);    }	// Allocate image data array	unsigned char Imagedata[Size][Size][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	int length,breadth,channel;
	unsigned char NewImagedata[Size][Size][BytesPerPixel];

    for(length = 0; length<Size; length++)
    {
        for(breadth = 0; breadth<Size; breadth++)
        {
            temp[length][breadth] = 1 - ((double)Imagedata[length][breadth][0]/255);
        }
    }

    for(length = 0; length<Size; length++)
    {
        for(breadth = 0; breadth<Size; breadth++)
        {
            if (temp[length][breadth]>=0.5)
            {
                error = temp[length][breadth]-1;
                NewImagedata[length][breadth][0] = (unsigned char) 0;
            }
            else
            {
                error = temp[length][breadth];
                NewImagedata[length][breadth][0] = (unsigned char) 255;
            }
            // distribute the error

            if (breadth+1 < Size)
            {
                temp[length][breadth+1]=temp[length][breadth+1]+error*8/32;
            }
            if (length+1 < Size && breadth+1 < Size)
            {
                temp[length+1][breadth+1]=temp[length+1][breadth+1]+error*4/32;
            }
            if (breadth+2 < Size)
            {
                temp[length][breadth+2]=temp[length][breadth+2]+error*4/32;
            }
            if (length+1 < Size && breadth+2 < Size)
            {
                temp[length+1][breadth+2]=temp[length+1][breadth+2]+error*2/32;
            }
            if (length+1 < Size)
            {
                temp[length+1][breadth]=temp[length+1][breadth]+error*8/32;
            }
            if (length+1 < Size && breadth-1 >= 0)
            {
                temp[length+1][breadth-1]=temp[length+1][breadth-1]+error*4/32;
            }
            if (length+1 < Size && breadth-2 >= 0)
            {
                temp[length+1][breadth-2]=temp[length+1][breadth-2]+error*2/32;
            }
        }
    }



// Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(NewImagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	return 0;
}
