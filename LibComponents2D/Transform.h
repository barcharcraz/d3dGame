#include <LibComponents/IComponent.h>
#ifndef LIBCOMPONENTS2D_TRANSFORM_H
#define LIBCOMPONENTS2D_TRANSFORM_H

namespace Components {
	struct Transform2D : public IComponent {
		Transform2D(const Eigen::Affine2f& trans) : transform(trans) {}
		Eigen::Affine2f transform;
	};
}

#endif