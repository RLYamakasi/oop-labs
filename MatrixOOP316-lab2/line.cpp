#include "line.h"
#include "colors.h"
#include "console_manager.h"
#include "random_engine.h"

#include<iostream>
#include<unistd.h>
#include <thread>
#include <chrono>


void Line::_UpdateTailPosition(){
    if (_tailY == _row)
        _tailY += _direction;
    else
        _tailY = _row;

    _tailX -= 1;
}

void Line::_UpdateHeadPosition(){
    if (_headY == _row)
        _headY += _direction;
    else
        _headY = _row;

    _headX -= 1;
}

int Line::GetRow() { return _row; }

int Line::GetDirection() { return _direction; }

void Line::MoveToTheEnd(int steps){
    
    for (int i = 0; i < steps; i++){
        if (!_crawledOut){
            _chars.emplace_front(_headX, _headY, _color);
            
            // update head position
            _UpdateHeadPosition();
            
        }
        else if (!_onTheBorder){
            _chars.emplace_front(_headX, _headY, _color);
            _chars.pop_back();

            _UpdateHeadPosition();
            _UpdateTailPosition();
        }
        else if (!_crawledgIn){
            _chars.pop_back();
            _UpdateTailPosition();
        }

        if (_headX == _consoleWidth - _length){
            _crawledOut = true;
        }

        if (_headX == 0){
            _onTheBorder = true;
        }

        if (_tailX == 0)
            _crawledgIn = true;

    }
}

bool Line::IsCrawledOut(){
    return _crawledOut;
}

bool Line::IsOnScreen(){
    return _headX == _consoleWidth;
}

void Line::Move(){

    auto now = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastMoveTime).count();

    if (delta >= _moveInterval){
        MoveToTheEnd(1);
        _lastMoveTime = now;
    }
}

bool Line::IsOutOfScreen(){
    return _crawledgIn;
}

Line::Line(int length, int row, int speed, int color){
    int* consoleSize = ConsoleManager::GetConsoleSize();
    _consoleHeigth = consoleSize[1];
    _consoleWidth = consoleSize[0];
    delete[] consoleSize;
    
    _headX = _consoleWidth;
    _headY = row;

    _tailX = _consoleWidth;
    _tailY = row;

    _length = length;
    _row = row;
    _speed = speed;
    _color = color;

    _moveInterval = 1000 / _speed;

    _direction = RandomEngine::RandInt(0, 1) == 0 ? 1 : -1;
}

Line::~Line() {}
// Line::~Line(){
//     delete &_chars;
// }