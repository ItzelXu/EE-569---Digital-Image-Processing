// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
	int length, breadth,channel, sum;
	unsigned char NewImagedata[Size][Size][1];

	// For each pixel, convert to grayscale using formula for average method
	for(length=0;length<Size;length++)
	{
	 for(breadth=0;breadth<Size;breadth++)
	 {
	  sum=0;
	  for(channel=0;channel<3;channel++)
	  {
	    sum=Imagedata[length][breadth][channel]+sum;
      }
      NewImagedata[length][breadth][0]=sum/3;
     }
    }

