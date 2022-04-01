//
// 
//

#ifndef BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_3_H
#define BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_3_H


void merge_filter(unsigned char img1[][SIZE], unsigned char img2[][SIZE]){
    for (int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < 256 ; j++){
            img1[i][j] = (img1[i][j] + img2[i][j]) / 2;
        }
    }
}


void darken_n_lighten(unsigned char img[][SIZE], bool mode){
    float ratio;
    (mode) ? ratio = 1.5 : ratio = 0.5;

    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE ; j++){
            int new_value = (float(img[i][j]) * ratio);
            if(new_value > 255){
                new_value = 255;
            }else if (new_value < 0){
                new_value = 0;
            }
            img[i][j] = (unsigned char) new_value;
        }
    }        
}




#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_3_H


