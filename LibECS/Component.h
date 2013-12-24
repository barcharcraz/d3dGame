#ifndef SPARSE_ECS_COMPONENT_H
#define SPARSE_ECS_COMPONENT_H
#include <type_traits>
#include <Utils/exceptions.h>
#include <new>
#include <typeindex>
namespace sparse {
    namespace ecs {
        typedef int ComponentType;
        typedef int Entity;
        typedef void(*CompInitFunc)(void* data);
        typedef void(*CompCopyFunc)(const void* src, void* dest);
        typedef void(*CompDeinitFunc)(void* data);
        template<typename T>
        void DefCompInitFunc(void* data) {
            ::new(data) T();
        }
        
        template<typename T>
        void DefCompCopyFunc(const void* src, void* dest) {
            ::new(dest) T(*reinterpret_cast<const T*>(src));
        }
#pragma warning( push )          //disable initialized not reffed, we do this
#pragma warning( disable: 4189 ) //because there is a compiler bug that triggers it here
        template<typename T>
        void DefCompDeinitFunc(void* data) {
            T* comp = reinterpret_cast<T*>(data);
            //we call the destructor explicitly
            //since it will not otherwise get called
            comp->~T();
        }
#pragma warning( pop )
        ComponentType GenID();
		ComponentType GenID(std::type_index);
        struct ComponentInfo {
            ComponentType type;
            std::size_t size;
            CompCopyFunc copy;
            CompDeinitFunc destroy;
        };
        template<typename T>
        ComponentInfo GenDefCompInfo() {
            ComponentInfo rv;
            rv.type = GenID(typeid(T));
            rv.size = sizeof(T);
            rv.copy = DefCompCopyFunc<T>;
            rv.destroy = DefCompDeinitFunc<T>;
            return rv;
        }
        struct Component {
            ComponentInfo* info;
			Entity ent;
		};

		template<typename T>
		struct ComponentHelper {
			ComponentInfo* info = GenDefCompInfo<T>;
			Entity ent;
		};
    }
}

#endif
