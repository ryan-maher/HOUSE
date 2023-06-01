#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <thread>
#include "introduction.h"
#include "gameroom.h"

// constructor
Introduction::Introduction(){

};

// runs the introduction
void Introduction::run_introduction()
{
    welcome();
    register_or_login();
}

// reads & returns the number of tokens the player has
int Introduction::get_tokens()
{
    std::ifstream read_file("data.txt");
    std::string current_line;
    std::string tmp;
    std::stringstream string_stream;
    int tokens;

    while (getline(read_file, current_line))
    {
        bool has_only_digits = (current_line.find_first_not_of("0123456789") == std::string::npos);
        if (has_only_digits)
        {
            tmp = current_line;
            break;
        }
    }

    string_stream << tmp;
    string_stream >> tokens;
    return tokens;
}

// adjust and set new token amount in the file
void Introduction::set_tokens(int tokens)
{
    std::ifstream data_file;
    data_file.open("data.txt");

    std::fstream tmp("test.txt", std::ios::out);

    std::string current_line;
    std::string line;

    while (getline(data_file, current_line))
    {
        tmp << current_line << std::endl;
    }

    tmp.close();
    data_file.close();

    std::ifstream test_file("test.txt");
    std::fstream data;
    data.open("data.txt", std::ios::out);

    while (getline(test_file, line))
    {
        bool has_only_digits = (line.find_first_not_of("0123456789") == std::string::npos);

        if (!has_only_digits)
        {
            data << line << std::endl;
        }
        else if (has_only_digits)
        {
            data << std::to_string(tokens) << std::endl;
        }
    }

    test_file.close();
    remove("test.txt");
    data.close();
}

// displays a welcome banner to the terminal window
void Introduction::welcome()
{
    // clear console
    system("clear");

    const int time = 400;

    // welcome banner
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "\n\n   ***       ***     *******     ***         ***   **********    ************" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "   ***       ***  ***       ***  ***         *** ***        ***  ****" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "   ***       *** ***         *** ***         *** *****           ****" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "   ************* ***         *** ***         ***      ****       **********" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "   ***       *** ***         *** ***         ***           ***** ****" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "   ***       ***  ***       ***  ****       **** ***        ***  ****" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    std::cout << "   ***       ***     *******       ***********     **********    ************" << std::endl;
}

// validates the user's input in this panel
bool Introduction::validate_input(int users_input)
{
    // clear console
    system("clear");

    const int time = 3000;

    // Check if user even entered a digit
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "\n\n\n\n\n\n\n\n\n\n                    PLEASE ENTER A VALID RESPONSE\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        return false;
    }

    // Check if digit is one of the available options
    if (users_input == (1) || users_input == (2))
    {
        return true;
    }
    else
    {
        std::cout << "\n\n\n\n\n\n\n\n\n\n                    PLEASE ENTER A VALID RESPONSE\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        return false;
    }
}

// prompts user to login if this option is selected
void Introduction::login()
{

    system("clear");
    std::string username;
    std::string password;
    std::string current_line;
    std::string next_line;
    std::string wait_message = "                PLEASE WAIT WHILE WE BRING YOU TO THE GAME FLOOR\n";

    const int time = 5000;

    bool user_info_found = false;

    std::cout << "\n\n\n\n                                 LOGIN MENU \n\n\n\n\n\n\n";
    std::cout << "                           ENTER YOUR USERNAME: ";
    std::cin >> username;
    std::cout << "                           ENTER YOUR PASSWORD: ";
    std::cin >> password;

    std::ifstream read_file("data.txt");

    while (getline(read_file, current_line))
    {

        getline(read_file, next_line);

        if ((username == current_line) && (password == next_line))
        {
            system("clear");
            std::cout << "\n\n\n\n\n\n\n\n                               LOGIN SUCCESSFUL\n";
            std::cout << "                              YOU HAVE " << get_tokens() << " TOKENS\n";
            std::cout << wait_message;
            std::this_thread::sleep_for(std::chrono::milliseconds(time));

            user_info_found = true;
        }
        std::cout << "\n";
    }

    read_file.close();

    if (!user_info_found)
    {
        system("clear");
        int needed_spaces = 5;

        spacing_buffer(needed_spaces);
        std::cout << "         COULD NOT FIND AN ACCOUNT WITH THE GIVEN USERNAME AND PASSWORD" << std::endl;
        std::cout << "                    PLEASE REGISTER OR TRY TO LOGIN AGAIN"
                  << std::endl;
        register_or_login();
    }

    Gameroom game_floor_obj;
    game_floor_obj.run_gameroom();
}

// prompts user to register if that option is selected
void Introduction::reg()
{
    system("clear");
    const int time = 4000;
    const int initial_tokens = 10;

    std::string username;
    std::string password;

    std::fstream data_file;
    data_file.open("data.txt", std::ios::out);

    std::cout << "\n\n\n\n                              REGISTRATION MENU \n\n\n\n\n\n\n";
    std::cout << "                             CREATE A USERNAME: ";
    std::cin >> username;
    std::cout << "                             CREATE A PASSWORD: ";
    std::cin >> password;

    system("clear");

    std::cout << "\n\n\n\n\n\n\n\n\n\n                     REGISTRATION COMPLETE, LOGIN TO CONTINUE. \n\n";

    data_file << username << std::endl;
    data_file << password << std::endl;
    data_file << initial_tokens << std::endl;

    data_file.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    login();
}

// direct programs control to either register or login method
void Introduction::direct_control_flow(int users_input)
{
    int login_option = 1;
    int register_option = 2;

    if (users_input == (login_option))
    {
        login();
    }
    else if (users_input == (register_option))
    {
        reg();
    }
}

// prompts user to register or login during menu screen
void Introduction::register_or_login()
{
    bool is_valid;
    int users_input;

    do
    {
        std::cout << "\n\n\n\n\n                                 1: LOGIN \n";
        std::cout << "                                 2: REGISTER \n\n";
        std::cout << "                               SELECT AN OPTION: ";
        std::cin >> users_input;
        is_valid = validate_input(users_input);

        system("clear");
        std::cout << "\n\n\n\n";

    } while (!is_valid);

    direct_control_flow(users_input);
}

// added white space to make program more visually appealing
void Introduction::spacing_buffer(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        std::cout << "\n";
    };
}
