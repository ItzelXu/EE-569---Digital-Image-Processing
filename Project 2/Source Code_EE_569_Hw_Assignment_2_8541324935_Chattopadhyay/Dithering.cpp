// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <math.h>

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

int main(int argc, char *argv[])
	{
	{

	int length,breadth,channel;
	unsigned char NewImagedata[Size][Size][BytesPerPixel];
	int MaxInt=0;
	int INDEX;

	cout<<"Enter the size for Index Matrix: ";
	cin>>INDEX;

	float* threshold = ThresholdMatrix(INDEX);

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
                NewImagedata[length][breadth][0] = 255;
            }
            else
            {
                NewImagedata[length][breadth][0] = 0;
            }
        }
    }

     // Write image data (filename specified by second argument) from image data matrix
}


