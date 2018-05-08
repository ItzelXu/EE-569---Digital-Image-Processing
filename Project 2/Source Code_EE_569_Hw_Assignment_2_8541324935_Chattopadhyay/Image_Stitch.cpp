// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    // Define file pointer and variables	FILE *file;
    int Width = atoi(argv[5]);
	int Height = atoi(argv[6]);
	int BytesPerPixel = atoi(argv[7]);
	int HeightNew = 1500;
	int WidthNew = 2000;

	unsigned char* ImageDataleft = new unsigned char [ Height*Width*BytesPerPixel ];
	unsigned char* ImageDatamiddle = new unsigned char [ Height*Width*BytesPerPixel ];
	unsigned char* ImageDataright = new unsigned char [ Height*Width*BytesPerPixel ];
	unsigned char* NewImagedata = new unsigned char [ HeightNew*WidthNew*BytesPerPixel ];

	// Read image (filename specified by first three arguments) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(ImageDataleft, sizeof(unsigned char), Height*Width*BytesPerPixel, file);	fclose(file);

	if (!(file=fopen(argv[2],"rb"))) {		cout << "Cannot open file: " << argv[2] <<endl;		exit(1);	}	fread(ImageDatamiddle, sizeof(unsigned char), Height*Width*BytesPerPixel, file);	fclose(file);

	if (!(file=fopen(argv[3],"rb"))) {		cout << "Cannot open file: " << argv[3] <<endl;		exit(1);	}	fread(ImageDataright, sizeof(unsigned char), Height*Width*BytesPerPixel, file);	fclose(file);

	unsigned char *** ImageData3Dleft = NULL;
    ImageData3Dleft = new unsigned char**[Height]();
	for(int i =0; i<Height; i++)
    {
        ImageData3Dleft[i] = new unsigned char*[Width]();
        for(int j=0; j<Width; j++)
        {
            ImageData3Dleft[i][j] = new unsigned char[BytesPerPixel]();
            for(int k=0;k<BytesPerPixel; k++)
            {
                ImageData3Dleft[i][j][k] = 0;
            }
        }
    }

    unsigned char *** ImageData3Dmiddle = NULL;
    ImageData3Dmiddle = new unsigned char**[Height]();
	for(int i =0; i<Height; i++)
    {
        ImageData3Dmiddle[i] = new unsigned char*[Width]();
        for(int j=0; j<Width; j++)
        {
            ImageData3Dmiddle[i][j] = new unsigned char[BytesPerPixel]();
            for(int k=0;k<BytesPerPixel; k++)
            {
                ImageData3Dmiddle[i][j][k] = 0;
            }
        }
    }

    unsigned char *** ImageData3Dright = NULL;
    ImageData3Dright = new unsigned char**[Height]();
	for(int i =0; i<Height; i++)
    {
        ImageData3Dright[i] = new unsigned char*[Width]();
        for(int j=0; j<Width; j++)
        {
            ImageData3Dright[i][j] = new unsigned char[BytesPerPixel]();
            for(int k=0;k<BytesPerPixel; k++)
            {
                ImageData3Dright[i][j][k] = 0;
            }
        }
    }

    unsigned char *** ImageDataOutput3D = NULL;
    ImageDataOutput3D = new unsigned char**[HeightNew]();
	for(int i =0; i<HeightNew; i++)
    {
        ImageDataOutput3D[i] = new unsigned char*[WidthNew]();
        for(int j=0; j<WidthNew; j++)
        {
            ImageDataOutput3D[i][j] = new unsigned char[BytesPerPixel]();
            for(int k=0;k<BytesPerPixel; k++)
            {
                ImageDataOutput3D[i][j][k] = 0;
            }
        }
    }

    int a = 0;
	for(int i=0; i<Height; i++)
    {
        for(int j=0; j<Width; j++)
        {
           ImageData3Dleft[i][j][0] = ImageDataleft[a];
           ImageData3Dleft[i][j][1] = ImageDataleft[a+1];
           ImageData3Dleft[i][j][2] = ImageDataleft[a+2];
           a = a+3;
        }
    }

    a = 0;
	for(int i=0; i<Height; i++)
    {
        for(int j=0; j<Width; j++)
        {
           ImageData3Dmiddle[i][j][0] = ImageDatamiddle[a];
           ImageData3Dmiddle[i][j][1] = ImageDatamiddle[a+1];
           ImageData3Dmiddle[i][j][2] = ImageDatamiddle[a+2];
           a = a+3;
        }
    }

    a = 0;
	for(int i=0; i<Height; i++)
    {
        for(int j=0; j<Width; j++)
        {
           ImageData3Dright[i][j][0] = ImageDataright[a];
           ImageData3Dright[i][j][1] = ImageDataright[a+1];
           ImageData3Dright[i][j][2] = ImageDataright[a+2];
           a = a+3;
        }
    }

	long double H1[1][3] = {0.498647171663, -0.015184049987, -159.127087621741};
    long double H2[1][3] = {-0.155394318544, 0.709035313228, -76.025282005641};
	long double H3[1][3] = {-0.000521779396, -0.000016413401, 1.172270103882};

	int NewHeight = 0 ;
    int NewWidth = 0 ;
    float DeltaHeight = 0 ;
    float DeltaWidth = 0 ;

    for (int i = 0 ; i < HeightNew  ; i++)
    {
        for (int j = 0 ; j < WidthNew  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                double x = 0 , y = 0;
            	x = (H1[0][0]*i + H1[0][1]*j +  H1[0][2]*1) / (H3[0][0]*i +  H3[0][1]*j +  H3[0][2] * 1) ;
            	y = (H2[0][0]*i + H2[0][1]*j +  H2[0][2]*1) / (H3[0][0]*i +  H3[0][1]*j +  H3[0][2] * 1) ;
            	if(x > 0 && x < 479 && y > 0 && y < 639)
                {
                    ImageDataOutput3D[j][i][k] = ImageData3Dleft[int(y)][int(x)][k];
                }
            }
        }
    }

    for (int i = 0 ; i < Height  ; i++)
    {
        for (int j = 0 ; j < Width  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                ImageDataOutput3D[i+300][j+750][k] = ImageData3Dmiddle[i][j][k];
            }
        }
    }

    long double H4[1][3] = {1.135907857984, 0.007268867267, -1090.102787733530};
	long double H5[1][3] = {0.172167247573, 1.057935306677, -503.475512302448};
	long double H6[1][3] = {0.000619895801, -0.000034072858, 0.417276274628};

	NewHeight = 0 ;
    NewWidth = 0 ;
    DeltaHeight = 0 ;
    DeltaWidth = 0 ;

    for (int i = 0 ; i < HeightNew  ; i++)
    {
        for (int j = 0 ; j < WidthNew  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                double x = 0 , y = 0;
            	x = (H4[0][0]*i + H4[0][1]*j +  H4[0][2]*1) / (H6[0][0]*i +  H6[0][1]*j +  H6[0][2] * 1) ;
            	y = (H5[0][0]*i + H5[0][1]*j +  H5[0][2]*1) / (H6[0][0]*i +  H6[0][1]*j +  H6[0][2] * 1) ;
            	if(x > 0 && x < 479 && y > 0 && y < 639)
                {
                    ImageDataOutput3D[j][i][k] = ImageData3Dright[int(y)][int(x)][k];
                }
            }
        }
    }

    a = 0;
	for (int i = 0; i < HeightNew; i++)
	{
		for (int j = 0; j < WidthNew; j++)
		{
			NewImagedata[a] = ImageDataOutput3D[i][j][0];
			NewImagedata[a+1] = ImageDataOutput3D[i][j][1];
			NewImagedata[a+2] = ImageDataOutput3D[i][j][2];
			a = a + 3;
		}
	}

    // Write image data (filename specified by fourth argument) from image data matrix
	if (!(file=fopen(argv[4],"wb"))) {    cout << "Cannot open file: " << argv[4] << endl;    exit(1);	}	fwrite(NewImagedata, sizeof(unsigned char), HeightNew*WidthNew*BytesPerPixel, file);	fclose(file);

	return 0 ;
}
