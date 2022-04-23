//Nmae : Youssef Mohamed Salah Eldin Anwar
// ID : 20210483

#ifdef _WIN32
    bool is_os_win_filter2 = true;
#else
    bool is_os_win_filter2 = false;
#endif


#ifndef BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H
#define BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H

#include <regex>

void clear_terminal(){
    if(is_os_win_filter2){
        system("CLS");
    }else{
        system("clear");
    }
}

void shuffle_img(unsigned char img[][SIZE][RGB])
{
    unsigned char img2[SIZE][SIZE][RGB];
    retake_input:

    int order[4];  //array to store input
    int num1{0}, num2{0};
    
    regex regex_filter("[1-4]{4}");
    string order_inpt;
    do{    
        cout << "Enter the quarter's order : ";
        getline(cin, order_inpt);
        for(int i = 0; i < order_inpt.length() - 1; i++){    //remove spaces between numbers
            if(order_inpt[i] == ' '){
                order_inpt.erase(i,1);
                i--;
            }
        }
        if(!regex_match(order_inpt ,regex_filter)){     //checks if input is valid or not ( from 1 to 4 )
            cout << endl <<"Invalid 546 input !" << endl;
            sleep(1);
            clear_terminal();
        }
    }while(!regex_match(order_inpt ,regex_filter));

    int order_number = stoi(order_inpt);

    for(int i = 0; i <= 3; i++){
        order[3-i] = order_number % 10;
        order_number /= 10;
    } 
    
    bool loopAgain = true;
    while (loopAgain)
    {
        loopAgain = false;

        for (int i = 0; i < 4; i++)    // nested loop to check if any number os repeated or not
        {
            for (int j = 0; j < 4; j++)
            {
                if ((order[j] == order[i]) && i != j)
                {
                    loopAgain = true;
                }
            }
        }
        
        if (loopAgain)
        {
            cout << "Invalid Input !" << endl;
            sleep(1);
            clear_terminal();
            goto retake_input;
        }
    }
                              // num1 and num2 value change according to the chosen quarter
    
    for (int i = 0; i < 129; i++)
    {
        for (int j = 0; j < 129; j++)
        {
            for (int k = 0; k < RGB; k++) {               

                if (order[0] == 1)                   // Four IF Conditions check which quarter  is chosen to be  top left in the New Image
                {
                    num1 = num2 = 0;
                }
                else if (order[0] == 2)
                {
                    num1 = 0;
                    num2 = 127;
                }
                else if (order[0] == 3)
                {
                    num1 = 127;
                    num2 = 0;
                }
                else if (order[0] == 4)
                {
                    num1 = num2 = 127;
                }

                img2[i][j][k] = img[i + num1][j + num2][k];
                
                if (order[2] == 1)      // Four IF Conditions check which quarter is chosen to be on Down left in the New Image  
                    num1 = num2 = 0;
                }
                else if (order[2] == 2)
                {
                    num1 = 0;
                    num2 = 127;
                }
                else if (order[2] == 3)
                {
                    num1 = 127;
                    num2 = 0;
                }
                else if (order[2] == 4)
                {
                    num1 = num2 = 127;
                }

                img2[i + 127][j][k] = img[i + num1][j + num2][k];

                if (order[1] == 1)   // Four IF Conditions check which quater is chosen to be on the top Right in the New image
                {
                    num1 = num2 = 0;
                }
                else if (order[1] == 2)
                {
                    num1 = 0;
                    num2 = 127;
                }
                else if (order[1] == 3)
                {
                    num1 = 127;
                    num2 = 0;
                }
                else if (order[1] == 4)
                {
                    num1 = num2 = 127;
                }

                img2[i][j + 127][k] = img[i + num1][j + num2][k];

                if (order[3] == 1)    // Four IF Conditions check which quarter is chosen to be down Right in the New image
                {
                    num1 = num2 = 0;
                }
                else if (order[3] == 2)
                {
                    num1 = 0;
                    num2 = 127;
                }
                else if (order[3] == 3)
                {
                    num1 = 127;
                    num2 = 0;
                }
                else if (order[3] == 4)
                {
                    num1 = num2 = 127;
                }
                
                img2[i + 127][j + 127][k] = img[i + num1][j + num2][k];

            }
        }
    }



    for (int i = 0; i < SIZE; i++)   //copies which is done by the filter to image1 
    {
        for (int j = 0; j < SIZE; j++)
        {
             for (int k = 0; k < RGB; k++)
             {
                img[i][j][k] = img2[i][j][k];
             }
        }
    }

}


void enlarge(unsigned char img[][SIZE][RGB] ,int quarter_num)
{
    unsigned char img2[SIZE][SIZE][RGB];
    int num1 = 0 ;
    int num2 = 0 ;

    if (quarter_num == 1){   // num1 and num2 value change according to the chosen quarter
        num1 = num2 = 0;
    }
    else if (quarter_num ==2){
        num2 = 127;
    }
    else if (quarter_num ==3){
        num1 = 127;
    }
    else if (quarter_num ==4){
        num1 = num2 = 127;
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k< RGB; k++)
            {
              img2 [i][j][k] = img[ i/2 + num1][j/2 + num2][k]; //Equation to perform Enlarge filter
            }
        }
    }


    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
             for (int k = 0; k < RGB; k++)
             {
                img[i][j][k] = img2[i][j][k];   //copies which is done by the filter to image1
             }
        }
    }

}


void rotate_img(unsigned char img[][SIZE][RGB] ,string degree)
{

   unsigned char img2[SIZE][SIZE][RGB];

   if (degree == "1")
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j <  SIZE ; j++)
            {
                for(int k = 0; k <  RGB ; k++)
                {
                    img2[i][j][k] = img[j][255 - i][k];   //Equation to rotate the image by 90 deg.
                }
            }
        }
    }

    else if (degree == "2")
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    img2[i][j][k] = img[SIZE - i][SIZE - j][k];   //Equation to rotate the image by 180 deg.
                }
            }
        }
    }

    else if (degree == "3")
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                 for (int k = 0; k < RGB; k++){
                    img2[i][j][k] = img[SIZE - j][i][k];  //Equation to rotate the image by 270 deg.
                 }
            }
        }
    }


    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)  //copies which is done by the filter to image1 
        {
             for (int k = 0; k < RGB; k++)
             {
                img[i][j][k] = img2[i][j][k];
             }
        }
    }

}


void invert(unsigned char img[][SIZE][RGB])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k< RGB; k++) {
                img[i][j][k] = 255 - img [i][j][k];   //Equation to perfrom Invert Filter
            }
        }
    }
}


#endif
