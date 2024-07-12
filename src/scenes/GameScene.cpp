//
// Created by keanu on 5/23/2024.
//

#include "GameScene.h"
#include "event_management/EventHandler.h"


Scenes::GameScene::GameScene(): Scene(std::make_shared<Camera2D>()),
                                po_levels_(std::make_unique<std::vector<CoreLogic::DataProcessing::Level>>(std::initializer_list<CoreLogic::DataProcessing::Level>{
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"assets/data/test.tmj", "lol"}), 0, CoreLogic::DataProcessing::LevelState::Default),
                                        CoreLogic::DataProcessing::Level(std::make_unique<std::vector<std::string>>(std::initializer_list<std::string>{"lel", "lol"}), 1, CoreLogic::DataProcessing::LevelState::War)
                        })), inputHandler_(std::make_unique<CoreLogic::EventManagement::InputHandler>())
{
    camera_ -> zoom = 1.0f;
    po_currentMap_ = std::make_unique<CoreLogic::DataProcessing::Map>(po_levels_ -> at(0).getMapPath());
    CoreLogic::DataProcessing::ActorStorage::po_layers_ = po_currentMap_ -> getLayers();
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
    Color bgColor = po_currentMap_ -> getBgColor();
    renderer.render(CoreLogic::DataProcessing::ActorStorage::getLayers(), po_actors_, *camera_, pa_canvas, bgColor);
}

void Scenes::GameScene::update()
{
    CoreLogic::DataProcessing::ticks++;

    Camera2D &camera = *camera_;
    /**
     *@note: eventhandler with movement Event version
     **/

    CoreLogic::EventManagement::EventHandler &eventHandler = CoreLogic::EventManagement::EventHandler::getInstance();
    CoreLogic::EventManagement::Actors::Drone &player = *CoreLogic::DataProcessing::ActorStorage::getPlayer();

    /**
     *@todo: InputHandler to be called static
     **/
    eventHandler.handleEvents(inputHandler_->handleInput(), player.getId());
    eventHandler.update();

    if (CoreLogic::DataProcessing::ticks % 15 == 0)
    {
        player.shiftFrame(player.getStateID(), CoreLogic::EventManagement::Direction::UP);
    }

    Vector2 playerPos = player.getPosition();

    /**
     * @attention: keep hard coded?
     * */
    /*(playerPos.x < 464) ? camera.target.x = 0 : camera.target.x = playerPos.x - 464;
    (playerPos.y < 254) ? camera.target.y = 0 : camera.target.y = playerPos.y - 254;
    (playerPos.x > 1104) ? camera.target.x = 576 : camera.target.x = playerPos.x - 464;
    (playerPos.y > 578) ? camera.target.y = 324 : camera.target.y = playerPos.y - 254;*/

    int screenWidth = CoreLogic::DataProcessing::screenWidth_;
    int screenHeight = CoreLogic::DataProcessing::screenHeight_;
    int screenX = screenWidth / 2;
    int screenY = screenHeight / 2;

    Vector2 playerSize = player.getSize();

    if (playerPos.x < screenX - (playerSize.x/2))
    {
        camera.target.x = 0;
    } else if (playerPos.x > 1536 - screenX - (playerSize.x/2)) {
        camera.target.x = 1536 - screenWidth;
    } else {
        camera.target.x = playerPos.x - screenX + (playerSize.x/2);
    }

    if (playerPos.y < screenY - (playerSize.y/2))
    {
        camera.target.y = 0;
    } else if (playerPos.y > 864 - screenY - (playerSize.y/2)) {
        camera.target.y = 864 - screenHeight;
    } else {
        camera.target.y = playerPos.y - screenY + (playerSize.y/2);
    }



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
