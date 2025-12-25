#pragma once 
#include<string>

class MySymbol{
    private:
        static std::string charset;
        int _x;
        int _y;
        char _c;
        int _color;
    public:
        void PutSymbol();
        void DeleteSymbol();
        void SetPosition(int new_x, int new_y);
        int* GetPosition();
        MySymbol(int x, int y, int color);
        ~MySymbol();
};