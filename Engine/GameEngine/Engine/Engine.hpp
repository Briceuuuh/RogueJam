/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
    #define ENGINE_HPP_
    #include "../Scene/Scene.hpp"
    #include "../System/Clock.hpp"
    #include "../Component/type.hpp"
    #include "../Component/ComponentPackage.hpp"
    #include "./Window.hpp"
    #include "./EManagers/EventManager.hpp"
    #include "./Network/Network.hpp"
    #include "./EManagers/EntityManager.hpp"
    #include "./EManagers/WindowManager.hpp"
    #include "./EManagers/SystemManager.hpp"
    #include "./EManagers/SceneManager.hpp"
    #include "./EManagers/SoundManager.hpp"
    #include "./ClientSession.hpp"
    #include <iostream>
    #include <map>
    using MainLoopCallback = std::function<void()>;

    class WindowManager;
    class EntityManager;
    class SceneManager;
    class SystemManager;
    class ClientSession;
    class Network;
    class SoundManager;

    class Engine {
        public:
            Engine(std::string ip, std::string port);
            ~Engine();

            EventManager *event;
            EntityManager *entity;
            WindowManager *window;
            SystemManager *system;
            Network *network;
            SceneManager *scene;
            GameClock *clock;
            SoundManager *sound;
            bool _DEBUGMOD_ = false;

            void catchWindowEvent(const MainLoopCallback& callback);

            void displayCurrentScene();

            class EngineException : public std::runtime_error {
                public:
                    EngineException(const std::string& msg) : std::runtime_error(msg) {};
            };
        private:
    };

#endif /* !ENGINE_HPP_ */
