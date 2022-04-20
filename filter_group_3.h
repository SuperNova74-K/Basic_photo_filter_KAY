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
    // creating a new img to not to mess up the old one
    unsigned char sml_img[SIZE][SIZE][RGB];
    
    //loop over rows with increment equal to dneo (to skip some rows thus reducing resolution) 
    for (int i = 0; i < SIZE ; i += deno)
    {
        // loop over pixels in row with incrememnt deno (to skip some pixels ot reduce resolution)
        for(int j = 0; j < SIZE ; j += deno){
            // pixel 3,3 in the original will be 1,1 in the sml_img so we basically divide by the deno (3 in this case)
            // to get the corresponding pixel 

            for(int color = 0; color < 3 ; color++){
                sml_img[i / deno][j / deno][color] = img[i][j][color];
            }
        }
    }
    // looping normally to copy the sml img into a small part of the original img
    // while in the same time changing the rest of the image to white.
    for (int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE ; j++){
            // if the loop is out of reach of the sml_img then make the pixel white
            if(i >= SIZE / deno || j >= SIZE / deno){
                for(int color = 0; color < 3 ; color++){
                    img[i][j][color] = 255;
                }
            }else{
                for(int color = 0; color < 3 ; color++){
                    img[i][j][color] = sml_img[i][j][color];
                }
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