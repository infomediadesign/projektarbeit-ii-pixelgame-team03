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
        Actor(Vector2 pa_position, Rectangle pa_hitbox, int pa_id, bool pa_collidable, std::string pa_name, Vector2 pa_size, bool pa_visible, int pa_elevation);
        virtual ~Actor() = default;

        //getters
        Vector2 getPosition(){return position_;};
        Rectangle getHitbox(){return hitbox_;};
        int getId(){return id_;};
        bool getCollidable(){return collidable_;};
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
        bool collidable_;
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
