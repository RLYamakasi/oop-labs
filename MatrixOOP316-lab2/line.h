#pragma once

#include<vector>
#include<chrono>
#include<map>
#include <deque>
#include "symbol.h"

class Line{
    private:
        int _consoleHeigth;
        int _consoleWidth;

        int _length;
        int _row; 
        int _speed;
        int _color;
        int _direction;

        int _headX;
        int _headY;
        int _tailX;
        int _tailY;

        std::deque<MySymbol> _chars;

        std::chrono::steady_clock::time_point _lastMoveTime;
        int _moveInterval;

        bool _crawledOut = false;
        bool _onTheBorder = false;
        bool _crawledgIn = false;
        
        void _UpdateTailPosition(); 
        void _UpdateHeadPosition();
        
        public:
        void Move();

        int GetRow();
        int GetDirection();
        bool IsOutOfScreen();
        bool IsCrawledOut();
        bool IsOnScreen();
        void MoveToTheEnd(int steps);
        Line(int length, int row, int speed, int color);
        ~Line();
};