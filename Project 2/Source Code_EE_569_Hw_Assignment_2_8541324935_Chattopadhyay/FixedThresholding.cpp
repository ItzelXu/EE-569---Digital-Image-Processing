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
	int threshold = 127;

	for(length = 0; length<Size; length++)
    {
        for(breadth = 0; breadth<Size; breadth++)
        {
            if(Imagedata[length][breadth][0] < threshold)
            {
               NewImagedata[length][breadth][0] = 0;
            }
            else if(Imagedata[length][breadth][0] > threshold)
            {
               NewImagedata[length][breadth][0] = 255;
            }
        }
     }

     // Write image data (filename specified by second argument) from image data matrix
}