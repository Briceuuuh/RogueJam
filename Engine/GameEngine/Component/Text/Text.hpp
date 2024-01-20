/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_
    #include <vector>
    #include "../IComponent.hpp"
    #include "SFML/Graphics.hpp"

    class Text : public IComponent {
        public:
            Text();
            ~Text();
            ComponentType_t &GetType();
            sf::Text &getText();
            void setText(sf::Text *text);
            void setText(std::string text, bool setFont);
            int &getSize();
            void setSize(int size);
            sf::Font &getFont();
            void setFont(sf::Font *font);
            void setFont(std::string font);
            bool &isVisible();
            void visibleState(bool state);
            void setColor(sf::Color color);

        private:
            bool _visible = true;
            sf::Text *_text;
            sf::Font *_font;
            int _size;
            ComponentType_t _type = TEXT;
    };

#endif /* !TEXT_HPP_ */
