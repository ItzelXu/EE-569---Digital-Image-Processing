// EE569 Homework Assignment #1
// Date:     February 4, 20018
// Name:     Tamoghna Chattopadhyay
// ID:       8541324935
// email:    tchattop@usc.edu

#include <stdio.h>
#include <math.h>
	{
	{

	// Allocate image data array


	for (int ch = 0; ch <= 2; ch++)
		{
			int sum = 0;
            float mse;
            float psnr_calculation, PSNR;

			for (int i = 0; i < Size; i++)
			{
				for (int j = 0; j < Size; j++)
				{
					sum = sum + pow((int)ImagedataNoise[i][j][ch] - (int)(Imagedata[i][j][ch]), 2);
				}
			}


			mse = (float)sum / (float)(Size*Size);
			psnr_calculation = (float(pow(255, 2)) / mse);
			PSNR = 10 * log10(psnr_calculation);
			if (ch == 0)
				cout << "Channel Red PSNR: " << PSNR << endl;
			if (ch == 1)
				cout << "Channel Green PSNR " << PSNR << endl;
			if (ch == 2)
				cout << "Channel Blue PSNR " << PSNR << endl;

		}

		return 0;
}