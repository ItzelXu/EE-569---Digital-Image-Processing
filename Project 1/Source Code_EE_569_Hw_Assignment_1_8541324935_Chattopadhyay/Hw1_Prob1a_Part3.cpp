// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
	int length, breadth, luminosity;
	unsigned char NewImagedata[Size][Size][1];

	// Find Grayscale image using formula for luminosity method
	for(length=0;length<Size;length++)
	{
	 for(breadth=0;breadth<Size;breadth++)
	 {
	  luminosity = 0.21*Imagedata[length][breadth][0]+0.72*Imagedata[length][breadth][1]+0.07*Imagedata[length][breadth][2];
      NewImagedata[length][breadth][0]=luminosity;
     }
    }

