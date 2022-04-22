/*
    CS112 : Structured Programming Assignment 3 - Full Submission 
    
    AUTOMATIC DETECTION & PROCESSING FOR COLOR & GRAYSCALE SIMULTANEOUSLY !!
    
    Authors:
    Khaled Waleed Salah , ID: 20210127
    
    (hanafy write here your name and id as well as youssef's)

    Institution : FCAI - CU 
    Prepared for : Dr.Mohammed El-Ramly , TA: Eng.Hager 
    Purpose : Console BMP 256*256 photo editor with multiple filters - Automatic color detection
    Last date of modification : 23 April 2022

    Version : 2.0 - Full Filters Working with Color & Grayscale

    NOTE: don't let the number of lines deceive you, most of them are either very readable code or comments :)

    */


#include <iostream>
#include <unistd.h>     // to make sleep() work
#include <fstream>      // to check for the existance of files
#include <filesystem>   // to check for the size of some files for color detection
#include <vector>
#include "bmplib.h"
#include "bmplib.cpp"
#include "filter_group_3.h"
#include "filter_group_1.h"
#include "filter_group_2.h"

using namespace std;

// this part is to detect OS for compatability.
#ifdef _WIN32
    bool is_os_win = true;
#else
    bool is_os_win = false;
#endif



// funcitons' prototypes

void clear();                       // to clear terminal for an elegant application
void print_options();               // printing the main menu options
void excute_choice(string choice);  // to excute user choice


// this is the most important funciton, takes a vecotr of all allowed strings and a mode to determine what message to print
// and finally a message for the user
string get_choice(vector<string>allowed, int mode, string message);


void load_img(int pic_number);              // to load image form disk to memory
int find(vector<string>vec, string target); // searches about a string in a vector of strings

bool is_colored(string filename);           // to check if the file is for a colored picture
bool can_open_file(string filename);        // to check if a file exist and we have the premission to open it
void save_file(char *option_as_C_string);   // to save files correctly depending on weather they are colored or not
void save_img_in_undo();                    // to save current image into the undo buffer for later undo
void undo();                                // to undo image


unsigned char img[SIZE][SIZE][RGB]; // declaring global colored img
unsigned char img2[SIZE][SIZE][RGB]; // declaring second global img for some filters to work
unsigned char img_undo[SIZE][SIZE][RGB]; // to later use the undo option


unsigned char img_GS[SIZE][SIZE]; // same thing for greyscale
unsigned char img2_GS[SIZE][SIZE]; 

int counter_for_undo = 0; // to make undo start saving in buffer correctly

bool is_current_colored; // for the save function to be able to save for GS or RGB accordingly to save image space


int main(){

    // We decided to make our program colorful for a more beatiful experience (Windows only but still compatible with other OS)
    char *color = "COLOR 07"; // this is the default color to use if user doesn't want this function of the system isn't windows
    char *color2 = "COLOR fa"; // secondry color in green to tell user that the operation succeded
    
    clear();
    cout << "Hello To our color & grayscale photo editor!" << endl;
    sleep(1);

    if(is_os_win){system("COLOR 0c");}// to turn the below text to blue
    cout << "THIS PHOTO EDITOR HAS AUTOMATIC DETECTION AND PROCCESSING FOR COLOR & GRAYSCALE, WORKS ON BOTH !" << endl << endl;
    sleep(2);
    if(is_os_win){system(color);}
    
    
    // run the color option if system is windows
    if(is_os_win){
        cout << "Please choose a color for the program !"<< endl;
        vector<string>allowed{"1","2","3","4"};
        string option = get_choice(allowed,1,"Choose from:\n(1) Pink & White (the best)\n(2) Blue & White\n(3) Aqua & Black\n(4) Default Console (boring)\nChoose an option: ");
        if(option == "1"){
            color = "COLOR fc";
            color2 = "COLOR fa";  // notice that color 2 changes according to color 1 not to mess with the background color
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


    string choice = "dummy"; // random intialization


    save_img_in_undo(); // to keep a copy of the original img in undo buffer
    

    // keep asking until the user wants to exit
    while(choice != "0"){
        vector<string>allowed = {"1","2","3","4","5","6","7","8","9","0","a","b","c","s","l","u"}; // this is a vector of all acceptable inputs
        // could have done this with regex but we wanted Custom function for easier debugging
        
        choice = get_choice(allowed,0, "d"); // getting the user choice using the fuction

        // undo should not start working until user has modified the image and untill they didn't do something like saving the image.
        if(counter_for_undo > 1 && choice != "s" && choice != "l" && choice !="u" && choice !="0"){
            save_img_in_undo();
        }
        else{
            counter_for_undo++;
        }

        excute_choice(choice); // to apply choice

        clear();


        // to tell user about the success of the operation
        if(choice != "0" && choice != "s" && choice != "l" && choice != "u"){
            
            if(is_os_win){system(color2);} // we turn the foreground green to report success ! but with prper background
            cout << "Filter Applied."<< endl;
            sleep(1.5);
            if(is_os_win){system(color);} // we then revert to the original colors the user has chosen

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
            cout << "Changes were reverted. (only one undo per modification)"<< endl;
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
    if(is_os_win){ // Clear terminal using proper command depending on OS
        system("CLS");
    }else{
        system("clear");
    }
}


bool is_colored(string filename){ // checking for color by checking file size (the resolution is constant anyway :) )
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
    cout << "(u) Undo (only one undo per change in photo)"<< endl;    
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
        // if mode is zero then print the main menu, else print the message provided for that input
        if(mode == 0){
            print_options();
        }else{
            cout << message;
        }
        string inpt; 
        getline(cin, inpt);
        int found = find(allowed,inpt);
        if(found != -1){
            // if the input was found in the allowed input then return that input
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
        rotate_img(img, option);
    }
    else if(choice == "7"){
        edge_detect(img);
    }
    else if(choice == "8"){
        vector<string>allowed{"1","2","3","4"};
        string option = get_choice(allowed,1,"Choose the qraurter you want to enlarge:\n(1) Top left\n(2) Top right\n(3) Donw left\n(4) Down right\nChoose an option: ");
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
        // the defense of this particular filter won't work with get_choice and it's too big so we put it in it's header
        shuffle_img(img);
    }
    else if(choice == "c"){
        blur_img(img);
    }
    // to save the image
    else if(choice == "s"){
        strt_of_Zloop: // a flag to be able to jumb here when needed (like a loop without the headache of the conditions)
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

                // if any character in the input is not allowed, reject the output and the filename cannot be more than 255 character
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
            // and turn that copy to C-string using dynamic memory allocation
            char *option_as_C_string = new char [option.length()+1];
            strcpy(option_as_C_string, option.c_str());
            


            if(exist){
                cout << "This file already exists, ARE YOU SURE you want to OVERWRITE it ? type (YES) or (yes) for yes, anything else for no :";
                string overwrite;
                getline(cin, overwrite);
                if(overwrite == "YES" || overwrite =="yes"){

                    save_file(option_as_C_string); // saving if the user wants to overwrite
                    delete[] option_as_C_string; // deleting the C-string to avoid memory leak
                    break;
                }
                else {
                    cout << "File was not overwriten, enter any character to re-enter the target's name...";
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


bool can_open_file(string filename){ // detects if a file exists and we can open it
    fstream FILE;
    FILE.open(filename);
    if(FILE && !FILE.fail()){
        FILE.close(); // avoiding memory leaks
        return true;
    }else{
        FILE.close();
        return false;
    }
}


void load_img(int pic_number){
    string inpt;
    
    ask_user:  // A flag to jumb here when needed

        if(pic_number == 1){
            cout << "Please enter the image name (must be in the directory of the program): ";
        }else{
            cout << "Please enter the second image's name (must be in the directory of the program): ";
        }


        getline(cin, inpt);
        inpt += ".bmp";
        if(can_open_file(inpt)){ 
            
            // Turning the string input to C_string to work with the read(RGB|GS)BMB functions
            char *inpt_as_C_string = new char [inpt.length() + 1];
            strcpy(inpt_as_C_string, inpt.c_str());


            if(is_colored(inpt)){

                // if file is colored then load it into an RGB photo 3d matrix
                readRGBBMP(inpt_as_C_string, (pic_number == 1) ? img : img2);
                is_current_colored = true; // change the indicator to yesssss
                delete[] inpt_as_C_string; // avoiding memory leaks like good programmers :)

            }else{

                readGSBMP(inpt_as_C_string, (pic_number == 1) ? img_GS : img2_GS);
                
                if(pic_number == 1){ // not to mess the saved image if the first photo is colored while the second is GS
                    is_current_colored = false;
                }

                delete[] inpt_as_C_string;

                // our filters only work on color, so if the user wants to edit a GS when copy it into a colored version
                // then we reverse the proccess when we want to save the file (to reduce storage sapce)
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


void undo(){ // just coping the buffer into the image to undo changes
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

void save_img_in_undo(){ // to save the current image into undo buffer

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
}

void save_file(char *option_as_C_string){ // to save file depending on it's attributes (color or GS)
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