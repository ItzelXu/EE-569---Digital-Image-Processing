// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>#include <iostream>#include <stdlib.h>using namespace std;
const int N = 3;	//N*N neighborhood

const int Size1 = 1800;
const int Size2 = 1200;
unsigned char temp1[Size2][Size1+N-1][3];

unsigned char temp2[Size2+N-1][Size1+N-1][3];

//int temp3[Size2+N-1][Size1+N-1][3];

unsigned char OilPaintingImage[Size2][Size1][3];
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);	}	// Allocate image data array	unsigned char Imagedata[Size2][Size1][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	int length,breadth,channel,intensity;
	int count1,count2;
    short location[Size1*Size2][2];
	unsigned char NewImagedata1[Size2][Size1][BytesPerPixel];
	int NumColor = 8;
	int Color[3][8];
	int nop, sum;
	int Value = (Size1*Size2)/NumColor;
	int Red,Green,Blue;
	int max;
	int a,b,c;
	int temp4[NumColor][NumColor][NumColor];
	int temp3[Size2+N-1][Size1+N-1][3];

    // Find and stor the location of each pixel of particular intensities in ascending order
    for(channel = 0; channel<3; channel++)
    {
      count1 = 0;
      for(intensity = 0; intensity<256; intensity++)
      {
        for(length = 0; length<Size2; length++)
        {
          for(breadth = 0; breadth<Size1; breadth++)
          {
            if((int)Imagedata[length][breadth][channel] == intensity)
            {
             location[count1][0] = length;
             location[count1][1] = breadth;
             count1 = count1 + 1;
            }
          }
        }
      }

	  count2 = 0;
      nop = 0;

      // Divide the pixels into N bins so that the sum of each bin is equal. Then assign the mean intensity of each bin accordingly
      // to the new image file to get the quantized image. The image will have N*N*N total colors now.
      for(intensity = Value-1;intensity < Size1*Size2;intensity = intensity+Value)
      {
        sum=0;
        for(breadth = nop; breadth <Value + nop;breadth++)
        {
            sum = sum + (int)Imagedata[location[breadth][0]][location[breadth][1]][channel];
        }
        for(breadth = nop;breadth <Value + nop;breadth++)
        {
            NewImagedata1[location[breadth][0]][location[breadth][1]][channel]=(unsigned char)(sum/Value);
        }
			nop = nop+Value;
			Color[channel][count2]=sum/(Value);
			count2 = count2+1;
	  }    }

    // Form a temporary image by adding rows and columns to the edges of the image by mirroring the original image. The number of rows and
    // and columns added on each edge depends on window size N by the value (N-1)/2
	for (channel=0; channel<3; channel++)
    {
		for(length=0; length<Size2; length++)
		{
			for(breadth=(N-1)/2;breadth<Size1+(N-1)/2; breadth++)
			{
				temp1[length][breadth][channel] = NewImagedata1[length][breadth-(N-1)/2][channel];
			}
		}

		for(length=0; length<Size2; length++)
        {
			for(breadth=0; breadth<(N-1)/2; breadth++)
            {
				temp1[length][breadth][channel] = temp1[length][((N-1)/2)-breadth+1][channel];
				temp1[length][Size1+((N-1)/2)+breadth][channel] = temp1[length][Size1+((N-1)/2)-(breadth+1)][channel];
			}
		}

		for(length=(N-1)/2; length<Size2+(N-1)/2; length++)
        {
			for(breadth=0; breadth<Size1+(N-1); breadth++)
			{
		        temp2[length][breadth][channel] = temp1[length-(N-1)/2][breadth][channel];
			}
		}

		for(breadth=0; breadth<Size1+(N-1); breadth++)
        {
			for(length=0; length<(N-1)/2; length++)
            {
				temp2[length][breadth][channel] = temp2[((N-1)/2)-length+1][breadth][channel];
				temp2[Size2+((N-1)/2)+length][breadth][channel] = temp2[Size2-((N-1)/2)-(length+1)][breadth][channel];
			}
		}
	}

	//Based on already stored quantized color intensities, form a temporary image from the extended image containing corresponding indexes
	// from the color matrix which stores all the colors.
	for(channel=0; channel<3; channel++)
    {
		for(length=0; length<Size2+N-1;length++)
        {
			for(breadth=0; breadth<Size1+N-1;breadth++)
            {
				for(nop=0; nop<NumColor; nop++)
				{
					if ((int) temp2[length][breadth][channel] == Color[channel][nop])
                    {
                        temp3[length][breadth][channel] = nop;

                    }
				}
			}
		}
	}

    for(length=0; length<Size2; length++)
    {
        for(breadth=0; breadth<Size1; breadth++)
        {
            // Form a sliding window
            for(a=0; a<NumColor; a++)
            {
                for(b=0; b<NumColor; b++)
                {
                    for(c=0; c<NumColor; c++)
                    {
							temp4[a][b][c]=0;
                    }
                }
            }

            // Store the values from temporary index array into window and find the number of times different colors occur
            for(a=0; a<=N-1; a++)
            {
                for(b=0; b<=N-1; b++)
                {
						   temp4[temp3[length+a][breadth+b][0]][temp3[length+a][breadth+b][1]][temp3[length+a][breadth+b][2]]++;
                }
            }


            max = temp4[0][0][0];
            Red=0;
            Green=0;
            Blue=0;

            // Find the maximum times a color repeats and store their indexes.
            for(a=0; a<NumColor; a++)
            {
                for(b=0; b<NumColor; b++)
                {
                    for(c=0; c<NumColor; c++)
                    {
                        if(max<temp4[a][b][c])
                        {
                            max=temp4[a][b][c];
                            Red = a;
                            Green = b;
                            Blue = c;
                        }
                    }
                }
            }

            // Copy max index to the new image to be formed
            OilPaintingImage[length][breadth][0]=(unsigned char)Color[0][Red];
            OilPaintingImage[length][breadth][1]=(unsigned char)Color[1][Green];
            OilPaintingImage[length][breadth][2]=(unsigned char)Color[2][Blue];
        }
    }

	// Write image data (filename specified by second argument) from image data matrix	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(OilPaintingImage, sizeof(unsigned char), (Size1)*(Size2)*BytesPerPixel, file);	fclose(file);	return 0;}