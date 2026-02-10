/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Raylib wrapper for Windows compatibility
*/

#ifndef RTYPE_RAYLIB_WRAPPER_HPP_
#define RTYPE_RAYLIB_WRAPPER_HPP_

#if defined(_WIN32)
    // Undefine conflicting macros that might have been included by asio/windows.h
    // Even with NOGDI/NOUSER, some might leak or be needed by other headers
    #undef Rectangle
    #undef CloseWindow
    #undef ShowCursor
    #undef LoadImage
    #undef DrawText
    #undef DrawTextEx
#endif

#include <raylib.h>

#endif /* !RTYPE_RAYLIB_WRAPPER_HPP_ */
