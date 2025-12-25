#pragma once

#include "figure.h"


class Explosion : public Figure {
    private:
        int _speed = 2;
        int _moveInterval = 1000; 
        void _Move() override;

        int _centerX;
        int _centerY;

        int _curRadius;
        int _maxRadius;


    public:
        Explosion(int centerX, int centerY, int minRadius, int maxRadius);

        void MoveIfReady() override;
        void Explode() override {};
        int GetCenterX() override { return _centerX; };
        int GetCenterY() override { return _centerY; };
};