#ifndef SPARSE_ECS_ROW_H
#define SPARSE_ECS_ROW_H
#include "Component.h"
#include <cstddef>
#include <iterator>
#include <vector>
#include <cassert>
#include <type_traits>
#include <stdexcept>
namespace sparse {
    namespace ecs {
        class Row {
        public:
            template<typename T> using iterator = T*;
            template<typename T> using const_iterator = const T*;
        public:
            template<typename T> T& operator[](std::size_t pos);
            template<typename T> const T& operator[](std::size_t pos) const;
            
            template<typename T> T& at(std::size_t pos);
            template<typename T> const T& at(std::size_t pos) const;

            void push_back(const void* arg);
            void* insert(void* pos, void* value);
            void* erase(void* pos);
            void* erase(void* first, void* last);

            template<typename T> 
            typename std::enable_if<!std::is_pointer<T>::value>::type 
                push_back(const T& arg);
            template<typename T> iterator<T> insert(iterator<T> pos, const T& value);
            template<typename T> iterator<T> erase(iterator<T> pos);
            template<typename T> iterator<T> erase(iterator<T> first, iterator<T> last);

            void* back();
            const void* back() const;
            std::size_t size() const;
            std::size_t capacity() const;
            //iterator stuff
            template<typename T> iterator<T> begin();
            template<typename T> const_iterator<T> begin() const;
            template<typename T> iterator<T> end();
            template<typename T> const_iterator<T> end() const;
        private:
            ComponentType type = -1;
            std::size_t item_size;
            std::vector<unsigned char> data;
        };
        template<typename T>
        T& Row::operator[](std::size_t pos) {
            return *(begin<T>() + pos);
        }
        template<typename T>
        const T& Row::operator[](std::size_t pos) const {
            return *(begin<T>() + pos);
        }
        
        template<typename T>
        T& Row::at(std::size_t pos) {
            if(!(pos < size())) {
                throw std::out_of_range("at out of range");
            }
            return this->operator[]<T>(pos);
        }
        template<typename T>
        const T& Row::at(std::size_t pos) const {
            if(!(pos < size())) {
                throw std::out_of_range("at out of range");
            }
            return this->operator[]<T>(pos);
        }

        template<typename T>
        typename std::enable_if<!std::is_pointer<T>::value>::type
        Row::push_back(const T& arg) {
            push_back(reinterpret_cast<const void*>(&arg));
        }
        template<typename T>
        auto Row::insert(iterator<T> pos, const T& value)->iterator<T> {
            return reinterpret_cast<iterator<T>>(insert(pos, &value));
        }

        template<typename T>
        auto Row::erase(iterator<T> pos)->iterator<T> {
            return reinterpret_cast<iterator<T>>(erase(pos));
        }
        template<typename T>
        auto Row::erase(iterator<T> first, iterator<T> last)->iterator<T> {
            return reinterpret_cast<iterator<T>>(erase(first, last));
        }

        template<typename T>
        auto Row::begin()->iterator<T> {
            assert(item_size == sizeof(T));
            return reinterpret_cast<T*>(data.data());
        }
        template<typename T>
        auto Row::begin() const->const_iterator<T> {
            assert(item_size == sizeof(T));
            return reinterpret_cast<const T*>(data.data());
        }
        template<typename T>
        auto Row::end()->iterator<T> {
            assert(item_size == sizeof(T));
            return begin<T>() + this->size();
        }
        template<typename T>
        auto Row::end() const->const_iterator<T> {
            assert(item_size == sizeof(T));
            return begin<T>() + this->size();
        }
    }
}

#endif
