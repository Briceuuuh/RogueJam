/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Hitbox
*/

#include "./Hitbox.hpp"

Hitbox::Hitbox()
{
}

/**
 * @brief Get the type of the Hitbox component.
 *
 * This function returns the type of the Hitbox component, which is represented by a ComponentType_t enumeration.
 *
 * @return A reference to the ComponentType_t enum indicating the component's type.
 */
ComponentType_t &Hitbox::GetType()
{
    return (this->_type);
}

/**
 * @brief Get the dimensions of the hitbox.
 *
 * This function returns the dimensions of the hitbox associated with the entity as a vector of integers. The hitbox
 * represents the area used for collision detection.
 *
 * @return A reference to a vector of integers representing the hitbox dimensions [height, width].
 */
std::vector<int> &Hitbox::getHitbox()
{
    static std::vector<int> vec(2);
    vec.at(0) = this->_height;
    vec.at(1) = this->_width;
    return (vec);
}

/**
 * @brief Set the dimensions of the hitbox.
 *
 * This function allows you to set or update the dimensions of the hitbox associated with the entity. The hitbox represents
 * the area used for collision detection.
 *
 * @param height The new height of the hitbox.
 * @param width The new width of the hitbox.
 */
void Hitbox::setHitbox(int height, int width)
{
    this->_height = height;
    this->_width = width;
}

bool Hitbox::getCollision(IEntity &entity1, IEntity &entity2)
{
    std::vector<IComponent *> comp1 = entity1.GetCurrentComponent();
    std::vector<IComponent *> comp2 = entity2.GetCurrentComponent();
    Position *pos1;
    Position *pos2;
    Visual *visu1;
    Visual *visu2;
    sf::FloatRect rect1;
    sf::FloatRect rect2;
    for (size_t i = 0; i != comp1.size(); i++) {
        if (comp1.at(i)->GetType() == POSITION) {
            pos1 = (Position *)comp1.at(i);
        }
        if (comp1.at(i)->GetType() == VISUAL) {
            visu1 = (Visual*)comp1.at(i);
        }
    }
    rect1 = sf::FloatRect(pos1->getPostion().at(0), pos1->getPostion().at(1), visu1->getScale().at(0), visu1->getScale().at(1));
    for (size_t i = 0; i != comp2.size(); i++) {
        if (comp2.at(i)->GetType() == POSITION) {
            pos2 = (Position *)comp1.at(i);
        }
        if (comp2.at(i)->GetType() == VISUAL) {
            visu2 = (Visual*)comp1.at(i);
        }
    }
    rect2 = sf::FloatRect(pos2->getPostion().at(0), pos2->getPostion().at(1), visu2->getScale().at(0), visu2->getScale().at(1));
    if (rect1.intersects(rect2)) {
        return true;
    }
    return false;
}

Hitbox::~Hitbox()
{
}
