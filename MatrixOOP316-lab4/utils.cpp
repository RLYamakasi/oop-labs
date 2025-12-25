#include"colors.h"
#include"random_engine.h"
#include"utils.h"


int Utils::GetRandomColor(){
    int color = RandomEngine::RandInt(RED, CYAN+7);
    // Offset of bright colors
    if (color > CYAN) color = color - 7 + 60;

    return color;
}