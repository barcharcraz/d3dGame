#ifndef LIBPHYSICS_SWEEPANDPRUNE_H
#define LIBPHYSICS_SWEEPANDPRUNE_H
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <array>
#include <map>
namespace Physics {
	struct BBox {
		std::array<std::vector<EndPoint>::iterator, 3> min;
		std::array<std::vector<EndPoint>::iterator, 3> max;
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
	private:
		std::vector<EndPoint> _X;
		std::vector<EndPoint> _Y;
		std::vector<EndPoint> _Z;
		std::vector<BBox> _objects;
		std::map<void*, handle> _objectMap;
		std::map<handle, handle> activePairs;
		void updateAxis(unsigned int axis, std::vector<EndPoint>::iterator pos, float newval);
		void checkAndAdd(handle obj1, handle obj2);
		void swapEndPoints(unsigned int axis, std::vector<EndPoint>::iterator a, std::vector<EndPoint>::iterator b);
	};
}

#endif
