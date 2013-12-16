#ifndef SPARSE_ECS_ROW_H
#define SPARSE_ECS_ROW_H
#include "Component.h"
#include <cstddef>
#include <iterator>
#include <vector>
#include <cassert>
#include <type_traits>
namespace sparse {
    namespace ecs {
        class Row {
        public:
            template<typename T> using iterator = T*;
            template<typename T> using const_iterator = const T*;
        public:
            template<typename T> T& operator[](std::size_t pos);
            template<typename T> const T& operator[](std::size_t pos) const;
            
            void push_back(void* arg);
            void* insert(void* pos, void* value);
            void* erase(void* pos);
            void* erase(void* first, void* last);

            template<typename T> void push_back(const T& arg);
            template<typename T> iterator<T> insert(iterator<T> pos, const T& value);
            template<typename T> iterator<T> erase(iterator<T> pos);
            template<typename T> iterator<T> erase(iterator<T> first, iterator<T> last);


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
            return begin<T>() + pos;
        }
        template<typename T>
        const T& Row::operator[](std::size_t pos) {
            return begin<T>() + pos;
        }

        template<typename T>
        void Row::push_back(const T& arg) {
            static_assert(std::is_trivially_copyable<T>::value, "ALL COMPONENTS MUST BE TRIVIAL");
            push_back(&arg);
        }
        template<typename T>
        auto Row::insert(iterator<T> pos, const T& value)->iterator<T> {
            static_assert(std::is_trivially_copyable<T>::value, "ALL COMPONENTS MUST BE TRIVIAL");
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
            assert(T::stype == this->type && item_size == sizeof(T));
            return reinterpret_cast<T*>(data.data());
        }
        template<typename T>
        auto Row::begin()->const_iterator<T> const {
            assert(T::stype == this->type && item_size == sizeof(T));
            return reinterpret_cast<const T*>(data.data());
        }
        template<typename T>
        auto Row::end()->iterator<T> {
            assert(T::stype == this->type && item_size == sizeof(T));
            return begin<T>() + size;
        }
        template<typename T>
        auto Row::end()->const_iterator<T> const {
            assert(T::stype == this->type && item_size == sizeof(T));
            return begin<T>() + size;
        }
    }
}

#endif