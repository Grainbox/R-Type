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

void ServerSystem::handle_client(Registry &r,
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

        switch (msg.header.type) {
            case MessageType::First_Con: {
                returnMessage = client_connect_handler(msg, archive_stream, archive);
                break;
            }
            case MessageType::Disconnect: {
                returnMessage = client_disconnect_handler(*message);
                break;
            }
            case MessageType::Create_Game: {
                returnMessage = create_game_handler(*message);
                break;
            }
            default:
                returnMessage = "Unknown message type received!";
        }
        _socket.async_send_to(boost::asio::buffer(returnMessage), _remoteEndpoint,
            boost::bind(&ServerSystem::handle_send, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
    std::cout << "-------------------------------------" << std::endl;
}

std::string ServerSystem::client_connect_handler(FirstConMessage &msg,
    std::istringstream &archive_stream,
    boost::archive::text_iarchive &archive)
{
    Entity client = r.spawnEntity();
    clients_entity[_remoteEndpoint] = client.getEntityId();

    std::cout << "Client Connected, assigned on: " << _remoteEndpoint << "->" << client.getEntityId() << std::endl;
    return "Client Connected";
}

std::string ServerSystem::client_disconnect_handler(std::string message)
{
    DisconnectMessage msg;
    std::istringstream archive_stream(message);
    boost::archive::text_iarchive archive(archive_stream);

    archive >> msg;

    r.killEntity(clients_entity[_remoteEndpoint], r.getCurrentScene());
    clients_entity.erase(_remoteEndpoint);

    std::cout << "Client Disconnected for reason: " << msg.reason << std::endl;
    return "Client Disconnected";
}

std::string ServerSystem::create_game_handler(std::string message)
{
    std::cout << "Create Game" << std::endl;

    TransfertECSMessage msg;
    msg.header.type = MessageType::ECS_Transfert;
    msg.comps = r.getComponentsArray();

    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);

    archive << msg;

    std::string serialized_str = archive_stream.str();

    std::cout << "Broadcasting Entities" << std::endl;

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
        boost::bind(&ServerSystem::handle_client, this,
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
