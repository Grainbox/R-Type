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
        using reference_type = std::optional<value_type> &;
        using const_reference_type = std::optional<value_type> const &;
        using container_t = std::vector<std::optional<value_type>>;
        using size_type = typename container_t::size_type;

        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

        /*!
         \brief Default constructor.
        */
        Sparse_Array() = default;

        /*!
         \brief Copy constructor.
         \param other Another Sparse_Array object to copy from.
        */
        Sparse_Array(Sparse_Array const &other) {
            this->_data = other._data;
        }

        /*!
         \brief Move constructor.
         \param other Another Sparse_Array object to move from.
        */
        Sparse_Array(Sparse_Array &&other) noexcept {
            this->_data = std::move(other._data);
        }

        /*!
         \brief Destructor.
        */
        ~Sparse_Array() = default;

        /*!
         \brief Copy assignment operator.
         \param other Another Sparse_Array object to assign from.
         \return Reference to the assigned Sparse_Array object.
        */
        Sparse_Array &operator=(Sparse_Array const &other) {
            this->_data = other._data;
            return *this;
        }

        /*!
         \brief Move assignment operator.
         \param other Another Sparse_Array object to move assign from.
         \return Reference to the assigned Sparse_Array object.
        */
        Sparse_Array &operator=(Sparse_Array &&other) noexcept {
            this->_data = std::move(other._data);
            return *this;
        }

        /*!
         \brief Subscript operator to access or modify elements.
         \param idx Index of the element to access.
         \return Reference to the element at the specified index.
        */
        reference_type operator[](size_t idx) {
            return this->_data[idx];
        }

        /*!
         \brief Subscript operator to access elements (const version).
         \param idx Index of the element to access.
         \return Const reference to the element at the specified index.
        */
        const_reference_type operator[](size_t idx) const {
            return this->_data[idx];
        }

        /*!
         \brief begin method
         \return begin method of the encapsulated vector.
        */
        iterator begin() {
            return this->_data.begin();
        }

        /*!
         \brief begin method (const version)
         \return begin method of the encapsulated vector.
        */
        const_iterator begin() const {
            return this->_data.begin();
        }

        /*!
         \brief cbegin method
         \return cbegin method of the encapsulated vector.
        */
        const_iterator cbegin() const {
            return this->_data.cbegin();
        }

        /*!
         \brief end method
         \return end method of the encapsulated vector.
        */
        iterator end() {
            return this->_data.end();
        }

        /*!
         \brief end method (const version)
         \return end method of the encapsulated vector.
        */
        const_iterator end() const {
            return this->_data.end();
        }

        /*!
         \brief cend method
         \return cend method of the encapsulated vector.
        */
        const_iterator cend() const {
            return this->_data.cend();
        }

        /*!
         \brief size method
         \return size method of the encapsulated vector.
        */
        size_type size() const {
            return this->_data.size();
        }

        /*!
         \brief insert_at method
         \param pos Position to insert the component.
         \param comp Component to insert
         \return A reference to the inserted component.
        */
        reference_type insert_at(size_type pos, Component const &comp) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = comp;
            return _data[pos];
        }

        /*!
         \brief insert_at method
         \param pos Position to insert the component.
         \param comp Component to insert
         \return A reference to the inserted component.
        */
        reference_type insert_at(size_type pos, Component &&other) {
            if (pos >= _data.size()) {
                _data.resize(pos + 1);
            }
            _data[pos] = std::move(other);
            return _data[pos];
        }

        /*!
         \brief erase method
         \param pos Position to erase the component.
        */
        void erase(size_type pos) {
            if (pos < _data.size()) {
                _data[pos] = std::nullopt;
            }
        }

        /*!
         \brief get_index method
         \param comp The component to get the index.
         \return The index of the given component if found.
        */
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
        container_t _data;  ///< The underlying container for the sparse array.
};

#endif /* !SPARSE_ARRAY_HPP_ */
