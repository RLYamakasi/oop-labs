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


void Line::_Move(){
    

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

void Line::MoveIfReady() {
    auto now = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastMoveTime).count();
    
    if (delta >= _moveInterval){
        _Move();
        _lastMoveTime = now;

    if (!_hasExploded){
        int probability = RandomEngine::RandInt(1, 1000);
        if (probability <= _epxlosionFrequency) {
            _hasExploded = true;
        }
    }
    }
}

void Line::Explode() {
    _chars.pop_front();
    if (_chars.empty()) {
        _isActive = false;
        return;
    }
    MySymbol newHead = _chars.front();
    _headX = newHead.GetX();
    _headY = newHead.GetY();
    _length--;
    _hasExploded = false;
}   


int Line::GetCenterX(){ return _headX; }
int Line::GetCenterY(){ return _headY; }

bool Line::IsCrawledOut(){
    return _crawledOut;
}

bool Line::IsOnScreen(){
    return _headX == _consoleWidth;
}

bool Line::IsOutOfScreen(){
    return _crawledgIn;
}

Line::Line(int length, int row, int speed, int color, int explosionFrequency) : Figure(){
    int* consoleSize = ConsoleManager::GetConsoleSize();
    _consoleHeigth = consoleSize[1];
    _consoleWidth = consoleSize[0];
    delete[] consoleSize;
    
    _headX = _consoleWidth;
    _headY = row;

    _epxlosionFrequency = explosionFrequency;

    _tailX = _consoleWidth;
    _tailY = row;

    _length = length;
    _row = row;
    _speed = speed;
    _color = color;

    _moveInterval = 1000 / _speed;

    _lastMoveTime = std::chrono::steady_clock::now();

    _direction = RandomEngine::RandInt(0, 1) == 0 ? 1 : -1;
}