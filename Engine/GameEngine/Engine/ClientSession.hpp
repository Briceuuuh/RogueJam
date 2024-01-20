/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** ClientSession
*/

#ifndef CLIENTSESSION_HPP_
    #define CLIENTSESSION_HPP_
    #include "./Network/Serialization.hpp"

    class ClientSession {
        public:
            ClientSession(Code *code);
            ClientSession(int id, int room);
            ~ClientSession();
            int &getRoom();
            int &getId();
            bool getUp();
            bool getDown();
            bool getLeft();
            bool getRight();
            bool getShoot();
            bool getHome();
            void changeHome(bool value);
            void changeUp(bool value);
            void changeDown(bool value);
            void changeLeft(bool value);
            void changeRight(bool value);
            void changeShoot(bool value);

        private:
            int _id;
            int _room;
            bool _up;
            bool _down;
            bool _left;
            bool _right;
            bool _shoot;
            bool _home;
    };

#endif /* !CLIENTSESSION_HPP_ */
