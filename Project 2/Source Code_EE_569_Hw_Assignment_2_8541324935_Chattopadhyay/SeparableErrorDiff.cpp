// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <math.h>

const int Size = 700;
double temp[Size][Size][3];
double error;
unsigned char NewImagedata[Size][Size][3];

int main(int argc, char *argv[])
	{
	{

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
    // Write image data (filename specified by second argument) from image data matrix
}