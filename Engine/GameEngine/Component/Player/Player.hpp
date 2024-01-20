/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_
    #include "../IComponent.hpp"

    class Player : public IComponent {
        public:
            Player();
            ~Player();
            ComponentType_t &GetType();
            bool &isPlayer();
            void playerState(bool state);
            int &getLevel();
            void setLevel(int level);

        private:
            bool _player = true;
            int _level = 0;
            ComponentType_t _type = PLAYER;
    };

#endif /* !PLAYER_HPP_ */
