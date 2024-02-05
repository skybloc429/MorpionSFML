#pragma once



#include "Render.h"
#include "Input.h"
#include "Morpion.h"
#include "Defines.h"

enum class Symbol;


struct Player {
    std::string name;
    Symbol symbol; 
    int score;
};