#pragma once
template <class T>
class Property
{
public:
	T propValue;
	Property() {};
	Property(T nv) {
		propValue = nv;
	}
	Property<T> &operator=(const Property<T> &rhs) {
		propValue = rhs.propValue;
		return *this;
	}
	Property<T> &operator=(const T &rhs) {
		propValue = rhs;
		return *this;
	}
	bool operator==(const Property<T> &rhs) const {
		if(propValue == rhs.propValue) {
			return true;
		} else {
			return false;
		}
	}
	bool operator==(const T &rhs) const {
		if(propValue == rhs) {
			return true;
		} else {
			return false;
		}
	}
	~Property() {};
};
	


