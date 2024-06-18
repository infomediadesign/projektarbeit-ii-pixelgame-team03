//
// Created by keanu on 6/1/2024.
//
#include "Store.h"
std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::tileMap_ = std::make_shared<Texture2D>(LoadTexture("assets/graphics/Tile_Atlas.png"));
std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::getTileMap() {return tileMap_;}

std::shared_ptr<CoreLogic::EventManagement::Drone> CoreLogic::DataProcessing::Player::player_ = std::make_shared<CoreLogic::EventManagement::Drone>(
        CoreLogic::EventManagement::Drone({0,0}, {0,0,0,0}, 0)
        );

std::shared_ptr<CoreLogic::EventManagement::Drone> CoreLogic::DataProcessing::Player::getPlayer() {return player_;}
