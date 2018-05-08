// EE569 Homework Assignment #2
// Date:     February 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <deque>

struct point
{
    int x;
    int y;
};

unsigned char labeldata[372][372];
unsigned char copydata[372][372];
unsigned char newimagedata1[372][372];
unsigned char newimagedata[372][372];

using namespace std;

int main(int argc, char *argv[])
{
    // Define file pointer and variables
    FILE *file;

    int size = 372;

    // Allocate image data array
    unsigned char imagedata[size][size];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(imagedata, sizeof(unsigned char), size*size, file);
    fclose(file);

    int iterations = 50;
    int label = 1;
    int height, width, index, count1;
    unsigned char temp[9];
    int Temp[9];
    int i, j, k, a, b, m, n;
    int Sizeofpuzzle[16] = {0};
    int coordx1, coordy1;
    int puzzle[16][4];
    int puzzleanti[16][4];
    int num1, flag;

    for(height = 0; height<size; height++)
    {
       for(width = 0; width<size; width++)
       {
           if(imagedata[height][width]<127)
           {
               imagedata[height][width] = 0;
           }
           else
           {
               imagedata[height][width] = 255;
           }
       }
    }

    for(height = 0; height<size; height++)
    {
       for(width = 0; width<size; width++)
       {
           labeldata[height][width] = 0;
       }
    }

    for(height = 0; height<size; height++)
    {
       for(width = 0; width<size; width++)
       {
           copydata[height][width] = imagedata[height][width];
       }
    }

    // Apply BFS to segment the picture
    for(height = 0; height<size; height++)
    {
        for(width = 0; width<size; width++)
        {
           if(copydata[height][width] == 0)
           {
               deque<point> q;
               q.clear();

               //Initialization
               q.push_back(point());
               q.back().y = height;
               q.back().x = width;
               labeldata[height][width] = label;
               copydata[height][width] = 255;

               //Loop
               while(!q.empty())
               {
                   a = q.front().y;
                   b = q.front().x;

                   if(b+1<size)
                   {
                       if(copydata[a][b+1] == 0)
                       {
                           q.push_back(point());
                           q.back().x = b+1;
                           q.back().y = a;
                           labeldata[a][b+1] = label;
                           copydata[a][b+1] = 255;
                       }
                   }
                   if(a-1>=0)
                   {
                       if(copydata[a-1][b] == 0)
                       {
                           q.push_back(point());
                           q.back().x = b;
                           q.back().y = a-1;
                           labeldata[a-1][b] = label;
                           copydata[a-1][b] = 255;
                       }
                   }
                   if(a+1<size)
                   {
                       if(copydata[a+1][b] == 0)
                       {
                           q.push_back(point());
                           q.back().x = b;
                           q.back().y = a+1;
                           labeldata[a+1][b] = label;
                           copydata[a+1][b] = 255;
                       }
                   }
                   if(b-1>=0)
                   {
                       if(copydata[a][b-1] == 0)
                       {
                           q.push_back(point());
                           q.back().x = b-1;
                           q.back().y = a;
                           labeldata[a][b-1] = label;
                           copydata[a][b-1] = 255;
                       }
                   }
                   q.pop_front();
               }
               copydata[height][width] = 0;
               label = label + 1;
           }
        }
    }

    // converting to binary image
    for(i = 0; i<height; i++)
    {
       for(j=0; j<width; j++)
       {
           if(imagedata[i][j] == 255)
           {
               imagedata[i][j] = 1;
           }
           else
           {
               imagedata[i][j] = 0;
           }
       }
    }

    for(i = 0; i<size; i++)
    {
        for(j = 0; j<size; j++)
        {
            newimagedata1[i][j] = 1;
        }
    }

    //Making an image with just black squares for the puzzles without any protrusion and holes. Here, the top left coordinate of each square
    //puzzle is found
    for(k = 1; k<= label; k++)
    {
        coordx1 = 0;
        coordy1 = 0;
        for(i = 0; i<size; i++)
        {
            for(j = 0; j<size; j++)
            {
                if(labeldata[i][j] == k && labeldata[i][j+1] == k && labeldata[i+1][j] == k && labeldata[i+1][j+1] == k && labeldata[i][j-1] == 0 && labeldata[i+1][j-1] == 0 && labeldata[i-1][j-1] == 0 && labeldata[i-1][j] == 0 && labeldata[i-1][j+1] == 0)
                {
                   coordx1 = j;
                   coordy1 = i;
                   for(m = coordx1; m <= coordx1+45; m++)
                   {
                       for(n = coordy1; n <= coordy1+45; n++)
                       {
                          newimagedata1[n][m] = 0;
                       }
                   }
                }
            }
         }
    }

    //The original image and the square image are XOR'd to get an image containing only the protrusions and holes in the image
    for(i = 0; i<size; i++)
    {
        for(j = 0; j<size; j++)
        {
            newimagedata[i][j] = imagedata[i][j]^newimagedata1[i][j];
        }
    }

    //Defining the protrusion or hole for each side of the puzzle piece in clockwise direction
    for(k = 1; k<= label; k++)
    {
        coordx1 = 0;
        coordy1 = 0;
        for(i = 0; i<size; i++)
        {
            for(j = 0; j<size; j++)
            {
                if(labeldata[i][j] == k && labeldata[i][j+1] == k && labeldata[i+1][j] == k && labeldata[i+1][j+1] == k && labeldata[i][j-1] == 0 && labeldata[i+1][j-1] == 0 && labeldata[i-1][j-1] == 0 && labeldata[i-1][j] == 0 && labeldata[i-1][j+1] == 0)
                {
                   coordx1 = j;
                   coordy1 = i;
                   if(newimagedata[coordy1-5][coordx1+23] == 1)
                   {
                       puzzle[k][0] = 1;
                   }
                   else if(newimagedata[coordy1+5][coordx1+23] == 1)
                   {
                       puzzle[k][0] = 2;
                   }
                   else
                   {
                       puzzle[k][0] = 0;
                   }

                   if(newimagedata[coordy1+23][coordx1+50] == 1)
                   {
                       puzzle[k][1] = 1;
                   }
                   else if(newimagedata[coordy1+23][coordx1+40] == 1)
                   {
                       puzzle[k][1] = 2;
                   }
                   else
                   {
                       puzzle[k][1] = 0;
                   }

                   if(newimagedata[coordy1+40][coordx1+23] == 1)
                   {
                       puzzle[k][2] = 2;
                   }
                   else if(newimagedata[coordy1+50][coordx1+23] == 1)
                   {
                       puzzle[k][2] = 1;
                   }
                   else
                   {
                       puzzle[k][2] = 0;
                   }

                   if(newimagedata[coordy1+23][coordx1+5] == 1)
                   {
                       puzzle[k][3] = 2;
                   }
                   else if(newimagedata[coordy1+23][coordx1-5] == 1)
                   {
                       puzzle[k][3] = 1;
                   }
                   else
                   {
                       puzzle[k][3] = 0;
                   }
                }
            }
        }
    }

    //Defining the protrusion or hole for each side of the puzzle piece in anticlockwise direction
    for(k = 1; k<= label; k++)
    {
        coordx1 = 0;
        coordy1 = 0;
        for(i = 0; i<size; i++)
        {
            for(j = 0; j<size; j++)
            {
                if(labeldata[i][j] == k && labeldata[i][j+1] == k && labeldata[i+1][j] == k && labeldata[i+1][j+1] == k && labeldata[i][j-1] == 0 && labeldata[i+1][j-1] == 0 && labeldata[i-1][j-1] == 0 && labeldata[i-1][j] == 0 && labeldata[i-1][j+1] == 0)
                {
                   coordx1 = j;
                   coordy1 = i;
                   if(newimagedata[coordy1-5][coordx1+23] == 1)
                   {
                       puzzleanti[k][0] = 1;
                   }
                   else if(newimagedata[coordy1+5][coordx1+23] == 1)
                   {
                       puzzleanti[k][0] = 2;
                   }
                   else
                   {
                       puzzleanti[k][0] = 0;
                   }

                   if(newimagedata[coordy1+23][coordx1+50] == 1)
                   {
                       puzzleanti[k][3] = 1;
                   }
                   else if(newimagedata[coordy1+23][coordx1+40] == 1)
                   {
                       puzzleanti[k][3] = 2;
                   }
                   else
                   {
                       puzzleanti[k][3] = 0;
                   }

                   if(newimagedata[coordy1+40][coordx1+23] == 1)
                   {
                       puzzleanti[k][2] = 2;
                   }
                   else if(newimagedata[coordy1+50][coordx1+23] == 1)
                   {
                       puzzleanti[k][2] = 1;
                   }
                   else
                   {
                       puzzleanti[k][2] = 0;
                   }

                   if(newimagedata[coordy1+23][coordx1+5] == 1)
                   {
                       puzzleanti[k][1] = 2;
                   }
                   else if(newimagedata[coordy1+23][coordx1-5] == 1)
                   {
                       puzzleanti[k][1] = 1;
                   }
                   else
                   {
                       puzzleanti[k][1] = 0;
                   }
                }
            }
        }
    }

    count1 = 0;

    //Checking for number of unique pieces
    for(k = 1; k<= label; k++)
    {
        flag = 0;
        num1 = puzzle[k][0]*1000+puzzle[k][1]*100+puzzle[k][2]*10+puzzle[k][3]*1;
        for(i = k+1; i<=label; i++)
        {
            if( num1 == puzzle[i][0]*1000+puzzle[i][1]*100+puzzle[i][2]*10+puzzle[i][3]*1 )
            {
                flag = 1;
                break;
            }
            else if( num1 == puzzle[i][1]*1000+puzzle[i][2]*100+puzzle[i][3]*10+puzzle[i][0]*1 )
            {
                flag = 1;
                break;
            }
            else if( num1 == puzzle[i][2]*1000+puzzle[i][3]*100+puzzle[i][0]*10+puzzle[i][1]*1 )
            {
                flag = 1;
                break;
            }
            else if( num1 == puzzle[i][3]*1000+puzzle[i][0]*100+puzzle[i][1]*10+puzzle[i][2]*1 )
            {
                flag = 1;
                break;
            }
            else if( num1 == puzzleanti[i][0]*1000+puzzleanti[i][1]*100+puzzleanti[i][2]*10+puzzleanti[i][3]*1 )
            {
                flag = 1;
                break;
            }
            else if( num1 == puzzleanti[i][1]*1000+puzzleanti[i][2]*100+puzzleanti[i][3]*10+puzzleanti[i][0]*1 )
            {
                flag = 1;
                break;
            }
            else if( num1 == puzzleanti[i][2]*1000+puzzleanti[i][3]*100+puzzleanti[i][0]*10+puzzleanti[i][1]*1 )
            {
                flag = 1;
                break;
            }
            else if( num1 == puzzleanti[i][3]*1000+puzzleanti[i][0]*100+puzzleanti[i][1]*10+puzzleanti[i][2]*1 )
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            count1 = count1+1;
        }
    }

    cout<<"Number of unique pieces :"<<count1;

    for(i = 0; i<size; i++)
    {
        for(j = 0; j<size; j++)
        {
            newimagedata1[i][j] = newimagedata1[i][j]*255;
        }
    }

    // output the image
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(newimagedata1, sizeof(unsigned char), size*size, file);
    fclose(file);

    return 0;
}











