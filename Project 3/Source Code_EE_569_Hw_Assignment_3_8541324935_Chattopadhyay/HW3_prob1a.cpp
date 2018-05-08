// EE569 Homework Assignment #3
// Date:     March 7, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{

    FILE* file;

    int size = 128;
    int BytesPerPixel = 1;
    int x = 2;
    int ImgHeightNew = size + 2 * x;
	int ImgWidthNew = size + 2 * x;
	int m, y, k, i, j, p, X, Y, itr, q;
	double sum, avg;

	float filter[3][5] = {
	                  {-1.0/6,-2.0/6,0,2.0/6,1.0/6},
                      {-1.0/4,0,2.0/4,0,-1.0/4},
                      {-1.0/6,2.0/6,0,-2.0/6,1.0/6}
                    };

    // 9 laws filter
    float law[9][25];

    unsigned char* ImageData = new unsigned char[size*size*BytesPerPixel];
    unsigned char* ImageDataOp = new unsigned char[ImgHeightNew*ImgWidthNew*BytesPerPixel];

    float featureVector[12][9] = {0};

    double* temp = new double [size*size*BytesPerPixel];

    for(m = 0 ; m < 12 ; m++)
    {
        char filename[20]={0};
        sprintf(filename,"texture%d.raw",m+1);

        if (!(file=fopen(filename,"rb")))
        {
             cout << "Cannot open file: " << filename <<endl;
		     exit(1);
        }
        fread(ImageData, sizeof(unsigned char), size*size*BytesPerPixel, file);
        fclose(file);
	    cout << "File " << filename << " has been read successfully! " << endl;

	    for (y = 0 ; y < 9 ; y++)
        {
            for(k = 0 ; k < BytesPerPixel ; k++)
            {
                //center
                for (i = 0 ; i < size ; i++)
                {
                    for (j = 0 ; j < size ; j++)
                    {
                        ImageDataOp[BytesPerPixel*((i+x)*ImgWidthNew+j+x)+k] = ImageData[BytesPerPixel*(i*size+j)+ k];
                    }
                }

                //top and bottom rows
                for (p = 0 ; p < x ; p++)
                {
                    for (j = 0 ; j < size ; j++)
                    {
                        ImageDataOp[BytesPerPixel*(p*ImgWidthNew+j+x)+k] = ImageData[BytesPerPixel*j+ k];
                        ImageDataOp[BytesPerPixel*((ImgHeightNew - p - 1)*ImgWidthNew+j+x)+k] = ImageData[BytesPerPixel*((size-1)*size+j)+ k];
                    }
                }

                //left and right columns
                for (p = 0 ; p < x ; p++)
                {
                    for (i = 0 ; i < ImgHeightNew ; i++)
                    {
                        ImageDataOp[BytesPerPixel*((i)*ImgWidthNew+p)+k] = ImageDataOp[BytesPerPixel*(i*ImgWidthNew+x)+ k];
                        ImageDataOp[BytesPerPixel*((i)*ImgWidthNew+(ImgWidthNew -p - 1))+k] = ImageDataOp[BytesPerPixel*(i*ImgWidthNew+(size - 1))+ k];
                    }
                }
            }

            for(i = 0 ; i < 3 ; i++)
            {
                for(j = 0 ; j < 3 ; j++)
                {
                    for(p = 0 ; p < 5 ; p++)
                    {
                        for(q = 0 ; q < 5 ; q++)
                        {
                            law[i*3+j][p*5+q] = filter[i][p]*filter[j][q];
                        }
                    }
                }
            }

            for(k = 0 ; k < BytesPerPixel; k++)
            {
                for(i = 0 ; i < size ; i++)
                {
                    for(j = 0 ; j < size ; j++)
                    {

                        sum = 0;
                        for(p = -x ; p <= x ; p++)
                        {
                            for(q = -x ; q <= x ; q++)
                            {
                                X = x + p;
                                Y = x + q;
                                sum += (double)ImageDataOp[BytesPerPixel*((i+X)*ImgWidthNew+j+Y)+k] * law[y][X*5+Y];
                            }
                        }
                        temp[BytesPerPixel*(i*size+j)+k] = sum;
                    }
                }
            }

            avg = 0;
            for(i = 0 ; i < size ; i++)
            {
                for(j = 0 ; j < size ; j++)
                {
                    avg += temp[i*size+j]*temp[i*size+j];
                }
            }
            avg /= size*size;
            featureVector[m][y] = avg;
        }
    }

    // Find min and max of feature vector
    double Min = featureVector[0][0];
    double Max = featureVector[0][0];
    for(i = 0 ; i < 12 ; i++)
    {
        for(j = 0 ; j < 9 ; j++)
        {
            if(featureVector[i][j] > Max)
            {
                Max = featureVector[i][j];
            }
            if(featureVector[i][j] < Min)
            {
                Min = featureVector[i][j];
            }

        }
    }

    for(i=0; i<12; i++)
    {
        for(j=0; j<9; j++)
        {
            featureVector[i][j] = ((featureVector[i][j]-Min)/(Max-Min));
        }
    }

    for(i=0; i<12; i++)
    {
        for(j=0; j<9; j++)
        {
            cout<<featureVector[i][j]<<","<<" ";
        }
        cout<<endl;
    }

    int labels[12] = {0};
    //int oldLabels[12] = {0};
    double centers[4][9] = {0};
    double newCenters[4][9] = {0};
    srand (time(NULL));

    for(y = 0 ; y < 9 ; y++)
    {
        centers[0][y] = featureVector[0][y];
        centers[1][y] = featureVector[1][y];
        centers[2][y] = featureVector[2][y];
        centers[3][y] = featureVector[7][y];
    }

    for(itr = 0 ; itr < 200 ; itr++)
    {
        int cnt[4] = {0} ;
        for(i = 0 ; i < 12 ; i++)
        {
            double dist[4] = {0};
            for(k = 0 ; k < 4 ; k++)
            {
                for(j = 0 ; j < 9 ; j++)
                {
                    dist[k] += sqrt((centers[k][j] - featureVector[i][j])*(centers[k][j] - featureVector[i][j])) ;
                }
            }

            double D = min(dist[0], min(dist[1], min(dist[2], dist[3])));

            if(D == dist[0])
            {
                for(j = 0 ; j < 9 ; j++)
                    newCenters[0][j] += featureVector[i][j];
                cnt[0]++;
                labels[i] = 0;
            }
            if(D == dist[1])
            {
                for(j = 0 ; j < 9 ; j++)
                    newCenters[1][j] += featureVector[i][j];
                cnt[1]++;
                labels[i] = 1;
            }
            if(D == dist[2])
            {
                for(j = 0 ; j < 9 ; j++)
                    newCenters[2][j] += featureVector[i][j];
                cnt[2]++;
                labels[i] = 2;
            }
            if(D == dist[3])
            {
                for(j = 0 ; j < 9 ; j++)
                    newCenters[3][j] += featureVector[i][j];
                cnt[3]++;
                labels[i] = 3;
            }
        }
        int cntr = 0;

        for(x =  0 ; x < 4 ; x++)
        {
            for(y = 0 ; y < 9 ; y++)
            {
                newCenters[x][y] /= cnt[x];
                if(newCenters[x][y] == centers[x][y])
                    cntr++;
                centers[x][y] = newCenters[x][y];
                newCenters[x][y] = 0 ;
            }
        }
        if(cntr == 36)
            break;
    }

    cout<<"\nFinal Class Labels:"<<endl;

    cout<<"Images belong to Class 1: ";
    for(j = 0 ; j < 12 ; j++)
    {
        if(labels[j] == 0)
            cout<<j+1<<" ";
    }
    cout<<endl;
    cout<<"Images belong to Class 2: ";
    for(j = 0 ; j < 12 ; j++)
    {
        if(labels[j] == 1)
            cout<<j+1<<" ";
    }
    cout<<endl;
    cout<<"Images belong to Class 3: ";
    for(j = 0 ; j < 12 ; j++)
    {
        if(labels[j] == 2)
            cout<<j+1<<" ";
    }
    cout<<endl;
    cout<<"Images belong to Class 4: ";
    for(j = 0 ; j < 12 ; j++)
    {
        if(labels[j] == 3)
            cout<<j+1<<" ";
    }
    cout<<endl;
    delete temp;
    delete ImageDataOp;
    delete ImageData;
    return 0;
}




