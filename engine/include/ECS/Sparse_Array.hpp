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
#include <memory>
#include <limits>

#include "Exceptions.hpp"

/*!
 \class Sparse_Array
 \brief A template class for a sparse array.

 This template class implements a sparse array which is a data structure that allows efficient storage of data with a high number of default values. It uses optional values to represent the presence or absence of data.
 \tparam Component The type of components stored in the sparse array.
*/
template <typename Component>
class Sparse_Array {
    public:
        using value_type = Component;
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<value_type>;
        using size_type = typename container_t::size_type;

        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

        // A simple wrapper to mimic std::optional for backward compatibility
        class ComponentHandle {
            public:
                ComponentHandle(value_type* ptr = nullptr) : _ptr(ptr) {}
                bool has_value() const { return _ptr != nullptr; }
                explicit operator bool() const { return has_value(); }
                value_type& value() { 
                    if (!_ptr) throw ComponentNotFoundException("Sparse_Array: Accessing empty component");
                    return *_ptr; 
                }
                value_type& operator*() { return value(); }
                value_type* operator->() { return _ptr; }
            private:
                value_type* _ptr;
        };

        Sparse_Array() = default;
        Sparse_Array(Sparse_Array const &) = default;
        Sparse_Array(Sparse_Array &&) noexcept = default;
        ~Sparse_Array() = default;
        Sparse_Array &operator=(Sparse_Array const &) = default;
        Sparse_Array &operator=(Sparse_Array &&) noexcept = default;

        ComponentHandle operator[](size_t idx) {
            if (idx >= _sparse.size() || _sparse[idx] == NOT_FOUND) return ComponentHandle(nullptr);
            return ComponentHandle(&_dense[_sparse[idx]]);
        }

        const ComponentHandle operator[](size_t idx) const {
            if (idx >= _sparse.size() || _sparse[idx] == NOT_FOUND) return ComponentHandle(nullptr);
            return ComponentHandle(const_cast<value_type*>(&_dense[_sparse[idx]]));
        }

        iterator begin() { return _dense.begin(); }
        const_iterator begin() const { return _dense.begin(); }
        const_iterator cbegin() const { return _dense.cbegin(); }
        iterator end() { return _dense.end(); }
        const_iterator end() const { return _dense.end(); }
        const_iterator cend() const { return _dense.cend(); }

        size_type size() const { return _sparse.size(); }
        size_type dense_size() const { return _dense.size(); }

        value_type& dense_at(size_type idx) { return _dense[idx]; }
        const value_type& dense_at(size_type idx) const { return _dense[idx]; }
        size_type get_entity_at(size_type idx) const { return _entities[idx]; }

        ComponentHandle insert_at(size_type pos, Component const &comp) {
            if (pos >= _sparse.size()) _sparse.resize(pos + 1, NOT_FOUND);
            
            if (_sparse[pos] != NOT_FOUND) {
                _dense[_sparse[pos]] = comp;
            } else {
                _sparse[pos] = _dense.size();
                _dense.push_back(comp);
                _entities.push_back(pos);
            }
            return ComponentHandle(&_dense[_sparse[pos]]);
        }

        ComponentHandle insert_at(size_type pos, Component &&other) {
            if (pos >= _sparse.size()) _sparse.resize(pos + 1, NOT_FOUND);

            if (_sparse[pos] != NOT_FOUND) {
                _dense[_sparse[pos]] = std::move(other);
            } else {
                _sparse[pos] = _dense.size();
                _dense.push_back(std::move(other));
                _entities.push_back(pos);
            }
            return ComponentHandle(&_dense[_sparse[pos]]);
        }

        void erase(size_type pos) {
            if (pos >= _sparse.size() || _sparse[pos] == NOT_FOUND) return;

            size_type dense_idx = _sparse[pos];
            size_type last_dense_idx = _dense.size() - 1;
            size_type last_entity = _entities[last_dense_idx];

            // Swap and pop
            _dense[dense_idx] = std::move(_dense[last_dense_idx]);
            _entities[dense_idx] = last_entity;
            _sparse[last_entity] = dense_idx;

            _dense.pop_back();
            _entities.pop_back();
            _sparse[pos] = NOT_FOUND;
        }

        size_type get_index(value_type const &comp) const {
            const value_type* ptr = std::addressof(comp);
            if (ptr < _dense.data() || ptr >= _dense.data() + _dense.size())
                throw ComponentNotFoundException("Error: Sparse_Array - get_index -> Component not in dense array");
            
            size_type dense_idx = static_cast<size_type>(ptr - _dense.data());
            return _entities[dense_idx];
        }

    private:
        static constexpr size_t NOT_FOUND = std::numeric_limits<size_t>::max();
        std::vector<value_type> _dense;      ///< Contiguous component data
        std::vector<size_type> _sparse;      ///< Mapping: Entity ID -> Dense Index
        std::vector<size_type> _entities;    ///< Mapping: Dense Index -> Entity ID
};

#endif /* !SPARSE_ARRAY_HPP_ */
