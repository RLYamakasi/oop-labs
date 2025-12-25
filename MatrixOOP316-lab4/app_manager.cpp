#include<stdexcept>
#include<cstdlib>
#include <string> 
#include<iostream>
#include <chrono>
#include <algorithm>

#include "app_manager.h"
#include "console_manager.h"
#include "colors.h"
#include "random_engine.h"
#include "line.h"
#include "validator.h"
#include "figure.h"
#include "explosion.h"

const std::string AppManager::_helpMsg = R"(
This is the console matrix program.

To run the program you need to provide:
    Line:
  • Line frequency    (integer 1–30)
  • Line speed               (integer 1–30)
  • Line length              (integer 1–30)
  • Epilepsy mode            (y/n flag)
  Explosion:
  • Explosion frequency  (integer 1-1000)
  • Min explosion range  (integer 1-10)
  • Max explosion range  (integer 1-10)

)";

const std::string AppManager::_invalidArgumentCountMsg = "Invalid argument count! Type make help to see help message\n";

AppManager::AppManager(std::string lineGenerationSpeed, std::string lineSpeed, std::string lineLength, std::string epilepsy,\
    std::string explosionFrequency, std::string minRadius, std::string maxRadius){
    bool cli_mode = true;

    _lineFrequency = Validator::ValidateLineFrequency(lineGenerationSpeed, cli_mode);
    _lineLength = Validator::ValidateLineLength(lineLength, cli_mode);
    _lineSpeed = Validator::ValidateLineSpeed(lineSpeed, cli_mode);
    _epilepsy = Validator::ValidateEpilepcy(epilepsy, cli_mode);

    _explosionFrequency = Validator::ValidateExplosionFrequency(explosionFrequency, cli_mode);
    _minExplosionRadius = Validator::ValidateMinExplosionRadius(minRadius, cli_mode);
    _maxExplosionRadius = Validator::ValidateMaxExplosionRadius(maxRadius, _minExplosionRadius, cli_mode);


    SetUp();
}

void AppManager::SetUp(){
    std::cout << std::unitbuf;
    RandomEngine::Init();
    ConsoleManager::ClearScreen();
    ConsoleManager::SetConsoleColor(WHITE);
    ConsoleManager::HideCursor();

    int* size = ConsoleManager::GetConsoleSize();
    _rowCount = size[1];
    delete[] size;
}

AppManager::AppManager(){

    bool cli_mode = false;

    _lineFrequency = Validator::ValidateLineFrequency("", cli_mode);
    _lineLength = Validator::ValidateLineLength("", cli_mode);
    _lineSpeed = Validator::ValidateLineSpeed("", cli_mode);
    _epilepsy = Validator::ValidateEpilepcy("", cli_mode);

     _explosionFrequency = Validator::ValidateExplosionFrequency("", cli_mode);
    _minExplosionRadius = Validator::ValidateMinExplosionRadius("", cli_mode);
    _maxExplosionRadius = Validator::ValidateMaxExplosionRadius("", _minExplosionRadius, cli_mode);

    SetUp();
}

void AppManager::Run(){

    auto start =  std::chrono::steady_clock::now();

    LinkedList<int> intervals = _GenerateIntervals(0, 1000, _lineFrequency);

    LinkedList<std::unique_ptr<Figure>> activeEntities;
    ArrayList<std::unique_ptr<Figure>> to_add;
    
    while (true){
        
        auto now = std::chrono::steady_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

        while (!intervals.empty() && delta >= intervals.front()){
            activeEntities.push_back(std::move(
                std::make_unique<Line>(_lineLength, GetRandomRow(), _lineSpeed, GetNewLineColor(), _explosionFrequency)
            )
            );

            intervals.pop_front();
        }

        for (auto it = activeEntities.begin(); it != activeEntities.end();) {
            if ((*it) == nullptr) {
                activeEntities.erase(it);
                continue;
            }
            (*it)->MoveIfReady();
            if ((*it)->HasExploded()  ) {
                (*it)->Explode();
                to_add.push_back( std::move(
                    std::make_unique<Explosion>((*it)->GetCenterX(), (*it)->GetCenterY(), _minExplosionRadius, _maxExplosionRadius)
                )
                );
            }

            if (!((*it)->IsActive())) {
                it = activeEntities.erase(it);
            }
            else {
                ++it;
            }
        }

        while (!to_add.empty()) {
            activeEntities.push_back(std::move(to_add.front()));
            to_add.pop_front();
        }

        if (delta >= 1000){
            intervals = _GenerateIntervals(0, 1000, _lineFrequency);
            start = now;
        }
    }
}


LinkedList<int> AppManager::_GenerateIntervals(int start, int stop, int count){
    ArrayList<int> temp(_lineFrequency);
    for (int i = 0; i < _lineFrequency; i++){
        temp.push_back(RandomEngine::RandInt(0, 1000));
    }

    std::sort(temp.begin(), temp.end());

    LinkedList<int> intervals;
    for (int v : temp) intervals.push_back(v);
    return intervals;
}


void AppManager::DisplayHelpText(){
    std::cout << _helpMsg;
}

int AppManager::GetRandomRow(){
    int* consoleSize = ConsoleManager::GetConsoleSize();
    int row = RandomEngine::RandInt(2, consoleSize[1]-1);
    delete[] consoleSize;

    return row;
}

int AppManager::GetNewLineColor(){
    int color;
    if (_epilepsy) {
        color = RandomEngine::RandInt(RED, CYAN+7);
        // Offset of bright colors
        if (color > CYAN) color = color - 7 + 60;
    }
    else color = WHITE;

    return color;
}

void AppManager::DisplayInvaidArgumentCountMsg(){
    std::cout << _invalidArgumentCountMsg;
}