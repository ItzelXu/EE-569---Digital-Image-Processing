// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
    int NewSize = 650;
    int length, breadth, channel;
    int xcoord, ycoord, temp;
    unsigned char NewImagedata[NewSize][NewSize][BytesPerPixel];
    float p,q;

    for (length = 0; length<NewSize; length++)
    {
     for(breadth = 0; breadth<NewSize; breadth++)
     {
      for(channel = 0; channel<3; channel++)
      {

       xcoord = length*((float)(Size)/(NewSize));
       ycoord = breadth*((float)(Size)/(NewSize));
       p = (float)length*(Size)/(NewSize) - xcoord;
       q = (float)breadth*(Size)/(NewSize) - ycoord;

       // For last pixel, directly copy pixel intensity for each channel
       if(xcoord==511&&ycoord==511)
				{
					NewImagedata[649][649][channel] = Imagedata[511][511][channel];
					continue;
				}

       // For edge, apply Interpolation formula partially as two terms become 0
       if(xcoord==511&&ycoord!=511)
				{
                    temp = (1-p)*(1-q)*(int)Imagedata[xcoord][ycoord][channel]+p*(1-q)*(int)Imagedata[xcoord][ycoord+1][channel];
                    NewImagedata[length][breadth][channel] = (char)temp;
                    continue;
				}

       // For edge, apply Interpolation formula partially as two terms become 0
       if(ycoord==511&&xcoord!=511)
				{
                    temp = (1-p)*(1-q)*(int)Imagedata[xcoord][ycoord][channel]+p*(1-q)*(int)Imagedata[xcoord+1][ycoord][channel];
                    NewImagedata[length][breadth][channel] = (char)temp;
					continue;
				}
       // Apply Formula for rest of the pixels
       temp = (1-p)*(1-q)*(int)Imagedata[xcoord][ycoord][channel]+q*(1-p)*(int)Imagedata[xcoord][ycoord+1][channel]+p*(1-q)*(int)Imagedata[xcoord+1][ycoord][channel]+p*q*(int)Imagedata[xcoord+1][ycoord+1][channel];
       NewImagedata[length][breadth][channel] = (char)temp;

      }
     }
    }
