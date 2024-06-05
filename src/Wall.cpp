#include "Wall.h"

Wall::Wall(const Vect& pos,float width_, float height_)
{
	position = pos;
	width = width_;
	height = height_;
}

void Wall::update(float elapsed)
{

}

Rect Wall::get_shape_as_aabb() const
{
	return Rect(Vect(position.x, position.y), Vect(width, height));
}

void Wall::event_collision(Vect overlap, Vect dir, const ShapeType& shape_type)
{
}

ShapeType Wall::get_shape_type() const
{
	return ShapeType::wall;
}
