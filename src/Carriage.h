#pragma once

#include "Shape.h"

class Carriage : public Shape {
public:

	void init(const ArkanoidSettings& settings);
	
	void update(float elapsed);
	void change_x_velosity(float value);
	
	float get_x_velocity() const;

	Rect get_shape_as_aabb() const override;
	void event_collision(Vect overlap, Vect dir, const ShapeType& shape_type) override;
	virtual ShapeType get_shape_type() const;

	
	//Vect FarthestPointInDirection(Vect dir) const override;
	

private:
	Vect position = Vect(0.0f);
	float width = 0.0f;
	float height = 0.0f;
	Vect velocity = Vect(0.0f);
};