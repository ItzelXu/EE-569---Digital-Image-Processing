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

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;

    int size1 = 480;
    int size2 = 640;
    // Allocate image data array
    unsigned char imagedata[size1][size2];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(imagedata, sizeof(unsigned char), size1*size2, file);
    fclose(file);

    int i;
    int count1 = 0;
    int count2 = 0;
    int height, width, a, b;
    int freq[200] = {0};

    for(height = 0; height<size1; height++)
    {
       for(width = 0; width<size2; width++)
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

    for(height = 0; height<size1; height++)
    {
        for(width = 0; width<size2; width++)
        {
           if(imagedata[height][width] == 255)
           {
               count2 = 0;
               deque<point> q;
               q.clear();

               //Initialization
               q.push_back(point());
               q.back().y = height;
               q.back().x = width;
               imagedata[height][width] = 0;
               count2 = count2 + 1;

               //Loop
               while(!q.empty())
               {
                   a = q.front().y;
                   b = q.front().x;

                   if(b+1<size2)
                   {
                       if(imagedata[a][b+1] == 255)
                       {
                           q.push_back(point());
                           q.back().x = b+1;
                           q.back().y = a;
                           imagedata[a][b+1] = 0;
                           count2 = count2 + 1;
                       }
                   }
                   if(a-1>=0)
                   {
                       if(imagedata[a-1][b] == 255)
                       {
                           q.push_back(point());
                           q.back().x = b;
                           q.back().y = a-1;
                           imagedata[a-1][b] = 0;
                           count2 = count2 + 1;
                       }
                   }
                   if(a+1<size1)
                   {
                       if(imagedata[a+1][b] == 255)
                       {
                           q.push_back(point());
                           q.back().x = b;
                           q.back().y = a+1;
                           imagedata[a+1][b] = 0;
                           count2 = count2 + 1;
                       }
                   }
                   if(b-1>=0)
                   {
                       if(imagedata[a][b-1] == 255)
                       {
                           q.push_back(point());
                           q.back().x = b-1;
                           q.back().y = a;
                           imagedata[a][b-1] = 0;
                           count2 = count2 + 1;
                       }
                   }
                   q.pop_front();
               }
               count1 = count1+1;
               imagedata[height][width] = 255;
               freq[count2] = freq[count2] + 1;
               //cout<<count1<<" "<<count2<<endl;
           }
        }
    }

    cout<< "The number of stars :"<<count1<<endl;

    for(i=0; i<200; i++)
    {
        cout<<freq[i]<< ", "<<endl;
    }

    // Write image data (filename specified by fourth argument) from image data matrix
	if (!(file=fopen(argv[2],"wb"))) {    cout << "Cannot open file: " << argv[2] << endl;    exit(1);	}	fwrite(imagedata, sizeof(unsigned char), size1*size2, file);	fclose(file);

	return 0 ;
}

