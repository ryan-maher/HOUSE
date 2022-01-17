#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>
#include "introduction.h"


Introduction::Introduction(){

};

// run the introduction
void Introduction::RunIntroduction(){
    Welcome();
    RegisterOrLogin();
}

// returns the number of tokens the player has
int Introduction::getTokens(){
    std::stringstream ss;
    ss<<Tokens;
    ss>>covertedTokens;
    return covertedTokens;
}

// the number of tokens the player has
// this number comes from txt file.
std::string Tokens;
int covertedTokens; 

// prints a welcome banner and adds space to clear terminal window
void Introduction::Welcome(){
    
    int time = 400;
    int VisualDelay = 500;
    // clear console
    system("clear");
    
    // welcome banner
    std::cout<<"\n";
    std::cout<<"\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(VisualDelay));
    std::cout<<"   ***       ***     *******     ***         ***   **********    ************"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout<<"   ***       ***  ***       ***  ***         *** ***        ***  ****"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout<<"   ***       *** ***         *** ***         *** *****           ****"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout<<"   ************* ***         *** ***         ***      ****       **********"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout<<"   ***       *** ***         *** ***         ***           ***** ****"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout<<"   ***       ***  ***       ***  ****       **** ***        ***  ****"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout<<"   ***       ***     *******       ***********     **********    ************"<<std::endl;
    std::cout<<"\n";
    std::cout<<"\n";
    std::cout<<"\n";
}

// Validates user's input
bool Introduction::InputValidation(int userInput){
    
    // clear console
    system("clear");
    
    // Check if user even entered a digit
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        std::cout<<"\nTHIS TIME, PLEASE ENTER A VALID RESPONSE\n";
        return false;
    }
    
    // Check if digit is one of the available options
    if(userInput == (1) || userInput == (2)){
        return true;
    }else{
        std::cout<<"\nTHIS TIME, PLEASE ENTER A VALID RESPONSE!\n";
        return false;
    }
}

// called if the user wants to login
void Introduction::login(){
    
    // spacer
    system("clear");
    
    std::string username;
    std::string password;
    std::string CurrentLine;
    std::string NextLine;
    //std::string Tokens;
    
    std::string pleaseWait = "PLEASE WAIT WHILE WE BRING YOU TO THE GAME FLOOR\n";
    
    int WaitTime = 5000;
    
    bool InfoFound = false;
    
    std::cout<<"\nENTER YOUR USERNAME: ";
    std::cin>>username;
    std::cout<<"ENTER YOUR PASSWORD: ";
    std::cin>>password;
    
    std::ifstream readFile("data.txt");
    
    while(getline(readFile,CurrentLine)){
        
        getline(readFile,NextLine);
        getline(readFile,Tokens);
        
        if((username == CurrentLine) && (password == NextLine)){
            system("clear");
            std::cout<<"\nLOGIN SUCCESSFUL\n";
            std::cout<<"YOU HAVE "<<Tokens<<" TOKENS\n";
            std::cout<<pleaseWait;
            std::this_thread::sleep_for(std::chrono::milliseconds(WaitTime));
            
            InfoFound = true;
        }
        std::cout<<"\n";
    }
    readFile.close();
    
    if(!InfoFound){
        system("clear");
        std::cout<<"COULD NOT FIND AN ACCOUNT WITH THE GIVEN USERNAME AND PASSWORD. PLEASE REGISTER OR TRY TO LOGIN AGAIN"<< std::endl;
        RegisterOrLogin();
    }
}

// called if the user does not have a login and wants to register
void Introduction::reg(){
    system("clear");
    std::string username;
    std::string password;
    int InitTokens = 10;
    
    std::fstream dataFile;
    dataFile.open("data.txt",std::ios::out);
    
    std::cout<<"\nCREATE A USERNAME: ";
    std::cin>>username;
    std::cout<<"CREATE A PASSWORD: ";
    std::cin>>password;
    system("clear");
    std::cout<<"\nREGISTRATION COMPLETE. LOGIN TO CONTINUE \n";
    std::cout<<"\n";
    
    dataFile << username << std::endl;
    dataFile << password << std::endl;
    dataFile << InitTokens << std::endl;
    
    dataFile.close();
    
    RegisterOrLogin();
}

// direct input to either register or login method
void Introduction::InputControlFlow(int userInput){
    int LoginOption = 1;
    int RegisterOption = 2;
    
    if(userInput == (LoginOption)){
        login();
    } else if(userInput == (RegisterOption)){
        reg();
    }
}

// prompts user to register or login
void Introduction::RegisterOrLogin(){
    bool isValid;
    int userInput;
    
    do {
    std::cout << "1: LOGIN \n";
    std::cout << "2: REGISTER \n";
    std::cout << "SELECT AN OPTION: ";
    std::cin >> userInput;
    isValid = InputValidation(userInput);
    } while (!isValid);
    
    InputControlFlow(userInput);
}
