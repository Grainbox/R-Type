/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerSystem
*/

#include "server/ServerSystem.hpp"

ServerSystem::ServerSystem(Registry &r, short port) : _socket(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), r(r)
{
    startReceive();
}

void ServerSystem::handle_client_system(Registry &r,
    const std::array<char, 1024>& receivedMessage, std::size_t length)
{
    std::string message(receivedMessage.begin(), receivedMessage.end() + length);
    std::cout << "-------------------------------------" << std::endl;

    std::istringstream archive_stream(message);
    boost::archive::text_iarchive archive(archive_stream);
    FirstConMessage msg;
    archive >> msg;

    std::string returnMessage = "ERROR";

    std::cout << "Deserialized message type: " << static_cast<int>(msg.header.type) << std::endl << std::endl;

    std::string scene = r.getCurrentScene();
    Sparse_Array<ReceiveUDP> &udpComp = r.getComponents<ReceiveUDP>(scene);

    for (size_t i = 0; i < udpComp.size(); i++) {
        auto &udp = udpComp[i];

        if (!udp)
            continue;

        MessageHandlerData data = {message, msg.header.type, &_socket, &_remoteEndpoint};
        r.getComScript(udp.value().script_id)(r, i, data);
    }

    std::cout << "-------------------------------------" << std::endl;
}

void ServerSystem::broadcast_message(const std::string& message)
{
    for (const auto& client : clients_entity) {
        std::cout << client.first << std::endl;
        _socket.async_send_to(
            asio::buffer(message), client.first,
            [](const std::error_code& error, std::size_t bytes_transferred) {
                if (!error) {
                    std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
                } else {
                    std::cerr << "Error sending message: " << error.message() << std::endl;
                }
            }
        );
    }
}

void ServerSystem::startReceive()
{
    _socket.async_receive_from(
        asio::buffer(_recvBuffer), _remoteEndpoint,
        [this](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                handle_client_system(r, _recvBuffer, bytes_recvd);
            }
            this->startReceive();
        });
}
