/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Sparse_Array
*/

#ifndef SPARSE_ARRAY_HPP_
#define SPARSE_ARRAY_HPP_

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <optional>
#include <memory>

#include "Exceptions.hpp"

template <typename Component>
class Sparse_Array {
    public:
        using value_type = Component;
        using reference_type = std::optional<value_type> &;
        using const_reference_type = std::optional<value_type> const &;
        using container_t = std::vector<std::optional<value_type>>;
        using size_type = typename container_t::size_type;

        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

        Sparse_Array() = default;

        Sparse_Array(Sparse_Array const &other) {
            this->_data = other._data;
        }
        Sparse_Array(Sparse_Array &&other) noexcept {
            this->_data = std::move(other._data);
        }

        ~Sparse_Array() = default;

        Sparse_Array &operator=(Sparse_Array const &other) {
            this->_data = other._data;
            return *this;
        }

        Sparse_Array &operator=(Sparse_Array &&other) noexcept {
            this->_data = std::move(other._data);
            return *this;
        }

        reference_type operator[](size_t idx) {
            return this->_data[idx];
        }

        const_reference_type operator[](size_t idx) const {
            return this->_data[idx];
        }

        iterator begin() {
            return this->_data.begin();
        }

        const_iterator begin() const {
            return this->_data.begin();
        }

        const_iterator cbegin() const {
            return this->_data.cbegin();
        }

        iterator end() {
            return this->_data.end();
        }

        const_iterator end() const {
            return this->_data.end();
        }

        const_iterator cend() const {
            return this->_data.cend();
        }

        size_type size() const {
            return this->_data.size();
        }

        reference_type insert_at(size_type pos, Component const &comp) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = comp;
            return _data[pos];
        }

        reference_type insert_at(size_type pos, Component &&other) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = std::move(other);
            return _data[pos];
        }

        void erase(size_type pos) {
            if (pos < _data.size()) {
                _data[pos] = std::nullopt;
            }
        }

        size_type get_index(value_type const &comp) const {
            auto it = std::find_if(_data.begin(), _data.end(),
                [&comp](const value_type& element) {
                    return std::addressof(comp) == std::addressof(element);
                });

            if (it != _data.end()) {
                return static_cast<size_type>(std::distance(_data.begin(), it));
            } else {
                throw ComponentNotFoundException("Error: Sparse_Array - get_index -> Cannot find component");
            }
        }

    protected:
    private:
        container_t _data;
};

#endif /* !SPARSE_ARRAY_HPP_ */
