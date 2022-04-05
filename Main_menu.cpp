#include <bits/stdc++.h>
#include <unistd.h> // to make sleep() work
#include <fstream>
#include "bmplib.h"
#include "bmplib.cpp"
#include "filter_group_3.h"
#include "filter_group_1.h"


using namespace std;

void clear();
void print_options();
void excute_choice(string choice);
string get_choice(string allowed);
void load_img(int pic_number);
int find(vector<string>vec, string target);

unsigned char img[SIZE][SIZE];
unsigned char img2[SIZE][SIZE];

int main(){
    cout << "Hello To Our Photoshop!";
    sleep(1.5);
    clear();
    load_img(1);
    string choice = "random";
    while(choice != "0"){
        print_options();
        vector<string>allowed = {"1","2","3","4","5","6","7","8","9","0","a","b","c","s"};
        // could have done this with regex but I wanted Custom function for easier debugging
        choice = get_choice(allowed);
        excute_choice(choice);
        clear();
        if(choice != "0"){
            cout << "Filter Applied.";
            sleep(1.5);
        }else{
            clear();
            cout << "Thanks for using our program.";
            return 0;
        }
    }
    
}

void clear(){
    system("CLS");
}

void print_options(){
    cout << "Please choose one of the follwoing" << endl;
    cout << "Available options:"<< endl;
    cout << "(1) Black & White"<< endl;
    cout << "(2) Invert"<< endl;
    cout << "(3) Merge"<< endl;
    cout << "(4) Flip";
    cout << "(5) Darken & Lighten"<< endl;
    cout << "(6) Rotate"<< endl;
    cout << "(7) Detect Edges"<< endl;
    cout << "(8) Enlarge"<< endl;
    cout << "(9) Shrink"<< endl;
    cout << "(a) Mirror 1/2 Image"<< endl;
    cout << "(b) Shuffle"<< endl;
    cout << "(c) Blur"<< endl;
    cout << "(s) Save the image to a file"<< endl;
    cout << "(0) Exit"<< endl;
}

int find(vector<string>vec, string target){
    for(int i = 0; i < vec.size() ; i++){
        if(vec[i] == target){
            return i;
        }
    }
    return -1;
}


string get_choice(vector<string>allowed)){
    string output;
    while (1)
    {
        cout << "Please enter option: ";
        string inpt; 
        getline(cin, inpt);
        // while((getchar()) != '\n');
        int found = find(allowed,inpt);
        if(found != -1){
            output = allowed[found];
            return output;
        }else{
            clear();
            cout << "wrong input, please enter a valid Option.";
            sleep(1);
            clear();
            print_options();
        }
    }

}

void excute_choice(string choice){
    clear();
    if(choice == "1"){
        black_white(img);
    }
    // Waiting for Anwar
    // if(choice == "2"){
    //     invert(img);
    // }
    else if(choice == "3"){
        load_img(2);
        merge_filter(img, img2);
    }
    else if(choice == "4"){
        cout << "Choose Mode:\n(1) Horizontal\n(2) Vertical" << endl;
        vector<string>allowed = {"1","2"};
        string option = get_choice(allowed);
        bool style = (option == "1") ? true : false;
        flip(img, style);
    }
    else if(choice == "5"){
        cout << "Choose Mode:\n(1) Lighten\n(2) Darken" << endl;
        vector<string>allowed = {"1","2"};
        string option = get_choice(allowed);
        bool style = (option == "1") ? true : false;
        darken_n_lighten(img,style);
    }
    // else if(choice == "6"){
    //     rotate
    // }
    else if(choice == "7"){
        edge_detect(img);
    }
    // else if(choice == "8"){
    //     enlarge
    // }
    else if(choice == "9"){
        cout << "Choose Mode:\n(1) 1/2\n(2) 1/3\n(3) 1/4" << endl;
        vector<string>allowed = {"1","2","3"};
        string option = get_choice(allowed);
        shrink_img(img, option + 1);
    }
    else if(choice == "a"){
        cout << "Choose Mode:\n(1) 1/2\n(2) 1/3\n(3) 1/4" << endl;
        vector<string>allowed = {"1","2","3","4"};
        string option = get_choice(allowed);
        mirror(img, allowed);
    }
    // else if(choice == "b"){
    //     Shuffle
    // }
    else if(choice == "c"){
        blur_img(img);
    }
    else if(choice == "s"){
        clear();
        cout << "Please write the Target file name\nNo special characters allowed\n(IF THE FILE EXISTS, IT WILL BE OVERWRITTEN !): ";
        string option;
        getline(cin, option);

    }
    
}

void load_img(int pic_number){
    if(pic_number == 1){
        char inpt[100];
        do{
        cout << "Please enter the name of the photo you would like to edit: ";
        cin.getline(inpt,100);
        strcat(inpt,".bmp");
        while((getchar()) != '\n');
        clear();
        }
        while(readGSBMP(inpt, img) == 1);
    }else{
        char inpt[100];
        do{
        cout << "Please enter the name of the second photo: ";
        cin.getline(inpt,100);
        strcat(inpt,".bmp");
        while((getchar()) != '\n');
        clear();
        }
        while(readGSBMP(inpt, img2) == 1);
    }
}

// needed functions:
/*
clear function
printing options
function for printing message and getting input, while also validating it
function for excuting the filter
function for changing the loaded image
funcition for loading image

*/

/*
Program goes like this:

print message for the user
take and validate input
excute
*/