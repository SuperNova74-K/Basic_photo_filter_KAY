#ifndef BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_3_H
#define BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_3_H

#include<cmath>
#include<algorithm>


void merge_filter(unsigned char img1[][SIZE][RGB], unsigned char img2[][SIZE][RGB]){
    // looping over every pixel
    for (int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE ; j++){
            // adding the values of the pixel form first photo and the pixel form second photo and getting their average
            // storing that average to the first image that we later save to the pc.
            for(int color = 0; color < 3 ; color++){
                img1[i][j][color] = (img1[i][j][color] + img2[i][j][color]) / 2;
            }
        }
    }
}


void darken_n_lighten(unsigned char img[][SIZE][RGB], bool mode){
    float ratio;
    // if the mode is true then we lighten the image by multiplying it's values by 1.5
    // if the mode is false we darken the image by multiplying it's value by 0.5
    (mode) ? ratio = 1.5 : ratio = 0.5;

    for (int i = 0; i < SIZE; i++){

        for(int j = 0; j < SIZE ; j++){

            for(int color = 0; color < 3 ; color++){

                // for every pixel we multiply by the ratio.
                int new_value = (float(img[i][j][color]) * ratio);

                // in case a pixel was 200 for eg. when we multiply it it turns into 300 which is out of range
                // so we bring them down to the maximum limit. 
                if(new_value > 255){
                    new_value = 255;
                }

                // we then change the pixel's value to the new value.
                img[i][j][color] = (unsigned char) new_value;
            }
        }
    }        
}


void shrink_img(unsigned char img[][SIZE][RGB], int deno){
    // this algoritm works by taking the average of a number of pixels equal to the square of the deno (denumerator of 1/2)
    // so for example if you want to shrink by 1/3 then the deno is 3 and you take a 3*3 square of pixels starting top left by the pixel you are trying to reach
    //              /  *  *
    //              *  *  *
    //              *  *  *  
    // the slash pixel (in the figure) is the pixel we are currently at and we take the average of every channel (reg-green-blue) of every pixel in 3 * 3 matrix starting
    // top-left from the pixel wanted
    // then we skip number of pixels equal to deno (to shrink properly).... 
    // basiaclly we are taking big squares in the original img and turning them into small pixels in the original by taking average of values. 

    // i+=deno to skip pixels in the original and loop only on the start of big squares, same thing with the j
    // and the condidtion is to avoid getting out of boundry of the original img
    for(int i = 0; i  + deno < SIZE;  i+=deno){
        for(int j = 0; j + deno < SIZE;  j+=deno)
        {
            // zero-ing the sum every pixel to avoid messing up the values.
            int sum_red = 0, sum_green = 0, sum_blue = 0;
            int n_pixels = 0;
            

            // when we find a starting pixel of a big square (like the slash pixel above) we loop over the whole square to take average
            // those loops are to loop inside of the big squares (conditions are adjusted to avoid getting out of the boundry)
            for(int k = i     ; k + 1 < SIZE && k < deno + i;  k++){
                for(int n = j ; n + 1 < SIZE && n < deno + j;  n++){

                    sum_red   += img[k][n][0];
                    sum_green += img[k][n][1];
                    sum_blue  += img[k][n][2];
                    // the pixel in the last row for example will only have 2 pixels to take average for so the number of pixels vary thus to
                    // calcute average properly we count them to later divide by their number
                    n_pixels ++;
                }
            }
            
            // assging the average to the small pixel in the original image
            // i/deno access is to put the pixels next to each other in the original pixel (since i & j can only point to a start of a big square)
            img[i/deno][j/deno][0] = (unsigned char) (round(sum_red / n_pixels));
            img[i/deno][j/deno][1] = (unsigned char) (round(sum_green / n_pixels));
            img[i/deno][j/deno][2] = (unsigned char) (round(sum_blue / n_pixels));
            
            // we then take the sum of all of these pixel and devide by 10 to get the average
            // store the average in the pixel in the new picture.
                
        }
    }

    // those for loops are to turn the rest of the pixels in the original image white
    // the initial value of the i & j depends on deno, if deno is even is diffirent from odd so we use trinary operator
    for(int i = 0; i < SIZE; i++){
        for(int j = (deno % 2 == 1) ? SIZE / deno : (SIZE / deno) - 1; j < SIZE; j++)
        {
            for(int color = 0; color < 3 ; color++)
            {
                    img[i][j][color] = 255;
            }
        }
    }
    for(int i = (deno % 2 == 1) ? SIZE / deno : (SIZE / deno) - 1; i < SIZE; i++){
        for(int j = 0; j <= SIZE / deno; j++)
        {
            for(int color = 0; color < 3 ; color++)
            {
                    img[i][j][color] = 255;
            }
        }
    }
}


void blur_img(unsigned char img[][SIZE][RGB]){
// THIS FILTER IS BASED ON THE GUSSIAN BLUR TECHNIQUE.

    // making a copy of the picture to avoid progressive (and wrong) blur
    unsigned char alt_img[SIZE][SIZE][RGB];

    // to copy the original picture into the alternative picture
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for(int color = 0; color < 3 ; color++)
            {
                    alt_img[i][j][color] = img[i][j][color];
            }
        }
    }
    

    int sum = 0;
    int n_pixels;
    // for every pixel in the alt image
    // add the values of the pixel itself and the 8 pixels around it to a value called sum.
    for(int i = 0; i < SIZE;  i++){
        for(int j = 0; j < SIZE;  j++)
        {
            for(int color = 0; color < 3 ; color++)
            {
                // zero-ing the sum every pixel to avoid messing up the values.
                sum = 0;

                n_pixels = 1; // n_pixels is a counter for pixels so we can later calculate the average properly (it's set to a one since it can't be less than one)

                // the following if statments are there to make sure that we dont'...
                // get out of range (you cannot take the pixel up left if you are already at the top left)
                // so we avoid out of index range by defining the ability to take the pixel based on the current
                // pixel location, if the if statment survived then we take the corrisponding pixel, if it doesn't
                // the we protected our program form meesing up the memory or crashing. 

                // Note: I am using (!) alot because I want to make it readable
                // the right(and faster) way to do it is using !(a == b || c == d) === a!=b && c!=d (DeMorgan's law)

                // top left
                if(!(i == 0 || j == 0)){
                    sum += alt_img[i-1][j-1][color];
                    n_pixels++;
                }

                // directly top
                if(!(i == 0)){
                    sum += alt_img[i-1][j][color];
                    n_pixels++;
                }


                //top right
                if(!(i == 0 || j == 255)){
                    sum += alt_img[i-1][j+1][color];
                    n_pixels++;
                }

                // left
                if(!(j == 0)){
                    sum += alt_img[i][j-1][color];
                    n_pixels++;
                }

                // the pixel itself must be present no matter what pixel you are at.
                sum += alt_img[i][j][color];


                // right
                if(!(j == 255)){
                    sum += alt_img[i][j+1][color];
                    n_pixels++;
                }

                //bottom left
                if(!(i == 255 || j == 0)){
                    sum += alt_img[i+1][j-1][color];
                    n_pixels++;
                }

                //directly below
                if(!(i == 255)){
                    sum += alt_img[i+1][j][color];
                    n_pixels++;
                }

                // bottom right
                if(!(j == 255 || i == 255)){
                    sum += alt_img[i+1][j+1][color];
                    n_pixels++;
                }

                // we then take the sum of all of these pixel and devide by 10 to get the average
                // store the average in the pixel in the new picture.
                img[i][j][color] = (unsigned char) (round(sum / n_pixels)); 
            }
        }
    }
}


#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_3_H