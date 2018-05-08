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

class image
{

public:
    int size1,size2,BytesPerPixel;
    unsigned char * Image1 = new unsigned char [1000000l];
    float * Image = new float [10000000];
    image();//default constructor
    image(int x,int y, int z); //parameterized constructor
    ~image(); //destructor


    unsigned char * readfile( char*[],int,int,int,int);
    unsigned char * MemAlloc(int,int,int);
    void writefile( char*[],unsigned char *,int,int,int,int);
    void print(float **,int,int,int,int);
    float ** conv1D2D(float *,int,int,int);
    double feature_ext(unsigned char *, float *,int);
    float *filter_segment(unsigned char *,int,int,int,int);
    float energy(float *,int,int,int,int,int,int,int);
};

image :: image() {}; //default constructor

image :: image(int x,int y,int z)
{
    //parameterized constructor
    size1=y;
    size2=x;
    BytesPerPixel=z;
}

image :: ~image()
{
    //destructor
}

unsigned char * image::MemAlloc(int size1,int size2,int BytesPerPixel)
{
    unsigned char * ImagePointer=new unsigned char [size1*size2*BytesPerPixel];
    return ImagePointer;

}

unsigned char * image::readfile( char *argv[],int index,int size1,int size2,int BytesPerPixel)
{
    FILE *file;
    unsigned char *Image=MemAlloc(size1,size2,BytesPerPixel);
    if (!(file=fopen(argv[index],"rb"))) {
        std::cout << "Cannot open file: " << argv[index] <<std::endl;
        exit(1);
    }
    fread(Image, sizeof(unsigned char), size1*size2*BytesPerPixel, file);
    fclose(file);
    return Image;
}

float **image:: conv1D2D(float * feature_vector, int size1,int size2,int h)
{
    float** f_vector = new float*[size1*size2];

    for(int i = 0; i < size1*size2; ++i)
    {
        f_vector[i] = new float[h];
    }

    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size2;j++)
        {
            for(int f=0;f<h;f++)
            {
                f_vector[((i*size2)+j)][f]=feature_vector[((i*size2)+j)*h + f];
            }
        }
    }
    return f_vector;
}

void image:: print(float **f_vector,int size1,int size2,int BytesPerPixel,int f)
{
    std::cout<<"\tThe feature vectors are:"<<std::endl;

    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size2;j++)
        {
            std::cout<<"Pixel: "<<(i*size2)+j;
            for(int h=0;h<f;h++)
            {
                std::cout<<"\t"<<f_vector[((i*size2)+j)][h];
            }
            std::cout<<std::endl;
        }
    }
}

//pixel value calculation
double image:: feature_ext(unsigned char *image, float *filter,int op)
{
    double pixel_value=0.0;
    switch(op)
    {
        case 1:
        {
            for (int i=0;i<25;i++)
            {
                pixel_value = pixel_value + (image[i]*filter[i]);
            }
            break;
        }
        case 2:
        {
            for (int i=0;i<9;i++)
            {
                pixel_value = pixel_value + (image[i]*filter[i]);
            }
            break;
        }
    }
    return pixel_value;
}

float *image::filter_segment(unsigned char *image,int size1,int size2,int BytesPerPixel,int op)
{
    float *temp = new float [size1*size2*BytesPerPixel];
    unsigned char image_arr[9]={0};
    int x=0,p=0,q=0;
    for(int rgb=0;rgb<BytesPerPixel;rgb++)
    {
        for (int i=0;i<size1;i++)
        {
            for(int j=0;j<size2;j++)
            {
                x=0;
                for(int m=i-1;m<=i+1;m++)
                {
                    for(int n=j-1;n<=j+1;n++)
                    {
                        if(m<0)
                        {
                            p=abs(m);
                        }
                        else if(m>=size1)
                        {
                            int pp=m-(size1-1);
                            p=(size1-1)-pp;
                        }
                        else
                        {
                            p=m;
                        }

                        if(n<0)
                        {
                            q=abs(n);
                        }
                        else if(n>=size2)
                        {
                            int qq=n-(size2-1);
                            q=(size2-1)-qq;
                        }
                        else
                        {
                            q=n;
                        }
                        image_arr[x++]=image[((p*size2)+q)*BytesPerPixel +rgb];
                    }
                }
                switch(op)
                {
                    case 1:
                    {
                        float filter[9]={1.0/4,0,1.0/4,0,0,0,-1.0/4,0,1.0/4};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                    case 2:
                    {
                        float filter[9]={1.0/4,0,-1.0/4,-2.0/4,0,2.0/4,1.0/4,0,-1.0/4};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                    case 3:
                    {
                        float filter[9]={-1.0/12,0,1.0/12,-2.0/12,0,2.0/12,-1.0/12,0,1.0/12};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                    case 4:
                    {
                        float filter[9]={1.0/4,-2.0/4,-1.0/4,0,0,0,-1.0/4,2.0/4,1.0/4};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                    case 5:
                    {
                        float filter[9]={1.0/4,-2.0/4,-1.0/4,-2.0/4,4.0/4,2.0/4,-1.0/4,2.0/4,1.0/4};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                    case 6:
                    {
                        float filter[9]={1.0/12,-2.0/12,-1.0/12,-2.0/12,4.0/12,2.0/12,-1.0/12,2.0/12,1.0/12};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                    case 7:
                    {
                        float filter[9]={-1.0/12,-2.0/12,-1.0/12,0,0,0,1.0/12,2.0/12,1.0/12};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                    case 8:
                    {
                        float filter[9]={-1.0/12,-2.0/12,-1.0/12,2.0/12,4.0/12,2.0/12,-1.0/12,-2.0/12,-1.0/12};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                    case 9:
                    {
                        float filter[9]={1.0/36,2.0/36,1.0/36,2.0/36,4.0/36,2.0/36,-1.0/36,-2.0/36,-1.0/36};
                        temp[((i*size2)+j)*BytesPerPixel +rgb] = feature_ext(image_arr, filter,2);
                        break;
                    }
                }
            }
        }
    }
    return temp;
}

float image:: energy(float * temp,int size1,int size2,int i, int j,int ByterPerPixel,int w,int f)
{
    int p=0,q=0;
    float average=0.0;

    for(int m=i-w;m<=i+w;m++)
    {
        for(int n=j-w;n<=j+w;n++)
        {
            if(m<0)
            {
               p=abs(m);
            }
            else if(m>=size1)
            {
                int pp=m-(size1-1);
                p=(size1-1)-pp;
            }
            else
            {
                p=m;
            }

            if(n<0)
            {
                q=abs(n);
            }
            else if(n>=size2)
            {
                int qq=n-(size2-1);
                q=(size2-1)-qq;
            }
            else
            {
                q=n;
            }

            average = average + pow(temp[((p*size2)+q)*ByterPerPixel],2);
        }
    }
    average = average/pow(((2*w)+1),2);
    return average;
}

using namespace std;

int main(int argc, char *argv[])
{
    FILE* file;

    int size1 = 600;
    int size2 = 450;
    int BytesPerPixel = 1;
	int i, j, f, im=1, window=6;;

	image object1(size1,size2,BytesPerPixel);
    image ob[9],object_op[9];

    for(i=0;i<12;i++)
    {
        //copying attributes to each object
        ob[i]=object1;
        object_op[i]=object1;
    }

    //for calculating the feature vector
    float *feature_vector = new float [size1*size2*9];
    //using feature vector for k-means calculation
    float** f_vector = new float*[size1*size2];

    for(int i = 0; i < size1*size2; ++i)
    {
        f_vector[i] = new float[9];
    }

    unsigned char* ImageData = new unsigned char[size1*size2*BytesPerPixel];
    if (!(file=fopen(argv[1],"rb")))
    {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(ImageData, sizeof(unsigned char), size1*size2*BytesPerPixel, file);
    fclose(file);
    cout << "File " << argv[1] << " has been read successfully! " << endl;



    for(f=0;f<9;f++)
    {
        ob[f].Image=ob[f].filter_segment(ImageData,object1.size1,object1.size2,object1.BytesPerPixel,f+1);

        for(i=0;i<object1.size1;i++)
        {
            for(j=0;j<object1.size2;j++)
            {
                feature_vector[((i*ob[f].size2)+j)*9 + f]= ob[f].energy(ob[f].Image,ob[f].size1,ob[f].size2,i,j,object1.BytesPerPixel,window,f);
            }
        }
    }

    f_vector=object1.conv1D2D(feature_vector,object1.size1,object1.size2,9);
    object1.print(f_vector,object1.size1,object1.size2,object1.BytesPerPixel,9);

    return 0;
}
