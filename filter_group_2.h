//Nmae : Youssef Mohamed Salah Eldin Anwar
// ID : 20210483
//

#ifndef BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H
#define BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H

#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H



 void ShuffleImageFilter()
{
    int order[4]{0};
    int num1{0}, num2{0};
    int quarterNum;
    cout << "enter which quater number do you want : ";
    bool loopAgain = true;
    while (loopAgain)
    {
        loopAgain = false;
        cin >> order[0] >> order[1] >> order[2] >> order[3];
        for (int i = 0; i < 4; i++)
        {
            if (order[i] > 4 || order[i] < 1)
            {
                loopAgain = true;
            }
        }

        for (int i = 0; i < 4; i++)
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
            cout << "Enter a valid input" << endl;
        }
    }
    for (int i = 0; i < SIZE / 2; i++)
    {
        for (int j = 0; j < SIZE / 2; j++)
        {


            if (order[0] == 1)
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
            image2[i][j] = image[i + num1][j + num2];
            if (order[2] == 1)
            {
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
            image2[i + 127][j] = image[i + num1][j + num2];
            if (order[1] == 1)
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
            image2[i][j + 127] = image[i + num1][j + num2];
            if (order[3] == 1)
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
            image2[i + 127][j + 127] = image[i + num1][j + num2];
        }
    }
}

 .......
 void   RotateImage( )
{


 int degree = 0;
    cout<<" enter degree : " ;
    cin>>degree;
   if (degree == 90)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j <  SIZE ; j++)
        {
            image2[i][j] = image[j][255 - i];

        }

        }
        }
    else if (degree == 180)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
            image2[i][j] = image[SIZE - i][SIZE - j];
            }
        }
    }
    else if (degree == 270)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image2[i][j] = image[SIZE - j][i];
            }
        }
    }
}







 .................
 /* void Enlarge Image Filter( ) {
        int num1 = 0 ;
     int num2 = 0 ;
      int quarterNum;
    cout <<"enter which quater number do you want : " << endl;
    cout<<"1-TOP Left"<<endl;
     cout<<"2-TOP Right"<<endl;
     cout<<"3-Down Left"<<endl;
      cout<<"4-Down Right"<<endl;
       cin>> quarterNum;
        while(true){
        if (quarterNum == 1){
                num1 = num2 = 0;
                break;
                }
         else if (quarterNum ==2){
         num2 = 127;
         break;
}
       else if (quarterNum ==3){
        num1 = 127;
        break;
}
        else if (quarterNum ==4){
            num1 = num2 = 127;
            break;

}
else if (!isdigit(quarterNum)){

            cout<<"please enter 1 or 2 or 3 or 4" << endl;
            cin>>quarterNum;
continue;

}
        else {
            cout<<"please enter 1 or 2 or 3 or 4" << endl;
            cin>>quarterNum;
            continue;
            }

        }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
            image2 [i][j] = image[ i/2 + num1][j/2 + num2];
    }
  }
}
........
void Invert Image Filter (){
image [i][j] = 255 - image [i][j]
}



