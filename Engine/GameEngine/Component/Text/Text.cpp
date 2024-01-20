/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Text
*/

#include "Text.hpp"

Text::Text()
{
    this->_font = new sf::Font();
    this->_text = new sf::Text();
}

/**
 * @brief Get the type of the component.
 *
 * @return A reference to the `ComponentType_t` representing the type of this component.
 */
ComponentType_t &Text::GetType()
{
    return (this->_type);
}

/**
 * @brief Get the `sf::Text` object associated with the component.
 *
 * @return A reference to the `sf::Text` object.
 */
sf::Text &Text::getText()
{
    return (*this->_text);
}

/**
 * @brief Set the `sf::Text` object associated with the component.
 *
 * @param text The `sf::Text` object to be associated with the component.
 */
void Text::setText(sf::Text *text)
{
    this->_text = text;
}

/**
 * @brief Set the `sf::Text` object associated with the component.
 *
 * @param text A `std::string` with the text you want to set.
 */
void Text::setText(std::string text, bool setFont)
{
    // sf::Text *txt = new sf::Text;
    if (setFont)
        this->_text->setFont(*this->_font);
    this->_text->setString(text);
}

/**
 * @brief Get the size of the text component.
 *
 * @return A reference to a integer representing the size of the text component.
 */
int &Text::getSize()
{
    return (this->_size);
}

/**
 * @brief Set the size of the text component.
 *
 * @param size An integer representing the size of the text component.
 */
void Text::setSize(int size)
{
    this->_size = size;
    this->_text->setCharacterSize(size);
}

/**
 * @brief Get the `sf::Font` associated with the text component.
 *
 * @return A reference to the `sf::Font` associated with the text component.
 */
sf::Font &Text::getFont()
{
    return (*this->_font);
}

/**
 * @brief Set the `sf::Font` associated with the text component.
 *
 * @param font The `sf::Font` to be associated with the text component.
 */
void Text::setFont(sf::Font *font)
{
    this->_font = font;
}

/**
 * @brief Set the `sf::Font` associated with the text component.
 *
 * @param font The `std::string` to be loaded for the text component.
 */
void Text::setFont(std::string font)
{
    this->_font->loadFromFile(font);
}

/**
 * @brief Check if the text component is visible.
 *
 * @return A reference to a boolean value indicating whether the text component is visible.
 */
bool &Text::isVisible()
{
    return (this->_visible);
}

/**
 * @brief Set the visibility state of the text component.
 *
 * @param state A boolean value representing the visibility state to be set for the text component.
 */
void Text::visibleState(bool state)
{
    this->_visible = state;
}

/**
 * @brief Set the color of the text.
 *
 * @param color A `sf::color` representing the color to be set for the text.
 */
void Text::setColor(sf::Color color)
{
    this->_text->setFillColor(color);
}

Text::~Text()
{
}
