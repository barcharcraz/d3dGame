#ifndef LIBCOMPONENTS_PARENTLINK_H
#define LIBCOMPONENTS_PARENTLINK_H
#include "IComponent.h"
#include "Transform.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Components {
    class ParentLink : public IComponent {
    public:
        enum parent_type {
            ROTATION = 1 << 0,
            TRANSLATION = 1 << 1,
            TRANSLATION_AND_ROTATION = ROTATION | TRANSLATION
        };
        ParentLink(Transform3D* src, ParentLink* par, parent_type type = TRANSLATION_AND_ROTATION);
        Components::ParentLink* parent;
        Components::Transform3D* transform_src;
        Eigen::Vector3f position;
        Eigen::Quaternionf rotation;
        parent_type type;
    };
}

#endif
