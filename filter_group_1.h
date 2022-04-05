// FCI � Programming 1 � 2022 - Assignment 3 
// Program Name: smallest ID filters.cpp
// Last Modification Date: xx/xx/xxxx
// Author1 and ID and Group: Abdelrahman Wael Mohammed Hanafy - ID:20210490
// Teaching Assistant: Hager Ali
// Purpose:


#ifndef BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H
#define BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H


// #include <iostream>
// #include <fstream>
// #include <cstring>
// #include <cmath>
// #include "bmplib.cpp"

using namespace std;

//image 2D array
// unsigned char image[SIZE][SIZE];
// unsigned char new_image[SIZE][SIZE];


//Black and White filter
void black_white(unsigned char img[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (img[i][j] >= 128) //if it's closer to white then make it white 
            {
                img[i][j] = 255;
            }
            else //if it's closer to black then make it black
            {
                img[i][j] = 0;
            }
        }

    }
}


//flip filter
void flip(unsigned char img[SIZE][SIZE], bool style) //a parameter that tells what style to do (horizontal or virtical)
{
    int temp;

    if (style == true) //or any thing else (you can change it to fit the final code) 
    {
        //we only swap half the image with the other half so I make it SIZE/2
        //if it was SIZE it will return to be the orignal image
        for (int i = 0; i < (SIZE / 2); i++)
        {
            for (int j = 0; j < (SIZE); j++)
            {
                //swaping 2 numbers
                temp = img[i][j];
                img[i][j] = img[255 - i][j];
                img[255 - i][j] = temp;
            }
        }
    }
    else if (style == false) //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++)
            {
                //swaping 2 numbers
                temp = img[i][j];
                img[i][j] = img[i][255 - j];
                img[i][255 - j] = temp;
            }
        }
    }

}


//mirror filter
void mirror(unsigned char img[SIZE][SIZE] ,string style) //a parameter that tells what style to do (lower or upper or left or right)
{
    /*
        Style menu:
        lower = 1;
        upper = 2;
        right = 3;
        left = 4;
    */


    if (style == "1") //or any thing else (you can change it to fit the final code) 
    {
        //only half the rows
        for (int i = 0; i < (SIZE / 2); i++)
        {
            for (int j = 0; j < (SIZE); j++)
            {
                img[i][j] = img[255 - i][j]; //make the upper half the flip of the lower half
            }
        }
    }
    else if (style == "2") //or any thing else (you can change it to fit the final code) 
    {
        //only half the rows
        for (int i = 0; i < (SIZE / 2); i++)
        {
            for (int j = 0; j < (SIZE); j++)
            {
                img[255 - i][j] = img[i][j]; //make the lower half the flip of the upper half 
            }
        }
    }
    else if (style == "3") //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++) //only half the columns
            {

                img[i][j] = img[i][255 - j]; //make the left half the flip of the right half

            }
        }
    }
    else if (style == "4") //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++) //only half the columns
            {

                img[i][255 - j] = img[i][j]; //make the right half the flip of the left half

            }
        }
    }

}


//edge detection filter
void edge_detect(unsigned char img[SIZE][SIZE])
{
    int avrege = 0;
    unsigned char new_image[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            new_image[i][j] = 255;
            avrege += img[i][j];
        }
    }

    avrege = avrege / (256 * 256); //clculating the avrege of pixels color
    int value = avrege / 4; //we are comparing each pixel value with this value to determine if its an edge or not


    for (int i = 1; i < SIZE - 1; i++) //"SIZE-1" is to avoid looping at the edges which can cause out of range error
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            if ( //checking all the 8 pixels around each pixel 
                (img[i + 1][j] - img[i][j]) > value || (img[i - 1][j] - img[i][j]) > value || (img[i][j + 1] - img[i][j]) > value ||
                (img[i][j - 1] - img[i][j]) > value || (img[i + 1][j + 1] - img[i][j]) > value || (img[i - 1][j - 1] - img[i][j]) > value ||
                (img[i + 1][j - 1] - img[i][j]) > value || (img[i - 1][j + 1] - img[i][j]) > value
                )
            {
                new_image[i][j] = 0; //if the diffrence between them is greater than the value then its an edge
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            img[i][j] = new_image[i][j]; //coping into the orignal image
        }
    }
}


#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H