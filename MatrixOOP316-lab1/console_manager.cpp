#include "console_manager.h"
#include "colors.h"

#include<iostream>
#include<sys/ioctl.h>
#include<unistd.h>

void ConsoleManager::ClearScreen(){
    std::cout << "\033[H\033[2J";
    ConsoleManager::GotoXY(1, 1);
}

void ConsoleManager::GotoXY(int col, int row){
    std::cout << "\033[" << row  << ';' << col << 'H';
}

void ConsoleManager::HideCursor(){
    std::cout << "\e[?25l";
}

void ConsoleManager::DisplayCursor(){
    std::cout << "\e[?25h";
}

void ConsoleManager::SetConsoleColor(int foreground=WHITE){
    std::cout << "\033[0;" << foreground << 'm';
}

void ConsoleManager::DestroySymbol(int x, int y){
    GotoXY(x, y);
    std::cout << ' ';
}

int* ConsoleManager::GetConsoleSize(){
    struct winsize w;
    // ioctl send systemcall with standart output descriptor STDOUT_FILENO
    // and TIOCGWINSZ a constant meaning "Standart INput Output Control Get WINdow SiZe"
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int rows = w.ws_row;
    int cols = w.ws_col;

    return new int[2] {cols, rows};
}