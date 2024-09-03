//
// Created by Josi on 03.09.2024.
//

#ifndef HIVE_LEVELSWITCH_H
#define HIVE_LEVELSWITCH_H

namespace CoreLogic::EventManagement::Object
{
    class LevelSwitch
    {
    public:
        int getNewLevelID() const;
    protected:
        int newLevelID_;
    };
}

#endif //HIVE_LEVELSWITCH_H
