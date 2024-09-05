//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_ACTOR_H
#define RAYLIBSTARTER_ACTOR_H


#include <raylib.h>
#include <string>
#include "user_interface/Sprite.h"

namespace CoreLogic::EventManagement
{
    class Actor
    {
    public:
        enum class CollisionType
        {
            NONE = 0,
            COLLISION = 1,
            ENEMYDEATH = 2,
            DEATH = 3,
            WALKABLE = 4
        };


        Actor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, CollisionType pa_collidable, Vector2 pa_size, bool pa_visible, int pa_elevation)
        : position_(pa_position), hitbox_(pa_hitbox), id_(pa_id), collisionType_(pa_collidable), visible_(pa_visible), size_(pa_size), elevation_(pa_elevation) {};
        virtual ~Actor() = default;

        //getters
        Vector2 getPosition(){return position_;};
        Rectangle getHitbox(){return hitbox_;};
        int getId(){return id_;};
        CollisionType getCollisionType(){return collisionType_;};
        void setCollisionType(CollisionType pa_collisionType){ collisionType_ = pa_collisionType;};
        bool getVisible(){return visible_;};
        void setVisible(bool pa_visible){ visible_ = pa_visible;};
        std::string getName(){return name_;};
        Vector2 getSize(){return size_;};

        UserInterface::Sprite getSprite(){return sprite_;};
        int getStateID(){return stateID_;};

        CoreLogic::UserInterface::Direction getPrimaryDirection(){return primaryDirection_;};
        void setPrimaryDirection(CoreLogic::UserInterface::Direction pa_primaryDirection){ primaryDirection_ = pa_primaryDirection;};


        void shiftFrame(int pa_stateID);
        void resetFrame(int pa_stateID);

        [[nodiscard]] int getElevation() const;
        void setElevation(int pa_elevation);

    protected:
        Vector2 position_;
        Rectangle hitbox_;
        const int id_;
        CollisionType collisionType_;
        bool visible_;
        std::string name_;
        const Vector2 size_;
        int elevation_;

        int stateID_ = 0;
        CoreLogic::UserInterface::Direction primaryDirection_ = CoreLogic::UserInterface::Direction::RIGHT;

        CoreLogic::UserInterface::Sprite sprite_;
    };
}



#endif //RAYLIBSTARTER_ACTOR_H
