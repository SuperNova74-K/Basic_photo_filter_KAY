#include <iostream>
#include <unistd.h> // to make sleep() work
#include <fstream>
#include "bmplib.h"
#include "bmplib.cpp"
#include "filter_group_3.h"
#include "filter_group_1.h"
#include "filter_group_2.h"


using namespace std;

void clear();
void print_options();
void excute_choice(string choice);
string get_choice(vector<string>allowed, int mode, string message);
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
        vector<string>allowed = {"1","2","3","4","5","7","8","9","0","a","c","s","l"};
        // could have done this with regex but I wanted Custom function for easier debugging
        choice = get_choice(allowed,0, "d");
        excute_choice(choice);
        clear();
        if(choice != "0" && choice != "s" && choice != "l"){
            cout << "Filter Applied."<< endl;
            sleep(1.5);
        }else if(choice == "s"){
            cout << "Image saved."<< endl;
            sleep(1.5);
        }
        else if(choice == "l"){
            cout << "Image Loaded."<< endl;
            sleep(1.5);
        }
        else{
            clear();
            cout << "Thanks for using our program!";
            sleep(2);
            return 0;
        }
    } 
}

void clear(){
    system("CLS");
}

void print_options(){
    clear();
    cout << "Please choose one of the follwoing" << endl;
    cout << "Available options:"<< endl;
    cout << "(1) Black & White"<< endl;
    cout << "(2) Invert"<< endl;
    cout << "(3) Merge"<< endl;
    cout << "(4) Flip"<< endl;
    cout << "(5) Darken & Lighten"<< endl;
    cout << "(6) Rotate (Temporarily not available)"<< endl;
    cout << "(7) Detect Edges"<< endl;
    cout << "(8) Enlarge"<< endl;
    cout << "(9) Shrink"<< endl;
    cout << "(a) Mirror 1/2 Image"<< endl;
    cout << "(b) Shuffle (Temporarily not available)"<< endl;
    cout << "(c) Blur"<< endl;
    cout << "(s) Save the image to a file"<< endl;
    cout << "(l) Load img to edit."<< endl;
    cout << "(0) Exit"<< endl;
    cout << "Enter Option:";
}

int find(vector<string>vec, string target){
    for(int i = 0; i < vec.size() ; i++){
        if(vec[i] == target){
            return i;
        }
    }
    return -1;
}


string get_choice(vector<string>allowed, int mode, string message){
    string output;
    while (1)
    {
        if(mode == 0){
            print_options();
        }else{
            cout << message;
        }
        string inpt; 
        getline(cin, inpt);
        int found = find(allowed,inpt);
        if(found != -1){
            output = allowed[found];
            return output;
        }else{
            clear();
            cout << "wrong input, please enter a valid Option." << endl;
        }
    }

}

void excute_choice(string choice){
    clear();
    if(choice == "1"){
        black_white(img);
    }
    if(choice == "2"){
        Invert_img_filter(img);
    }
    else if(choice == "3"){
        load_img(2);
        merge_filter(img, img2);
    }
    else if(choice == "4"){
        vector<string>allowed{"1","2"};
        string option = get_choice(allowed,1,"Choose Mode:\n(1) Horizontal\n(2) Vertical\nChoose an option: ");
        bool style = (option == "1");
        flip(img, style);
    }
    else if(choice == "5"){
        vector<string>allowed{"1","2"};
        string option = get_choice(allowed,1,"Choose Mode:\n(1) Lighten\n(2) Darken\nChoose an option: ");
        bool style = (option == "1");
        darken_n_lighten(img,style);
    }
    // else if(choice == "6"){
    //     rotate
    // }
    else if(choice == "7"){
        edge_detect(img);
    }
    else if(choice == "8"){
        vector<string>allowed{"1","2","3","4"};
        string option = get_choice(allowed,1,"Choose the qraurter you want to enlarge:\n(1) First quarter\n(2) Second quarter\n(3) Third quarter\n(4) Fourth quarter\nChoose an option: ");
        enlarge_img_filter(img, option);
    }
    else if(choice == "9"){
        vector<string>allowed{"1","2","3"};
        string option = get_choice(allowed,1,"Choose Mode:\n(1) 1/2\n(2) 1/3\n(3) 1/4\nChoose an option: ");
        shrink_img(img, stoi(option) + 1);
    }
    else if(choice == "a"){
        vector<string>allowed{"1","2","3","4"};
        string option = get_choice(allowed,1,"Choose the part to mirror:\n(1) lower\n(2) upper\n(3) right\n(4) Left\nChoose an option: ");
        mirror(img, option);
    }
    // else if(choice == "b"){
    //     Shuffle
    // }
    else if(choice == "c"){
        blur_img(img);
    }
    else if(choice == "s"){
        strt_of_Zloop:
        while(true){
            clear();
            cout << "Please write the Target file name\n{\\/:*?\"<>|} characters are not allowed: ";
            string option = "";
            getline(cin, option);

            vector<string> not_allowed{"\\", "/", ":", "*", "?", "\"", "<", ">", "|"};
            for(auto i : option){
                string tmp_to_chnge_chr_2_strng;
                tmp_to_chnge_chr_2_strng += i;
                if((find(not_allowed, tmp_to_chnge_chr_2_strng) != -1) || option.size() > 254){
                    clear();
                    cout << "This filename is not allowed !";
                    sleep(5);
                    clear();
                    option.clear();
                    cin.clear();
                    goto strt_of_Zloop;

                }
            }


            option += ".bmp";
            ifstream exist;
            exist.open(option);
            char *option_as_C_string = new char [option.length()+1];
            strcpy(option_as_C_string, option.c_str());
            if(exist){
                cout << "This file already exists, ARE YOU SURE you want to OVERWRITE it ? type (YES) for yes, anything else for no :";
                string overwrite;
                getline(cin, overwrite);
                if(overwrite == "YES"){
                    writeGSBMP(option_as_C_string, img);
                    delete[] option_as_C_string;
                    break;
                }
                else {
                    cout << "File was not overwriten, enter any key to re-enter the target name...";
                    string temp; getline(cin, temp);
                    clear();
                    goto strt_of_Zloop;
                }
            }else{
                writeGSBMP(option_as_C_string, img);
                delete[] option_as_C_string;
                break;
            }
        }
    }
    else if(choice == "l"){
        clear();
        load_img(1);
    }
    
}

void load_img(int pic_number){
    if(pic_number == 1){
        char inpt[100];
        do{
        cout << "Please enter the name of the photo you would like to edit: ";
        cin.getline(inpt,100);
        strcat(inpt,".bmp");
        clear();
        }
        while(readGSBMP(inpt, img) == 1);
    }else{
        char inpt[100];
        do{
        cout << "Please enter the name of the second photo: ";
        cin.getline(inpt,100);
        strcat(inpt,".bmp");
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