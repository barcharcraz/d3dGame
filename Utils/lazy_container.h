#ifndef UTILS_LAZYCONTAINER_H
#define UTILS_LAYZCONTAINER_H
#include <memory>
#include <vector>
#include <algorithm>
namespace utils {
	template<typename T>
	class lazy_container {
	public:
		typedef T value_type;
		typedef typename std::vector<T>::size_type size_type;
		typedef typename std::vector<T>::iterator iterator;
		typedef typename std::vector<T>::const_iterator const_iterator;
	public:
		const T& operator[](size_type i) const { return m_cont[i]; }
		T& operator[](size_type i){ return m_cont[i]; }
		iterator begin() { return m_cont.begin(); }
		iterator end() { return m_cont.end(); }
		const_iterator begin() const { return m_cont.begin(); }
		const_iterator end() const { return m_cont.end(); }
        const_iterator cbegin() const { return m_cont.cbegin(); }
        const_iterator cend() const { return m_cont.cend(); }
		iterator cache_begin() { return m_cache.begin(); }
		iterator cache_end() { return m_cache.end(); }
		const_iterator cache_begin() const { return m_cache.begin(); }
		const_iterator cache_end() const { return m_cache.end(); }
		size_type size() const { return m_cont.size(); }
        T& front() { return m_cont.front(); }
        const T& front() const { return m_cont.front(); }
        T& back() {
            if (!m_cache.empty()) {
                return m_cache.back();
            } else {
                return m_cont.back();
            }
        }
        const T& back() const {
            if (!m_cache.empty()) {
                return m_cache.back();
            } else {
                return m_cont.back();
            }
        }
		iterator insert(iterator pos, const T& value) {
			auto idx = pos - m_cont.begin();
			m_dirty.insert(m_dirty.begin() + idx, false);
			return m_cont.insert(pos, value);
		}
		iterator insert(iterator pos, T&& value) {
			auto idx = pos - m_cont.begin();
			m_dirty.insert(m_dirty.begin() + idx, false);
			return m_cont.insert(pos, std::move(value));
		}
		void push_back(const T& value) {
			m_cache.push_back(value);
            m_dirty.push_back(false);
		}
		void push_back(T&& value) {
			m_cache.push_back(std::move(value));
            m_dirty.push_back(false);
		}
        iterator erase(const_iterator pos) {
            m_dirty[pos - cbegin()] = true;
            std::ptrdiff_t dist = pos - begin();
            return begin() + dist + 1;
        }
        iterator erase(const_iterator begin, const_iterator end) {
            for (auto i = begin; i != end; ++i) {
                m_dirty[i - cbegin()] = true;
            }
            return end + 1;
        }
        void finalize_ops() {
			m_cont.erase(std::remove_if(m_cont.begin(), m_cont.end(),
				[&](const T& type) {
				std::ptrdiff_t idx = &type - m_cont.data();
				if (m_dirty[idx] == true) {
					return true;
				} else {
					return false;
				}
			}), m_cont.end());
			m_cont.insert(m_cont.end(),
						  std::make_move_iterator(m_cache.begin()),
						  std::make_move_iterator(m_cache.end()));
            m_cache.clear();
			m_dirty = std::vector<bool>(m_cont.size(), false);
        }

	private:
		std::vector<T> m_cont;
		std::vector<T> m_cache;
		std::vector<bool> m_dirty;
	};
}

#endif
