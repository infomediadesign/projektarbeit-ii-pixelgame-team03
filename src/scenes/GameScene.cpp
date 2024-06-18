//
// Created by keanu on 5/23/2024.
//

#include "GameScene.h"
#include "event_management/EventHandler.h"


Scenes::GameScene::GameScene(): Scene(std::make_shared<Camera2D>()),
                                po_levels_(std::make_unique<std::vector<CoreLogic::DataProcessing::Level>>(std::initializer_list<CoreLogic::DataProcessing::Level>{
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"assets/data/test.tmj", "lol"}), 0, CoreLogic::DataProcessing::LevelState::Default),
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"lel", "lol"}), 1, CoreLogic::DataProcessing::LevelState::War)
                        }))
{
    camera_ -> zoom = 1.0f;
    po_currentMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(po_levels_ -> at(0).getMapPath());
    po_previousMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(*po_currentMap_);
    currentLevelID_ = po_levels_ -> at(0).getLevelID();
    previousLevelID_ = currentLevelID_;
}

int Scenes::GameScene::getCurrentLevelID()
{
    return currentLevelID_;
}

void Scenes::GameScene::draw(RenderTexture2D &pa_canvas)
{
    CoreLogic::UserInterface::Renderer& renderer = *CoreLogic::UserInterface::Renderer::getInstance();
    std::shared_ptr<std::vector<tson::Layer>> layers = po_currentMap_ -> getLayers();
    Color bgColor = po_currentMap_ -> getBgColor();
    renderer.render(layers, po_actors_, *camera_, pa_canvas, bgColor);
}

void Scenes::GameScene::update()
{
    CoreLogic::DataProcessing::ticks++;

    Camera2D &camera = *camera_;
    /**
     *@note: eventhandler with movement Event version
     **/

    CoreLogic::EventManagement::EventHandler &eventHandler = CoreLogic::EventManagement::EventHandler::getInstance();
    CoreLogic::EventManagement::Actors::Drone &player = *CoreLogic::DataProcessing::Player::getPlayer();

    /**
     *@todo: InputHandler to be called static
     **/
    eventHandler.handleEvents(InputHandler::handleInput(), player.getId());
    eventHandler.update();
    Vector2 playerPos = player.getPosition();

    /**
     * @attention: keep hard coded?
     * */
    (playerPos.x < 464) ? camera.target.x = 0 : camera.target.x = playerPos.x - 464;
    (playerPos.y < 254) ? camera.target.y = 0 : camera.target.y = playerPos.y - 254;
    (playerPos.x > 1104) ? camera.target.x = 576 : camera.target.x = playerPos.x - 464;
    (playerPos.y > 578) ? camera.target.y = 324 : camera.target.y = playerPos.y - 254;


    /**
     *@note: old prototype movement
     **/
    /*if (IsKeyDown(KEY_LEFT))
     {
        if (IsKeyDown(KEY_UP))
        {
            camera.target.x -= 2;
            camera.target.y -= 2;
            return;
        }
        camera.target.x -= 3;
     }
     if (IsKeyDown(KEY_RIGHT))
     {
         camera.target.x += 3;
     }
     if (IsKeyDown(KEY_UP))
     {
         camera.target.y -= 3;
     }
     if (IsKeyDown(KEY_DOWN))
     {
         camera.target.y += 3;
     }*/

    /**
     * @Pseudo_Code: So soll nachher der Eventhandler evtl. aussehen
     * @note: veraltet
     */

   /* KeyboardKey *keys = GetKeyPressed();
    if (keys == nullptr)
    {
        GamepadButton *buttons = InputHandler::getGamepadInputs();
        GamepadAxis *axes = InputHandler::getGamepadAxes();
    }

    Commands* commands = InputHandler::getCommands(keys);

    EventHandler::handleCommands(commands);*/

}


void Scenes::GameScene::render()
{

}

void Scenes::GameScene::switchLevel()
{

}
