#pragma once

#include "line.h"
#include"containers/array_list.h"
#include"containers/linked_list.h"

#include <string>
#include <unordered_set>
#include <memory>

using std::unordered_set;

class AppManager{
    private:
        int _rowCount;

        int _lineSpeed;
        int _lineLength;
        int _lineFrequency;
        bool _epilepsy;

        int _explosionFrequency;
        int _minExplosionRadius;
        int _maxExplosionRadius;

        static const std::string _helpMsg;
        static const std::string _invalidArgumentCountMsg;

        LinkedList<int> _GenerateIntervals(int start, int stop, int count);


    public:
        AppManager();
        AppManager(std::string lineGenerationSpeed, std::string lineSpeed, std::string lineLength, std::string epilepsy,\
    std::string explosionFrequency, std::string minRadius, std::string maxRadius);
        static void DisplayHelpText();
        static void DisplayInvaidArgumentCountMsg();
        Line GenerateLine();
        int GetRandomRow();
        int GetNewLineColor();
        void SetUp();
        void Run();
};