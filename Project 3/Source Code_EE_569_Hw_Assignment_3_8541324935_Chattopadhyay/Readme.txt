EE 569 Homework Assignment 3
// Date:     March 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

Compiled on CodeBlocks with gcc compiler
Run the codes in command line or powershare as given inside the files.
Operating System: Windows 10

Format of writing in Powershell:
 \.program_name input_image.raw output_image.raw [BytesPerPixel = 3]

Set BytesPerpixel if dealing with RGB image. If you leave it blank, it will be considered as grayscale image.

The Python codes were compiled on Anaconda on Spyder - Python 3.2 GUI.
The Matlab codes were compiled on Matlab R2017a

Additionally, Piotr's Matlab Toolbox (version 3.26 or later) is also required. It can be downloaded at:
https://pdollar.github.io/toolbox/.

Add edge detection code to Matlab path (change to current directory first): // For all folders in the toolboxs
>> addpath(pwd); savepath;

For question3, first download and install opencv into Annaconda. This can be done by typing on Annaconda command prompt:
conda install opencv

For Bag of words;
On Annaconda command prompt:
Training the classifier : python findFeatures.py -t dataset/train/
Testing the classifier: python getClass.py -t dataset/test --visualize

If you get any library missing error, then install that library to Annaconda.