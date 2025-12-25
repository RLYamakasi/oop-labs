#include "explosion.h"
#include "console_manager.h"
#include<math.h>
#include<unordered_set>

void Explosion::_Move() {
    // clear previous frame points
    _chars.clear();

    // advance radius
    _curRadius++;
    if (_curRadius > _maxRadius) {
        _isActive = false;
        return;
    }

    int r = _curRadius;
    int x = 0;
    int y = r;
    int d = 1 - r; // decision variable

    // small hash-set to avoid duplicate (x,y) inserts caused by symmetry
    std::unordered_set<uint64_t> used;
    used.reserve(r * 8 + 16);

    auto try_add = [&](int px, int py) {
        int X = _centerX + px;
        int Y = _centerY + py;
        if (X < 0 || X >= _consoleWidth || Y < 0 || Y >= _consoleHeigth) return;
        uint64_t key = ((uint64_t)(uint32_t)X << 32) | (uint32_t)Y;
        if (used.insert(key).second) {
            _chars.emplace_back(X, Y, Utils::GetRandomColor());
        }
    };

    // plot the 8 symmetric points for (x,y)
    auto plot8 = [&](int px, int py) {
        try_add( px,  py);
        try_add( py,  px);
        try_add(-px,  py);
        try_add(-py,  px);
        try_add( px, -py);
        try_add( py, -px);
        try_add(-px, -py);
        try_add(-py, -px);
    };

    while (x <= y) {
        plot8(x, y);
        ++x;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            --y;
            d += 2 * (x - y) + 1;
        }
    }
}


void Explosion::MoveIfReady() {
    auto now = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastMoveTime).count();
    
    if (delta >= _moveInterval){
        _Move();
        _lastMoveTime = now;
    }
}

Explosion::Explosion(int centerX, int centerY, int minRadius, int maxRadius) : Figure(){
    int* consoleSize = ConsoleManager::GetConsoleSize();
    _consoleHeigth = consoleSize[1];
    _consoleWidth = consoleSize[0];
    delete[] consoleSize;

    _centerX = centerX;
    _centerY = centerY;

    _lastMoveTime = std::chrono::steady_clock::now();
    _speed = 2;
    _moveInterval = 1000 / 2;

    _curRadius = minRadius - 1;
    _maxRadius = maxRadius;

    
}