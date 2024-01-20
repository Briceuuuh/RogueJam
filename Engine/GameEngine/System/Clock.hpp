/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Clock
*/

#ifndef GAMECLOCK_HPP_
    #define GAMECLOCK_HPP_
    #include <SFML/System.hpp>
    #include <map>
    #include <string>

    class GameClock {
        public:
            GameClock();
            ~GameClock();

            void createClock(std::string clockName);
            void deleteClock(std::string clockName);

            sf::Clock &getClock(std::string clockName);
            void restart(std::string clockName);
            float getTimeElapsed(std::string clockName);

            class ClockException : public std::runtime_error {
                public:
                    ClockException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            std::map<std::string, sf::Clock> _clocks;
    };

#endif /* !GAMECLOCK_HPP_ */
