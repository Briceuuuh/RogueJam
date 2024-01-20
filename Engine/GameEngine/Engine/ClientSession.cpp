/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

ClientSession::ClientSession(Code *code)
{
    this->_id = code->getId();
    this->_room = code->getRoom();
    this->_up = code->getUp();
    this->_down = code->getDown();
    this->_left = code->getLeft();
    this->_right = code->getRight();
    this->_shoot = code->getShoot();
    this->_home = false;
}

ClientSession::ClientSession(int id, int room)
{
    this->_id = id;
    this->_room = room;
    this->_up = false;
    this->_down = false;
    this->_left = false;
    this->_right = false;
    this->_home = true;
    this->_shoot = false;
}

ClientSession::~ClientSession()
{
}

int &ClientSession::getRoom()
{
    return (this->_room);
}

int &ClientSession::getId()
{
    return (this->_id);
}

bool ClientSession::getUp()
{
    return (this->_up);
}

bool ClientSession::getDown()
{
    return (this->_down);
}

bool ClientSession::getLeft()
{
    return (this->_left);
}

bool ClientSession::getRight()
{
    return (this->_right);
}

bool ClientSession::getShoot()
{
    return (this->_shoot);
}

bool ClientSession::getHome()
{
    return (this->_home);
}

void ClientSession::changeUp(bool value)
{
    this->_up = value;
}

void ClientSession::changeDown(bool value)
{
    this->_down = value;
}

void ClientSession::changeLeft(bool value)
{
    this->_left = value;
}

void ClientSession::changeRight(bool value)
{
    this->_right = value;
}

void ClientSession::changeShoot(bool value)
{
    this->_shoot = value;
}

void ClientSession::changeHome(bool value)
{
    this->_home = value;
}
