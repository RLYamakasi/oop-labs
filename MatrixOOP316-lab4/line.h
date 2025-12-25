#pragma once

#include<chrono>
#include "symbol.h"
#include "figure.h"

class Line : public Figure {
    private:
        

        int _length;
        int _row; 
        int _color;
        int _direction;

        int _headX;
        int _headY;
        int _tailX;
        int _tailY;

        int _epxlosionFrequency;


        bool _crawledOut = false;
        bool _onTheBorder = false;
        bool _crawledgIn = false;
        
        void _UpdateTailPosition(); 
        void _UpdateHeadPosition();
        
        void _Move() override;
        public:

        bool IsExplodbale() override { return true; };

        int GetRow();
        int GetDirection();
        bool IsOutOfScreen();
        bool IsCrawledOut();
        bool IsOnScreen();
        Line(int length, int row, int speed, int color, int explosionFrequency);
        
        int GetCenterX() override;
        int GetCenterY() override;
        void MoveIfReady() override;
        void Explode() override;
};