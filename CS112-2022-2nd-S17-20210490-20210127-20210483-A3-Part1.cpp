/*
    CS112 : Structured Programming Assignment 3 - First Submission
    
    Authors:
    Khaled Waleed Salah , ID: 20210127
    Abdelrahman Wael Mohammed Hanafy , ID: 20210490
    Youssef Mohamed Salah Eldin Anwar , ID: 20210483 

    Prepared for : Dr.Mohammed El-Ramly , TA: Hager Ali
    Purpose : Photo Editor with multiple filters
    Date : 7 April 2022

    Version : 1.2
    Scheduled Features : - Filter 6 & Filter B
                         - Undo option
                         - Display photo
                         - Colorful theme for the Terminal / CMD
                         - Fixing Clear() Function to work with Mac & Linux
*/




#include <iostream>
#include <unistd.h> // to make sleep() work
#include <vector>
#include <fstream>
#include "bmplib.h"
#include "bmplib.cpp"
#include "filter_group_3.h"
#include "filter_group_1.h"
#include "filter_group_2.h"


using namespace std;

// funcitons prototypes
void clear(); // to clear terminal for an elegant application
void print_options(); // printing the main menu options
void excute_choice(string choice); // to excute user choice

// this is the most important funciton, takes a vecotr of all allowed strings and a mode to determine what message to print
// and finally a message for the user
string get_choice(vector<string>allowed, int mode, string message);


void load_img(int pic_number);
int find(vector<string>vec, string target); // searches about a string in a vector of strings

unsigned char img[SIZE][SIZE]; // declaring global img
unsigned char img2[SIZE][SIZE]; // declaring second global img for some filters to work





int main(){
    cout << "Hello To Our Photo Editor!";
    sleep(1.5);
    clear();
    load_img(1);
    string choice = "random"; // random intialization

    // keep asking untill the user wants to exit
    while(choice != "0"){
        vector<string>allowed = {"1","2","3","4","5","7","8","9","0","a","c","s","l"}; // this is a vector of all acceptable inputs
        // could have done this with regex but we wanted Custom function for easier debugging
        
        choice = get_choice(allowed,0, "d"); // getting the user choice using the fuction 
        excute_choice(choice);
        clear();

        // to tell user about the success of the operation
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
        // if it survived all of this that means it's difinelty zero, so we exit the program
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
    // looping over the vecotr to search for the target
    for(int i = 0; i < vec.size() ; i++){
        if(vec[i] == target){
            // if target found, return it's index
            return i;
        }
    }
    // if it survived till here then return -1 to indicate it's not found
    return -1;
}


string get_choice(vector<string>allowed, int mode, string message){
    string output;
    while (1)
    {
        // if mode is zero then print the main menu, else print the message provided
        if(mode == 0){
            print_options();
        }else{
            cout << message;
        }
        string inpt; 
        getline(cin, inpt);
        int found = find(allowed,inpt);
        if(found != -1){
            // if the input was found in the allowed input then retun that input
            output = allowed[found];
            return output;
        }else{
            // if it's not the case then give the user a message
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
        // in this example we give allowed inputs "1" and "2" to the get_choice function as well as a message to input
        // for the user and that funcitons does the defense for us and return only a good value.
        vector<string>allowed{"1","2"};
        string option = get_choice(allowed,1,"Choose Mode:\n(1) Horizontal\n(2) Vertical\nChoose an option: ");
        bool style = (option == "1");
        flip(img, style); // feeding the filter the info needed to work
    }
    else if(choice == "5"){
        vector<string>allowed{"1","2"};
        string option = get_choice(allowed,1,"Choose Mode:\n(1) Lighten\n(2) Darken\nChoose an option: ");
        bool style = (option == "1");
        darken_n_lighten(img,style);
    }
    // we haven't done the filter 6 yet (will be done after the mid-terms)
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
    // else if(choice == "b"){ // we haven't done this filter yet, scheduled after the mid-terms
    //     Shuffle
    // }
    else if(choice == "c"){
        blur_img(img);
    }
    // to save the image
    else if(choice == "s"){
        strt_of_Zloop: // a flag to be able to jumb here when needed
        while(true){
            clear();
            cout << "Please write the Target file name\n{\\/:*?\"<>|} characters are not allowed: ";
            string option = "";
            getline(cin, option);

            // some special characters are not allowed in naming of files in windows so we prevent the user form messing the file
            vector<string> not_allowed{"\\", "/", ":", "*", "?", "\"", "<", ">", "|"};
            for(auto i : option){
                // here we convert the char into a string to be able to pass it in the find() without function overloading
                string tmp_to_chnge_chr_2_strng;
                tmp_to_chnge_chr_2_strng += i;

                // if any character in the input is not allowed, reject the output and the filename cannot be more than 254 character
                // to prevent windows rejecting the file
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

            // if filename was valid, we add the extention name
            option += ".bmp";

            // this part is to check if the file exists and asking if the user is sure about overwriting it
            ifstream exist;
            exist.open(option);

            // the function writeGSBMP that came with the library only supports the filename as C-String
            // while we get the input form user as String Class for easier I/O so we make a copy of the string
            // and turn that copy to C-string usin dynamic memory allocation
            char *option_as_C_string = new char [option.length()+1];
            strcpy(option_as_C_string, option.c_str());


            if(exist){
                cout << "This file already exists, ARE YOU SURE you want to OVERWRITE it ? type (YES) for yes, anything else for no :";
                string overwrite;
                getline(cin, overwrite);
                if(overwrite == "YES"){
                    writeGSBMP(option_as_C_string, img);
                    delete[] option_as_C_string; // deleting the C-string to avoid memory leak
                    break;
                }
                else {
                    cout << "File was not overwriten, enter any key to re-enter the target name...";
                    string temp; getline(cin, temp);
                    clear();
                    goto strt_of_Zloop;
                }
            }else{
                // if everything goes well we save the file
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
        // the maximum filename size on windows is 255 character, so the user won't find a picture with a name bigger than that anyways
        char inpt[255];
        do{
        cout << "Please enter the name of the photo you would like to edit: ";
        cin.getline(inpt,255);
        strcat(inpt,".bmp");
        clear();
        }
        // we keep trying to get input untill the readGSBMP funciton returns anything else than 1 (which means file exists and valid)
        while(readGSBMP(inpt, img) == 1);
    }else{
        char inpt[255];
        do{
        cout << "Please enter the name of the second photo: ";
        cin.getline(inpt,255);
        strcat(inpt,".bmp");
        clear();
        }
        while(readGSBMP(inpt, img2) == 1);
    }
}
