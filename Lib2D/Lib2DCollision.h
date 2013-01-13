#pragma once
#include <d2d1_1.h>
#include <vector>
#include <atlbase.h>
#include "Lib2DBoundingBox.h"

class Lib2DCollision {
private:
    std::vector<Lib2DBoundingBox> m_bbox;
};