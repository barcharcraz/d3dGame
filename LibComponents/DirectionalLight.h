#ifndef LIBCOMPONENTS_DIRECTIONALLIGHT_H
#define LIBCOMPONENTS_DIRECTIONALLIGHT_H
#include "IComponent.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Components {
	class DirectionalLight : public IComponent {
	public:
		DirectionalLight(const Eigen::Vector4f& color, const Eigen::Vector3f& dir)
			: Color(data.Color), Direction(data.Direction)
		{
			data.Color = color;
			data.Direction = dir;
		}
		struct Data {
			Eigen::Vector4f Color;
			Eigen::Vector3f Direction;
		};
		Data data;
		Eigen::Vector4f& Color;
		Eigen::Vector3f& Direction;
	};
}

#endif