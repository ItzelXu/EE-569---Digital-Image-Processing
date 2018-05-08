// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <math.h>using namespace std;int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 512;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw noisy_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4)
	{		BytesPerPixel = 1; // default is grey image	}	else
	{		BytesPerPixel = atoi(argv[3]);    }	// Allocate image data array	unsigned char Imagedata[Size][Size][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);

	// Allocate image data array	unsigned char ImagedataNoise[Size][Size][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[2],"rb"))) {		cout << "Cannot open file: " << argv[2] <<endl;		exit(1);	}	fread(ImagedataNoise, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	for (int ch = 0; ch <= 2; ch++)
		{
			int sum = 0;
            float mse;
            float psnr_calculation, PSNR;

			for (int i = 0; i < Size; i++)
			{
				for (int j = 0; j < Size; j++)
				{
					sum = sum + pow((int)ImagedataNoise[i][j][ch] - (int)(Imagedata[i][j][ch]), 2);
				}
			}


			mse = (float)sum / (float)(Size*Size);
			psnr_calculation = (float(pow(255, 2)) / mse);
			PSNR = 10 * log10(psnr_calculation);
			if (ch == 0)
				cout << "Channel Red PSNR: " << PSNR << endl;
			if (ch == 1)
				cout << "Channel Green PSNR " << PSNR << endl;
			if (ch == 2)
				cout << "Channel Blue PSNR " << PSNR << endl;

		}

		return 0;
}
