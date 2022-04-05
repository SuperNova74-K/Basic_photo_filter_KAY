//Nmae : Youssef Mohamed Salah Eldin Anwar
// ID : 20210483
//

#ifndef BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H
#define BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H

#endif //BASIC_PHOTO_FILTER_KAY_FILTER_GROUP_2_H
void Enlarge Image Filter( ) {
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
void Invert Image Filter (){
image [i][j] = 255 - image [i][j]
}



