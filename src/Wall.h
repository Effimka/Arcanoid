#pragma once

#include "Shape.h"


class Wall : public Shape {

public:
	Wall(const Vect& pos, float width_, float height_);
	void update(float elapsed);
	Rect get_shape_as_aabb() const override;
	void event_collision(Vect overlap, Vect dir, const ShapeType& shape_type) override;
	virtual ShapeType get_shape_type() const;

	Vect position = Vect(0.0f);

	float width = 0.0f;
	float height = 0.0f;
};