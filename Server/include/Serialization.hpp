/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** serialization
*/

#ifndef SERIALIZATION_HPP_
    #define SERIALIZATION_HPP_
    #include <bitset>
    #include <iostream>
    #include <string>

    class Code {
        public:
            Code();
            ~Code();

            void getReceivePackage(std::string);
            void switchToBinary();
            void takeInformation();

            void compressInformation();
            void switchToAscii();
            std::string getSendPackage();

            int &getRoom();
            int &getId();
            std::string &getEvent();
            bool getUp();
            bool getDown();
            bool getLeft();
            bool getRight();
            bool getShoot();

            void changeRoom(int room);
            void changeId(int id);
            void changeEvent(std::string event);
            void changeUp(bool status);
            void changeDown(bool status);
            void changeLeft(bool status);
            void changeRight(bool status);
            void changeShoot(bool status);

            std::string decompressEvent();
            std::string compressEvent();

            void cleanValue();
        private:
            std::string _sendPackage;
            std::string _receivePackage;
            int _room;
            int _id;
            std::string _event;
            bool _up;
            bool _down;
            bool _right;
            bool _left;
            bool _shoot;
    };

#endif /* !SERIALIZATION_HPP_ */