// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
	int length, breadth,channel, max, min;
	unsigned char NewImagedata[Size][Size][1];

	// For each pixel, convert to grayscale using formula for lightness method
	for(length=0;length<Size;length++)
	{
	 for(breadth=0;breadth<Size;breadth++)
	 {
	  max=0;
	  min=Imagedata[length][breadth][0];
	  for(channel=0;channel<3;channel++)
	  {
	    if(Imagedata[length][breadth][channel]>max)
	    max=Imagedata[length][breadth][channel];
	    if(Imagedata[length][breadth][channel]<min)
	    min=Imagedata[length][breadth][channel];
      }
      NewImagedata[length][breadth][0]=(min+max)/2;
     }
    }

