// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>


using namespace std;

unsigned char newimagedata[100][100];
unsigned char weight_m[100][100];

int main(int argc, char *argv[])
{
    //Define file pointer and variables
    FILE *file;

    int height = 100;
    int width = 100;

    //Allocate image data array
    unsigned char imagedata[height][width];

    //Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(imagedata, sizeof(unsigned char), height*width, file);
    fclose(file);

    //Shrink conditional mark patterns
    unsigned char conditional_thinning[46][9]={ {0,1,0,0,1,1,0,0,0}, {0,1,0,1,1,0,0,0,0}, {0,0,0,1,1,0,0,1,0}, {0,0,0,0,1,1,0,1,0},
                                                {0,0,1,0,1,1,0,0,1}, {1,1,1,0,1,0,0,0,0}, {1,0,0,1,1,0,1,0,0}, {0,0,0,0,1,0,1,1,1},
                                                {1,1,0,0,1,1,0,0,0}, {0,1,0,0,1,1,0,0,1}, {0,1,1,1,1,0,0,0,0}, {0,0,1,0,1,1,0,1,0},
                                                {0,1,1,0,1,1,0,0,0}, {1,1,0,1,1,0,0,0,0}, {0,0,0,1,1,0,1,1,0}, {0,0,0,0,1,1,0,1,1},
                                                {1,1,0,0,1,1,0,0,1}, {0,1,1,1,1,0,1,0,0},
                                                {1,1,1,0,1,1,0,0,0}, {0,1,1,0,1,1,0,0,1}, {1,1,1,1,1,0,0,0,0}, {1,1,0,1,1,0,1,0,0}, {1,0,0,1,1,0,1,1,0},
                                                {0,0,0,1,1,0,1,1,1}, {0,0,0,0,1,1,1,1,1}, {0,0,1,0,1,1,0,1,1},
                                                {1,1,1,0,1,1,0,0,1}, {1,1,1,1,1,0,1,0,0}, {1,0,0,1,1,0,1,1,1}, {0,0,1,0,1,1,1,1,1},
                                                {0,1,1,0,1,1,0,1,1}, {1,1,1,1,1,1,0,0,0}, {1,1,0,1,1,0,1,1,0}, {0,0,0,1,1,1,1,1,1},
                                                {1,1,1,0,1,1,0,1,1}, {0,1,1,0,1,1,1,1,1}, {1,1,1,1,1,1,1,0,0} ,{1,1,1,1,1,1,0,0,1},
                                                {1,1,1,1,1,0,1,1,0}, {1,1,0,1,1,0,1,1,1}, {1,0,0,1,1,1,1,1,1}, {0,0,1,1,1,1,1,1,1},
                                                {1,1,1,0,1,1,1,1,1}, {1,1,1,1,1,1,1,0,1}, {1,1,1,1,1,0,1,1,1}, {1,0,1,1,1,1,1,1,1}};

    int iterations = 25;
    int i, j, k, a, b, m, n;
    unsigned char temp[9];
    int Temp[9];
    int index, count1;

    // converting to binary image
    for(i = 0; i<height; i++)
    {
       for(j=0; j<width; j++)
       {
           if(imagedata[i][j]<127)
           {
               imagedata[i][j] = 0;
           }
           else
           {
               imagedata[i][j] = 1;
           }
       }
    }

    //interchange colors in image
    for(i = 0; i<height; i++)
    {
       for(j=0; j<width; j++)
       {
               imagedata[i][j] = 1 - imagedata[i][j];
       }
    }

    for(k = 0; k<iterations; k++)
    {
        // initialize the m matrix as 0
        for(i = 0; i<height; i++)
        {
            for(j = 0; j<width; j++)
            {
                weight_m[i][j] = 0;
            }
        }

        for(i = 1; i<height-1 ;i++)
        {
            for(j = 1; j<width-1; j++)
            {
                if(imagedata[i][j]==1)
                {
                    // gather 3*3 matrix of data points to compare to masks
                    index = 0;
                    for(a = i-1; a<= i+1; a++)
                    {
                        for(b= j-1; b<=j+1; b++)
                        {
                            temp[index] = imagedata[a][b];
                            index++;
                        }
                    }

                    bool flag;

                    // test for conditional mask
                    for (m = 0; m<46; m++)
                    {
                        flag = true;
                        for(n = 0; n<9; n++)
                        {
                             if (int(conditional_thinning[m][n])!= int(temp[n]))
                             {
                                flag = false;
                                break;
                             }
                        }

                        if( flag == true)
                        {
                             weight_m[i][j]=1;
                             break;
                        }
                    }
                }
            }
        }

        // apply unconditional masks
        for(i = 0; i<height; i++)
        {
            for(j = 0; j<width; j++)
            {
                if(weight_m[i][j]==0)
                {
                    newimagedata[i][j]= imagedata[i][j];
                }
                else
                {
                    // gather 3*3 matrix of data points from m matrix to compare to masks
                    index = 0;
                    for(a = i-1; a<= i+1; a++)
                    {
                        for(b= j-1; b<=j+1; b++)
                        {
                            temp[index] = weight_m[a][b];
                            index++;
                        }
                    }

                    // convert to integer to compare
                    for(m = 0; m<9; m++)
                    {
                        Temp[m] = temp[m];
                    }

                    // set flag
                    bool flag = false;

                    // check the different masks

                    //Spur
                    if(Temp[0]==0 && Temp[1]==0 && Temp[2]==1 && Temp[3]==0 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==1 && Temp[1]==0 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }

                    //Single 4 connection
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==1 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }

                    // L cluster
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[2]==1 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==1 && Temp[2]==1 && Temp[3]==0 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==1 && Temp[1]==1 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==1 && Temp[1]==0 && Temp[2]==0 && Temp[3]==1 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[2]==0 && Temp[3]==1 && Temp[4]==1 && Temp[5]==0 && Temp[6]==1 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==0 && Temp[6]==1 && Temp[7]==1 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==1 && Temp[8]==1)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==0 && Temp[8]==1)
                    {
                          flag = true;
                    }

                    //4-connected offset
                    else if(Temp[0]==0 && Temp[1]==1 && Temp[2]==1 && Temp[3]==1 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==1 && Temp[1]==1 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==1 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==0 && Temp[8]==1)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[2]==1 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==1 && Temp[8]==0)
                    {
                          flag = true;
                    }

                    //Spur corner cluster
                    else if(Temp[0]==0 && ((Temp[1]|Temp[5])==1) && Temp[2]==1 && Temp[3]==0 && Temp[4]==1 && Temp[6]==1 && Temp[7]==0 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==1 && ((Temp[1]|Temp[3])==1) && Temp[2]==0 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==0 && Temp[8]==1)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==0 && ((Temp[3]|Temp[7])==1) && Temp[1]==0 && Temp[2]==1 && Temp[4]==1 && Temp[5]==0 && Temp[6]==1 && Temp[8]==0)
                    {
                          flag = true;
                    }
                    else if(Temp[0]==1 && (Temp[5]|Temp[7]==1) && Temp[1]==0 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[6]==0 && Temp[8]==1)
                    {
                          flag = true;
                    }

                    //Corner Cluster
                    else if(Temp[0]==1 && Temp[1]==1 && Temp[3]==1 && Temp[4]==1)
                    {
                         flag = true;
                    }

                    // Tee Branch
                    else if(Temp[1]==1 && Temp[2]==0 && Temp[3]==1 && Temp[4]==1 && Temp[5]==1 && Temp[7]==0 && Temp[8]==0)
                    {
                        flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==1 && Temp[3]==1 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==0)
                    {
                        flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==0 && Temp[3]== 1 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==1)
                    {
                        flag = true;
                    }
                    else if(Temp[1]==0 && Temp[2]==0 && Temp[3]==1 && Temp[4]==1 && Temp[5]==1  && Temp[7]==1 && Temp[8]==0)
                    {
                        flag = true;
                    }
                    else if(Temp[1]==1 && Temp[3]==1 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==1 && Temp[8]==0)
                    {
                        flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==1  && Temp[2]==0 && Temp[3]==1 && Temp[4]==1 && Temp[5]==0 && Temp[7]==1)
                    {
                        flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==1 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[7]==1)
                    {
                        flag = true;
                    }
                    else if(Temp[1]==1 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[6]==0 && Temp[7]==1 && Temp[8]==0)
                    {
                        flag = true;
                    }

                    // Vee Branch
                    else if(Temp[0]==1 && Temp[2]==1 && Temp[4]==1 && ((Temp[6]|Temp[7]|Temp[8])== 1))
                    {
                        flag = true;
                    }
                    else if(Temp[0]==1 && Temp[4]==1 && Temp[6]==1 && ((Temp[2]|Temp[5]|Temp[8])==1))
                    {
                        flag = true;
                    }
                    else if(Temp[4]==1 && Temp[6]==1 && Temp[8]==1 && ((Temp[0]|Temp[1]|Temp[2])==1))
                    {
                        flag = true;
                    }
                    else if(Temp[2]==1 && Temp[4]==1 && Temp[8]==1 && ((Temp[0]|Temp[3]|Temp[6])==1))
                    {
                        flag = true;
                    }

                    //Diagonal Branch
                    else if(Temp[1]==1 && Temp[2]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[6]==1 && Temp[7]==0)
                    {
                        flag = true;
                    }
                    else if(Temp[0]==0 && Temp[1]==1 && Temp[3]==1 && Temp[4]==1 && Temp[5]==0 && Temp[7]==0 && Temp[8]==1)
                    {
                        flag = true;
                    }
                    else if(Temp[1]==0 && Temp[2]==1 && Temp[3]==1 && Temp[4]==1 && Temp[5]==0 && Temp[6]==0 && Temp[7]==1)
                    {
                        flag = true;
                    }
                    else if(Temp[0]==1 && Temp[1]==0 && Temp[3]==0 && Temp[4]==1 && Temp[5]==1 && Temp[7]==1 && Temp[8]==0)
                    {
                        flag = true;
                    }
                    if(flag == true)
                    {
                        newimagedata[i][j]=1;
                    }
                    else
                    {
                        newimagedata[i][j]=0;
                    }
                }
            }
        }

        for(i = 0; i<height; i++)
        {
            for(j = 0; j<width; j++)
            {
                imagedata[i][j] = newimagedata[i][j];
            }
        }
    }

    for(i = 0; i<height; i++)
    {
            for(j = 0; j<width; j++)
            {
                newimagedata[i][j] = newimagedata[i][j]*255;
            }
    }

    for(i = 0; i<height; i++)
    {
            for(j = 0; j<width; j++)
            {
                newimagedata[i][j] = 255 - newimagedata[i][j];
            }
    }


    // output the image
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(newimagedata, sizeof(unsigned char), height*width, file);
    fclose(file);

    return 0;
}
