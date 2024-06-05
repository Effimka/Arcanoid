#include "Ball.h"
#include "Colaiders.h"


Ball::Ball(const Vect& pos, float init_speed, float rad, float max_speed, float max_radius) : position(pos)
{
    radius_max = max_radius;
    speed_max = max_speed;
    radius = radius_init = rad;
    speed = speed_init = init_speed;
    velocity = Vect(speed);
    current_state = States::base;
}

void Ball::update(float elapsed)
{
    position += velocity * elapsed;

    if (current_state != States::base)
    {
        time_to_use_bonus += elapsed;
        if (time_to_use_bonus >= time_to_use_bonus_max) {
            time_to_use_bonus = 0.0f;
            change_state(States::base);
        }
    }
}

Rect Ball::get_shape_as_aabb() const
{
    float d = 2 * radius;
    Vect p_left = Vect(position.x - radius, position.y - radius);
    Vect diametr = Vect(d, d);

    return Rect(p_left, diametr);
}

void Ball::event_collision(Vect overlap, Vect dir, const ShapeType& shape_type)
{

    if (overlap.x < overlap.y) {
        position.x += overlap.x * dir.x;
    }
    else {
        position.y += overlap.y * dir.y;
    }

    if(!same_sign(dir.x, velocity.x))
        velocity.x *= -1;

    if (!same_sign(dir.y, velocity.y))
        velocity.y *= -1;
}

ShapeType Ball::get_shape_type() const
{
    return ShapeType::ball;
}

float Ball::get_radius() const
{
    return radius;
}

Vect Ball::get_position() const
{
    return position;
}

Vect Ball::get_dir() const
{
    return velocity.Normalized();
}

Ball Ball::clone()
{
   //ToDo
    Vect pos = get_rand_point_in_range(position, Vect(position.x + 2 * radius, position.y + 2 * radius));
    Ball b = *this;
    b.position = pos;
    return  b;
}

void Ball::change_state(States state)
{
    //mb use state pattern
    if (current_state == state) {
        time_to_use_bonus -= 3.f;
        return;
    }
    else if ((current_state == States::radiusX2 && state == States::speedX2) ||
        (current_state == States::speedX2 && state == States::radiusX2))
    {
        if (radius_max - radius_init <= radius_max / 2)
            radius = radius_max;
        else
            radius = radius_init * 2.f;

        if (speed_max - speed_init <= speed_max / 2)
            speed = speed_max;
        else
            speed = speed_init * 2;
    }

    switch (state)
    {
    case States::base:
        radius = radius_init;
        speed = speed_init;
        break;
    case States::radiusX2:
        if (radius_max - radius_init <= radius_max / 2)
            radius = radius_max;
        else
            radius = radius_init * 2.f;
        break;
    case States::speedX2:
        if (speed_max - speed_init <= speed_max / 2)
            speed = speed_max;
        else
            speed = speed_init * 2;
        break;
    default:
        break;
    }
    current_state = state;

    Vect dir = get_dir();
    velocity = Vect(dir.x * speed, dir.y * speed);
}
