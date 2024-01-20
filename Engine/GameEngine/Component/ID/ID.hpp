/*
** EPITECH PROJECT, 2023
** B-CPP-500-RUN-5-1-rtype-florian.etheve
** File description:
** ID
*/

#ifndef ID_HPP_
    #define ID_HPP_
    #include "../IComponent.hpp"

    class ID : public IComponent {
        public:
            ID();
            ~ID();
            ComponentType_t &GetType();
            std::string &getTag();
            void setTag(std::string tag);
            unsigned int &getID();
            void setID(unsigned int ID);

        private:
            unsigned int _ID;
            std::string _tag;
            ComponentType_t _type = _ID_;
    };

#endif /* !ID_HPP_ */