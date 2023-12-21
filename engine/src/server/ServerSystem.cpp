/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ServerSystem
*/

#include "server/ServerSystem.hpp"

ServerSystem::ServerSystem(Registry &r, short port) : _socket(io_service, udp::endpoint(udp::v4(), port)), r(r)
{
    startReceive();
}

void ServerSystem::handle_client_system(Registry &r,
    const boost::system::error_code& error,
    std::size_t bytes_transferred)
{
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Bytes received: " << bytes_transferred << std::endl;

    if (!error || error == boost::asio::error::message_size) {
        auto message = std::make_shared<std::string>(_recvBuffer.data(), bytes_transferred);

        std::cout << "Received data: " << *message << std::endl;

        std::istringstream archive_stream(*message);
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

            returnMessage = r.getComScript(udp.value().script_id)(r, i, *message, msg.header.type);
        }

        if (msg.header.type == MessageType::First_Con)
            returnMessage = client_connect_handler(msg);
        if (msg.header.type == MessageType::Disconnect)
            returnMessage = client_disconnect_handler(*message);

        _socket.async_send_to(boost::asio::buffer(returnMessage), _remoteEndpoint,
            boost::bind(&ServerSystem::handle_send, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
    std::cout << "-------------------------------------" << std::endl;
}

std::string ServerSystem::client_connect_handler(FirstConMessage &msg)
{
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);

    archive << msg;

    std::string serialized_str = archive_stream.str();

    // Entity client = r.spawnEntity(r.getCurrentScene());
    // clients_entity[_remoteEndpoint] = client.getEntityId();

    // std::cout << "Client Connected, assigned on: " << _remoteEndpoint << "->" << client.getEntityId() << std::endl;
    return serialized_str;
}

std::string ServerSystem::client_disconnect_handler(std::string message)
{
    DisconnectMessage msg;
    std::istringstream archive_stream(message);
    boost::archive::text_iarchive archive(archive_stream);

    archive >> msg;

    std::string serialized_str = archive_stream.str();

    // r.killEntity(clients_entity[_remoteEndpoint], r.getCurrentScene());
    // clients_entity.erase(_remoteEndpoint);

    std::cout << "Client Disconnected for reason: " << msg.reason << std::endl;
    return serialized_str;
}

void ServerSystem::broadcast_message(const std::string& message)
{
    auto shared_message = std::make_shared<std::string>(message);

    for (const auto& client : clients_entity) {
        std::cout << client.first << std::endl;
        _socket.async_send_to(boost::asio::buffer(*shared_message), client.first,
            boost::bind(&ServerSystem::handle_send, this, shared_message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

void ServerSystem::startReceive()
{
    _socket.async_receive_from(
        boost::asio::buffer(_recvBuffer), _remoteEndpoint,
        boost::bind(&ServerSystem::handle_client_system, this,
            r,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void ServerSystem::handle_send(std::shared_ptr<std::string> message,
    const boost::system::error_code& ec,
    std::size_t bytes_transferred)
{
    startReceive();
}
