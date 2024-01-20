/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** WindowManager
*/

#include "WindowManager.hpp"
#include "./../Engine.hpp"

/**
 * Constructor for the WindowManager class.
 * Initializes a WindowManager with references to defaultScene, actualScene, and a scene map.
 *
 * @param defaultScene A reference to the default scene's name.
 * @param actualScene  A reference to the currently active scene's name.
 * @param scene        A reference to a map of scene names to IScene pointers.
 */
WindowManager::WindowManager(std::string &defaultScene, std::string &actualScene, std::map<std::string, IScene *> &scene) : _defaultScene(defaultScene), _actualScene(actualScene), _scene(scene)
{
    this->_window = new Window();
}

/**
 * Creates a window for rendering.
 *
 * @param width       An integer representing the width of the window.
 * @param height      An integer representing the height of the window.
 * @param windowTitle A string representing the title of the window.
 *
 * @throws WindowManagerException if the default scene, actual scene, or scene map is not properly initialized.
 */
void WindowManager::create(int width, int height, std::string windowTitle)
{
    if (this->_defaultScene == "None" || this->_actualScene == "None" || this->_scene.size() <= 0)
        throw WindowManagerException("WindowManager.create error: You can't create window because the engine don't have any scenes\n");
    this->_window->createWindow(width, height, windowTitle);
}

/**
 * Displays the contents of the window.
 */
void WindowManager::display()
{
    this->_window->display();
}

/**
 * Closes the window.
 */
void WindowManager::close()
{
    this->_window->close();
}

/**
 * Runs the main loop for the window.
 *
 * @param callback A MainLoopCallback function or callable that is executed in the main loop.
 * @param engine   A reference to an Engine object.
 */
void WindowManager::run(const MainLoopCallback& callback, Engine &engine)
{
    while (this->_window->windowIsRunning()) {
        callback();
        this->_window->display();
        engine.displayCurrentScene();
    }
}

/**
 * @brief Set the title of the window.
 *
 * This function allows you to set the title of the window to the specified string. The window title is typically displayed in the
 * window's title bar.
 *
 * @param windowTitle A string specifying the new window title.
 */
void WindowManager::setTitle(std::string windowTitle)
{
    this->_window->setTitle(windowTitle);
}

/**
 * @brief Get the current title of the window.
 *
 * This function returns the current title of the window as a string.
 *
 * @return A reference to a string specifying the current window title.
 */

std::string &WindowManager::getTitle()
{
    return (this->_window->getTitle());
}

/**
 * @brief Set the dimensions (width and height) of the window.
 *
 * This function allows you to set the dimensions of the window by specifying the new width and height. It controls the size of the
 * window's rendering area.
 *
 * @param width The new width of the window.
 * @param height The new height of the window.
 */
void WindowManager::setDimension(int width, int height)
{
    this->_window->setDimension(width, height);
}

/**
 * @brief Get the current dimensions (width and height) of the window.
 *
 * This function returns the current dimensions of the window as a vector of integers [width, height].
 *
 * @return A reference to a vector of integers specifying the current dimensions of the window [width, height].
 */
std::vector<int> &WindowManager::getDimension()
{
    static std::vector<int> vec(2);
    vec.at(0) = this->_window->getDimension().at(0);
    vec.at(1) = this->_window->getDimension().at(1);

    return (vec);
}

/**
 * @brief Get the current mouse position within the window.
 *
 * This function returns the current mouse position within the window as an sf::Vector2i object.
 *
 * @return An sf::Vector2i object specifying the current mouse position.
 */
sf::Vector2i WindowManager::getMousePosition()
{
    return this->_window->getMousePosition();
}

/**
 * @brief Set the default background color for the window.
 *
 * This function allows you to set the default background color for the window. The specified color will be used as the default
 * background color when rendering the scene.
 *
 * @param color An sf::Color object specifying the new default background color.
 */
void WindowManager::setDefaultColor(sf::Color color)
{
    this->_window->setWinDefaultColor(color);
}

/**
 * @brief Get the current default background color for the window.
 *
 * This function returns the current default background color for the window as an sf::Color object.
 *
 * @return A reference to an sf::Color object specifying the current default background color.
 */
sf::Color &WindowManager::getDefaultColor()
{
    return (this->_window->getWinDefaultColor());
}

/**
 * @brief Get a reference to the window managed by the WindowManager.
 *
 * This function returns a reference to the window managed by the WindowManager, allowing access to its properties and methods.
 *
 * @return A reference to the Window object managed by the WindowManager.
 */
Window &WindowManager::get()
{
    return (*this->_window);
}

/**
 * @brief Get a reference to the sf::RenderWindow associated with the window managed by the WindowManager.
 *
 * This function returns a reference to the sf::RenderWindow associated with the window managed by the WindowManager. It allows direct
 * access to the underlying RenderWindow for advanced rendering and configuration.
 *
 * @return A reference to the sf::RenderWindow associated with the window managed by the WindowManager.
 */
sf::RenderWindow &WindowManager::getWindow()
{
    return (this->_window->getRenderWindow());
}

WindowManager::~WindowManager()
{
    delete (this->_window);
}
