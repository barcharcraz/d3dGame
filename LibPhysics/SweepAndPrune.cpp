#include "SweepAndPrune.h"
#include <numeric>
#include <algorithm>
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
		max.box = std::numeric_limits<unsigned int>::max();
		min.box = std::numeric_limits<unsigned int>::max();
		max.value = std::numeric_limits<float>::max();
		min.value = std::numeric_limits<float>::lowest();
		_X.push_back(min);
		_X.push_back(max);
		_Y.push_back(min);
		_Y.push_back(max);
		_Z.push_back(min);
		_Z.push_back(max);
		_axis[0] = &_X;
		_axis[1] = &_Y;
		_axis[2] = &_Z;
	}
	void SweepAndPrune::UpdateObject(const Eigen::AlignedBox3f& aabb, void* obj) {
		auto min = aabb.min();
		auto max = aabb.max();
		handle boxIdx = _objectMap.at(obj);
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
		auto boxIdx = _objects.size() - 1;
		_objectMap[obj] = boxIdx;
		for (unsigned int i = 0; i < 3; ++i) {
			EndPoint min;
			EndPoint max;
			//make sure we are not screwing around with the high bit
			assert(boxIdx <= (std::numeric_limits<unsigned int>::max() & ~EndPoint::max));
			min.box = boxIdx;
			max.box = boxIdx | EndPoint::max;
			min.value = std::numeric_limits<float>::max();
			max.value = std::numeric_limits<float>::max();
			
			//this stuff is slow as balls
			_axis[i]->insert(_axis[i]->end() - 1, min);
			_objects[boxIdx].min[i] = _axis[i]->size() - 2;
			updateAxis(i, _axis[i]->size() - 2, minvec(i));
			_axis[i]->insert(_axis[i]->end() - 1, max);
			_objects[boxIdx].max[i] = _axis[i]->size() - 2;
			updateAxis(i, _axis[i]->size() - 2, maxvec(i));
		}
	}
	void SweepAndPrune::RemoveObject(void* object) {
		handle hand = _objectMap.at(object);
		if (activePairs.count(hand) > 0) {
			auto range = activePairs.equal_range(hand);
			for (auto i = range.first; i != range.second; ++i) {
				auto other_range = activePairs.equal_range(i->second);
				for (auto j = other_range.first; i != other_range.second; ++j) {
					if (j->second == hand) {
						activePairs.erase(j);
					}
				}
			}
			activePairs.erase(hand);
		}
		auto& box = _objects[hand];
		for (unsigned int i = 3; i < 3; ++i) {
			_axis[i]->erase(_axis[i]->begin() + box.max[i]);
			fixRefs(i, box.max[i]);
			_axis[i]->erase(_axis[i]->begin() + box.min[i]);
			fixRefs(i, box.min[i]);
		}
		fixObjectRefs(hand);
		_objects.erase(_objects.begin() + hand);
		_objectMap.erase(object);

	}
	void SweepAndPrune::updateAxis(unsigned int axis, unsigned int pos, float newval) {
		auto axisvector = _axis[axis];
		
		if (newval == _axis[axis]->at(pos).value) {
			//the value has not actually changed, do nothing
			return;
		}
		float oldval = axisvector->at(pos).value;
		axisvector->at(pos).value = newval;
		if (newval <= axisvector->at(pos + 1).value && newval >= axisvector->at(pos - 1).value) {
			//we have changed but we are still in the correct place
			return;
		}
		
		
		if (newval < oldval) {
			//going down
			while (newval < axisvector->at(pos-1).value) {
				swapEndPoints(axis, pos-1, pos);
				checkAndAdd(boxIndex(axisvector->at(pos).box), boxIndex(axisvector->at(pos-1).box));
				pos -= 1;
			}
		} else {
			//going up
			while (newval > axisvector->at(pos+1).value) {
				swapEndPoints(axis, pos+1, pos);
				checkAndAdd(boxIndex(axisvector->at(pos).box), boxIndex(axisvector->at(pos+1).box));
				pos += 1;
			}
		}
		

	}
	std::vector<void*> SweepAndPrune::QueryObject(void* object) {
		auto hand = _objectMap.at(object);
		std::vector<void*> rv;
		if (activePairs.count(hand) > 0) {
			auto range = activePairs.equal_range(hand);
			for (auto i = range.first; i != range.second; ++i) {
				rv.push_back(_objects[i->second].userRef);
			}
		}
		return rv;
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
			activePairs.emplace(box1, box2);
			activePairs.emplace(box2, box1);
		}
	}
	void SweepAndPrune::swapEndPoints(unsigned int axis, unsigned int a, unsigned int b) {
		auto axisvec = _axis[axis];
		EndPoint& aend = axisvec->at(a);
		EndPoint& bend = axisvec->at(b);
		auto amax = isMax(aend.box);
		auto bmax = isMax(bend.box);
		auto aidx = boxIndex(aend.box);
		auto bidx = boxIndex(bend.box);
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

		std::swap(axisvec->begin() + a, axisvec->begin() + b);
	}
	void SweepAndPrune::fixRefs(unsigned int axis, unsigned int start) {
		auto axisvec = _axis[axis];
		for (unsigned int i = start; i < axisvec->size() - 1; ++i) {
			unsigned int boxIdx = boxIndex(axisvec->at(i).box);
			bool max = isMax(axisvec->at(i).box);
			if (max)
				_objects[boxIdx].max[axis] = i;
			else
				_objects[boxIdx].min[axis] = i;
		}
	}
	void SweepAndPrune::fixObjectRefs(unsigned int start) {
		for (auto& elm : _objectMap) {
			if (elm.second > start) {
				elm.second -= 1;
			}
		}
		for (auto& elm : activePairs) {
			if (elm.first > start)
				elm.second -= 1;
			if (elm.second > start)
				elm.second -= 1;
		}
	}
}
