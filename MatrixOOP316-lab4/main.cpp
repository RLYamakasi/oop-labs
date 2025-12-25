#include<iostream>
#include <string>
#include <csignal>

#include "app_manager.h"
#include "console_manager.h"
#include "colors.h"

AppManager* globalManager = nullptr;

void signalHandler(int signum) {
    ConsoleManager::ClearScreen();
    ConsoleManager::SetConsoleColor(WHITE);
    ConsoleManager::DisplayCursor();
    exit(0);
}



int main(int argc, char* argv[]){
    srand(time(NULL));
    std::signal(SIGTERM, &signalHandler);
    std::signal(SIGINT, &signalHandler);

    if (argc != 2 && argc != 8 && argc != 1){
        AppManager::DisplayInvaidArgumentCountMsg();
        return 0;
    }

    if (argc == 2 and (std::string(argv[1]) == "-h" or std::string(argv[1]) == "--help")){
        AppManager::DisplayHelpText();
        return 0;
    }
    else if (argc == 2){
        AppManager::DisplayInvaidArgumentCountMsg();
        return 0;
    }

    AppManager manager = (argc == 8)
    ? AppManager(std::string(argv[1]), std::string(argv[2]), std::string(argv[3]), std::string(argv[4]), std::string(argv[5]), std::string(argv[6]), std::string(argv[7]))
    : AppManager();
    
    globalManager = &manager;

    manager.Run();


    return 0;
}