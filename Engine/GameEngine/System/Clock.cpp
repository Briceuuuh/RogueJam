/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Clock
*/

#include "Clock.hpp"
#include <iostream>

GameClock::GameClock()
{
}

GameClock::~GameClock()
{
}
/**
 * @brief Create a named clock for time management.
 *
 * @param clockName The name of the clock to be created.
 * @throws ClockException if clockName is empty, null, or already exists.
 */
void GameClock::createClock(std::string clockName)
{
    if (clockName.empty() || clockName.c_str() == nullptr || clockName.c_str()[0] == '\0')
        throw ClockException("Clock.create: Invalide or null clock name passed as parameter\n");
    if (this->_clocks.find(clockName) != this->_clocks.end())
        throw ClockException("Clock.create: Clock with the name: " + clockName + ", already exist\n");
    sf::Clock clock;
    std::pair<std::string, sf::Clock> newline(clockName, clock);
    this->_clocks.insert(newline);
}

/**
 * @brief Delete a named clock.
 *
 * @param clockName The name of the clock to be deleted.
 * @throws ClockException if clockName is empty, null, or the clock doesn't exist.
 */
void GameClock::deleteClock(std::string clockName)
{
    if (clockName.empty() || clockName.c_str() == nullptr || clockName.c_str()[0] == '\0')
        throw ClockException("Clock.delete: Invalide or null clock name passed as parameter\n");

    auto line = this->_clocks.find(clockName);
    if (line == this->_clocks.end())
        throw ClockException("Clock.delete: Clock with the name: " + clockName + ", not exist\n");

    this->_clocks.erase(line);
}

/**
 * @brief Retrieve a reference to a named clock.
 *
 * @param clockName The name of the clock to be retrieved.
 * @throws ClockException if clockName is empty, null, or the clock doesn't exist.
 * @return Reference to an sf::Clock object.
 */
sf::Clock &GameClock::getClock(std::string clockName)
{
    if (clockName.empty() || clockName.c_str() == nullptr || clockName.c_str()[0] == '\0')
        throw ClockException("Clock.getClock: Invalide or null clock name passed as parameter\n");

    auto line = this->_clocks.find(clockName);
    if (line == this->_clocks.end())
        throw ClockException("Clock.getClock: Clock with the name: " + clockName + ", not exist\n");

    return (line->second);
}

/**
 * @brief Restart a named clock, resetting its elapsed time to zero.
 *
 * @param clockName The name of the clock to be restarted.
 * @throws ClockException if clockName is empty, null, or the clock doesn't exist.
 */
void GameClock::restart(std::string clockName)
{
    if (clockName.empty() || clockName.c_str() == nullptr || clockName.c_str()[0] == '\0')
        throw ClockException("Clock.restart: Invalide or null clock name passed as parameter\n");

    auto line = this->_clocks.find(clockName);
    if (line == this->_clocks.end())
        throw ClockException("Clock.restart: Clock with the name: " + clockName + ", not exist\n");

    line->second.restart();
}

/**
 * @brief Get the elapsed time in seconds from a named clock.
 *
 * @param clockName The name of the clock for which you want to get the elapsed time.
 * @throws ClockException if clockName is empty, null, or the clock doesn't exist.
 * @return Elapsed time in seconds as a floating-point value.
 */
float GameClock::getTimeElapsed(std::string clockName)
{
    if (clockName.empty() || clockName.c_str() == nullptr || clockName.c_str()[0] == '\0')
        throw ClockException("Clock.getTimeElapsed: Invalide or null clock name passed as parameter\n");

    auto line = this->_clocks.find(clockName);
    if (line == this->_clocks.end())
        throw ClockException("Clock.getTimeElapsed: Clock with the name: " + clockName + ", not exist\n");

    return (line->second.getElapsedTime().asSeconds());
}