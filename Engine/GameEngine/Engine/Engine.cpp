/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(std::string ip, std::string port)
{
    this->event = new EventManager();
    this->scene = new SceneManager(*this);
    this->entity = new EntityManager(this->scene->getScene(), *this);
    this->window = new WindowManager(this->scene->getDefaultScene(), this->scene->getActualScene(), this->scene->getScene());
    this->clock = new GameClock();
    this->system = new SystemManager(*this);
    this->network = new Network(*this, ip, port);
    this->sound = new SoundManager();
}

/**
 * @brief Continuously monitor and catch window events, invoking the provided callback.
 *
 * @param callback A function to be called for each window event.
 */
void Engine::catchWindowEvent(const MainLoopCallback& callback)
{
    while (this->window->getWindow().pollEvent(this->event->getEventAttribut())) {
        if (this->event->WindowCloseEvent() || this->scene->getActualScene() == "close")
            this->window->close();
        callback();
    }
}

/**
 * @brief Display the entities in the current game scene.
 *
 * This method displays the entities in the current game scene. It checks for the visibility of entities and their components, and adds visible entities to the rendering queue. The scene is then displayed using the window manager.
 */
void Engine::displayCurrentScene()
{
    if (this->scene->getDefaultScene() == "None" || this->scene->getActualScene() == "None" || this->scene->getScene().size() <= 0)
        throw EngineException("Engine.drawScene error: You can't draw scene because the engine don't have any scenes\n");

    auto scene = this->scene->getScene().find(this->scene->getActualScene());
    if (scene == this->scene->getScene().end())
        throw EngineException("Engine.drawScene error: Can't draw scene\n");

    std::map<std::string, IEntity *> sceneEntity = scene->second->getEntity();

    std::vector<sf::Sprite> validSpriteToDraw;
    std::vector<sf::Text *> validTextToDraw;

    for (auto ent = sceneEntity.begin(); ent != sceneEntity.end(); ent++) {
        bool visible = true;
        bool valid = false;
        Visual *visualComp = (Visual *)ent->second->getComponent(VISUAL);
        Position *positionComp = (Position *)ent->second->getComponent(POSITION);
        Text *text = (Text *)ent->second->getComponent(TEXT);
        if (visualComp && positionComp)
            valid = true;
        if (visualComp->isVisible())
            visible = true;
        if (valid && visible && !text) {
            std::vector<int> pos(2);
            pos = positionComp->getPostion();
            visualComp->getSprite().setPosition((float)pos.at(0), (float)pos.at(1));
            validSpriteToDraw.push_back(visualComp->getSprite());
        }
        if (valid && visible && text) {
            std::vector<int> pos(2);
            pos = positionComp->getPostion();
            // visualComp->getSprite().setPosition((float)pos.at(0), (float)pos.at(1));
            validTextToDraw.push_back(&text->getText());
        }
    }

    this->window->get().addSpriteToDraw(validSpriteToDraw);
    this->window->get().addTextToDraw(validTextToDraw);
    this->window->display();
    std::cout << "stop\n";

    if (this->_DEBUGMOD_ == true) {
        std::cout << "---------------------| Scene debug |---------------------"<< std::endl;
        std::cout << "Current scene: [" + this->scene->getActualScene() + "]"<< std::endl;
        std::cout << "Current entity in scene:"<< std::endl;
        for (auto i = sceneEntity.begin(); i != sceneEntity.end(); i++) {
            std::cout << "\t[Entity name]:\t" + i->second->getName() + "";
            std::vector<IComponent*> comp = i->second->GetCurrentComponent();
            std::cout << "\n\t\t[Components id]: ";
            for (size_t j = 0; j != comp.size(); j++) {
                if (j + 1 == comp.size())
                    std::cout << "[" << comp.at(j)->GetType() << "]" << std::endl;
                else
                    std::cout << "[" << comp.at(j)->GetType() << "], ";

            }
        }
        std::cout << "---------------------------------------------------------\n"<< std::endl;
    }
}

/**
 * @brief Destructor for the Engine class.
 *
 * This destructor deallocates the memory used by the `Entity`, `EventManager`, and `WindowManager` objects created during the engine's lifetime.
 */
Engine::~Engine()
{
    delete (this->event);
    delete (this->scene);
    delete (this->entity);
    delete (this->window);
    delete (this->clock);
    delete (this->system);
    delete (this->network);
}
