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
		class Row;
		template<typename T, typename R>
		class row_raw_iterator_base;
		typedef row_raw_iterator_base<void*, Row> row_raw_iterator;
		typedef row_raw_iterator_base<const void*, const Row> row_const_raw_iterator;
		template<typename T, typename R>
		class row_iterator_base;
		template<typename T>
		using row_iterator = row_iterator_base<T, row_raw_iterator>;
		template<typename T>
		using const_row_iterator = row_iterator_base<T, row_const_raw_iterator>;
		class Row {
        public:
            template<typename T> using iterator = row_iterator<T>;
            template<typename T> using const_iterator = const_row_iterator<T>;
        public:
            Row() = default;
            Row(const Row& other);
            Row& operator=(const Row& other);
            Row(Row&& other);
            Row& operator=(Row&& other);
            ~Row();

            template<typename T> T& operator[](std::size_t pos);
            template<typename T> const T& operator[](std::size_t pos) const;
            
            template<typename T> T& at(std::size_t pos);
            template<typename T> const T& at(std::size_t pos) const;
			
			void* at(std::size_t pos);
			const void* at(std::size_t pos) const;

			bool is_alive(Entity ent) const;
			void* EntityComp(Entity ent);
			const void* EntityComp(Entity ent) const;
			template<typename T> T* EntityComp(Entity ent);
			template<typename T> T* EntityComp(Entity ent) const;

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
			row_raw_iterator begin();
			row_const_raw_iterator begin() const;
			row_raw_iterator end();
			row_const_raw_iterator end() const;
            template<typename T> iterator<T> begin();
            template<typename T> const_iterator<T> begin() const;
            template<typename T> iterator<T> end();
            template<typename T> const_iterator<T> end() const;
        private:
            ComponentType type = -1;
            std::size_t item_size;
			bool isSparseOpt = false;
            std::vector<unsigned char> data;
			std::vector<bool> alive;
        };
		template<typename T, typename R>
		class row_raw_iterator_base {
		public:
			row_raw_iterator_base(std::size_t idx, R* row);
			row_raw_iterator_base& operator++();
			bool operator==(const row_raw_iterator_base& other) const;
			bool operator!=(const row_raw_iterator_base& other) const;
			row_raw_iterator_base<T, R> operator+(size_t) const;
			//note: the operator*s of this iterator work
			//in a strange way (they return a void*)
			T operator*() const;
		private:
			R* m_row;
			std::size_t index = std::numeric_limits<size_t>::max();
		};
		template<typename T, typename R>
		class row_iterator_base {
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;

		public:
			row_iterator_base(const R& from)
				: m_base(from) {}
			reference operator*() const {
				return *reinterpret_cast<T*>(*m_base);
			}
			pointer operator->() const {
				return reinterpret_cast<T*>(*m_base);
			}
			row_iterator_base<T,R>& operator++() {
				m_base++;
				return *this;
			}
			bool operator==(const row_iterator_base<T,R>& other) const {
				return m_base == other.m_base;
			}
			bool operator!=(const row_iterator_base<T,R>& other) const {
				return m_base != other.m_base;
			}
			row_iterator_base<T, R> operator+(std::size_t num) const {
				return row_iterator_base<T, R>(m_base + num);
			}
		private:
			R m_base;
		};
		

		template<typename T>
		class RowAdapter {
		public:
			explicit RowAdapter(Row& row)
				: m_row(row) {}
			T& EntityComp(Entity ent) {
				return *reinterpret_cast<T*>(m_row.EntityComp(ent));
			}
			T& operator[](std::size_t pos) {
				return *reinterpret_cast<T*>(m_row[pos]);
			}
			bool is_alive(Entity ent) const {
				return m_row.is_alive(ent);
			}
			const T& operator[](std::size_t pos) const {
				return *reinterpret_cast<T*>(m_row[pos]);
			}
			row_iterator<T> begin() {
				return row_iterator<T>(m_row.begin());
			}
			const_row_iterator<T> begin() const {
				return const_row_iterator<T>(m_row.begin());
			}
			row_iterator<T> end() {
				return row_iterator<T>(m_row.end());
			}
			const_row_iterator<T> end() const {
				return const_row_iterator<T>(m_row.end());
			}
		private:
			Row& m_row;
		};
		template<typename T>
		class ConstRowAdapter {
		public:
			explicit ConstRowAdapter(const Row& row)
				: m_row(row) {}
			const T& EntityComp(Entity ent) const {
				return *reinterpret_cast<T*>(m_row.EntityComp(ent));
			}
			bool is_alive(Entity ent) const {
				return m_row.is_alive();
			}
			const T& operator[](std::size_t pos) const {
				return *reinterpret_cast<const T*>(m_row[pos]);
			}
			const_row_iterator<T> begin() const {
				return const_row_iterator<T>(m_row.begin());
			}
			const_row_iterator<T> end() const {
				return const_row_iterator<T>(m_row.end());
			}
		private:
			const Row& m_row;
		};
		template<typename T>
		RowAdapter<T> MakeAdapter(Row& r) {
			return RowAdapter<T>(r);
		}
		template<typename T>
		ConstRowAdapter<T> MakeAdapter(const Row& r) {
			return ConstRowAdapter<T>(r);
		}
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
		T* Row::EntityComp(Entity pos) {
			return reinterpret_cast<T*>(EntityComp(pos));
		}
		template<typename T>
		const T* Row::EntityComp(Entity pos) {
			return reinterpret_cast<T*>(EntityComp(pos));
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
			return iterator<T>(begin());
        }
        template<typename T>
        auto Row::begin() const->const_iterator<T> {
            assert(item_size == sizeof(T));
			return const_iterator<T>(begin());
        }
        template<typename T>
        auto Row::end()->iterator<T> {
            assert(item_size == sizeof(T));
			return iterator<T>(end());
        }
        template<typename T>
        auto Row::end() const->const_iterator<T> {
            assert(item_size == sizeof(T));
			return const_iterator<T>(end());
        }
    }
}

#endif
