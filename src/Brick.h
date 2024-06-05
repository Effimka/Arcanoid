#pragma once

#include "Shape.h"


class Brick : public Shape {

public:
	Brick(const Vect& pos, float width_, float height_);
	void update();
	Rect get_shape_as_aabb() const override;
	void event_collision(Vect overlap, Vect dir, const ShapeType& shape_type) override;
	bool is_dead() const;

	virtual ShapeType get_shape_type() const;
	ImColor get_color();

private:
	Vect position = Vect(0.0f);
	bool dead = false;
	float width = 0.0f;
	float height = 0.0f;

	float health = 0;
	float max_health = 0;

	ImColor color{ 0, 255, 0 };
};