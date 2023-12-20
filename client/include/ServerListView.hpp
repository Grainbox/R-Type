/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerListView
*/

#ifndef SERVERLISTVIEW_HPP_
#define SERVERLISTVIEW_HPP_

    #include "client/ClientEngine.hpp"

class ServerListView {
    public:
        ServerListView(Registry &r) : r(&r) {};

        void process()
        {
            
        }

    protected:
    private:
        Registry *r;
};

#endif /* !SERVERLISTVIEW_HPP_ */
