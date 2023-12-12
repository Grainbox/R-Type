/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ClientEngine
*/

#include "client/ClientEngine.hpp"

ClientEngine::ClientEngine(Registry *r)
    : r(r), window(sf::VideoMode(800, 600), "My Engine"), _udp_socket(io_context_)
{
    _udp_socket.open(asio::ip::udp::v4());
    _server_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string("127.0.0.1"), 4242);

    send_hello();
    send_hello();
    start_receive();
    run();
}

void ClientEngine::send_hello()
{
    std::string message = "hello";
    _udp_socket.send_to(asio::buffer(message), _server_endpoint);
}

void ClientEngine::start_receive()
{
    _udp_socket.async_receive_from(
        asio::buffer(recv_buffer_), _server_endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd)
        {
            handle_receive(ec, bytes_recvd);
        });
}

void ClientEngine::handle_receive(const std::error_code &error, std::size_t bytes_transferred)
{
    if (!error)
    {
        std::string received_message(recv_buffer_, bytes_transferred);
        std::cout << "Received: " << received_message << std::endl;
    }
    start_receive();
}

void ClientEngine::run()
{
    while (this->window.isOpen())
    {
        this->processEvents();
        this->update();
        this->render();

        io_context_.poll();
    }
}

void ClientEngine::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        system.control_system(*r, event);
        system.click_system(*r, event, window);
    }
}

void ClientEngine::update()
{
    system.position_system(*r);
}

void ClientEngine::render()
{
    window.clear();

    system.draw_system(*r, window);
    system.draw_hitbox_system(*r, window);

    window.display();
}
