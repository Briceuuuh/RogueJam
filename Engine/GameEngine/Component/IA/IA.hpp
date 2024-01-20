/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** IA
*/

#ifndef IA_HPP_
    #define IA_HPP_
    #include "../IComponent.hpp"

    class IA : public IComponent {
        public:
            IA();
            ~IA();
            ComponentType_t &GetType();
            bool &isIA();
            void IAState(bool state);
            int &getLevel();
            void setLevel(int level);

        private:
            bool _IA = true;
            int _level = 0;
            ComponentType_t _type = _IA_;
    };

#endif /* !IA_HPP_ */
