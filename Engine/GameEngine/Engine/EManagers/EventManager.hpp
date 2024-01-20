/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** EventManager
*/

#ifndef EVENTMANAGER_HPP_
    #define EVENTMANAGER_HPP_
    #include "./Event.hpp"
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include "./KeyboardEnum.hpp"
    #include "../Window.hpp"

    class EventManager {
        public:
            EventManager();
            ~EventManager();
            sf::Event &getEventAttribut();
            bool WindowCloseEvent();
            keyboardInput_t getKeyPressed();
            keyboardInput_t getMouseClick();

            /**
             * @brief Add an event to the list of catchable events.
             *
             * This function adds a specific window event to the list of catchable events. When the `EventManager` processes window events, it will consider the events added to this list for handling. Events that have been added can be caught and processed by your application.
             *
             * @param event The window event (WindowEvent_t) to be added to the list of catchable events.
             */
            template<typename... WindowEvent_t>
            void addEventToCatch(WindowEvent_t... events) {
                (_addEventIfNotExists(events), ...);
            }

            /**
             * @brief Remove an event from the list of catchable events.
             *
             * This function removes a specific window event from the list of catchable events. Events that are no longer needed can be removed from the list. After removal, the `EventManager` will no longer process this event type.
             *
             * @param event The window event (WindowEvent_t) to be removed from the list of catchable events.
             */
            template<typename... WindowEvent_t>
            void removeEventToCatch(WindowEvent_t... events) {
                (_removeEventIfExists(events), ...);
            }

            class EventManagerException : public std::runtime_error {
                public:
                    EventManagerException(const std::string& msg) : std::runtime_error(msg) {};
            };

        private:
            void _addEventIfNotExists(WindowEvent_t event) {
                for (const auto &lineEvent : _eventCatchable) {
                    if (lineEvent == event)
                        return;
                }
                _eventCatchable.push_back(event);
            }

            void _removeEventIfExists(WindowEvent_t event) {
                _eventCatchable.erase(std::remove(_eventCatchable.begin(), _eventCatchable.end(), event), _eventCatchable.end());
            }
            sf::Event _event;
            std::vector<WindowEvent_t> _eventCatchable;
    };

#endif /* !EVENTMANAGER_HPP_ */
