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


#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H