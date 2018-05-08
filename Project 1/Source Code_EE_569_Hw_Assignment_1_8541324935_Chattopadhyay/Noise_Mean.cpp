// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
const int Size = 512;
const int N = 7;	//N*N neighborhood
unsigned char temp1[Size][Size+N-1][3];
unsigned char temp2[Size+N-1][Size+N-1][3];

	{
	{
	int length,breadth,channel;
	int hist[BytesPerPixel][256]={0};
    int i,j,k,l,temp,sum;
    unsigned char NewImagedata1[Size][Size][BytesPerPixel];
    int temp3[N*N];

    // Find Histogram of image
	for(length = 0; length<Size; length++)
    {
     for(breadth = 0; breadth<Size; breadth++)
     {
      for(channel = 0; channel<3; channel++)
      {
	    hist[channel][(int)Imagedata[length][breadth][channel]]= hist[channel][(int)Imagedata[length][breadth][channel]]+1;
      }
     }
    }

    // Display Histogram values
	for(j=0;j<256;j++)
    {
        for(i=0;i<3;i++)
        {
            cout<< hist[i][j] << ", ";
        }
        cout<<j<<", ";
        cout<<endl;
    }

    // Make temporary image with extended rows and columns on all edges. The number of rows and columns depends on window
    // size N and is given by (N-1)
    for (channel=0; channel<3; channel++)
    {
		for(length=0; length<Size; length++)
		{
			for(breadth=(N-1)/2;breadth<Size+(N-1)/2;breadth++)
			{
				temp1[length][breadth][channel] = Imagedata[length][breadth-(N-1)/2][channel];
			}
		}

		for(length=0; length<Size; length++)
        {
			for(breadth=0; breadth<(N-1)/2;breadth++)
            {
				temp1[length][breadth][channel] = Imagedata[length][(N-1)/2-breadth][channel];
				temp1[length][Size+(N-1)/2+breadth][channel] = Imagedata[length][Size-((N-1)/2+breadth)][channel];
			}
		}

		for(length=(N-1)/2; length<Size+(N-1)/2; length++)
        {
			for(breadth=0; breadth<Size+(N-1); breadth++)
			{
		        temp2[length][breadth][channel] = temp1[length-(N-1)/2][breadth][channel];
			}
		}

		for(breadth=0; breadth<Size+(N-1); breadth++)
        {
			for(length=0; length<(N-1)/2; length++)
            {
				temp2[length][breadth][channel] = temp1[(N-1)/2-length][breadth][channel];
				temp2[Size+(N-1)/2+length][breadth][channel] = temp1[Size-((N-1)/2+length)][breadth][channel];
			}
		}
	}

    // Apply the mean filter by checking for the mean in a window
	for(channel = 0; channel < 3; channel++)
	{
        for(length = 0; length < Size; length++)
        {
            for(breadth = 0; breadth < Size; breadth++)
            {
                for(i=0; i<N*N; i++)
                {
                    temp3[i] = 0;
                }

                l = 0;
                for(i=0; i<N; i++)
                {
                   for(j=0; j<N; j++)
                   {
                       k = (int)temp2[length+i][breadth+j][channel];
                       temp3[l] = k;
                       l++;
                   }
                }

                sum = 0;
                for(i=0; i<N*N; i++)
                {
                    sum = sum + temp3[i];
                }


                NewImagedata1[length][breadth][channel]=sum/(N*N);
            }
       }
	}



