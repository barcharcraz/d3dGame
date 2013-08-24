#include "SweepAndPrune.h"
#include <numeric>
namespace Physics {
	namespace {
		bool isMax(unsigned int box) {
			return box & EndPoint::max;
		}
		unsigned int boxIndex(unsigned int box) {
			return box & ~EndPoint::max;
		}
	}
	SweepAndPrune::SweepAndPrune() {
		//add sentinals to the end point vectors
		EndPoint max;
		EndPoint min;
		max.box = EndPoint::max;
		min.box = EndPoint::min;
		max.value = std::numeric_limits<float>::max();
		min.value = std::numeric_limits<float>::lowest();
		_X.push_back(min);
		_X.push_back(max);
		_Y.push_back(min);
		_Y.push_back(max);
		_Z.push_back(min);
		_Z.push_back(max);
	}
	void SweepAndPrune::UpdateObject(const Eigen::AlignedBox3f& aabb, void* obj) {
		auto min = aabb.min();
		auto max = aabb.max();
		auto& box = _objects[_objectMap.at(obj)];
		for (unsigned int i = 0; i < 3; ++i) {
			updateAxis(i, box.min[i], min(i));
			updateAxis(i, box.max[i], max(i));
		}
		
	}
	void SweepAndPrune::AddObject(const Eigen::AlignedBox3f& box, void* obj) {
		auto maxvec = box.max();
		auto minvec = box.min();
		BBox toAdd;
		toAdd.userRef = obj;
		_objects.push_back(toAdd);
		handle boxIdx = _objects.size() - 1;
		for (unsigned int i = 0; i < 3; ++i) {
			EndPoint min;
			EndPoint max;
			//make sure we are not screwing around with the high bit
			assert(boxIdx <= (std::numeric_limits<unsigned int>::max() & ~EndPoint::max));
			min.box = boxIdx;
			max.box = boxIdx | EndPoint::max;
			min.value = minvec(i);
			max.value = maxvec(i);

		}
	}
	void SweepAndPrune::updateAxis(unsigned int axis, std::vector<EndPoint>::iterator pos, float newval) {
		if (newval == pos->value) {
			//the value has not actually changed, do nothing
			return;
		}
		if (newval <= (pos + 1)->value && newval >= (pos - 1)->value) {
			//we have changed but we are still in the correct place
			return;
		}
		pos->value = newval;
		
		if (newval < pos->value) {
			//going down
			auto downItr = pos - 1;
			while (newval < downItr->value) {
				swapEndPoints(axis, downItr, pos);
				std::swap(downItr, pos);
				checkAndAdd(boxIndex(pos->box), boxIndex(downItr->box));
				pos -= 1;
				downItr -= 1;
			}
		} else {
			//going down
			auto upItr = pos + 1;
			while (newval > upItr->value) {
				swapEndPoints(axis, upItr, pos);
				std::swap(upItr, pos);
				checkAndAdd(boxIndex(pos->box), boxIndex(upItr->box));
				pos += 1;
				upItr += 1;
			}
		}
		

	}
	void SweepAndPrune::checkAndAdd(handle box1, handle box2) {
		auto& bbox1 = _objects[box1];
		auto& bbox2 = _objects[box2];
		bool areIntersecting = true;
		bool isActive = (activePairs.count(box1) > 0) && (activePairs.count(box2) > 0);
		for (unsigned int i = 0; i < 3; ++i) {
			if (!(bbox1.max[i] > bbox2.min[i]) && !(bbox1.min[i] < bbox2.max[i])) {
				areIntersecting = false;
				break;
			}
		}
		if (areIntersecting && isActive) {
			return;
		} else if (!areIntersecting && isActive) {
			activePairs.erase(box1);
			activePairs.erase(box2);
		} else if (areIntersecting) {
			activePairs[box1] = box2;
			activePairs[box2] = box1;
		}
	}
	void SweepAndPrune::swapEndPoints(unsigned int axis, std::vector<EndPoint>::iterator a, std::vector<EndPoint>::iterator b) {
		auto amax = isMax(a->box);
		auto bmax = isMax(b->box);
		auto aidx = boxIndex(a->box);
		auto bidx = boxIndex(b->box);
		auto& abox = _objects[aidx];
		auto& bbox = _objects[bidx];
		if (amax)
			abox.max[axis] = b;
		else
			abox.min[axis] = b;
		if (bmax)
			bbox.max[axis] = a;
		else
			bbox.min[axis] = a;

		std::swap(a, b);
	}
}