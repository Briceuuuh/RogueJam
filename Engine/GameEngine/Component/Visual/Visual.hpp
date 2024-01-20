/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Visual
*/

#ifndef VISUAL_HPP_
    #define VISUAL_HPP_
    #include <vector>
    #include "../IComponent.hpp"
    #include "SFML/Graphics.hpp"

    class Visual : public IComponent {
        public:
            Visual();
            ~Visual();
            ComponentType_t &GetType();
            sf::Texture &getTexture();
            void setTextureFromFile(std::string filepath);
            sf::Sprite &getSprite();
            void setTexture(sf::Texture texture);
            void setRect(sf::IntRect rect);

            const sf::IntRect &getRect();
            std::vector<float> &getScale();
            void setScale(float height, float witdh);
            bool &isVisible();
            void visibleState(bool state);

            sf::IntRect getDefaultRect();

            class VisualException : public std::runtime_error {
                public:
                    VisualException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            bool _visible = true;
            sf::Texture _texture;
            sf::Sprite _sprite;
            sf::IntRect _defaultRect;
            float _height;
            float _width;
            ComponentType_t _type = VISUAL;
    };

#endif /* !VISUAL_HPP_ */
