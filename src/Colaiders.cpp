#include "Colaiders.h"
#include "Shape.h"
#include <random>
#include "mathfu/utilities.h"

std::random_device random_device;
std::mt19937 generator(random_device());

ImColor green{ 0, 255, 0 };
ImColor yellow{255, 255, 0};
ImColor red{ 255, 0, 0 };


ImColor make_color_by_health(float health, float max_health)
{
	float pr = health / max_health;
	if (pr >= 0.75)
		return green;
	else if (pr <= 0.75 && pr >= 0.4)
		return yellow;
	
	return red;
}

int get_bonus()
{
	std::uniform_int_distribution<int> bonus(0, 2);
	return bonus(generator);
}

float get_rand_float_in_range(float from , float to) {
	std::uniform_real_distribution<float> rand(from, to);
	return rand(generator);
}

int get_rand_sign() {
	if (get_rand_float_in_range() >= 0.5f)
		return -1;
	return 1;
}

int get_rand_health(int from, int to)
{
	std::uniform_int_distribution<int> health(from, to);
	if (get_rand_float_in_range() > 0.55f)
		return health(generator);
	
	return 1;
}

Vect get_rand_point_in_range(const Vect& p_left, const Vect& p_right)
{	
	std::uniform_real_distribution<float> x_axis(p_left.x, p_right.x);
	std::uniform_real_distribution<float> y_axis(p_left.y, p_right.y);

	return Vect(x_axis(generator), y_axis(generator));
}

bool same_sign(float a, float b)
{
	return (a > 0 && b > 0) || (a < 0 && b < 0);
}

Rect rect_to_screen(const Rect& rect, const Vect& world_to_screen)
{
	Vect p_min = rect.pos * world_to_screen;
	Vect size = rect.size * world_to_screen;
	Vect p_max = Vect(p_min.x + size.x, p_min.y + size.y);
	return Rect(p_min, p_max);
}

bool is_collision_aabb(const Rect& rect1, const Rect& rect2)
{
	if (rect1.pos.x < rect2.pos.x + rect2.size.x && rect1.pos.x + rect1.size.x > rect2.pos.x &&
		rect1.pos.y < rect2.pos.y + rect2.size.y && rect1.pos.y + rect1.size.y > rect2.pos.y) {
		return true;
	}
	else {
		return false;
	}
}

bool collision_collaider(Shape& a_shape, Shape& b_shape, const Vect& a_dir, Vect& world_pos, Vect& normal)
{
	Rect rect1 = a_shape.get_shape_as_aabb();
	Rect rect2 = b_shape.get_shape_as_aabb();
	Vect dir = Vect(0.f);

	if (a_shape.get_shape_type() == ShapeType::ball && b_shape.get_shape_type() == ShapeType::ball)
		return false;

	if (is_collision_aabb(rect1, rect2)) {

		if (rect1.pos.y + rect1.size.y > rect2.pos.y && rect1.pos.y < rect2.pos.y)
			dir.y = -1.f;
		if (rect1.pos.y < rect2.pos.y + rect2.size.y && rect1.pos.y + rect1.size.y > rect2.pos.y + rect2.size.y)
			dir.y = 1.f;

		if (rect1.pos.x + rect1.size.x > rect2.pos.x && rect1.pos.x < rect2.pos.x)
			dir.x = -1.f;
		if (rect1.pos.x < rect2.pos.x + rect2.size.x && rect1.pos.x + rect1.size.x > rect2.pos.x + rect2.size.x)
			dir.x = 1.f;


		dir.x += a_dir.x;
		dir.y += a_dir.y;

		Vect overlap;
		overlap.x = std::min(rect1.pos.x + rect1.size.x, rect2.pos.x + rect2.size.x) - std::max(rect1.pos.x, rect2.pos.x);
		overlap.y = std::min(rect1.pos.y + rect1.size.y, rect2.pos.y + rect2.size.y) - std::max(rect1.pos.y, rect2.pos.y);



		a_shape.event_collision(overlap, dir, b_shape.get_shape_type());
		b_shape.event_collision(overlap, dir, a_shape.get_shape_type());

		if (a_shape.get_shape_type() == ShapeType::ball)
		{
			normal = dir;
			world_pos = Vect(rect1.pos.x + rect1.size.x / 2, rect1.pos.y + rect1.size.x / 2);
		}

		return true;
	}
	return false;
}
