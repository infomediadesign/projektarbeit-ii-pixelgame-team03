//
// Created by keanu on 5/23/2024.
//

#ifndef RAYLIBSTARTER_ACTOR_H
#define RAYLIBSTARTER_ACTOR_H


#include <raylib.h>
#include <string>

namespace CoreLogic::EventManagement
{
    class Actor
    {
    public:
        enum class CollisionType
        {
            NONE,
            COLLISION,
            ENEMYDEATH,
            DEATH
        };
        enum class Direction
        {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        Actor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, CollisionType pa_collidable, Vector2 pa_size, bool pa_visible, int pa_elevation)
        : position_(pa_position), hitbox_(pa_hitbox), id_(pa_id), collisionType_(pa_collidable), visible_(pa_visible), size_(pa_size), elevation_(pa_elevation) {};
        virtual ~Actor() = default;

        //getters
        Vector2 getPosition(){return position_;};
        Rectangle getHitbox(){return hitbox_;};
        int getId(){return id_;};
        CollisionType getCollisionType(){return collisionType_;};
        bool getVisible(){return visible_;};
        std::string getName(){return name_;};
        Vector2 getSize(){return size_;};



        /**
         *@note: erstmal auskommentiert, da noch in keiner kindklasse implementiert
         **/
//        virtual void shiftFrame() = 0;

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


        /**
         *@todo: implement sprites
         **/
    };
}



#endif //RAYLIBSTARTER_ACTOR_H
