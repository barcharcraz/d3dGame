#include "Row.h"
#include <new>
#include <cstring>
#include <vector>
namespace sparse {
    namespace ecs {
        namespace {
            const size_t initial_capacity = 10;
            void* erase_num(std::vector<unsigned char*>& vec, void* pos, std::size_t num) {

            }
        }
        void Row::push_back(void* value) {
            Component* comp = reinterpret_cast<Component*>(value);
            if (type == -1) {
                type = comp->type;
                item_size = comp->size;
            }
            assert(comp->type == type && comp->size == item_size);
            auto inserted = data.insert(data.end(), item_size, 0);
            std::memcpy(&*inserted, value, item_size);
        }
        void* Row::insert(void* pos, void* value) {
            Component* comp = reinterpret_cast<Component*>(value);
            if (type == -1) {
                type = comp->type;
                item_size = comp->size;
            }
            assert(comp->type == type && comp->size == item_size);
            auto index = reinterpret_cast<unsigned char*>(pos) - data.data();
            auto insertionPoint = data.begin() + index;
            auto inserted = data.insert(insertionPoint, comp->size, 0);
            std::memcpy(&*inserted, value, item_size);
            return &*inserted;
        }
        void* Row::erase(void* pos) {
            Component* comp = reinterpret_cast<Component*>(pos);
            assert(comp->type == type && comp->size == item_size);
            unsigned char* chr = reinterpret_cast<unsigned char*>(pos);
            auto indexStart = chr - data.data();
            auto indexEnd = (chr + comp->size) - data.data();
            auto iterStart = data.begin() + indexStart;
            auto iterEnd = data.begin() + indexEnd;
            auto erased = data.erase(iterStart, iterEnd);
            if (erased == data.end()) {
                return end<void*>();
            }
            return &*erased;
            
        }
        void* Row::erase(void* first, void* last) {
            Component* comp = reinterpret_cast<Component*>(first);
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

    }
}