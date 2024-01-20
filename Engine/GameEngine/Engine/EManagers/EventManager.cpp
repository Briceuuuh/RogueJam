/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** EventManager
*/

#include "EventManager.hpp"

/**
 * @brief Construct a new EventManager object.
 *
 * The EventManager class manages various types of events such as keyboard input events and window close events. It initializes with keyboard input, close events, and mouse events as catchable by default.
 */
EventManager::EventManager()
{
    this->addEventToCatch(KEY_INPUT, MOUSE_EVENT, CLOSE_EVENT);
}

/**
 * @brief Get the event attributes.
 *
 * This function provides access to the attributes of the most recent event. You can use this to inspect the type and other details of the event.

 * @return A reference to the SFML event object (`sf::Event`) that stores the event's attributes.
 */
sf::Event &EventManager::getEventAttribut()
{
    return (this->_event);
}

/**
 * @brief Check for a window close event.
 *
 * This function checks if window close events are catchable and, if so, whether a window close event has occurred. If the application has specified that window close events should be caught, this function returns `true` if a window close event has been detected.

 * @return `true` if a window close event has occurred and is catchable, otherwise `false`.
 */
bool EventManager::WindowCloseEvent()
{
    bool catchValue = false;

    for (size_t i = 0; i != this->_eventCatchable.size(); i++) {
        if (this->_eventCatchable.at(i) == CLOSE_EVENT)
            catchValue = true;
    }

    if (!catchValue)
        return false;

    if (this->_event.type == sf::Event::Closed)
        return true;
    return false;
}

/**
 * @brief Get the type of key that was pressed.
 *
 * This function checks if keyboard input events are catchable and, if so, returns the type of key that was pressed. If the application has specified that keyboard input events should be caught, this function returns the type of key that was pressed based on the detected key press event.

 * @return The type of key that was pressed (keyboardInput_t). It returns a specific key code (e.g., KEY_A, KEY_B, KEY_UP, KEY_DOWN) or KEY_NULL if no relevant key press event is detected.
 */
keyboardInput EventManager::getKeyPressed()
{
    bool catchValue = false;

    for (size_t i = 0; i != this->_eventCatchable.size(); i++) {
        if (this->_eventCatchable.at(i) == KEY_INPUT)
            catchValue = true;
    }

    if (!catchValue)
        return KEY_NULL;

    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::A)
        return (KEY_A);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Z)
        return (KEY_Z);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::E)
        return (KEY_E);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::R)
        return (KEY_R);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::T)
        return (KEY_T);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Y)
        return (KEY_Y);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::U)
        return (KEY_U);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::I)
        return (KEY_I);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::O)
        return (KEY_O);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::P)
        return (KEY_P);

    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Q)
        return (KEY_Q);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::S)
        return (KEY_S);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::D)
        return (KEY_D);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::F)
        return (KEY_F);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::G)
        return (KEY_G);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::H)
        return (KEY_H);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::J)
        return (KEY_J);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::K)
        return (KEY_K);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::L)
        return (KEY_L);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::M)
        return (KEY_M);

    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::W)
        return (KEY_W);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::X)
        return (KEY_X);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::C)
        return (KEY_C);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::V)
        return (KEY_V);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::B)
        return (KEY_B);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::N)
        return (KEY_N);

    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Up)
        return (KEY_UP);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Left)
        return (KEY_LEFT);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Right)
        return (KEY_RIGHT);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Down)
        return (KEY_DOWN);

    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Space)
        return (KEY_SPACE);
    if (this->_event.type == sf::Event::KeyPressed && this->_event.key.code == sf::Keyboard::Enter)
        return (KEY_ENTER);

    return (KEY_NULL);
}

/**
 * @brief Get the type of mouse click event.
 *
 * This function checks if mouse click events are catchable, and if so, determines the type of mouse click event (left, right, middle). If the application has specified that mouse click events should be caught, this function returns the type of the mouse click event detected by the event manager.
 *
 * @return The type of mouse click event (keyboardInput_t). It returns MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE, or KEY_NULL based on the detected mouse click event.
 */
keyboardInput_t EventManager::getMouseClick()
{

    bool catchValue = false;

    for (size_t i = 0; i != this->_eventCatchable.size(); i++) {
        if (this->_eventCatchable.at(i) == KEY_INPUT)
            catchValue = true;
    }

    if (!catchValue)
        return KEY_NULL;

    if (this->_event.type == sf::Event::MouseButtonPressed && this->_event.mouseButton.button == sf::Mouse::Right)
        return (MOUSE_RIGHT);
    if (this->_event.type == sf::Event::MouseButtonPressed && this->_event.mouseButton.button == sf::Mouse::Middle)
        return (MOUSE_MIDDLE);
    if (this->_event.type == sf::Event::MouseButtonPressed && this->_event.mouseButton.button == sf::Mouse::Left)
        return (MOUSE_LEFT);

    return (KEY_NULL);
}

EventManager::~EventManager()
{
}