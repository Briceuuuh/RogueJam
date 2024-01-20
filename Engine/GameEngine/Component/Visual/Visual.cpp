/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Visual
*/

#include "Visual.hpp"

Visual::Visual()
{
    this->_defaultRect.height = -1;
}

/**
 * @brief Get the type of the Visual component.
 *
 * This function returns the type of the Visual component, which is represented by a ComponentType_t enumeration.
 *
 * @return A reference to the ComponentType_t enum indicating the component's type.
 */
ComponentType_t &Visual::GetType()
{
    return (this->_type);
}

/**
 * @brief Get the texture associated with the entity's visual representation.
 *
 * This function returns the texture associated with the entity's visual representation as an sf::Texture reference.
 *
 * @return A reference to the sf::Texture object representing the entity's visual texture.
 */
sf::Texture &Visual::getTexture()
{
    return (this->_texture);
}

/**
 * @brief Set the texture for the entity's visual representation from a file.
 *
 * This function allows you to set or update the texture for the entity's visual representation by loading it from a file.
 *
 * @param filepath The path to the image file from which to load the texture.
 */
void Visual::setTextureFromFile(std::string filepath)
{
    if (filepath.empty() || filepath.c_str() == nullptr || filepath.c_str()[0] == '\0')
        throw VisualException("Visual.setTextureFromFile error: Empty or invalid filepath passed as parameter\n");
    this->_texture.loadFromFile(filepath);
    this->_sprite.setTexture(this->_texture);
    this->_width = this->_sprite.getGlobalBounds().width;
    this->_height = this->_sprite.getGlobalBounds().height;

}

/**
 * @brief Get the sprite used for rendering the entity's visual representation.
 *
 * This function returns the sprite used for rendering the entity's visual appearance as an sf::Sprite reference.
 *
 * @return A reference to the sf::Sprite object representing the entity's visual sprite.
 */
sf::Sprite &Visual::getSprite()
{
    return (this->_sprite);
}


/**
 * @brief Set the texture for the entity's visual representation.
 *
 * This function allows you to set or update the texture for the entity's visual representation by directly assigning an sf::Texture.
 *
 * @param texture The new sf::Texture object to assign to the entity's visual representation.
 */
void Visual::setTexture(sf::Texture texture)
{
    this->_texture = texture;
}

/**
 * @brief Set the rendering rectangle for the entity's visual representation.
 *
 * This function allows you to specify a rendering rectangle for the entity's visual representation. The rendering rectangle
 * defines the portion of the texture that should be displayed when rendering the entity.
 *
 * @param rect An sf::IntRect specifying the rendering rectangle for the visual representation.
 */
void Visual::setRect(sf::IntRect rect)
{
    this->_sprite.setTextureRect(rect);
    if (this->_defaultRect.height == -1)
        this->_defaultRect = rect;
}

/**
 * @brief Get the current rendering rectangle for the entity's visual representation.
 *
 * This function returns the current rendering rectangle used for displaying the entity's visual appearance as an sf::IntRect.
 *
 * @return An sf::IntRect specifying the current rendering rectangle for the visual representation.
 */
const sf::IntRect &Visual::getRect()
{
    return this->_sprite.getTextureRect();
}

/**
 * @brief Get the default rendering rectangle for the entity's visual representation.
 *
 * This function returns the default rendering rectangle for the entity's visual representation as an sf::IntRect.
 *
 * @return An sf::IntRect specifying the default rendering rectangle for the visual representation.
 */
sf::IntRect Visual::getDefaultRect()
{
    return this->_defaultRect;
}

/**
 * @brief Get the scaling factors for the entity's visual representation.
 *
 * This function returns the scaling factors used for the entity's visual representation as a vector of integers [height, width].
 *
 * @return A reference to a vector of integers specifying the scaling factors [height, width] for the visual representation.
 */
std::vector<float> &Visual::getScale()
{
    static std::vector<float> vec(2);
    vec.at(0) = this->_height;
    vec.at(1) = this->_width;

    return (vec);
}

/**
 * @brief Set the scaling factors for the entity's visual representation.
 *
 * This function allows you to specify the scaling factors for the entity's visual representation. The scaling factors affect the
 * size of the rendered visual representation.
 *
 * @param height The scaling factor for the height of the visual representation.
 * @param width The scaling factor for the width of the visual representation.
 */
void Visual::setScale(float height, float width)
{
    if (height < 0 || width < 0)
        throw VisualException("Visual.setScale error: Negative number passed as parameter\n");

    this->_sprite.setScale(height, width);
    this->_width = this->_sprite.getGlobalBounds().width;
    this->_height = this->_sprite.getGlobalBounds().height;
}

/**
 * @brief Check the visibility state of the entity's visual representation.
 *
 * This function returns the current visibility state of the entity's visual representation. It indicates whether the entity's visual
 * representation is visible or hidden.
 *
 * @return A reference to a boolean variable that indicates the visibility state.
 */
bool &Visual::isVisible()
{
    return (this->_visible);
}

/**
 * @brief Set the visibility state of the entity's visual representation.
 *
 * This function allows you to set or update the visibility state of the entity's visual representation. It controls whether the visual
 * representation is visible or hidden in the scene.
 *
 * @param state The new visibility state, where true indicates visibility and false indicates hidden.
 */
void Visual::visibleState(bool state)
{
    this->_visible = state;
}

Visual::~Visual()
{
}
