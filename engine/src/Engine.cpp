/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Engine
*/

#include "Engine.hpp"

/*!
 \brief Constructor of Engine.

 \param config Pointer to a EngineConfig object.
*/
Engine::Engine()
{
}

/*!
 \brief Destructor of ServerEngine.
*/
Engine::~Engine()
{
}

/*!
 \brief Convert a normal string to a binary string
 \param s Your original string
 \return Your string converted to binary
*/
std::string Engine::stringToBinary(const std::string &s) {
    std::string binaryString;
    for (char c : s) {
        binaryString += std::bitset<8>(c).to_string();
    }
    return binaryString;
}

/*!
 \brief Convert a binary string to a normal string
 \param binary Your binary string
 \return Your binary string converted to normal
*/
std::string Engine::binaryToString(const std::string &binary) {
    std::string originalString;
    std::stringstream sstream(binary);
    while(sstream.good()) {
        std::bitset<8> bits;
        sstream >> bits;
        originalString += char(bits.to_ulong());
    }
    return originalString;
}
