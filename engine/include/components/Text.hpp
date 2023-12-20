/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

    #include <iostream>
    #include <raylib.h>

class Text {
    public:
        Text(std::string txt) : text(txt) {};
        Text(std::string txt, Color col) : text(txt), rgb(col) {};
        Text(std::string txt, std::size_t size) : text(txt), font_size(size) {};
        Text(std::string txt, Color col, std::size_t size) : text(txt), rgb(col), font_size(size) {};

        std::string text = "";
        Color rgb = {0, 0, 0, 255};
        std::size_t font_size = 20;
    protected:
    private:
};

#endif /* !TEXT_HPP_ */
