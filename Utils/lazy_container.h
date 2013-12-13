#ifndef UTILS_LAZYCONTAINER_H
#define UTILS_LAYZCONTAINER_H
#include <memory>
#include <vector>
namespace utils {
	template<typename T>
	class lazy_container {
	public:
		typedef T value_type;
		typedef std::vector<T>::size_type size_type;
		typedef std::vector<T>::iterator iterator;
		typedef std::vector<T>::const_iterator const_iterator;
	public:
		const T& operator[](size_type i) { return m_cont[i]; } const;
		T& operator[](size_type i){ return m_cont[i]; }
		iterator begin() { return m_cont.begin(); }
		iterator end() { return m_cont.end(); }
		const_iterator begin(){ return m_cont.begin(); } const;
		const_iterator end(){ return m_cont.end(); } const;
		size_type size(){ return m_cont.size(); } const;
		iterator insert(const_iterator pos, const T& value) { 
			m_cont.insert(pos, value); 
		}
		iterator insert(const_iterator pos, T&& value) {
			m_cont.insert(pos, value);
		}
		void push_back(const T& value) {
			m_cache.push_back(value);
		}
		void push_back(T&& value) {
			m_cache.push_back(value);
		}

	private:
		std::vector<T> m_cont;
		std::vector<T> m_cache;
		std::vector<bool> m_dirty;
	};
}

#endif