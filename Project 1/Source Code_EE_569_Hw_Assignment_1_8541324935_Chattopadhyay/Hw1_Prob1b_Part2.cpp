// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
	int Size2 = 480;
	int length, breadth;
	unsigned char ImagedataMagenta[Size1][Size2][1];

	//Convert RGB to Magenta Grayscale image
	for(length=0;length<Size1;length++)
	{
	 for(breadth=0;breadth<Size2;breadth++)
	 {
          ImagedataMagenta[length][breadth][0] = (255 - ((float)Imagedata[length][breadth][1]));
     }
    }


