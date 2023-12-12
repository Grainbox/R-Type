/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ClientEngine
*/

#include "client/ClientEngine.hpp"

/*!
 \brief Constructor of ClientEngine.

 \param r Pointer to a Registry object.
 \param port Port number on which the client is connecting.
*/
ClientEngine::ClientEngine(Registry *r, short server_port)
    : r(r), window(sf::VideoMode(800, 600), "My Engine"), _udp_socket(io_context_)
{
    _udp_socket.open(asio::ip::udp::v4());
    _server_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string("127.0.0.1"), server_port);

    send_hello();
    start_receive();
    run();
}

/*!
 \brief Exemple function that sends a "hello" message to the server.
*/
void ClientEngine::send_hello()
{
    std::string message = "hello";
    _udp_socket.send_to(asio::buffer(message), _server_endpoint);
}

/*!
 \brief Listen for the server messages asynchronously.
*/
void ClientEngine::start_receive()
{
    _udp_socket.async_receive_from(
        asio::buffer(recv_buffer_), _server_endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd)
        {
            handle_receive(ec, bytes_recvd);
        });
}

/*!
 \brief Handles data received from the server.

 \param error Boost ASIO error code, if any.
 \param bytes_transferred Number of bytes received.
*/
void ClientEngine::handle_receive(const std::error_code &error, std::size_t bytes_transferred)
{
    if (!error)
    {
        std::string received_message(recv_buffer_, bytes_transferred);
        std::cout << "Received: " << received_message << std::endl;
    }
    start_receive();
}

/*!
 \brief Runs the game loop and call the ECS.
*/
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

/*!
 \brief Process the SFML events and dispatch it on event related systems.
*/
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

/*!
 \brief Updates the window state by calling systems.
*/
void ClientEngine::update()
{
    system.position_system(*r);
}

/*!
 \brief Render entities on the window by calling related systems.
*/
void ClientEngine::render()
{
    window.clear();

    system.draw_system(*r, window);
    system.draw_hitbox_system(*r, window);

    window.display();
}
