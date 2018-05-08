// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>using namespace std;int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size1 = 400;
	int Size2 = 300;
	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		}    // Allocate image data array	unsigned char Imagedata[Size1][Size2][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

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

	// Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(NewImagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	return 0;
}
