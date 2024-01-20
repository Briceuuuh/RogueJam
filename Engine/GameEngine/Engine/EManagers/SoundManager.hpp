/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** SoundManager
*/

#ifndef SOUNDMANAGER_HPP_
    #define SOUNDMANAGER_HPP_
    #include <iostream>
    #include <map>
    #include <string>
    #include <SFML/Audio.hpp>
    #include "../Engine.hpp"

    typedef enum SoundType {
        SOUND,
        MUSIC
    } SoundType_t;

    class SoundManager {
        public:
            SoundManager();
            ~SoundManager();
            void Create(SoundType_t type, std::string audioName, std::string audioPath);
            void Delete(SoundType_t type, std::string audioName);
            void play(SoundType_t type, std::string audioName);
            void pause(SoundType_t type, std::string audioName);
            void stop(SoundType_t type, std::string audioName);
            void setVolume(SoundType_t type, std::string audioName, float volume);
            void setLoop(std::string audioName, bool state);

            class SoundManagerException : public std::runtime_error {
                public:
                    SoundManagerException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            std::map<std::string, sf::Music*> _musics;
            std::map<std::string, sf::Sound*> _sounds;
    };

#endif /* !SOUNDMANAGER_HPP_ */
