#pragma once

#include<chrono>
#include<deque>
#include<iostream>
#include"symbol.h"
#include"utils.h"


class Figure {
    public:
    virtual void MoveIfReady(){
            auto now = std::chrono::steady_clock::now();
            auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastMoveTime).count();

            if (delta >= _moveInterval){
                _Move();
                _lastMoveTime = now;
        }
    }

    virtual bool IsExplodbale(){ return false; };
    virtual void Explode() = 0;
    virtual bool IsActive() { return _isActive; };
    virtual bool HasExploded() { return _hasExploded; };

    virtual int GetCenterX() = 0;
    virtual int GetCenterY() = 0;

    virtual ~Figure() = default;
    protected:
        Figure() = default;
        std::chrono::steady_clock::time_point _lastMoveTime;
        int _moveInterval;
        std::deque<MySymbol> _chars;
        int _speed;
        bool _isActive = true;
        bool _hasExploded = false;

        int _consoleHeigth;
        int _consoleWidth;

        virtual void _Move() = 0;
};