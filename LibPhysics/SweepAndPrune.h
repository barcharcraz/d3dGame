#ifndef LIBPHYSICS_SWEEPANDPRUNE_H
#define LIBPHYSICS_SWEEPANDPRUNE_H
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <array>
#include <map>
namespace Physics {
	struct BBox {
		std::array<unsigned int, 3> min;
		std::array<unsigned int, 3> max;
		void* userRef;
	};
	struct EndPoint {
		static const unsigned int min = 0;
		static const unsigned int max = 0x80000000;
		//box index and min/max value, note 31bits for box index
		//and thus a maximum of around 2 billion objects
		unsigned int box; 
		float value;
	};
	class SweepAndPrune {
		typedef unsigned int handle;
	public:
		SweepAndPrune();
		void AddObject(const Eigen::AlignedBox3f& box, void* obj);
		void UpdateObject(const Eigen::AlignedBox3f& box, void* obj);
		void RemoveObject(void* obj);
		unsigned int NumCollisions();
		std::vector<void*> QueryObject(void* object);
	private:
		std::array<std::vector<EndPoint>*, 3 > _axis;
		std::vector<EndPoint> _X;
		std::vector<EndPoint> _Y;
		std::vector<EndPoint> _Z;
		std::vector<BBox> _objects;
		std::map<void*, handle> _objectMap;
		std::vector<std::pair<handle, handle>> activePairs;
		void updateAxis(unsigned int axis, unsigned int pos, float newval);
		void checkAndAdd(handle obj1, handle obj2);
		void swapEndPoints(unsigned int axis, unsigned int a, unsigned int b);
		void fixRefs(unsigned int axis, unsigned int start);
		void fixObjectRefs(unsigned int start);
	};
}

#endif
