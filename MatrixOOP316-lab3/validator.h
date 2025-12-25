#pragma once

#include<string>

class Validator{
    private:
    
        static const std::string _invalidLineSpeedErrorMsg;
        static const std::string _invalidLineGenerationSpeedErrorMsg;
        static const std::string _invalidLineLengthErrorMsg;
        static const std::string _invalidEpilepcyErrorMsg;

        static const std::string _invalidExplosionFrequencyErrorMsg;
        static const std::string _invalidMinExplosionRadiusErrorMsg;
        static const std::string _invalidMaxExplosionRadiusErrorMsg;
        static const std::string _minExplosionGreaterErrorMsg;

        static const std::string _lineSpeedInputMsg;
        static const std::string _lineGenerationSpeedInputMsg;
        static const std::string _lineLengthInputMsg;
        static const std::string _epilepcyModeInputMsg;

        static const std::string _explosionFrequencyInputMsg;
        static const std::string _minExplosionRadiusInputMsg;
        static const std::string _maxExplosionRadiusInputMsg;

        static int _ValidateStringData(std::string inputData, std::string inputMsg, std::string errorMsg,\
        int start_range, int end_range, bool cli_mode);
        static int _IntegerTryParse(std::string inputData, std::string errorMasg, bool& error, \
        int start_range, int end_range);
        static bool _EpilepsyTryParse(std::string inputData, std::string errorMsg, bool& error);
        static int _StringToInt(std::string& inputData);

    public:
        static int* ValidateInput(std::string lineSpeed, std::string lineLength, std::string epilepsy);
        static int ValidateLineSpeed(std::string lineSpeed, bool cli_mode);
        static int ValidateLineLength(std::string lineLength, bool cli_mode);
        static bool ValidateEpilepcy(std::string epilepcy, bool cli_mode);
        static int ValidateLineFrequency(std::string lineGenerationSpeed, bool cli_mode);

        static int ValidateExplosionFrequency(std::string explosionFrequency, bool cli_mode);
        static int ValidateMinExplosionRadius(std::string minExplosionRadius, bool cli_mode);
        static int ValidateMaxExplosionRadius(std::string maxExplosionRadius, int minExplosionRadius, bool cli_mode);

};