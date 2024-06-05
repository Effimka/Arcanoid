#pragma once

//#include "Shape.h"
#include "base.h"
class Shape;

int get_bonus();

int get_rand_sign();

float get_rand_float_in_range(float from = 0.f, float to = 1.f);

ImColor make_color_by_health(float health, float max_health);

int get_rand_health(int from = 1, int to = 10);

Vect get_rand_point_in_range(const Vect& p_left, const Vect& p_right);

bool same_sign(float a, float b);

Rect rect_to_screen(const Rect& rect, const Vect& world_to_screen);

bool is_collision_aabb(const Rect& rect1, const Rect& rect2);

bool collision_collaider(Shape& a_shape, Shape& b_shape, const Vect& a_dir = Vect(0.f), Vect& world_pos = Vect(0.f), Vect& normal = Vect(0.f));


