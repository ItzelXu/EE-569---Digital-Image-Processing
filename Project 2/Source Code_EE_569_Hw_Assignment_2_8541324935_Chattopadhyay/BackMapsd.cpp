// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <math.h>
int main(int argc, char *argv[])
	{
	{

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

    // Write image data (filename specified by second argument) from image data matrix
}

