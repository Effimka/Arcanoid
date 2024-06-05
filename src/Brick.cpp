#include "Brick.h"
#include "Colaiders.h"
#include "BonusHandler.h"
#include "Score.h"

Brick::Brick(const Vect& pos,float width_, float height_)
{
	position = pos;
	width = width_;
	height = height_;
	max_health = get_rand_health();
	health = max_health;
	color = make_color_by_health(health, max_health);
}

void Brick::update()
{
	color = make_color_by_health(health, max_health);
}

Rect Brick::get_shape_as_aabb() const
{
	return Rect(Vect(position.x, position.y), Vect(width, height));
}

void Brick::event_collision(Vect overlap, Vect dir, const ShapeType& shape_type)
{
	if (shape_type == ShapeType::ball) 
		health -= 1;
	
	if (health <= 0) {
		if (max_health >= 5) {
			Vect pos = Vect(position.x + width / 2, position.y + width / 2);
			BonusHandler::instance().add_bonus(pos, 30.0f, 20.0f);
		}

		Score::intstance().score += 10;
		dead = true;
	}
}

bool Brick::is_dead() const
{
	return dead;
}


ShapeType Brick::get_shape_type() const
{
	return ShapeType::rect;
}

ImColor Brick::get_color()
{
	return color;
}
