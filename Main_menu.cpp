/*
    CS112 : Structured Programming Assignment 3 - First Submission
    
    Authors:
    Khaled Waleed Salah , ID: 20210127
    (hanafy write here your name and id as well as youssef's)


    Prepared for : Dr.Mohammed El-Ramly , TA: Hager (write her second name hanafy)
    Purpose : Photo Editor with multiple filters
    Date : 7 April 2022

    Version : 1.5
    Scheduled Features : - Filter 6 & Filter B           needs integration with the main menu
                         - Undo option                   work on progress
                         - Display photo
                         - Colorful theme for the Terminal / CMD   # DONE.... windows only but still compatible with other os
                         - Fixing Clear() Function to work with Mac & Linux        # done
                         - Adding more defensive regarding target file naming (last character must not be space)            # Done
*/


#include <iostream>
#include <unistd.h> // to make sleep() work
#include <fstream>
#include <filesystem>
#include <vector>
#include "bmplib.h"
#include "bmplib.cpp"
#include "filter_group_3.h"
#include "filter_group_1.h"
#include "filter_group_2.h"

using namespace std;

#ifdef _WIN32
    bool is_os_win = true;
#else
    bool is_os_win = false;
#endif



// funcitons prototypes

void clear(); // to clear terminal for an elegant application
void print_options(); // printing the main menu options
void excute_choice(string choice); // to excute user choice

// this is the most important funciton, takes a vecotr of all allowed strings and a mode to determine what message to print
// and finally a message for the user
string get_choice(vector<string>allowed, int mode, string message);


void load_img(int pic_number);
int find(vector<string>vec, string target); // searches about a string in a vector of strings

bool is_colored(string filename);
bool can_open_file(string filename);
void save_file(char *option_as_C_string);
void undo();


unsigned char img[SIZE][SIZE][RGB]; // declaring global colored img
unsigned char img2[SIZE][SIZE][RGB]; // declaring second global img for some filters to work
unsigned char img_undo[SIZE][SIZE][RGB]; // to later use the undo option


unsigned char img_GS[SIZE][SIZE]; // same thing for greyscale
unsigned char img2_GS[SIZE][SIZE];
unsigned char img_GS_undo[SIZE][SIZE];

bool is_current_colored;


int main(){
    char *color = "COLOR 07";
    char *color2 = "COLOR fa";
    clear();
    cout << "Hello To Our Photo Editor!" << endl;
    sleep(1);
    if(is_os_win){
        cout << "Please choose a color for the program !"<< endl;
        vector<string>allowed{"1","2","3","4"};
        string option = get_choice(allowed,1,"Choose from:\n(1) Pink & White (the best)\n(2) Blue & White\n(3) Aqua & Black\n(4) Default Console (boring)\nChoose an option: ");
        if(option == "1"){
            color = "COLOR fc";
            color2 = "COLOR fa"; 
        }else if(option == "2"){
            color = "COLOR f1";
            color2 = "COLOR fa";
        }else if(option == "3"){
            color = "COLOR 0b";
            color2 = "COLOR 0a";
        }else{
            color2 = "COLOR 0a";
        }
        system(color);
    }
    clear();
    load_img(1);


    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                img_undo[i][j][k] = img[i][j][k];
            }
            
        }
        
    }
    

    string choice = "dummy"; // random intialization

    // keep asking untill the user wants to exit
    while(choice != "0"){
        vector<string>allowed = {"1","2","3","4","5","6","7","8","9","0","a","b","c","s","l","u"}; // this is a vector of all acceptable inputs
        // could have done this with regex but we wanted Custom function for easier debugging
        
        choice = get_choice(allowed,0, "d"); // getting the user choice using the fuction 
        excute_choice(choice);
        clear();

        // to tell user about the success of the operation
        if(choice != "0" && choice != "s" && choice != "l" && choice != "u"){
            
            if(is_os_win){system(color2);}
            cout << "Filter Applied."<< endl;
            sleep(1.5);
            if(is_os_win){system(color);}

        }else if(choice == "s"){

            if(is_os_win){system(color2);}
            cout << "Image saved."<< endl;
            sleep(1.5);
            if(is_os_win){system(color);}
        }
        else if(choice == "l"){
            if(is_os_win){system(color2);}
            cout << "Image Loaded."<< endl;
            sleep(1.5);
            if(is_os_win){system(color);}
        }
        else if(choice == "u"){
            if(is_os_win){system(color2);}
            cout << "Changes were reverted. (only on step)"<< endl;
            sleep(2);
            if(is_os_win){system(color);}
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
    if(is_os_win){
        system("CLS");
    }else{
        system("clear");
    }
}

bool is_colored(string filename){
    // this function is called when we already know that the file exists so no need to check
    if(std::filesystem::file_size(filename) > 70000){
        return true;
    }else{
        return false;
    }
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
    cout << "(6) Rotate"<< endl;
    cout << "(7) Detect Edges"<< endl;
    cout << "(8) Enlarge"<< endl;
    cout << "(9) Shrink"<< endl;
    cout << "(a) Mirror 1/2 Image"<< endl;
    cout << "(b) Shuffle"<< endl;
    cout << "(c) Blur"<< endl;
    cout << "(u) Undo (only one step)"<< endl;    
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
        invert(img);
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
    else if(choice == "6"){
        vector<string>allowed{"1","2","3"};
        string option = get_choice(allowed,1,"Choose a degree to rotate by:\n(1) 90\n(2) 180\n(3) 270\nChoose an option: ");
        rotate_img(img, stoi(option));
    }
    else if(choice == "7"){
        edge_detect(img);
    }
    else if(choice == "8"){
        vector<string>allowed{"1","2","3","4"};
        string option = get_choice(allowed,1,"Choose the qraurter you want to enlarge:\n(1) Top left\n(2) Top right\n(3) Donw left\n(4) Down right\nChoose an option: ");
        // enlarge(img, option);
        enlarge(img ,stoi(option));
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
    else if(choice == "b"){
        clear();
        shuffle_img(img);;
    }
    else if(choice == "c"){
        blur_img(img);
    }
    // to save the image
    else if(choice == "s"){
        strt_of_Zloop: // a flag to be able to jumb here when needed
        while(true){
            clear();
            cout << "Please write the Target file name\n{\\/:*?\"<>|} characters are not allowed and a space at the end is not allowed: ";
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
                if((find(not_allowed, tmp_to_chnge_chr_2_strng) != -1) || option.size() > 255 || option[option.length() - 1] == ' '){
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
            bool exist = can_open_file(option);
            

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
                    
                    save_file(option_as_C_string);
                    delete[] option_as_C_string; // deleting the C-string to avoid memory leak
                    break;
                }
                else {
                    cout << "File was not overwriten, enter any key to re-enter the target name...";
                    string temp;
                    getline(cin, temp);
                    clear();
                    delete[] option_as_C_string;
                    goto strt_of_Zloop;
                }
            }else{
                // if everything goes well we save the file
                    save_file(option_as_C_string);
                    delete[] option_as_C_string; // deleting the C-string to avoid memory leak
                    break;
            }
        }
    }
    
    else if(choice == "l"){
        clear();
        load_img(1);
    }
    if(choice == "u"){
        undo();
    }
    
}


bool can_open_file(string filename){
    fstream FILE;
    FILE.open(filename);
    if(FILE && !FILE.fail()){
        FILE.close();
        return true;
    }else{
        FILE.close();
        return false;
    }
}


void load_img(int pic_number){
    string inpt;
    
    ask_user:

        if(pic_number == 1){
            cout << "Please enter the image name (must be in the directory of the program): ";
        }else{
            cout << "Please enter the second image's name (must be in the directory of the program): ";
        }


        getline(cin, inpt);
        inpt += ".bmp";
        if(can_open_file(inpt)){
            
            char *inpt_as_C_string = new char [inpt.length() + 1];
            strcpy(inpt_as_C_string, inpt.c_str());


            if(is_colored(inpt)){

                readRGBBMP(inpt_as_C_string, (pic_number == 1) ? img : img2);
                is_current_colored = true;
                delete[] inpt_as_C_string;

            }else{

                readGSBMP(inpt_as_C_string, (pic_number == 1) ? img_GS : img2_GS);
                is_current_colored = false;
                delete[] inpt_as_C_string;


                for (int i = 0; i < SIZE; i++)
                {
                    for (int j = 0; j < SIZE; j++)
                    {
                        for (int color = 0; color < 3; color++)
                        {
                            (pic_number == 1) ? img[i][j][color] = img_GS[i][j] : img2[i][j][color] = img2_GS[i][j];
                        }
                    }
                }

            }
        }else{
            clear();
            cout << "File Does not exist or cannot be opened!, Please try agian and try changing syntax...";
            sleep(2);
            clear();
            goto ask_user;
        }
}

void undo(){
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                img[i][j][k] = img_undo[i][j][k];
            }
            
        }
        
    }
}

void save_file(char *option_as_C_string){
    if(is_current_colored){
            writeRGBBMP(option_as_C_string, img);
    }else{
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                img_GS[i][j] = img[i][j][0];
            }
            
        }
        writeGSBMP(option_as_C_string, img_GS);
    }
}