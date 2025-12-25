#include<iostream>
#include <string>
#include <csignal>

#include "app_manager.h"
#include "console_manager.h"

AppManager* globalManager = nullptr;

void signalHandler(int signum) {
    globalManager->~AppManager();
    exit(0);
}



int main(int argc, char* argv[]){


    if (argc != 2 && argc != 5 && argc != 1){
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

    AppManager manager = (argc == 5)
    ? AppManager(std::string(argv[1]), std::string(argv[2]), std::string(argv[3]), std::string(argv[4]))
    : AppManager();
    
    globalManager = &manager;

     std::signal(SIGTERM, &signalHandler);
    std::signal(SIGINT, &signalHandler);

    manager.Run();

    return 0;
}