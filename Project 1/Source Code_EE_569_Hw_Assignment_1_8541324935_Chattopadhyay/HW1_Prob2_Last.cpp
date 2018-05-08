// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <math.h>
    int length,breadth,channel;
    unsigned char NewImagedata1[Size][Size][BytesPerPixel];
    unsigned char NewImagedata2[Size][Size][BytesPerPixel];

    for(length = 0; length < Size; length++)
    {
     for(breadth = 0; breadth < Size; breadth++)
     {
       for(channel = 0; channel < 3; channel++)
       {
          NewImagedata1[length][breadth][channel]=Imagedata[length][Size-1-breadth][channel];
       }
     }
    }

    for(channel = 0; channel < 3; channel++)
    {
        for(length = 0; length < Size; length++)
        {
           for(breadth = 0; breadth < Size; breadth++)
           {
               NewImagedata2[length][breadth][channel] = (255 - ((float)NewImagedata1[length][breadth][channel]));
           }
        }
    }

    for(length = 0; length < Size; length++)
    {
        for(breadth = 0; breadth < Size; breadth++)
        {

            NewImagedata2[length][breadth][0] = floor((float(NewImagedata2[length][breadth][0]) / float(255) * 120.0) + 127);
            NewImagedata2[length][breadth][1] = floor((float(NewImagedata2[length][breadth][1]) / float(255) * 110.0) + 40);
            NewImagedata2[length][breadth][2] = floor((float(NewImagedata2[length][breadth][2]) / float(255) * 125.0) + 25);

        }
    }

