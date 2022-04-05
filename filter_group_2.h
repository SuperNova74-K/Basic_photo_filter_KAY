//Nmae : Youssef Mohamed Salah Eldin Anwar
// ID : 20210483
//

#ifndef BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H
#define BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H


void enlarge_img_filter(unsigned char img[][256], string quarterNum){
        int num1 = 0 ;
        int num2 = 0 ;
        unsigned char img2[256][256];
        while(true){
                if (quarterNum == "1"){
                        num1 = num2 = 0;
                        break;
                }
                else if (quarterNum =="2"){
                        num2 = 127;
                        break;
                }
                else if (quarterNum =="3"){
                        num1 = 127;
                        break;
                }
                else if (quarterNum =="4"){
                        num1 = num2 = 127;
                        break;

                }
                // else if (!isdigit(quarterNum)){
                //         cout<<"please enter 1 or 2 or 3 or 4" << endl;
                //         cin>>quarterNum;
                //         continue;
                // }
                // else {
                //         cout<<"please enter 1 or 2 or 3 or 4" << endl;
                //         cin>>quarterNum;
                //         continue;
                // }
        }

        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                        img2 [i][j] = img[ i/2 + num1][j/2 + num2];
                }
        }
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                        img [i][j] = img2[i][j];
                }
        }
}


void Invert_img_filter (unsigned char img[][256]){
        for (int i = 0; i < 256; i++)
        {
                for (int j = 0; j < 256; j++)
                {
                        img [i][j] = 255 - img [i][j];
                }
        }
}

#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H