/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Exceptions
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>
#include <string>

class ComponentNotFoundException : public std::exception {
public:
    explicit ComponentNotFoundException(const std::string& message)
        : msg_(message) {}

    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class EntityNotFoundException : public std::exception {
public:
    explicit EntityNotFoundException(const std::string& message)
        : msg_(message) {}

    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class LoadAssetException : public std::exception {
public:
    explicit LoadAssetException(const std::string& message)
        : msg_(message) {}

    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

#endif /* !EXCEPTIONS_HPP_ */
