#pragma once
//////////////////////////////////////////////////////////////////////////
// this is a c++ standard implementation of a property
// because this is a winAPI based project anyways it is better
// to use __declspec(property), however I have included this
// template for reference and funzies
//////////////////////////////////////////////////////////////////////////
template <class T, class D>
class PropBase
{
public:
	T propValue;
	PropBase() {};
	PropBase(T nv) {
		propValue = nv;
	}
	PropBase<T,D> &operator=(const PropBase<T,D> &rhs) {
		propValue = rhs.propValue;
		return *this;
	}
	virtual PropBase<T,D> &operator=(const T &rhs) {
		propValue = rhs;
		return *this;
	}
	bool operator==(const PropBase<T,D> &rhs) const {
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
	~PropBase() {};
};

template<class T>
class Property : public PropBase<T, Property<T> >
{
public:
	Property(T nv) : PropBase(nv) {}
};

#define PROPERTY(t, n) __declspec(property ( put = property_set_##n, get = property_get_##n) ) t n; \
	typedef t property_tmp_type_##n
#define READONLY_PROPERTY(t, n) __declspec(property (get = property_get_##n ) ) t n; \
	typedef t property_tmp_type_##n
#define WRITEONLY_PROPERTY(t, n) __declspec(property ( put = property_set_##n ) ) t n; \
	typedef t property_tmp_type_##n

#define GET(n) property_tmp_type_##n property_get_##n()
#define SET(n) void property_set_##n(const property_tmp_type_##n& value)
