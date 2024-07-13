//
// Created by keanu on 5/23/2024.
//

#include "Scene.h"

CoreLogic::Scene::Scene(std::shared_ptr <Camera2D> pa_camera): camera_(pa_camera), po_actors_(std::make_shared<std::map<int, std::vector<CoreLogic::EventManagement::Actor>>>()), po_inputHandler_(std::make_unique<CoreLogic::EventManagement::InputHandler>()){}
