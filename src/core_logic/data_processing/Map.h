//
// Created by keanu on 5/22/2024.
//

#ifndef RAYLIBSTARTER_MAP_H
#define RAYLIBSTARTER_MAP_H


#include <vector>
#include "TilesonUtilities.h"
#include "raylib.h"
#include "event_management/Actor.h"
#include "event_management/actors/enemies/Hazmat.h"
#include "event_management/actors/enemies/Colonist.h"
#include "event_management/actors/enemies/Mech.h"


namespace CoreLogic::DataProcessing
{
    class Map
    {
    public:
        explicit Map(std::string pa_filename);

        std::shared_ptr<tson::Map> getMap();

        std::shared_ptr<std::map<int, std::vector<tson::Layer>>> getLayers();

        std::shared_ptr<std::map<int, std::vector<tson::Object>>> getObjects();

        Color getBgColor();

    private:
        Map() = delete;

    protected:
        std::shared_ptr<tson::Map> po_map_;
        std::shared_ptr<std::map<int, std::vector<tson::Layer>>> po_layers_;
        std::shared_ptr<std::map<int, std::vector<tson::Object>>> po_objects_;
        int elevationLevels_;
        int levelID_;
        Color bgColor_;
        void loadObjects();
        void initializeLists();

        template <typename T>
        typename std::enable_if<!std::is_pointer<T>::value && !std::is_same<T, std::shared_ptr<typename std::remove_reference<T>::type>>::value,
                std::shared_ptr<std::map<int, std::vector<T>>>>::type
        initializeSpecificLists();
        template <typename T>
        typename std::enable_if<std::is_same<T, std::shared_ptr<typename std::remove_reference<T>::type>>::value,
                std::shared_ptr<std::map<int, std::vector<T>>>>::type
        initializeSpecificLists();

    };
}



#endif //RAYLIBSTARTER_MAP_H
