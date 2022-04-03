// FCI – Programming 1 – 2022 - Assignment 3 
// Program Name: smallest ID filters.cpp
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Abdelrahman Wael Mohammed Hanafy - ID:20210490
// Teaching Assistant: Hager Ali
// Purpose:


#ifndef BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H
#define BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

//image 2D array
unsigned char image[SIZE][SIZE];


//Black and White filter
void black_white()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] >= 128) //if it's closer to white then make it white 
            {
                image[i][j] = 255;
            }
            else //if it's closer to black then make it black
            {
                image[i][j] = 0;
            }
        }

    }
}


//flip filter
void flip(string style) //a parameter that tells what style to do (horizontal or virtical)
{
    int temp;

    if (style == "horizontal") //or any thing else (you can change it to fit the final code) 
    {
        //we only swap half the image with the other half so I make it SIZE/2
        //if it was SIZE it will return to be the orignal image
        for (int i = 0; i < (SIZE / 2); i++)
        {
            for (int j = 0; j < (SIZE); j++)
            {
                //swaping 2 numbers
                temp = image[i][j];
                image[i][j] = image[255 - i][j];
                image[255 - i][j] = temp;
            }
        }
    }
    else if (style == "virtical") //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++)
            {
                //swaping 2 numbers
                temp = image[i][j];
                image[i][j] = image[i][255 - j];
                image[i][255 - j] = temp;
            }
        }
    }

}


#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H