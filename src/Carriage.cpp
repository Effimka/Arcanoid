#include "Carriage.h"

void Carriage::init(const ArkanoidSettings& settings)
{
	width = settings.carriage_width;
	height = settings.carriage_width_min / 2;
	position = Vect(settings.world_size.x * 0.5 - width / 2, settings.world_size.y * 0.95f);
}

void Carriage::update(float elapsed)
{
	position += velocity * elapsed;
}

Rect Carriage::get_shape_as_aabb() const
{
	return Rect(Vect(position.x, position.y) , Vect(width, height));
}

void Carriage::change_x_velosity(float value)
{
	velocity.x += value;
}


float Carriage::get_x_velocity() const
{
	return velocity.x;
}

void Carriage::event_collision(Vect overlap, Vect dir, const ShapeType& shape_type)
{
	if (shape_type == ShapeType::wall)
	{
		position.x += overlap.x * dir.x;
		velocity.x = 0;
	}
}

ShapeType Carriage::get_shape_type() const
{
	return ShapeType::carriage;
}
