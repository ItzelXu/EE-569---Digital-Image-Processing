// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
	int Size2 = 300;


	int length,breadth,channel,intensity;
	int count;
	int location[Size1*Size2][2];
	int NumberOfBoxes = (Size1*Size2)/256;
	int hist[BytesPerPixel][256]={0};
	int histbucket[BytesPerPixel][256]={0};
	int cumhist[BytesPerPixel][256]={0};
	int nop;
	int i,j;
	unsigned char NewImagedata[Size1][Size2][BytesPerPixel];

	// Make histogram of image
	for(length = 0; length<Size1; length++)
    {
     for(breadth = 0; breadth<Size2; breadth++)
     {
      for(channel = 0; channel<3; channel++)
      {
	    hist[channel][(int)Imagedata[length][breadth][channel]]= hist[channel][(int)Imagedata[length][breadth][channel]]+1;
      }
     }
    }

    // According to intensity store the location of each pixel in ascending order. Also count the number of pixels for each intensity level
	for(channel = 0; channel<3; channel++)
    {
      count = 0;
      for(intensity = 0; intensity<256; intensity++)
      {
        for(length = 0; length<Size1; length++)
        {
          for(breadth = 0; breadth<Size2; breadth++)
          {
            if((int)Imagedata[length][breadth][channel] == intensity)
            {
             location[count][0] = length;
             location[count][1] = breadth;
             count = count + 1;
            }
          }
        }
      }

     // Divide the pixels into equal number of buckets and form the new image
	 nop = 0;
	 for(intensity = 0; intensity<256; intensity++)
     {
	   for(length = nop; length < NumberOfBoxes + nop; length++)
	   {
	     NewImagedata[location[length][0]][location[length][1]][channel] = (unsigned char)intensity;
	   }
	   nop = nop + NumberOfBoxes;
     }
	}

	//Find Histogram of new image
	for(length = 0; length<Size1; length++)
    {
     for(breadth = 0; breadth<Size2; breadth++)
     {
      for(channel = 0; channel<3; channel++)
      {
	    histbucket[channel][(int)NewImagedata[length][breadth][channel]]= hist[channel][(int)NewImagedata[length][breadth][channel]]+1;
      }
     }
    }

    for(i=0;i<3;i++)
    {
     cumhist[i][0]=histbucket[i][0];
     for(j=1;j<256;j++)
     {
       cumhist[i][j]=histbucket[i][j]+cumhist[i][j-1];
     }
    }

    for(j=0;j<256;j++)
    {
        for(i=0;i<3;i++)
        {
            cout<< cumhist[i][j] << ", ";
        }
        cout<<endl;
    }

	// Write image data (filename specified by second argument) from image data matrix
}