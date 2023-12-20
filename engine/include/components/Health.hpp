/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

    #include <iostream>

class Health {
    public:
        Health() {};
        Health(size_t hp) : health(hp) {};
        size_t health = 100;
    protected:
    private:
};

#endif /* !HEALTH_HPP_ */
