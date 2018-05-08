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

unsigned char newimagedata[700][700][3];
int temp[700][700][3];

struct
{
    double red;
    double green;
    double blue;
}CMY[700][700];

struct
{
    double red;
    double green;
    double blue;
}Error[700][700];

int main(int argc, char *argv[])
{
    // Define file pointer and variables
    FILE *file;
    int bytesPerPixel = 3;
    int size = 700;

    // Allocate image data array
    unsigned char imagedata[size][size][bytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(imagedata, sizeof(unsigned char), size*size*bytesPerPixel, file);
    fclose(file);

    int height, width, index;
    double x,y,z;
    cout<<"Flag 1"<<endl;

    cout<<"Flag 2"<<endl;


     // define the 6 MBVQ in the CMYK space
    double mbvq1[4][3]={{0,0,0},{0,0,1},{1,0,0},{0,1,0}};
    double mbvq2[4][3]={{0,0,1},{1,0,0},{1,0,1},{0,1,0}};
    double mbvq3[4][3]={{0,0,1},{1,0,1},{0,1,1},{0,1,0}};
    double mbvq4[4][3]={{1,1,1},{1,0,1},{0,1,1},{1,1,0}};
    double mbvq5[4][3]={{0,1,1},{1,1,0},{1,0,1},{0,1,0}};
    double mbvq6[4][3]={{1,0,1},{1,0,0},{0,1,0},{1,1,0}};
    double dis1,dis2,dis3,dis4;

    // initialize the error
    for (height = 0; height<size; height++)
    {
        for (width=0; width<size; width++)
        {
            Error[height][width].red = 0;
            Error[height][width].green = 0;
            Error[height][width].blue = 0;
        }
    }

    // CMY space conversion
    for (height = 0; height<size; height++)
    {
        for (width = 0; width<size; width++)
        {
            CMY[height][width].red = 1-(double)imagedata[height][width][0]/255;
            CMY[height][width].green = 1-(double)imagedata[height][width][1]/255;
            CMY[height][width].blue = 1-(double)imagedata[height][width][2]/255;
            temp[height][width][0] = (int)imagedata[height][width][0];
            temp[height][width][1] = (int)imagedata[height][width][1];
            temp[height][width][2] = (int)imagedata[height][width][2];
        }
    }

    //Color Half Toning
    for (height = 0; height<size; height++)
    {
        if(height%2 == 0)
        {
            for (width = 0; width<size; width++)
            {
                x = CMY[height][width].red + Error[height][width].red;
                y = CMY[height][width].green + Error[height][width].green;
                z = CMY[height][width].blue + Error[height][width].blue;

                if(x+y<=1)
                {
                    if(y+z<=1)
                    {
                        if(x+y+z<=1)
                        {
                             //CMYW
                             if(x>=0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x>=0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }

                             // calculate the distance
                             dis1 = (x-mbvq1[0][0])*(x-mbvq1[0][0])+(y-mbvq1[0][1])*(y-mbvq1[0][1])+(z-mbvq1[0][2])*(z-mbvq1[0][2]);
                             dis2 = (x-mbvq1[1][0])*(x-mbvq1[1][0])+(y-mbvq1[1][1])*(y-mbvq1[1][1])+(z-mbvq1[1][2])*(z-mbvq1[1][2]);
                             dis3 = (x-mbvq1[2][0])*(x-mbvq1[2][0])+(y-mbvq1[2][1])*(y-mbvq1[2][1])+(z-mbvq1[2][2])*(z-mbvq1[2][2]);
                             dis4 = (x-mbvq1[3][0])*(x-mbvq1[3][0])+(y-mbvq1[3][1])*(y-mbvq1[3][1])+(z-mbvq1[3][2])*(z-mbvq1[3][2]);

                             // compare the distance and find the smallest one
                             if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                             {
                                 index = 0;
                             }
                             if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                             {
                                 index = 1;
                             }
                             if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                             {
                                 index = 2;
                             }
                             if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                             {
                                 index = 3;
                             }

                             // get the error
                             Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq1[index][0];
                             Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq1[index][1];
                             Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq1[index][2];

                             // Error Diffusion
                             if(width+1<size)
                             {
                                 Error[height][width+1].red=Error[height][width+1].red+Error[height][width].red*7/16;
                                 Error[height][width+1].green=Error[height][width+1].green+Error[height][width].green*7/16;
                                 Error[height][width+1].blue=Error[height][width+1].blue+Error[height][width].blue*7/16;
                             }
                             if(width-1>=0 && height+1<size)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*3/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*3/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*1/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*1/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }
                        }
                        else
                        {
                             //MYGC
                             if(x>=0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x>=0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }

                             // calculate the distance
                             dis1 = (x-mbvq2[0][0])*(x-mbvq2[0][0])+(y-mbvq2[0][1])*(y-mbvq2[0][1])+(z-mbvq2[0][2])*(z-mbvq2[0][2]);
                             dis2 = (x-mbvq2[1][0])*(x-mbvq2[1][0])+(y-mbvq2[1][1])*(y-mbvq2[1][1])+(z-mbvq2[1][2])*(z-mbvq2[1][2]);
                             dis3 = (x-mbvq2[2][0])*(x-mbvq2[2][0])+(y-mbvq2[2][1])*(y-mbvq2[2][1])+(z-mbvq2[2][2])*(z-mbvq2[2][2]);
                             dis4 = (x-mbvq2[3][0])*(x-mbvq2[3][0])+(y-mbvq2[3][1])*(y-mbvq2[3][1])+(z-mbvq2[3][2])*(z-mbvq2[3][2]);

                             // compare the distance and find the smallest one
                             if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                             {
                                 index = 0;
                             }
                             if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                             {
                                 index = 1;
                             }
                             if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                             {
                                 index = 2;
                             }
                             if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                             {
                                 index = 3;
                             }

                             // get the error
                             Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq2[index][0];
                             Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq2[index][1];
                             Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq2[index][2];

                             // Error Diffusion
                             if(width+1<size)
                             {
                                 Error[height][width+1].red=Error[height][width+1].red+Error[height][width].red*7/16;
                                 Error[height][width+1].green=Error[height][width+1].green+Error[height][width].green*7/16;
                                 Error[height][width+1].blue=Error[height][width+1].blue+Error[height][width].blue*7/16;
                             }
                             if(width-1>=0 && height+1<size)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*3/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*3/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*1/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*1/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }
                        }
                    }
                    else
                    {
                        //RGMY
                             if(x>=0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x>=0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }

                             // calculate the distance
                             dis1 = (x-mbvq3[0][0])*(x-mbvq3[0][0])+(y-mbvq3[0][1])*(y-mbvq3[0][1])+(z-mbvq3[0][2])*(z-mbvq3[0][2]);
                             dis2 = (x-mbvq3[1][0])*(x-mbvq3[1][0])+(y-mbvq3[1][1])*(y-mbvq3[1][1])+(z-mbvq3[1][2])*(z-mbvq3[1][2]);
                             dis3 = (x-mbvq3[2][0])*(x-mbvq3[2][0])+(y-mbvq3[2][1])*(y-mbvq3[2][1])+(z-mbvq3[2][2])*(z-mbvq3[2][2]);
                             dis4 = (x-mbvq3[3][0])*(x-mbvq3[3][0])+(y-mbvq3[3][1])*(y-mbvq3[3][1])+(z-mbvq3[3][2])*(z-mbvq3[3][2]);

                             // compare the distance and find the smallest one
                             if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                             {
                                 index = 0;
                             }
                             if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                             {
                                 index = 1;
                             }
                             if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                             {
                                 index = 2;
                             }
                             if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                             {
                                 index = 3;
                             }

                             // get the error
                             Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq3[index][0];
                             Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq3[index][1];
                             Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq3[index][2];

                             // Error Diffusion
                             if(width+1<size)
                             {
                                 Error[height][width+1].red=Error[height][width+1].red+Error[height][width].red*7/16;
                                 Error[height][width+1].green=Error[height][width+1].green+Error[height][width].green*7/16;
                                 Error[height][width+1].blue=Error[height][width+1].blue+Error[height][width].blue*7/16;
                             }
                             if(width-1>=0 && height+1<size)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*3/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*3/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*1/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*1/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }
                    }
                    }
                    else
                    {
                        if(y+z>1)
                        {
                             if(x+y+z>2)
                             {
                                // KRGB
                                if(x>=0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x>=0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }

                                // calculate the distance
                                dis1 = (x-mbvq4[0][0])*(x-mbvq4[0][0])+(y-mbvq4[0][1])*(y-mbvq4[0][1])+(z-mbvq4[0][2])*(z-mbvq4[0][2]);
                                dis2 = (x-mbvq4[1][0])*(x-mbvq4[1][0])+(y-mbvq4[1][1])*(y-mbvq4[1][1])+(z-mbvq4[1][2])*(z-mbvq4[1][2]);
                                dis3 = (x-mbvq4[2][0])*(x-mbvq4[2][0])+(y-mbvq4[2][1])*(y-mbvq4[2][1])+(z-mbvq4[2][2])*(z-mbvq4[2][2]);
                                dis4 = (x-mbvq4[3][0])*(x-mbvq4[3][0])+(y-mbvq4[3][1])*(y-mbvq4[3][1])+(z-mbvq4[3][2])*(z-mbvq4[3][2]);

                                // compare the distance and find the smallest one
                                if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                                {
                                   index = 0;
                                }
                                if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                                {
                                   index = 1;
                                }
                                if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                                {
                                   index = 2;
                                }
                                if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                                {
                                   index = 3;
                                }

                                // get the error
                                Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq4[index][0];
                                Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq4[index][1];
                                Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq4[index][2];

                                // Error Diffusion
                                if(width+1<size)
                                {
                                   Error[height][width+1].red=Error[height][width+1].red+Error[height][width].red*7/16;
                                   Error[height][width+1].green=Error[height][width+1].green+Error[height][width].green*7/16;
                                   Error[height][width+1].blue=Error[height][width+1].blue+Error[height][width].blue*7/16;
                                }
                                if(width-1>=0 && height+1<size)
                                {
                                   Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*3/16;
                                   Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*3/16;
                                   Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*3/16;
                                }
                                if(height+1<size && width+1<size)
                                {
                                   Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*1/16;
                                   Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*1/16;
                                   Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*1/16;
                                }
                                if(height+1<size)
                                {
                                   Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                   Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                   Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                                }
                             }
                             else
                             {
                                 //RGBM
                                if(x>=0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x>=0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }

                                // calculate the distance
                                dis1 = (x-mbvq5[0][0])*(x-mbvq5[0][0])+(y-mbvq5[0][1])*(y-mbvq5[0][1])+(z-mbvq5[0][2])*(z-mbvq5[0][2]);
                                dis2 = (x-mbvq5[1][0])*(x-mbvq5[1][0])+(y-mbvq5[1][1])*(y-mbvq5[1][1])+(z-mbvq5[1][2])*(z-mbvq5[1][2]);
                                dis3 = (x-mbvq5[2][0])*(x-mbvq5[2][0])+(y-mbvq5[2][1])*(y-mbvq5[2][1])+(z-mbvq5[2][2])*(z-mbvq5[2][2]);
                                dis4 = (x-mbvq5[3][0])*(x-mbvq5[3][0])+(y-mbvq5[3][1])*(y-mbvq5[3][1])+(z-mbvq5[3][2])*(z-mbvq5[3][2]);

                                // compare the distance and find the smallest one
                                if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                                {
                                   index = 0;
                                }
                                if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                                {
                                   index = 1;
                                }
                                if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                                {
                                   index = 2;
                                }
                                if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                                {
                                   index = 3;
                                }

                                // get the error
                                Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq5[index][0];
                                Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq5[index][1];
                                Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq5[index][2];

                                // Error Diffusion
                                if(width+1<size)
                                {
                                   Error[height][width+1].red=Error[height][width+1].red+Error[height][width].red*7/16;
                                   Error[height][width+1].green=Error[height][width+1].green+Error[height][width].green*7/16;
                                   Error[height][width+1].blue=Error[height][width+1].blue+Error[height][width].blue*7/16;
                                }
                                if(width-1>=0 && height+1<size)
                                {
                                   Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*3/16;
                                   Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*3/16;
                                   Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*3/16;
                                }
                                if(height+1<size && width+1<size)
                                {
                                   Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*1/16;
                                   Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*1/16;
                                   Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*1/16;
                                }
                                if(height+1<size)
                                {
                                   Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                   Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                   Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                                }
                             }
                        }
                        else
                        {
                            //CMGB
                                if(x>=0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x>=0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }

                                // calculate the distance
                                dis1 = (x-mbvq6[0][0])*(x-mbvq6[0][0])+(y-mbvq6[0][1])*(y-mbvq6[0][1])+(z-mbvq6[0][2])*(z-mbvq6[0][2]);
                                dis2 = (x-mbvq6[1][0])*(x-mbvq6[1][0])+(y-mbvq6[1][1])*(y-mbvq6[1][1])+(z-mbvq6[1][2])*(z-mbvq6[1][2]);
                                dis3 = (x-mbvq6[2][0])*(x-mbvq6[2][0])+(y-mbvq6[2][1])*(y-mbvq6[2][1])+(z-mbvq6[2][2])*(z-mbvq6[2][2]);
                                dis4 = (x-mbvq6[3][0])*(x-mbvq6[3][0])+(y-mbvq6[3][1])*(y-mbvq6[3][1])+(z-mbvq6[3][2])*(z-mbvq6[3][2]);

                                // compare the distance and find the smallest one
                                if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                                {
                                   index = 0;
                                }
                                if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                                {
                                   index = 1;
                                }
                                if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                                {
                                   index = 2;
                                }
                                if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                                {
                                   index = 3;
                                }

                                // get the error
                                Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq6[index][0];
                                Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq6[index][1];
                                Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq6[index][2];

                                // Error Diffusion
                                if(width+1<size)
                                {
                                   Error[height][width+1].red=Error[height][width+1].red+Error[height][width].red*7/16;
                                   Error[height][width+1].green=Error[height][width+1].green+Error[height][width].green*7/16;
                                   Error[height][width+1].blue=Error[height][width+1].blue+Error[height][width].blue*7/16;
                                }
                                if(width-1>=0 && height+1<size)
                                {
                                   Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*3/16;
                                   Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*3/16;
                                   Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*3/16;
                                }
                                if(height+1<size && width+1<size)
                                {
                                   Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*1/16;
                                   Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*1/16;
                                   Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*1/16;
                                }
                                if(height+1<size)
                                {
                                   Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                   Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                   Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                                }

                         }
                      }
                }
            }

        else
        {
            for (width = size-1; width>=0; width--)
            {
                x = CMY[height][width].red + Error[height][width].red;
                y = CMY[height][width].green + Error[height][width].green;
                z = CMY[height][width].blue + Error[height][width].blue;

                if(x+y<=1)
                {
                    if(y+z<=1)
                    {
                        if(x+y+z<=1)
                        {
                             //CMYW
                             if(x>=0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x>=0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }

                             // calculate the distance
                             dis1 = (x-mbvq1[0][0])*(x-mbvq1[0][0])+(y-mbvq1[0][1])*(y-mbvq1[0][1])+(z-mbvq1[0][2])*(z-mbvq1[0][2]);
                             dis2 = (x-mbvq1[1][0])*(x-mbvq1[1][0])+(y-mbvq1[1][1])*(y-mbvq1[1][1])+(z-mbvq1[1][2])*(z-mbvq1[1][2]);
                             dis3 = (x-mbvq1[2][0])*(x-mbvq1[2][0])+(y-mbvq1[2][1])*(y-mbvq1[2][1])+(z-mbvq1[2][2])*(z-mbvq1[2][2]);
                             dis4 = (x-mbvq1[3][0])*(x-mbvq1[3][0])+(y-mbvq1[3][1])*(y-mbvq1[3][1])+(z-mbvq1[3][2])*(z-mbvq1[3][2]);

                             // compare the distance and find the smallest one
                             if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                             {
                                 index = 0;
                             }
                             if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                             {
                                 index = 1;
                             }
                             if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                             {
                                 index = 2;
                             }
                             if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                             {
                                 index = 3;
                             }

                             // get the error
                             Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq1[index][0];
                             Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq1[index][1];
                             Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq1[index][2];

                             // Error Diffusion
                             if(width-1>=0)
                             {
                                 Error[height][width-1].red=Error[height][width-1].red+Error[height][width].red*7/16;
                                 Error[height][width-1].green=Error[height][width-1].green+Error[height][width].green*7/16;
                                 Error[height][width-1].blue=Error[height][width-1].blue+Error[height][width].blue*7/16;
                             }
                             if(width+1<size && height+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*3/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*3/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width-1>=0)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*1/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*1/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }
                        }
                        else
                        {
                             //MYGC
                             if(x>=0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x>=0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }

                             // calculate the distance
                             dis1 = (x-mbvq2[0][0])*(x-mbvq2[0][0])+(y-mbvq2[0][1])*(y-mbvq2[0][1])+(z-mbvq2[0][2])*(z-mbvq2[0][2]);
                             dis2 = (x-mbvq2[1][0])*(x-mbvq2[1][0])+(y-mbvq2[1][1])*(y-mbvq2[1][1])+(z-mbvq2[1][2])*(z-mbvq2[1][2]);
                             dis3 = (x-mbvq2[2][0])*(x-mbvq2[2][0])+(y-mbvq2[2][1])*(y-mbvq2[2][1])+(z-mbvq2[2][2])*(z-mbvq2[2][2]);
                             dis4 = (x-mbvq2[3][0])*(x-mbvq2[3][0])+(y-mbvq2[3][1])*(y-mbvq2[3][1])+(z-mbvq2[3][2])*(z-mbvq2[3][2]);

                             // compare the distance and find the smallest one
                             if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                             {
                                 index = 0;
                             }
                             if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                             {
                                 index = 1;
                             }
                             if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                             {
                                 index = 2;
                             }
                             if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                             {
                                 index = 3;
                             }

                             // get the error
                             Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq2[index][0];
                             Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq2[index][1];
                             Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq2[index][2];

                             // Error Diffusion
                             if(width-1>=0)
                             {
                                 Error[height][width-1].red=Error[height][width-1].red+Error[height][width].red*7/16;
                                 Error[height][width-1].green=Error[height][width-1].green+Error[height][width].green*7/16;
                                 Error[height][width-1].blue=Error[height][width-1].blue+Error[height][width].blue*7/16;
                             }
                             if(width+1<size && height+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*3/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*3/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width-1>=0)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*1/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*1/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }
                        }
                    }
                    else
                    {
                        //RGMY
                             if(x>=0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x>=0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x>=0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)0;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y>=0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y>=0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)0;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }
                             if(x<0.5&&y<0.5&&z>=0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)0;
                             }
                             if(x<0.5&&y<0.5&&z<0.5)
                             {
                                 newimagedata[height][width][0]=(unsigned char)255;
                                 newimagedata[height][width][1]=(unsigned char)255;
                                 newimagedata[height][width][2]=(unsigned char)255;
                             }

                             // calculate the distance
                             dis1 = (x-mbvq3[0][0])*(x-mbvq3[0][0])+(y-mbvq3[0][1])*(y-mbvq3[0][1])+(z-mbvq3[0][2])*(z-mbvq3[0][2]);
                             dis2 = (x-mbvq3[1][0])*(x-mbvq3[1][0])+(y-mbvq3[1][1])*(y-mbvq3[1][1])+(z-mbvq3[1][2])*(z-mbvq3[1][2]);
                             dis3 = (x-mbvq3[2][0])*(x-mbvq3[2][0])+(y-mbvq3[2][1])*(y-mbvq3[2][1])+(z-mbvq3[2][2])*(z-mbvq3[2][2]);
                             dis4 = (x-mbvq3[3][0])*(x-mbvq3[3][0])+(y-mbvq3[3][1])*(y-mbvq3[3][1])+(z-mbvq3[3][2])*(z-mbvq3[3][2]);

                             // compare the distance and find the smallest one
                             if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                             {
                                 index = 0;
                             }
                             if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                             {
                                 index = 1;
                             }
                             if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                             {
                                 index = 2;
                             }
                             if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                             {
                                 index = 3;
                             }

                             // get the error
                             Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq3[index][0];
                             Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq3[index][1];
                             Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq3[index][2];

                             // Error Diffusion
                             if(width-1>=0)
                             {
                                 Error[height][width-1].red=Error[height][width-1].red+Error[height][width].red*7/16;
                                 Error[height][width-1].green=Error[height][width-1].green+Error[height][width].green*7/16;
                                 Error[height][width-1].blue=Error[height][width-1].blue+Error[height][width].blue*7/16;
                             }
                             if(width+1<size && height+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*3/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*3/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width-1>=0)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*1/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*1/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }
                    }
                    }
                    else
                    {
                        if(y+z>1)
                        {
                             if(x+y+z>2)
                             {
                                // KRGB
                                if(x>=0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x>=0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }

                                // calculate the distance
                                dis1 = (x-mbvq4[0][0])*(x-mbvq4[0][0])+(y-mbvq4[0][1])*(y-mbvq4[0][1])+(z-mbvq4[0][2])*(z-mbvq4[0][2]);
                                dis2 = (x-mbvq4[1][0])*(x-mbvq4[1][0])+(y-mbvq4[1][1])*(y-mbvq4[1][1])+(z-mbvq4[1][2])*(z-mbvq4[1][2]);
                                dis3 = (x-mbvq4[2][0])*(x-mbvq4[2][0])+(y-mbvq4[2][1])*(y-mbvq4[2][1])+(z-mbvq4[2][2])*(z-mbvq4[2][2]);
                                dis4 = (x-mbvq4[3][0])*(x-mbvq4[3][0])+(y-mbvq4[3][1])*(y-mbvq4[3][1])+(z-mbvq4[3][2])*(z-mbvq4[3][2]);

                                // compare the distance and find the smallest one
                                if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                                {
                                   index = 0;
                                }
                                if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                                {
                                   index = 1;
                                }
                                if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                                {
                                   index = 2;
                                }
                                if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                                {
                                   index = 3;
                                }

                                // get the error
                                Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq4[index][0];
                                Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq4[index][1];
                                Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq4[index][2];

                             // Error Diffusion
                             if(width-1>=0)
                             {
                                 Error[height][width-1].red=Error[height][width-1].red+Error[height][width].red*7/16;
                                 Error[height][width-1].green=Error[height][width-1].green+Error[height][width].green*7/16;
                                 Error[height][width-1].blue=Error[height][width-1].blue+Error[height][width].blue*7/16;
                             }
                             if(width+1<size && height+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*3/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*3/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width-1>=0)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*1/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*1/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }
                             }
                             else
                             {
                                 //RGBM
                                if(x>=0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x>=0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }

                                // calculate the distance
                                dis1 = (x-mbvq5[0][0])*(x-mbvq5[0][0])+(y-mbvq5[0][1])*(y-mbvq5[0][1])+(z-mbvq5[0][2])*(z-mbvq5[0][2]);
                                dis2 = (x-mbvq5[1][0])*(x-mbvq5[1][0])+(y-mbvq5[1][1])*(y-mbvq5[1][1])+(z-mbvq5[1][2])*(z-mbvq5[1][2]);
                                dis3 = (x-mbvq5[2][0])*(x-mbvq5[2][0])+(y-mbvq5[2][1])*(y-mbvq5[2][1])+(z-mbvq5[2][2])*(z-mbvq5[2][2]);
                                dis4 = (x-mbvq5[3][0])*(x-mbvq5[3][0])+(y-mbvq5[3][1])*(y-mbvq5[3][1])+(z-mbvq5[3][2])*(z-mbvq5[3][2]);

                                // compare the distance and find the smallest one
                                if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                                {
                                   index = 0;
                                }
                                if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                                {
                                   index = 1;
                                }
                                if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                                {
                                   index = 2;
                                }
                                if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                                {
                                   index = 3;
                                }

                                // get the error
                                Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq5[index][0];
                                Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq5[index][1];
                                Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq5[index][2];

                                // Error Diffusion
                             if(width-1>=0)
                             {
                                 Error[height][width-1].red=Error[height][width-1].red+Error[height][width].red*7/16;
                                 Error[height][width-1].green=Error[height][width-1].green+Error[height][width].green*7/16;
                                 Error[height][width-1].blue=Error[height][width-1].blue+Error[height][width].blue*7/16;
                             }
                             if(width+1<size && height+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*3/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*3/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width-1>=0)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*1/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*1/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }
                            }
                        }
                        else
                        {
                            //CMGB
                                if(x>=0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x>=0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x>=0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)0;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y>=0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y>=0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)0;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }
                                if(x<0.5&&y<0.5&&z>=0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)0;
                                }
                                if(x<0.5&&y<0.5&&z<0.5)
                                {
                                   newimagedata[height][width][0]=(unsigned char)255;
                                   newimagedata[height][width][1]=(unsigned char)255;
                                   newimagedata[height][width][2]=(unsigned char)255;
                                }

                                // calculate the distance
                                dis1 = (x-mbvq6[0][0])*(x-mbvq6[0][0])+(y-mbvq6[0][1])*(y-mbvq6[0][1])+(z-mbvq6[0][2])*(z-mbvq6[0][2]);
                                dis2 = (x-mbvq6[1][0])*(x-mbvq6[1][0])+(y-mbvq6[1][1])*(y-mbvq6[1][1])+(z-mbvq6[1][2])*(z-mbvq6[1][2]);
                                dis3 = (x-mbvq6[2][0])*(x-mbvq6[2][0])+(y-mbvq6[2][1])*(y-mbvq6[2][1])+(z-mbvq6[2][2])*(z-mbvq6[2][2]);
                                dis4 = (x-mbvq6[3][0])*(x-mbvq6[3][0])+(y-mbvq6[3][1])*(y-mbvq6[3][1])+(z-mbvq6[3][2])*(z-mbvq6[3][2]);

                                // compare the distance and find the smallest one
                                if(dis1<dis2 && dis1<dis3 && dis1<dis4)
                                {
                                   index = 0;
                                }
                                if(dis2<dis1 && dis2<dis3 && dis2<dis4)
                                {
                                   index = 1;
                                }
                                if(dis3<dis1 && dis3<dis2 && dis3<dis4)
                                {
                                   index = 2;
                                }
                                if(dis4<dis1 && dis4<dis2 && dis4<dis3)
                                {
                                   index = 3;
                                }

                                // get the error
                                Error[height][width].red = CMY[height][width].red + Error[height][width].red - mbvq6[index][0];
                                Error[height][width].green = CMY[height][width].green + Error[height][width].green - mbvq6[index][1];
                                Error[height][width].blue = CMY[height][width].blue + Error[height][width].blue - mbvq6[index][2];

                                // Error Diffusion
                             if(width-1>=0)
                             {
                                 Error[height][width-1].red=Error[height][width-1].red+Error[height][width].red*7/16;
                                 Error[height][width-1].green=Error[height][width-1].green+Error[height][width].green*7/16;
                                 Error[height][width-1].blue=Error[height][width-1].blue+Error[height][width].blue*7/16;
                             }
                             if(width+1<size && height+1<size)
                             {
                                 Error[height+1][width+1].red=Error[height+1][width+1].red+Error[height][width].red*3/16;
                                 Error[height+1][width+1].green=Error[height+1][width+1].green+Error[height][width].green*3/16;
                                 Error[height+1][width+1].blue=Error[height+1][width+1].blue+Error[height][width].blue*3/16;
                             }
                             if(height+1<size && width-1>=0)
                             {
                                 Error[height+1][width-1].red=Error[height+1][width-1].red+Error[height][width].red*1/16;
                                 Error[height+1][width-1].green=Error[height+1][width-1].green+Error[height][width].green*1/16;
                                 Error[height+1][width-1].blue=Error[height+1][width-1].blue+Error[height][width].blue*1/16;
                             }
                             if(height+1<size)
                             {
                                 Error[height+1][width].red=Error[height+1][width].red+Error[height][width].red*1/16;
                                 Error[height+1][width].green=Error[height+1][width].green+Error[height][width].green*1/16;
                                 Error[height+1][width].blue=Error[height+1][width].blue+Error[height][width].blue*1/16;
                             }

                         }
                      }
                }
            }

    }

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(newimagedata, sizeof(unsigned char), size*size*bytesPerPixel, file);
    fclose(file);

    return 0;
}



