#include<stdexcept>
#include<cstdlib>
#include <string> 
#include<iostream>
#include<sstream>

#include "validator.h"

const std::string Validator::_invalidLineSpeedErrorMsg = "\nLine speed must be integer in range [1;30]\n\n";
const std::string Validator::_invalidLineLengthErrorMsg = "\nLine length must be integer in range [1;30]\n\n";
const std::string Validator::_invalidEpilepcyErrorMsg = "\nEpilepsy must be y or n\n\n";
const std::string Validator::_invalidLineGenerationSpeedErrorMsg = "\nLine frequency must be integer in range [1;30]\n\n";

const std::string Validator::_invalidExplosionFrequencyErrorMsg = "\nExplosion frequency must be integer in range [1;1000]\n\n";
const std::string Validator::_invalidMinExplosionRadiusErrorMsg = "\nExplosion minmal radius must be integer in range[1;10]\n\n";
const std::string Validator::_invalidMaxExplosionRadiusErrorMsg = "\nExplosion maximal radius must be integer in range[1;10]\n\n";
const std::string Validator::_minExplosionGreaterErrorMsg = "\nMin explosion radius must be greater then max\n\n";

const std::string Validator::_lineGenerationSpeedInputMsg = "Enter the line frequency(integer in range 1-30): ";
const std::string Validator::_lineSpeedInputMsg = "Enter the line speed(integer in range 1-30): ";
const std::string Validator::_lineLengthInputMsg = "Enter the line legth(integer in range 1-30): ";
const std::string Validator::_epilepcyModeInputMsg = "Turn on epilepsy mode? [y\\N]: ";

const std::string Validator::_explosionFrequencyInputMsg = "Enter explosion frequency(integer in range[1;1000]): ";
const std::string Validator::_minExplosionRadiusInputMsg = "Enter min explosion radius(integer in range[1;10]): ";
const std::string Validator::_maxExplosionRadiusInputMsg = "Enter max explosion radius(integer in range[1;10]): ";

bool Validator::ValidateEpilepcy(std::string epilepcy, bool cli_mode) {
    bool error = true;
    bool result;

    if (cli_mode){
        result = _EpilepsyTryParse(epilepcy, _invalidEpilepcyErrorMsg, error);
        if (!error)
            return result;
    }

    while(error) {
        std::cout << _epilepcyModeInputMsg;
        std::cin >> epilepcy;

        result = _EpilepsyTryParse(epilepcy, _invalidEpilepcyErrorMsg, error);
        if (!error)
            return result;
    }

    // never reaches this line anyways
    return false;
}

int Validator::ValidateExplosionFrequency(std::string frequency, bool cli_mode){
    return _ValidateStringData(frequency, _explosionFrequencyInputMsg, _invalidExplosionFrequencyErrorMsg, 1, 1000, cli_mode);
}

int Validator::ValidateMinExplosionRadius(std::string radius, bool cli_mode) {
    return _ValidateStringData(radius, _minExplosionRadiusInputMsg, _invalidMinExplosionRadiusErrorMsg, 1, 10, cli_mode);
}

int Validator::ValidateMaxExplosionRadius(std::string maxRadius, int minRadius, bool cli_mode) {
    int parsedData = _ValidateStringData(maxRadius, _maxExplosionRadiusInputMsg, _invalidMaxExplosionRadiusErrorMsg, 1, 10, cli_mode);

    while (parsedData < minRadius) {
        std::cout << _minExplosionGreaterErrorMsg;
        parsedData = _ValidateStringData(maxRadius, _maxExplosionRadiusInputMsg, _invalidMaxExplosionRadiusErrorMsg, 1, 10, cli_mode);
    }

    return parsedData;
}


int Validator::ValidateLineFrequency(std::string lineGenerationSpeed, bool cli_mode){
    int validatedLineLength = _ValidateStringData(lineGenerationSpeed, _lineGenerationSpeedInputMsg,\
         _invalidLineGenerationSpeedErrorMsg, 1, 30, cli_mode);
    
    return validatedLineLength;
}

int Validator::ValidateLineLength(std::string lineLength, bool cli_mode){
    int validatedLineLength = _ValidateStringData(lineLength, _lineLengthInputMsg, _invalidLineLengthErrorMsg,\
    1, 30, cli_mode);
    
    return validatedLineLength;
}

int Validator::ValidateLineSpeed(std::string lineSpeed, bool cli_mode){
    int validatedLineSpeed = _ValidateStringData(lineSpeed, _lineSpeedInputMsg, _invalidLineSpeedErrorMsg   ,\
    1, 30, cli_mode);

    return validatedLineSpeed;
}

bool Validator::_EpilepsyTryParse(std::string inputData, std::string errorMsg, bool& error){
    error = false;
    if (inputData == "Y" || inputData == "y")
        return true;
        
    if (inputData == "N" || inputData == "n")
        return false;

    error = true;
    std::cout << _invalidEpilepcyErrorMsg;

    return false;
}


int Validator::_StringToInt(std::string& inputData){
    for (char c: inputData){
        int dif = c - '0';

        if (dif > 9 || dif < 0){
            throw std::invalid_argument("Nan");
        }
    }
    return std::stoi(inputData);
}


int Validator::_IntegerTryParse(std::string inputData, std::string errorMsg, bool& error,\
    int start_range, int end_eange){
    int parsedData;

    try {
        parsedData = _StringToInt(inputData);

        if (parsedData > end_eange || parsedData < start_range){
            error = true;
            throw std::invalid_argument(errorMsg);
        }

        error = false;
        return parsedData;
    }
    catch (const std::invalid_argument&){
        std::cout << errorMsg;
        error = true;
    }

    return 0;
}

int Validator::_ValidateStringData(std::string inputData, std::string inputMsg, std::string errorMsg,\
int start_range, int end_range, bool cli_mode){
    bool error = true;
    int parsedData;

    if (cli_mode){
        parsedData = _IntegerTryParse(inputData, errorMsg, error, start_range, end_range);
        if (!error)
            return parsedData;
    }

    while (error) {
        std::cout << inputMsg;
        std::cin >> inputData;
        parsedData = _IntegerTryParse(inputData, errorMsg, error, start_range, end_range);
        if (!error)
            return parsedData;
    } 

    return 0;
}