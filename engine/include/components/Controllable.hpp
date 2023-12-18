/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

/*!
 \class Controllable
 \brief Component that is used on entities that can be controlled by user.
*/
class Controllable {
    public:
        void setKeyboardKey(int *moveKey, int newKey) {
            *moveKey = newKey;
        }
        int Up = -1;     // Valeur initiale pour indiquer qu'aucune touche n'est assignée
        int Down = -1;   // Utilisez -1 ou une autre valeur pour représenter 'Unknown'
        int Left = -1;
        int Right = -1;
    protected:
    private:
};

#endif /* !CONTROLLABLE_HPP_ */
