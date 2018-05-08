// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <math.h>using namespace std;
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 512;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4)
	{		BytesPerPixel = 1; // default is grey image	}	else
	{		BytesPerPixel = atoi(argv[3]);    }	// Allocate image data array	unsigned char Imagedata[Size][Size][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	int length,breadth,channel;
	unsigned char NewImagedata[Size][Size][BytesPerPixel];
    float l,b,xCircle,yCircle,x,y;

    for(channel = 0; channel<3 ; channel++)
    {
        for(length = 0; length<Size; length++)
        {
            for(breadth = 0; breadth<Size; breadth++)
            {
                    l = (((float)length/511)*(-2))+1;
                    b = (((float)breadth/511)*(2))-1;
                    xCircle = (l * sqrt(1 - 0.5*(b*b)));
                    yCircle = (b * sqrt(1 - 0.5*(l*l)));
                    x = ((xCircle-1)/(-2))*511;
                    y = ((yCircle+1)/(2))*511;
                    NewImagedata[length][breadth][channel] = (int)Imagedata[(int)x][(int)y][channel];
            }
        }
    }

    // Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(NewImagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	return 0;
}


