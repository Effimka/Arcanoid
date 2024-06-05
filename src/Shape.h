#pragma once

#include "arkanoid.h"

class Shape {
public:
	virtual Rect get_shape_as_aabb() const = 0;
	virtual void event_collision(Vect overlap, Vect dir, const ShapeType& shape_type) = 0;
	virtual ShapeType get_shape_type() const = 0;
	virtual ~Shape() {}

};
