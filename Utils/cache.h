#ifndef UTILS_CACHE_H
#define UTILS_CACHE_H
#include <unordered_map>
namespace utils {
    template<typename K, typename V>
    class CacheContext {
    public:
        void ForceAdd(K key) {
            m_data.emplace(key, V(key));
        }
        void ForceClear(K key) {
            m_data.erase(key);
        }
        V& Retrieve(K key) {
            if(m_data.count(key) == 0) {
                ForceAdd(key);
            }
            return m_data[key];
        }
    private:
        std::unordered_map<K, V> m_data;
    };
    template<typename K, typename V>
    class Cache {
    public:
        Cache() {
            activeCtx = &defaultCtx;
        }
        void ForceAdd(K key) {
            activeCtx->ForceAdd(key);
        }
        void ForceClear(K key) {
            activeCtx->ForceClear(key);
        }
        V& Retrieve(K key) {
            return activeCtx->Retrieve(key);
        }
        void SetActiveCache(CacheContext<K, V>* ctx) {
            if(nullptr == ctx) {
                activeCtx = &defaultCtx;
            } else {
                activeCtx = ctx;
            }
        }
        CacheContext<K, V>* GetCurrentContext() {
            return activeCtx;
        }
    private:
        CacheContext<K,V> defaultCtx;
        CacheContext<K,V>* activeCtx; 
    };
}
#endif
