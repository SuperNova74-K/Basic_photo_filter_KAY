// FCI � Programming 1 � 2022 - Assignment 3 
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
unsigned char newImage[SIZE][SIZE];


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


//mirror filter
void mirror(string style) //a parameter that tells what style to do (lower or upper or left or right)
{


    if (style == "lower") //or any thing else (you can change it to fit the final code) 
    {
        //only half the rows
        for (int i = 0; i < (SIZE / 2); i++)
        {
            for (int j = 0; j < (SIZE); j++)
            {
                image[i][j] = image[255 - i][j]; //make the upper half the flip of the lower half
            }
        }
    }
    else if (style == "upper") //or any thing else (you can change it to fit the final code) 
    {
        //only half the rows
        for (int i = 0; i < (SIZE / 2); i++)
        {
            for (int j = 0; j < (SIZE); j++)
            {
                image[255 - i][j] = image[i][j]; //make the lower half the flip of the upper half 
            }
        }
    }
    else if (style == "right") //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++) //only half the columns
            {

                image[i][j] = image[i][255 - j]; //make the left half the flip of the right half

            }
        }
    }
    else if (style == "left") //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++) //only half the columns
            {

                image[i][255 - j] = image[i][j]; //make the right half the flip of the left half

            }
        }
    }

}


//edge detection filter
void edge_detect()
{
    int avrege = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            newImage[i][j] = 255;
            avrege += image[i][j];
        }
    }

    avrege = avrege / (256 * 256); //clculating the avrege of pixels color
    int value = avrege / 4; //we are comparing each pixel value with this value to determine if its an edge or not


    for (int i = 1; i < SIZE - 1; i++) //"SIZE-1" is to avoid looping at the edges which can cause out of range error
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            if ( //checking all the 8 pixels around each pixel 
                (image[i + 1][j] - image[i][j]) > value || (image[i - 1][j] - image[i][j]) > value || (image[i][j + 1] - image[i][j]) > value ||
                (image[i][j - 1] - image[i][j]) > value || (image[i + 1][j + 1] - image[i][j]) > value || (image[i - 1][j - 1] - image[i][j]) > value ||
                (image[i + 1][j - 1] - image[i][j]) > value || (image[i - 1][j + 1] - image[i][j]) > value
                )
            {
                newImage[i][j] = 0; //if the diffrence between them is greater than the value then its an edge
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = newImage[i][j]; //coping into the orignal image
        }
    }
}


#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H