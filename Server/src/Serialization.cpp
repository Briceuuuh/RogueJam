/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Serialization
*/

#include "../include/Serialization.hpp"

/**
 * @brief Decodes the binary representation of an event and returns its human-readable form.
 *
 * @return A string representing the human-readable form of the decoded event. Returns nullptr if the binary representation is unknown.
 */
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

/**
 * @brief Encodes an event as a binary representation.
 *
 * @return A string representing the binary-encoded form of the event. Returns nullptr if the event name is unknown.
 */
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

/**
 * @brief Resets or clears the internal state and values.
 */
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

/**
 * @brief Prepares the send package by compressing information, cleaning internal values, and converting to ASCII format.
 *
 * @return A string representing the prepared send package in ASCII format.
 */
std::string Code::getSendPackage()
{
    this->compressInformation();
    this->cleanValue();
    this->switchToAscii();
    return (this->_sendPackage);
}

/**
 * @brief Sets the receive package and processes it by extracting the first two characters, converting to binary format.
 *
 * @param receivePackage A string containing the receive package in ASCII format.
 */

void Code::getReceivePackage(std::string receivePackage)
{
    this->_receivePackage = receivePackage.substr(0, 2);
    this->switchToBinary();
    this->takeInformation();
}

/**
 * @brief Converts the internal receive package from ASCII to binary format.
 */
void Code::switchToBinary()
{
    std::string tmp;
    for (size_t i = 0; i != this->_receivePackage.size(); i++) {
        std::bitset<8> binaire(this->_receivePackage.at(i));
        tmp += binaire.to_string();
    }
    this->_receivePackage = tmp;
}

/**
 * @brief Compresses information for the send package, including room and id values, event code, and input flags.
 */
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

/**
 * @brief Converts the binary-encoded send package to ASCII format.
 */
void Code::switchToAscii()
{
    std::string result = "";
    this->_sendPackage += "000";
    for (size_t i = 0; i != this->_sendPackage.size(); i += 8) {
        std::string byte = this->_sendPackage.substr(i, 8);
        int character = std::bitset<8>(byte).to_ulong();
        result += character;
    }
    this->_sendPackage = result;
}

/**
 * @brief Extracts information from the received package and updates class attributes accordingly.
 */
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

/**
 * @brief Gets the room number stored in the class.
 *
 * @return A reference to the room number.
 */
int &Code::getRoom()
{
    return (this->_room);
}

/**
 * @brief Gets the player's ID stored in the class.
 *
 * @return A reference to the player's ID.
 */

int &Code::getId()
{
    return (this->_id);
}

/**
 * @brief Gets the event string stored in the class.
 *
 * @return A reference to the event string.
 */
std::string &Code::getEvent()
{
    return (this->_event);
}

/**
 * @brief Checks whether the "up" input flag is set in the class.
 *
 * @return True if the "up" input flag is set; false otherwise.
 */
bool Code::getUp()
{
    return (this->_up);
}

/**
 * @brief Checks whether the "down" input flag is set in the class.
 *
 * @return True if the "down" input flag is set; false otherwise.
 */
bool Code::getDown()
{
    return (this->_down);
}

/**
 * @brief Checks whether the "left" input flag is set in the class.
 *
 * @return True if the "left" input flag is set; false otherwise.
 */
bool Code::getLeft()
{
    return (this->_left);
}

/**
 * @brief Checks whether the "right" input flag is set in the class.
 *
 * @return True if the "right" input flag is set; false otherwise.
 */
bool Code::getRight()
{
    return (this->_right);
}

/**
 * @brief Checks whether the "shoot" input flag is set in the class.
 *
 * @return True if the "shoot" input flag is set; false otherwise.
 */
bool Code::getShoot()
{
    return (this->_shoot);
}

/**
 * @brief Changes the room number stored in the class.
 *
 * @param room The new room number.
 */
void Code::changeRoom(int room)
{
    this->_room = room;
}

/**
 * @brief Changes the player's ID stored in the class.
 *
 * @param id The new player's ID.
 */
void Code::changeId(int id)
{
    this->_id = id;
}

/**
 * @brief Changes the event string stored in the class.
 *
 * @param event The new event string.
 */
void Code::changeEvent(std::string event)
{
    this->_event = event;
}

/**
 * @brief Changes the "up" input flag to the specified status.
 *
 * @param status The new status of the "up" input flag (true for active, false for inactive).
 */
void Code::changeUp(bool status)
{
    this->_up = status;
}

/**
 * @brief Changes the "down" input flag to the specified status.
 *
 * @param status The new status of the "down" input flag (true for active, false for inactive).
 */
void Code::changeDown(bool status)
{
    this->_down = status;
}

/**
 * @brief Changes the "left" input flag to the specified status.
 *
 * @param status The new status of the "left" input flag (true for active, false for inactive).
 */
void Code::changeLeft(bool status)
{
    this->_left = status;
}

/**
 * @brief Changes the "right" input flag to the specified status.
 *
 * @param status The new status of the "right" input flag (true for active, false for inactive).
 */
void Code::changeRight(bool status)
{
    this->_right = status;
}

/**
 * @brief Changes the "shoot" input flag to the specified status.
 *
 * @param status The new status of the "shoot" input flag (true for active, false for inactive).
 */
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