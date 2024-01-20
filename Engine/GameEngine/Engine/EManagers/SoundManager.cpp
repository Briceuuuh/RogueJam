/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** SoundManager
*/

#include "SoundManager.hpp"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

/**
 * @brief Create and load an audio resource (sound or music) and add it to the sound manager.
 *
 * This function allows you to manage audio assets for use in your application.
 *
 * @param type The type of audio resource to create (SOUND for sound, MUSIC for music).
 * @param audioName The name to assign to the audio resource.
 * @param audioPath The file path to the audio asset to be loaded.
 * @throws SoundManagerException if the audio resource with the same name already exists or if loading the audio asset fails.
 */
void SoundManager::Create(SoundType_t type, std::string audioName, std::string audioPath)
{
    if (type == SOUND) {
        auto find = this->_sounds.find(audioName);
        if (find != this->_sounds.end())
            throw SoundManagerException("Sound.Create: Sound with the name '" + audioName + "' already exist in the sound managers");

        sf::SoundBuffer *buffer = new sf::SoundBuffer();
        if (!buffer->loadFromFile(audioPath)) {
            std::cerr << "Sound.Create: " + audioName + " can't be loaded." << std::endl;
            return;
        }
        sf::Sound *sound = new sf::Sound();
        sound->setBuffer(*buffer);
        std::pair<std::string, sf::Sound*> newline(audioName, sound);

        this->_sounds.insert(newline);
    } else {
        auto find = this->_musics.find(audioName);
        if (find != this->_musics.end())
            throw SoundManagerException("Sound.Create: Music with the name '" + audioName + "' already exist in the sound managers");
        sf::Music *music = new sf::Music();
        if (!music->openFromFile(audioPath)) {
            std::cerr << "Sound.Create: " + audioName + " can't be loaded." << std::endl;
            return;
        }
        std::pair<std::string, sf::Music*> newline(audioName, music);
        this->_musics.insert(newline);
    }
}

/**
 * @brief Delete an existing audio resource (sound or music) from the sound manager.
 *
 * This function allows you to remove audio assets from the manager when they are no longer needed.
 *
 * @param type The type of audio resource to delete (SOUND for sound, MUSIC for music).
 * @param audioName The name of the audio resource to be deleted.
 * @throws SoundManagerException if the specified audio resource does not exist in the sound manager.
 */
void SoundManager::Delete(SoundType_t type, std::string audioName)
{
    if (type == SOUND) {
        auto find = this->_sounds.find(audioName);
        if (find != this->_sounds.end())
            this->_sounds.erase(find);
        else
            throw SoundManagerException("Sound.Delete: Sound with the name '" + audioName + "' not exist in the sound managers");
    } else {
        auto find = this->_musics.find(audioName);
        if (find != this->_musics.end())
            this->_musics.erase(find);
        else
            throw SoundManagerException("Sound.Delete: Music with the name '" + audioName + "' not exist in the sound managers");
    }
}

/**
 * @brief Play an audio resource (sound or music) from the sound manager.
 *
 * This function allows you to control the playback of audio assets in your application.
 *
 * @param type The type of audio resource to play (SOUND for sound, MUSIC for music).
 * @param audioName The name of the audio resource to be played.
 * @throws SoundManagerException if the specified audio resource does not exist in the sound manager or if the music resource is already playing.
 */
void SoundManager::play(SoundType_t type, std::string audioName)
{
    if (type == SOUND) {
        auto find = this->_sounds.find(audioName);
        if (find != this->_sounds.end())
            find->second->play();
        else
            throw SoundManagerException("Sound.Play: Sound with the name '" + audioName + "' not exist in the sound managers");
    } else {
        auto find = this->_musics.find(audioName);
        if (find != this->_musics.end() && find->second->getStatus() == sf::Sound::Status::Stopped) {
            find->second->play();
        } else if (find != this->_musics.end() && find->second->getStatus() != sf::Sound::Status::Stopped)
            return;
        else
            throw SoundManagerException("Sound.Play: Music with the name '" + audioName + "' not exist in the sound managers");
    }
}

/**
 * @brief Pause an audio resource (sound or music) that is currently playing.
 *
 * This function provides control over the playback of audio assets in your application.
 *
 * @param type The type of audio resource to pause (SOUND for sound, MUSIC for music).
 * @param audioName The name of the audio resource to be paused.
 * @throws SoundManagerException if the specified audio resource does not exist in the sound manager.
 */
void SoundManager::pause(SoundType_t type, std::string audioName)
{
    if (type == SOUND) {
        auto find = this->_sounds.find(audioName);
        if (find != this->_sounds.end())
            find->second->pause();
        else
            throw SoundManagerException("Sound.Pause: Sound with the name '" + audioName + "' not exist in the sound managers");
    } else {
        auto find = this->_musics.find(audioName);
        if (find != this->_musics.end())
            find->second->pause();
        else
            throw SoundManagerException("Sound.Pause: Music with the name '" + audioName + "' not exist in the sound managers");
    }
}

/**
 * @brief Stop the playback of an audio resource (sound or music) from the sound manager.
 *
 * This function provides control over stopping audio assets in your application.
 *
 * @param type The type of audio resource to stop (SOUND for sound, MUSIC for music).
 * @param audioName The name of the audio resource to be stopped.
 * @throws SoundManagerException if the specified audio resource does not exist in the sound manager.
 */

void SoundManager::stop(SoundType_t type, std::string audioName)
{
    if (type == SOUND) {
        auto find = this->_sounds.find(audioName);
        if (find != this->_sounds.end())
            find->second->stop();
        else
            throw SoundManagerException("Sound.Stop: Sound with the name '" + audioName + "' not exist in the sound managers");
    } else {
        auto find = this->_musics.find(audioName);
        if (find != this->_musics.end())
            find->second->stop();
        else
            throw SoundManagerException("Sound.Stop: Music with the name '" + audioName + "' not exist in the sound managers");
    }
}

/**
 * @brief Set the volume level of an audio resource (sound or music) from the sound manager.
 *
 * This function allows you to control the volume of audio assets in your application.
 *
 * @param type The type of audio resource to set the volume for (SOUND for sound, MUSIC for music).
 * @param audioName The name of the audio resource for which the volume should be set.
 * @param volume The desired volume level specified as a floating-point value.
 * @throws SoundManagerException if the specified audio resource does not exist in the sound manager.
 */
void SoundManager::setVolume(SoundType_t type, std::string audioName, float volume)
{
    if (type == SOUND) {
        auto find = this->_sounds.find(audioName);
        if (find != this->_sounds.end())
            find->second->setVolume(volume);
        else
            throw SoundManagerException("Sound.setVolume: Sound with the name '" + audioName + "' not exist in the sound managers");
    } else {
        auto find = this->_musics.find(audioName);
        if (find != this->_musics.end())
            find->second->setVolume(volume);
        else
            throw SoundManagerException("Sound.setVolume: Music with the name '" + audioName + "' not exist in the sound managers");
    }
}

/**
 * @brief Set the loop state of a music by name.
 *
 * This function sets the loop state of a loaded music by its unique name. If the music with the specified name exists in the sound manager, its loop state will be updated to the specified value. If the music does not exist, a SoundManagerException will be thrown.
 *
 * @param audioName The unique name of the music to modify the loop state for.
 * @param state A boolean indicating whether the music should loop (true) or play once (false).
 *
 * @throw SoundManagerException If the music with the given name does not exist in the sound manager.
 */
void SoundManager::setLoop(std::string audioName, bool state)
{
    auto find = this->_musics.find(audioName);
    if (find != this->_musics.end())
        find->second->setLoop(state);
    else
        throw SoundManagerException("Sound.setLoop: Music with the name '" + audioName + "' not exist in the sound managers");
}
