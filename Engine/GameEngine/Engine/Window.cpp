/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Window
*/

#include "Window.hpp"

Window::Window()
{
}

/**
 * @brief Creates a window with the specified dimensions and window title.
 *
 * This function creates a graphical window using the Simple and Fast Multimedia Library (SFML).
 * The window is specified by its width, height, and window title. The function ensures that
 * only one window can be created at a time and that the provided parameters are valid.
 *
 * @param width The width of the window in pixels.
 * @param height The height of the window in pixels.
 * @param windowTitle The title to be displayed in the window's title bar.
 *
 */
void Window::createWindow(int width, int height, std::string windowTitle)
{
    if (windowTitle.empty() || windowTitle.c_str() == nullptr || windowTitle.c_str()[0] == '\0')
        throw WindowException("Window.createWindow error: Empty or invalid window title passed as parameter\n");
    if (this->_window.isOpen())
        throw WindowException("Window.createWindow error: You can't create more than one window (here window: '" + windowTitle + "')\n");
    if (width <= 0 || height <= 0)
        throw WindowException("Window.createWindow error: Null or negative window dimension passed as parameter\n");
    this->_window.create({(unsigned int)width, (unsigned int)height}, windowTitle, sf::Style::Titlebar | sf::Style::Close);
    this->_width = width;
    this->_height = height;
    this->_windowOpened = true;
    this->_window.setFramerateLimit(120);
}

/**
* @brief Clears the window, draws sprites, and displays the content.
 *
 * This function is responsible for updating the window's content. It performs the following actions:
 * 1. Clears the window using the default background color obtained from `getWinDefaultColor()`.
 * 2. Draws all the registered sprites stored in `_spriteToDraw`.
 * 3. Displays the updated content of the window.
 *
 */
void Window::display()
{
    this->_window.clear(this->getWinDefaultColor());

    for (size_t i = 0; i != this->_spriteToDraw.size(); i++)
        this->_window.draw(this->_spriteToDraw.at(i));

    for (size_t i = 0; i != this->_TextToDraw.size(); i++)
        this->_window.draw(*this->_TextToDraw.at(i));

    this->_window.display();
}

/**
 * @brief Closes the window and marks it as closed.
 *
 * This function is responsible for closing the graphical window created by the application.
 * It performs the following actions:
 * 1. Marks the window as closed by setting `_windowOpened` to `false`.
 * 2. Physically closes the window using the SFML library.
 */
void Window::close()
{
    this->_windowOpened = false;
    this->_window.close();
}

/**
 * @brief Sets the title of the window.
 *
 * This function is used to change the title of the graphical window created by the application.
 * It takes a new window title as a parameter and performs the following actions:
 * 1. Checks if the provided `windowName` is empty or contains an invalid character (e.g., '\0').
 * 2. Sets the window title to the provided `windowName` by updating the `_title` member variable.
 * 3. Updates the window's title using the SFML library to reflect the new title.
 *
 * @param windowName The new title to set for the window.
 */
void Window::setTitle(std::string windowName)
{
    if (windowName.empty() || windowName.c_str() == nullptr || windowName.c_str()[0] == '\0')
        throw WindowException("Window.setTitle error: Empty or invalid window title passed as parameter\n");
    this->_title = windowName;
    this->_window.setTitle(windowName);
}

/**
 * @brief Retrieves the title of the window.
 *
 * This function allows you to retrieve the current title of the graphical window.
 *
 * @return A reference to the window's title as a `std::string`.
 */
std::string &Window::getTitle()
{
    return (this->_title);
}

/**
 * @brief Sets the dimensions of the window.
 *
 * This function is used to change the dimensions (width and height) of the graphical window
 * created by the application. It takes new width and height values as parameters and performs
 * the following actions:
 * 1. Checks if the provided `width` and `height` are non-positive (null or negative).
 * 2. Sets the internal `_width` and `_height` member variables to the new values.
 * 3. Updates the window's dimensions using the SFML library to reflect the new size.
 *
 * @param width The new width of the window in pixels.
 * @param height The new height of the window in pixels.
 */
void Window::setDimension(int width, int height)
{
    if (width <= 0 || height <= 0)
        throw WindowException("Window.setDimension error: Null or negative window dimension passed as parameter\n");
    this->_width = width;
    this->_height = height;
    this->_window.setSize({(unsigned int)width, (unsigned int)height});
}

/**
 * @brief Retrieves the current mouse cursor position relative to the window.
 *
 * This function allows you to obtain the current position of the mouse cursor within
 * the graphical window. It uses the SFML library to calculate the position.
 *
 * @return An `sf::Vector2i` representing the current mouse cursor position relative to the window.
 */
sf::Vector2i Window::getMousePosition()
{
    return this->_mouse.getPosition(this->_window);
}

/**
 * @brief Retrieves the dimensions (width and height) of the window.
 *
 * This function allows you to obtain the current dimensions (width and height) of the graphical window.
 * It returns a reference to a static `std::vector<int>` that holds the window's dimensions.
 *
 * @return A reference to a `std::vector<int>` containing the window's dimensions, where index 0 represents
 * the width and index 1 represents the height.
 */
std::vector<int> &Window::getDimension()
{
    static std::vector<int> vec(2);
    vec.at(0) = this->_width;
    vec.at(1) = this->_height;
    return (vec);
}

/**
 * @brief Checks whether the window is currently running.
 *
 * This function allows you to determine whether the graphical window created by the application is currently open and running.
 *
 * @return A reference to a boolean that indicates whether the window is running.
 *         `true` if the window is open and running, `false` if it is closed.
 */
bool &Window::windowIsRunning()
{
    return (this->_windowOpened);
}

/**
 * @brief Sets the default background color for the window.
 *
 * This function allows you to specify a default background color for the graphical window
 * created by the application. The background color will be used when clearing the window.
 *
 * @param color An `sf::Color` representing the new default background color for the window.
 */
void Window::setWinDefaultColor(sf::Color color)
{
    this->_winDefaultColor = color;
}

/**
 * @brief Retrieves the default background color of the window.
 *
 * This function allows you to obtain the current default background color used for the graphical window's
 * background when clearing the window. It returns a reference to an `sf::Color`.
 *
 * @return A reference to the `sf::Color` representing the default background color of the window.
 */
sf::Color &Window::getWinDefaultColor()
{
    return (this->_winDefaultColor);
}

/**
 * @brief Draws a sprite at a specified position within the window and updates the window's content.
 *
 * This function is used to draw a given `sf::Sprite` object at a specified position within the graphical
 * window created by the application. After drawing the sprite, it immediately updates the window's content.
 *
 * @param sprite The `sf::Sprite` object to be drawn within the window.
 * @param position A vector of integers representing the position at which to place the sprite
 *                within the window. The first element represents the x-coordinate, and the second
 *                element represents the y-coordinate.
 */
void Window::drawInWindow(sf::Sprite sprite, std::vector<int> position)
{
    sprite.setPosition({(float)position.at(0), (float)position.at(1)});
    this->_window.draw(sprite);
    this->_window.display();
}

/**
 * @brief Retrieves the underlying SFML RenderWindow object.
 *
 * This function allows you to obtain a reference to the underlying SFML `sf::RenderWindow` object.
 * This object represents the graphical window created by the application and can be used to perform
 * various operations and customization not provided by the Window class.
 *
 * @return A reference to the `sf::RenderWindow` representing the graphical window.
 */
sf::RenderWindow &Window::getRenderWindow()
{
    return (this->_window);
}

/**
 * @brief Sets a collection of sprites to be drawn in the window.
 *
 * This function allows you to specify a collection of `sf::Sprite` objects to be drawn within the
 * graphical window. The provided sprites replace any existing sprites that were set for drawing.
 *
 * @param sprite A vector of `sf::Sprite` objects to be drawn within the window.
 */
void Window::addSpriteToDraw(std::vector<sf::Sprite> sprite)
{
    this->_spriteToDraw = sprite;
}

/**
 * @brief Retrieves the collection of sprites to be drawn in the window.
 *
 * This function allows you to obtain a reference to the collection of `sf::Sprite` objects that have been
 * set to be drawn within the graphical window. These sprites represent the content that will be rendered
 * when the `display()` method is called.
 *
 * @return A reference to a vector of `sf::Sprite` objects to be drawn within the window.
 */
std::vector<sf::Sprite> &Window::getSpriteToDraw()
{
    return (this->_spriteToDraw);
}


/**
 * @brief Sets a collection of text to be drawn in the window.
 *
 * This function allows you to specify a collection of `sf::Text` objects to be drawn within the
 * graphical window. The provided text replace any existing text that were set for drawing.
 *
 * @param sprite A vector of `sf::Text` objects to be drawn within the window.
 */
void Window::addTextToDraw(std::vector<sf::Text *> text)
{
    this->_TextToDraw = text;
}

/**
 * @brief Retrieves the collection of Text to be drawn in the window.
 *
 * This function allows you to obtain a reference to the collection of `sf::Text` objects that have been
 * set to be drawn within the graphical window. These Text represent the content that will be rendered
 * when the `display()` method is called.
 *
 * @return A reference to a vector of `sf::Text` objects to be drawn within the window.
 */
std::vector<sf::Text*> &Window::getTextToDraw()
{
    return (this->_TextToDraw);
}

Window::~Window()
{
}
