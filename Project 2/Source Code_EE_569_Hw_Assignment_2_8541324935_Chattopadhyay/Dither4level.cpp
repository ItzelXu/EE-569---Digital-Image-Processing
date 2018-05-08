// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <math.h>using namespace std;

int* IndexMatrix(int index)
{
    int* InMat = new int[index*index];

    if(index == 2)
    {
        InMat[0] = 1;
        InMat[1] = 2;
        InMat[2] = 3;
        InMat[3] = 0;
    }
    else if(index!=2)
    {
        for(int i=0; i<index/2; i++)
        {
            for(int j=0; j<index/2; j++)
            {
                InMat[i*index+j]=4*IndexMatrix(index/2)[(i%(index/2))*(index/2)+j%(index/2)]+1;
            }
            for (int j=index/2; j<index; j++)
            {
                InMat[i*index+j]=4*IndexMatrix(index/2)[(i%(index/2))*(index/2)+j%(index/2)]+2;
            }
        }
        for (int i=index/2; i<index; i++)
        {
            for (int j=0; j<index/2; j++)
            {
                InMat[i*index+j]=4*IndexMatrix(index/2)[(i%(index/2))*(index/2)+j%(index/2)]+3;
            }
            for (int j=index/2; j<index; j++)
            {
                InMat[i*index+j]=4*IndexMatrix(index/2)[(i%(index/2))*(index/2)+j%(index/2)];
            }
        }
    }

    return InMat;
}

float* ThresholdMatrix(int index)
{
    int* indexmat = IndexMatrix(index);
    float* ThreshMat = new float[index*index];

    for (int i=0; i<index; i++)
    {
        for (int j=0; j<index; j++)
        {
            ThreshMat[i*index+j]=(float(indexmat[i*index+j])+0.5)/(index*index);
        }
    }
    return ThreshMat;
}

int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 512;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4)
	{		BytesPerPixel = 1; // default is grey image	}	else
	{		BytesPerPixel = atoi(argv[3]);    }	// Allocate image data array	unsigned char Imagedata[Size][Size][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	int length,breadth,channel;
	unsigned char NewImagedata[Size][Size][BytesPerPixel];
	int MaxInt=0;
	int INDEX;

	cout<<"Enter the size for Index Matrix: ";
	cin>>INDEX;

	float* threshold = ThresholdMatrix(INDEX);

	float thresh[3];
	thresh[0] = float(85)/2/255;
	thresh[1] = float(170+85)/2/255;
	thresh[2] = float(255+170)/2/255;

	for(length = 0; length<Size; length++)
    {
        for(breadth = 0; breadth<Size; breadth++)
        {
            NewImagedata[length][breadth][0] = Imagedata[length][breadth][0];
        }
    }

    for(length = 0; length<Size; length++)
    {
        for(breadth = 0; breadth<Size; breadth++)
        {
            if(NewImagedata[length][breadth][0]>MaxInt)
            {
                MaxInt = NewImagedata[length][breadth][0];
            }
        }
    }

    for(length = 0; length<Size; length++)
    {
        for(breadth = 0; breadth<Size; breadth++)
        {
            if(float(NewImagedata[length][breadth][0])/MaxInt>threshold[(length%INDEX)*INDEX+(breadth%INDEX)])
            {
                if(float(NewImagedata[length][breadth][0])/MaxInt>thresh[2])
                {
                    NewImagedata[length][breadth][0] = 255;
                }
                if(thresh[1]<float(NewImagedata[length][breadth][0])/MaxInt<=thresh[2])
                {
                    NewImagedata[length][breadth][0] = 170;
                }
            }
            else
            {
                if(float(NewImagedata[length][breadth][0])/MaxInt<thresh[0])
                {
                    NewImagedata[length][breadth][0] = 0;
                }
                if(thresh[0]<=float(NewImagedata[length][breadth][0])/MaxInt<=thresh[1])
                {
                    NewImagedata[length][breadth][0] = 85;
                }
            }
        }
    }

     // Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(NewImagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);	fclose(file);	return 0;
}
