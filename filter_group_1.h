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

// img 2D array
// unsigned char img[SIZE][SIZE];
// unsigned char new_image[SIZE][SIZE];


//Black and White filter
void black_white(unsigned char img[SIZE][SIZE][RGB])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int red = img[i][j][0]; //the red value
            int green = img[i][j][1]; // the green value
            int blue = img[i][j][2]; // the blue value

            //"sqrt((red*red) + (green*green) + (blue*blue)" an equation I found on the internet to tell if a color is light or dark
            if (sqrt((red * red) + (green * green) + (blue * blue)) > 200) //if this condition is correct then the color is a light color
            {
                //making each pixel white
                img[i][j][0] = 255;
                img[i][j][1] = 255;
                img[i][j][2] = 255;
            }
            else //else its a dark color
            {
                //making each pixel black
                img[i][j][0] = 0;
                img[i][j][1] = 0;
                img[i][j][2] = 0;
            }
        }
    }
}


//flip filter
void flip(unsigned char img[SIZE][SIZE][RGB], bool style) //a parameter that tells what style to do (horizontal or virtical)
{
    int temp;

    if (style == true) //or any thing else (you can change it to fit the final code) 
    {
        //we only swap half the img with the other half so I make it SIZE/2
        //if it was SIZE it will return to be the orignal img
        for (int i = 0; i < (SIZE / 2); i++)
        {
            for (int j = 0; j < (SIZE); j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    //swaping 2 numbers
                    temp = img[i][j][k];
                    img[i][j][k] = img[255 - i][j][k];
                    img[255 - i][j][k] = temp;
                }
            }
        }
    }
    else if (style == false) //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    //swaping 2 numbers
                    temp = img[i][j][k];
                    img[i][j][k] = img[i][255 - j][k];
                    img[i][255 - j][k] = temp;
                }
            }
        }
    }

}


//mirror filter
void mirror(unsigned char img[SIZE][SIZE][RGB] ,string style) //a parameter that tells what style to do (lower or upper or left or right)
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
                for (int k = 0; k < 3; k++)
                {
                    img[i][j][k] = img[255 - i][j][k]; //make the upper half the flip of the lower half
                }
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
                for (int k = 0; k < 3; k++)
                {
                    img[255 - i][j][k] = img[i][j][k]; //make the lower half the flip of the upper half 
                }
            }
        }
    }
    else if (style == "3") //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++) //only half the columns
            {
                for (int k = 0; k < 3; k++)
                {
                    img[i][j][k] = img[i][255 - j][k]; //make the left half the flip of the right half
                }
            }
        }
    }
    else if (style == "4") //or any thing else (you can change it to fit the final code)
    {
        for (int i = 0; i < (SIZE); i++)
        {
            for (int j = 0; j < (SIZE / 2); j++) //only half the columns
            {
                for (int k = 0; k < 3; k++)
                {
                    img[i][255 - j][k] = img[i][j][k]; //make the right half the flip of the left half
                }
            }
        }
    }

}


//edge detection filter
void edge_detect(unsigned char img[SIZE][SIZE][RGB])
{
    int avrege_r = 0;
    int avrege_g = 0;
    int avrege_b = 0;
    unsigned char new_image[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            //coloring the img white
            new_image[i][j][0] = 255;
            new_image[i][j][1] = 255;
            new_image[i][j][2] = 255;

            //calculating the avrege or red, green and blue
            avrege_r += img[i][j][0];
            avrege_g += img[i][j][1];
            avrege_b += img[i][j][2];
        }
    }

    avrege_r = avrege_r / (256 * 256); //clculating the avrege of red pixels
    avrege_g = avrege_g / (256 * 256); //clculating the avrege of green pixels
    avrege_b = avrege_b / (256 * 256); //clculating the avrege of blue pixels


    //the value that I'm comparing with is (sum of every avrege/4) / 3
    int value = ((avrege_r / 4) + (avrege_g / 4) + (avrege_b / 4)) / 3;


    for (int i = 1; i < SIZE - 1; i++) //"SIZE-1" is to avoid looping at the edges which can cause out of range error
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            //calculating the avrege of the colors (red, green and blue) of every pixel around the current pixel
            int current = (img[i][j][0] + img[i][j][1] + img[i][j][2]) / 3;
            int top = (img[i + 1][j][0] + img[i + 1][j][1] + img[i + 1][j][2]) / 3;
            int bottom = (img[i - 1][j][0] + img[i - 1][j][1] + img[i - 1][j][2]) / 3;
            int right = (img[i][j + 1][0] + img[i][j + 1][1] + img[i][j + 1][2]) / 3;
            int left = (img[i][j - 1][0] + img[i][j - 1][1] + img[i][j - 1][2]) / 3;
            int top_right = (img[i + 1][j + 1][0] + img[i + 1][j + 1][1] + img[i + 1][j + 1][2]) / 3;
            int top_left = (img[i + 1][j - 1][0] + img[i + 1][j - 1][1] + img[i + 1][j - 1][2]) / 3;
            int bottom_right = (img[i - 1][j + 1][0] + img[i - 1][j + 1][1] + img[i - 1][j + 1][2]) / 3;
            int bottom_left = (img[i - 1][j - 1][0] + img[i - 1][j - 1][1] + img[i - 1][j - 1][2]) / 3;

            if ( //checking the difference between all 8 pixels around the current pixel and the current pixel then compare it with the value calculated before
                (top - current) > value || (bottom - current) > value || (right - current) > value ||
                (left - current) > value || (top_right - current) > value || (bottom_left - current) > value ||
                (top_left - current) > value || (bottom_right - current) > value
                )
            {
                new_image[i][j][0] = 0; //if the diffrence between them is greater than the value then its an edge
                new_image[i][j][1] = 0;
                new_image[i][j][2] = 0;
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                img[i][j][k] = new_image[i][j][k]; //coping into the orignal img
            }
        }
    }
}


#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_1_H