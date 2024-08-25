//
// Created by Josi on 08.08.2024.
//

#ifndef HIVE_SOUNDHANDLER_H
#define HIVE_SOUNDHANDLER_H


#include <map>
#include <vector>
#include "raylib.h"

class SoundHandler
{
public:
    SoundHandler();
    void playSound(int eventID);
protected:
    std::map<int, std::vector<Sound>> soundMap;
};


#endif //HIVE_SOUNDHANDLER_H
