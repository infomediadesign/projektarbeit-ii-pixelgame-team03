//
// Created by keanu on 6/1/2024.
//
#include "Store.h"

CoreLogic::DataProcessing::TileMap* CoreLogic::DataProcessing::TileMap::po_instance_ = nullptr;
std::mutex CoreLogic::DataProcessing::TileMap::mutex_;

CoreLogic::DataProcessing::TileMap::TileMap()
{
    tileMap_ = std::make_shared<Texture2D>(LoadTexture("assets/graphics/hive_ARTI_TileAtlas_2024-07-02.png"));
}

CoreLogic::DataProcessing::TileMap::~TileMap()
{
    UnloadTexture(*tileMap_);
}

CoreLogic::DataProcessing::TileMap *CoreLogic::DataProcessing::TileMap::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (po_instance_ == nullptr)
    {
        po_instance_ = new TileMap();
    }
    return po_instance_;
}

std::shared_ptr<Texture2D> CoreLogic::DataProcessing::TileMap::getTileMap()
{
    return tileMap_;
}
