// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <math.h>

const int Size = 512;
double temp[Size][Size];
double error;

int main(int argc, char *argv[])
	{
	{

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



// Write image data (filename specified by second argument) from image data matrix
}