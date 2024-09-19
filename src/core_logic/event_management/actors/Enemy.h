//
// Created by Josi on 12.06.2024.
//

#ifndef HIVE_ENEMY_H
#define HIVE_ENEMY_H

#include <map>
#include "event_management/Actor.h"
#include "data_processing/TilesonUtilities.h"

namespace CoreLogic::EventManagement::Actors {

    class Enemy : public Actor
    {
    public:
        enum EnemyState
        {
            IDLE,
            VISION
        };
        enum EnemyType
        {
            COLONIST,
            MECH
        };

        Enemy(Vector2 pa_position, Rectangle pa_hitbox, int pa_objectId, Vector2 pa_objectSize, int pa_objectElevation, bool pa_objectClockwise,
              CoreLogic::UserInterface::Direction pa_objectStartingDirection, std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_objectTurnCycle,
              Vector2 pa_visionPoint, EnemyType pa_enemyType);
        void update();
        void forceTurn(Vector2 pa_triggerPoint);
        void die();
        [[nodiscard]] bool getVisionConnected()const{return visionConnected_;}

        bool getClockwise() const;
        void setClockwise(bool pa_clockwise);

        [[nodiscard]] bool getDead() const;
        void setDead(bool pa_dead);

        [[nodiscard]] std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> getTurnCycles() const;
        void setTurnCycles(std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> pa_turnCycles);

        void setState(EnemyState pa_state) { state_ = pa_state; }
    protected:
        bool visionConnected_ = false;
        const Vector2 visionOrigin_;
        void checkVision();

        bool checkVisionCollisionObjects(DataProcessing::Line *pa_visionRays, bool *pa_visionCollisions);
        bool clockwise_;
        std::map<CoreLogic::UserInterface::Direction, std::pair<int, int>> turnCycles;
        void updateTurnCycle();
        void shiftFrame(int pa_frameShift) override;

        void turn();
        bool dead_ = false;
        EnemyState state_ = IDLE;
        EnemyType enemyType_ = COLONIST;

    };
}

#endif //HIVE_ENEMY_H
