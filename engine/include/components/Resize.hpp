/*
** EPITECH PROJECT, 2023
** **
** File description:
** **
*/

#ifndef RESIZE_HPP_
#define RESIZE_HPP_

/*!
 \class Resize
 \brief Component that is used on entities to resize textures.
*/
class Resize {
    public:
        Resize(int rx, int ry) : rx(rx), ry(ry) {};

        int rx;
        int ry;
    protected:
    private:
};

#endif /* !RESIZE_HPP_ */
