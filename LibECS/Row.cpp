#include "Row.h"
#include <new>
#include <cstring>
#include <vector>
namespace sparse {
    namespace ecs {
        namespace {
            const size_t initial_capacity = 10;
            void* erase_num(std::vector<unsigned char>& vec, void* pos, std::size_t num) {
                Component* comp = reinterpret_cast<Component*>(pos);
                unsigned char* chr = reinterpret_cast<unsigned char*>(pos);
                auto indexStart = chr - vec.data();
                auto indexEnd = (chr + (comp->size * num)) - vec.data();
                auto iterStart = vec.begin() + indexStart;
                auto iterEnd = vec.begin() + indexEnd;
                auto erased = vec.erase(iterStart, iterEnd);
                auto erasedIndex = erased - vec.begin();
                return vec.data() + erasedIndex;
            }
        }
        void Row::push_back(const void* value) {
            const Component* comp = reinterpret_cast<const Component*>(value);
            if (type == -1) {
                type = comp->type;
                item_size = comp->size;
            }
            assert(comp->type == type && comp->size == item_size);
            data.insert(data.end(), item_size + 1, 0);
            std::memcpy(back(), value, item_size);
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
            data.insert(insertionPoint, comp->size, 0);
            std::memcpy(&data[index], value, item_size);
            return &data[index];
        }
        void* Row::erase(void* pos) {
            Component* comp = reinterpret_cast<Component*>(pos);
            assert(comp->type == type && comp->size == item_size);
            return erase_num(data, pos, 1);
        }
        void* Row::erase(void* first, void* last) {
            Component* comp = reinterpret_cast<Component*>(first);
            assert(comp->type == type && comp->size == item_size);
            auto numErase = 
                reinterpret_cast<unsigned char*>(last) - 
                reinterpret_cast<unsigned char*>(first);
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

    }
}
