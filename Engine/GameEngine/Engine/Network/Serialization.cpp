/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Serialization
*/
#include "Serialization.hpp"

std::string Code::decompressEvent()
{
    if (this->_event == "000")
        return ("start");
    if (this->_event == "001")
        return ("end");
    if (this->_event == "010")
        return ("display entity");
    if (this->_event == "011")
        return ("remove entity");
    if (this->_event == "100")
        return ("move entity");
    if (this->_event == "101")
        return ("map state");
    if (this->_event == "110")
        return ("error");
    if (this->_event == "111")
        return ("new connection");
    return (nullptr);
}

std::string Code::compressEvent()
{
    if (this->_event == "start")
        return ("000");
    if (this->_event == "end")
        return ("001");
    if (this->_event == "display entity")
        return ("010");
    if (this->_event == "remove entity")
        return ("011");
    if (this->_event == "move entity")
        return ("100");
    if (this->_event == "map state")
        return ("101");
    if (this->_event == "error")
        return ("110");
    if (this->_event == "new connection")
        return ("111");
    return (nullptr);
}

void Code::cleanValue()
{
    std::string str;
    this->_up = false;
    this->_down = false;
    this->_left = false;
    this->_right = false;
    this->_shoot = false;
    this->_id = 0;
    this->_room = 0;
    this->_event.clear();
    this->_receivePackage.clear();
}

std::string &Code::getPackage()
{
    return (this->_sendPackage);
}

std::string Code::getSendPackage()
{
    this->compressInformation();
    this->cleanValue();
    this->_sendPackage += "000";
    this->switchToAscii();
    return (this->_sendPackage);
}

void Code::getReceivePackage(std::string receivePackage)
{
    this->_receivePackage = receivePackage.substr(0, 2);
    this->switchToBinary();
    this->takeInformation();
}

void Code::switchToBinary()
{
    std::string tmp;
    for (size_t i = 0; i != this->_receivePackage.size(); i++) {
        std::bitset<8> binaire(this->_receivePackage.at(i));
        tmp += binaire.to_string();
    }
    this->_receivePackage = tmp;
}

void Code::compressInformation()
{
    this->_id--;
    this->_room--;
    std::string res;
    std::string tmp;
    for (int i = 1; i >= 0; --i) {
        int bit = (this->_room >> i) & 1;
        tmp += std::to_string(bit);
    }
    res += tmp;
    tmp.clear();
    for (int i = 2; i >= 0; --i) {
        int bit = (this->_id >> i) & 1;
        tmp += std::to_string(bit);
    }
    res += tmp;
    res += this->compressEvent();
    if (this->_up == true)
        res.push_back('0');
    else
        res.push_back('1');

    if (this->_down == true)
        res.push_back('0');
    else
        res.push_back('1');

    if (this->_right == true)
        res.push_back('0');
    else
        res.push_back('1');

    if (this->_left == true)
        res.push_back('0');
    else
        res.push_back('1');

    if (this->_shoot == true)
        res.push_back('0');
    else
        res.push_back('1');
    this->_sendPackage = res;
}

void Code::switchToAscii()
{
    std::string result = "";
    for (size_t i = 0; i != this->_sendPackage.size(); i += 8) {
        std::string byte = this->_sendPackage.substr(i, 8);
        int character = std::bitset<8>(byte).to_ulong();
        result += character;
    }
    this->_sendPackage = result;
}

void Code::setSendPackage(std::string send)
{
    this->_sendPackage = send;
}

void Code::setSendPackage(int id, int room, std::string event, bool up, bool down, bool left, bool right, bool shoot)
{
    this->_id = id;
    this->_room = room;
    this->_event = event;
    this->_up = up;
    this->_down = down;
    this->_left = left;
    this->_right = right;
    this->_shoot = shoot;
}

void Code::takeInformation()
{
    std::string tmp = this->_receivePackage.substr(0, 2);
    this->_receivePackage.erase(0, 2);
    int decimal = 0;
    int longueur = tmp.length();
    for (int i = longueur - 1; i >= 0; i--) {
        if (tmp[i] == '1') {
            decimal += 1 << (longueur - 1 - i);
        }
    }
    this->_room = decimal;
    this->_room++;

    tmp = this->_receivePackage.substr(0, 3);
    this->_receivePackage.erase(0, 3);
    decimal = 0;
    longueur = tmp.length();
    for (int i = longueur - 1; i >= 0; i--) {
        if (tmp[i] == '1') {
            decimal += 1 << (longueur - 1 - i);
        }
    }
    this->_id = decimal;
    this->_id++;

    this->_event = this->_receivePackage.substr(0, 3);
    this->_receivePackage.erase(0, 3);
    this->_event = this->decompressEvent();
    if (this->_receivePackage.substr(0, 1) == "0")
        this->_up = true;
    else
        this->_up = false;
    this->_receivePackage.erase(0, 1);

    if (this->_receivePackage.substr(0, 1) == "0")
        this->_down = true;
    else
        this->_down = false;
    this->_receivePackage.erase(0, 1);

    if (this->_receivePackage.substr(0, 1) == "0")
        this->_right = true;
    else
        this->_right = false;
    this->_receivePackage.erase(0, 1);

    if (this->_receivePackage.substr(0, 1) == "0")
        this->_left = true;
    else
        this->_left = false;
    this->_receivePackage.erase(0, 1);

    if (this->_receivePackage.substr(0, 1) == "0")
        this->_shoot = true;
    else
        this->_shoot = false;
    this->_receivePackage.erase(0, 1);
}

int &Code::getRoom()
{
    return (this->_room);
}

int &Code::getId()
{
    return (this->_id);
}

std::string &Code::getEvent()
{
    return (this->_event);
}

bool Code::getUp()
{
    return (this->_up);
}

bool Code::getDown()
{
    return (this->_down);
}

bool Code::getLeft()
{
    return (this->_left);
}

bool Code::getRight()
{
    return (this->_right);
}

bool Code::getShoot()
{
    return (this->_shoot);
}

void Code::changeRoom(int room)
{
    this->_room = room;
}

void Code::changeId(int id)
{
    this->_id = id;
}

void Code::changeEvent(std::string event)
{
    this->_event = event;
}

void Code::changeUp(bool status)
{
    this->_up = status;
}

void Code::changeDown(bool status)
{
    this->_down = status;
}

void Code::changeLeft(bool status)
{
    this->_left = status;
}

void Code::changeRight(bool status)
{
    this->_right = status;
}

void Code::changeShoot(bool status)
{
    this->_shoot = status;
}

Code::Code()
{

}

Code::~Code()
{
}