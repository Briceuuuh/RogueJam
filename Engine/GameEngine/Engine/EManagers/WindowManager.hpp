/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** WindowManager
*/

#ifndef WINDOWMANAGER_HPP_
    #define WINDOWMANAGER_HPP_
    #include <string>
    #include <functional>
    #include "../Window.hpp"
    #include "../../Scene/Scene.hpp"
    #include "../../Engine/Engine.hpp"
    using MainLoopCallback = std::function<void()>;

    class Engine;

    class WindowManager {
        public:
            WindowManager(std::string &defaultScene, std::string &actualScene, std::map<std::string, IScene *> &scene);
            ~WindowManager();
            void create(int width, int height, std::string windowTitle);
            void display();
            void close();
            void run(const MainLoopCallback& callback, Engine &engine);
            void setTitle(std::string windowTitle);
            std::string &getTitle();

            sf::Vector2i getMousePosition();

            void setDimension(int width, int height);
            std::vector<int> &getDimension();
            void setDefaultColor(sf::Color color);
            sf::Color &getDefaultColor();
            Window &get();
            sf::RenderWindow &getWindow();

            class WindowManagerException : public std::runtime_error {
                public:
                    WindowManagerException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            std::string &_defaultScene;
            std::string &_actualScene;
            Window *_window;
            std::map<std::string, IScene *> &_scene;
    };

#endif /* !WINDOWMANAGER_HPP_ */
