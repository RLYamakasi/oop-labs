#include <iostream>

#include "symbol.h"
#include "console_manager.h"
#include "random_engine.h"


std::string MySymbol::charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void MySymbol::PutSymbol(){
    ConsoleManager::GotoXY(_x, _y);
    std::cout << "\033[" << _color << 'm' << _c << "\033[0m";
}

void MySymbol::DeleteSymbol(){
    ConsoleManager::GotoXY(_x, _y);
    std::cout << ' ';
}

void MySymbol::SetPosition(int new_x, int new_y){
    DeleteSymbol();
    _x = new_x;
    _y = new_y; 
    PutSymbol();
}

int MySymbol::GetX(){ return _x; }
int MySymbol::GetY(){ return _y; }

MySymbol::MySymbol(int x, int y, int color){
    _x = x;
    _y = y;
    _color = color;

    int pos = RandomEngine::RandInt(0, MySymbol::charset.size() - 1);
    _c = MySymbol::charset[pos];

    PutSymbol();
}

MySymbol::~MySymbol(){
    DeleteSymbol();
}