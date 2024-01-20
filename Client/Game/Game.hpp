/*
** EPITECH PROJECT, 2023
** Sans titre(Espace de travail)
** File description:
** Game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_
    #include "../ImportEngine.hpp"

    class Game {
        public:
            Game(Engine &engine);
            ~Game();
            void gameplayTouch();
            void moveUp();
            void moveDown();
            void moveLeft();
            void moveRight();
            void shoot();
            void moveParallax(std::string parallaxName, float speed);
            void preLaunchSetting();
            void networkProtocol();
            void updateEnnemyHealth();

        private:
            Engine *_engine;
    };

#endif /* !GAME_HPP_ */
