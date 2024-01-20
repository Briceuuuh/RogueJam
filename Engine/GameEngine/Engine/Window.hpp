/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** Window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_
    #include <iostream>
    #include <SFML/Graphics.hpp>

    class Window {
        public:
            Window();
            ~Window();
            void createWindow(int width, int height, std::string windowTitle);
            void display();
            void close();
            void setTitle(std::string windowName);
            std::string &getTitle();
            void setDimension(int width, int height);
            std::vector<int> &getDimension();

            sf::Vector2i getMousePosition();

            bool &windowIsRunning();
            void setWinDefaultColor(sf::Color color);
            sf::Color &getWinDefaultColor();

            void drawInWindow(sf::Sprite sprite, std::vector<int> position);
            sf::RenderWindow &getRenderWindow();

            void addSpriteToDraw(std::vector<sf::Sprite> sprite);
            std::vector<sf::Sprite> &getSpriteToDraw();

            void addTextToDraw(std::vector<sf::Text *> text);
            std::vector<sf::Text *> &getTextToDraw();

            class WindowException : public std::runtime_error {
                public:
                    WindowException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            std::vector<sf::Sprite> _spriteToDraw;
            std::vector<sf::Text *> _TextToDraw;
            sf::RenderWindow _window;
            std::string _title;
            int _height;
            int _width;
            bool _windowOpened;
            sf::Mouse _mouse;
            sf::Color _winDefaultColor = sf::Color::Black;
    };

#endif /* !WINDOW_HPP_ */
