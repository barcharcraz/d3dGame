#include "Row.h"
#include <new>
#include <cstring>
#include <vector>
namespace sparse {
    namespace ecs {
		template class row_raw_iterator_base<void*, Row>;
		template class row_raw_iterator_base<const void*, const Row>;
        namespace {
            const size_t initial_capacity = 10;
            void* erase_num(std::vector<unsigned char>& vec, void* pos, std::size_t num) {
                ComponentInfo* comp = reinterpret_cast<Component*>(pos)->info;
                unsigned char* chr = reinterpret_cast<unsigned char*>(pos);
                auto indexStart = chr - vec.data();
                auto indexEnd = (chr + (comp->size * num)) - vec.data();
                auto iterStart = vec.begin() + indexStart;
                auto iterEnd = vec.begin() + indexEnd;
                for(auto i = iterStart; i != iterEnd; ++i) {
                    //derefer and then refer the iterator then
                    //cast it to a componet so we can call its destructors
                    ComponentInfo* icomp = reinterpret_cast<Component*>(&*i)->info;
                    icomp->destroy(&*i);
                }
                auto erased = vec.erase(iterStart, iterEnd);
                auto erasedIndex = erased - vec.begin();
                return vec.data() + erasedIndex;
            }
        }
        Row::Row(const Row& other)
            : type(other.type), item_size(other.item_size)
        {
            for(auto s = std::begin(other.data); s != other.data.end(); s += other.item_size + 1) 
            {
                push_back(&*s);
            }
        }
        Row& Row::operator=(const Row& other) {
            this->type = other.type;
            this->item_size = other.item_size;
            for(auto i = other.data.begin(); i < other.data.end(); i += other.item_size + 1) {
                push_back(&*i);
            }
            return *this;
        }
        Row::Row(Row&& other)
            : type(other.type), item_size(other.item_size), data(std::move(other.data))
        {
        }
        Row& Row::operator=(Row&& other) {
            type = other.type;
            item_size = other.item_size;
            data = std::move(data);
            return *this;
        }
        Row::~Row() {
            if(data.empty()) {
                return;
            }
            unsigned char* base = &*data.begin();
            for(unsigned i = 0; i < size(); ++i) {
                ComponentInfo* info = reinterpret_cast<Component*>(base + ((item_size + 1) * i))->info;
                info->destroy((base + ((item_size + 1) * i)));
            }
        }
		void* Row::at(std::size_t pos) {
			return data.data() + (pos * (item_size + 1));
		}
		const void* Row::at(std::size_t pos) const {
			return data.data() + (pos * (item_size + 1));
		}
		bool Row::is_alive(Entity ent) const {
			if (alive.size() <= ent) {
				return false;
			}
			return alive[ent];
		}
		void* Row::EntityComp(Entity ent) {
			if (!is_alive(ent)) {
				throw utils::precondition_error("entity does not have requested component");
			}
			if (!isSparseOpt) {
				return at(ent);
			} else {
				throw utils::not_supported_error("sparse optimized storage is not implemented");
			}
		}
		const void* Row::EntityComp(Entity ent) const {
			if (!is_alive(ent)) {
				throw utils::precondition_error("entity does not have component");
			}
			if (!isSparseOpt) {
				return at(ent);
			} else {
				throw utils::not_supported_error("sparse optimized storage is not implemented");
			}
		}
        void Row::push_back(const void* value) {
            const ComponentInfo* comp = reinterpret_cast<const Component*>(value)->info;
            if (type == -1) {
                type = comp->type;
                item_size = comp->size;
            }
            assert(comp->type == type && comp->size == item_size);
            data.insert(data.end(), item_size + 1, 0);
			alive.push_back(true);
            comp->copy(value, back());
        }
        void* Row::insert(void* pos, void* value) {
            ComponentInfo* comp = reinterpret_cast<Component*>(value)->info;
            if (type == -1) {
                type = comp->type;
                item_size = comp->size;
            }
            assert(comp->type == type && comp->size == item_size);
            auto index = reinterpret_cast<unsigned char*>(pos) - data.data();
            auto insertionPoint = data.begin() + index;
            data.insert(insertionPoint, comp->size, 0);
			alive.insert(alive.begin() + index, true);
            comp->copy(value, &data[index]);
            return &data[index];
        }
        void* Row::erase(void* pos) {
            Component* comp = reinterpret_cast<Component*>(pos);
            assert(comp->info->type == type && comp->info->size == item_size);
			auto index = reinterpret_cast<unsigned char*>(pos) - data.data();
			alive.erase(alive.begin() + index);
			return erase_num(data, pos, 1);
        }
        void* Row::erase(void* first, void* last) {
            Component* comp = reinterpret_cast<Component*>(first);
            assert(comp->info->type == type && comp->info->size == item_size);
            auto numErase = 
                reinterpret_cast<unsigned char*>(last) - 
                reinterpret_cast<unsigned char*>(first);
			auto index = reinterpret_cast<unsigned char*>(first) - data.data();
			auto indexlast = reinterpret_cast<unsigned char*>(last) -data.data();
			alive.erase(alive.begin() + index, alive.begin() + indexlast);
            return erase_num(data, first, numErase);
        }
        void* Row::back() {
            return reinterpret_cast<unsigned char*>(&data.back()) -
                item_size;
        }
        const void* Row::back() const {
            return reinterpret_cast<const unsigned char*>(&data.back()) -
                item_size;
        }
        std::size_t Row::size() const {
            if (type == -1) {
                return 0;
            }
            return data.size() / item_size;
        }
        std::size_t Row::capacity() const {
            if (type == -1) {
                //we do not know how big out types are
                //so we can not look at the capacity
                return 0;
            }
            return data.capacity() / item_size;
        }
		//raw iterator begin and end functions
		row_raw_iterator Row::begin() {
			return row_raw_iterator(0, this);
		}
		row_const_raw_iterator Row::begin() const {
			return row_const_raw_iterator(0, this);
		}
		row_raw_iterator Row::end() {
			return row_raw_iterator(size(), this);
		}
		row_const_raw_iterator Row::end() const {
			return row_const_raw_iterator(size(), this);
		}


		//row iterators
		template<typename T, typename R>
		row_raw_iterator_base<T, R>::row_raw_iterator_base(std::size_t idx, R* row)
			: m_row(row), index(idx) {}

		template<typename T, typename R>
		row_raw_iterator_base<T,R>& row_raw_iterator_base<T,R>::operator++() {
			index++;
			//we want to loop until the index is alive, so we 
			//loop while it is not alive and increment it
			while (index < m_row->size() && !m_row->is_alive(index)) {
				index++;
			}
			return *this;
		}
		template<typename T, typename R>
		bool row_raw_iterator_base<T,R>::operator==(const row_raw_iterator_base<T,R>& other) const {
			if (index >= m_row->size() && other.index >= other.m_row->size()) {
				//we are both past the end
				return true;
			}
			if (index == other.index && m_row == other.m_row) {
				return true;
			}
			return false;
		}
		template<typename T, typename R>
		bool row_raw_iterator_base<T,R>::operator!=(const row_raw_iterator_base& other) const {
			return !(*this == other);
		}
		template<typename T, typename R>
		row_raw_iterator_base<T, R> row_raw_iterator_base<T, R>::operator+(size_t num) const {
			return row_raw_iterator_base<T, R>(index + num, m_row);
		}
		template<typename T, typename R>
		T row_raw_iterator_base<T,R>::operator*() const {
			return m_row->at(index);
		}

    }
}
