#include "Bonus.h"
#include "Colaiders.h"

Bonus::Bonus(const Vect& pos, float radius_, float initial_speed_)
{
    position = Vect(pos.x + radius, pos.y + radius);
    initial_speed = initial_speed_;
    radius = radius_;
    velocity = Vect(0.f, initial_speed);
    switch (get_bonus()) {
    case 0:
        bonus = std::make_unique<CmdRadiusX2UP>(CmdRadiusX2UP());
        color = ImColor(0, 139, 139);
        break;
    case 1:
        bonus = std::make_unique<CmdBallX5>(CmdBallX5());
        color = ImColor(128, 0, 128);
        break;
    case 2:
        bonus = std::make_unique<CmdSpeedX2UP>(CmdSpeedX2UP());
        color = ImColor(240, 230, 140);
        break;
    }
}

void Bonus::update(float elapsed)
{
    position += velocity * elapsed;
}

Rect Bonus::get_shape_as_aabb() const
{
    float d = 2 * radius;
    Vect p_left = Vect(position.x - radius, position.y - radius);
    Vect diametr = Vect(d, d);

    return Rect(p_left, diametr);
}

void Bonus::event_collision(Vect overlap, Vect dir, const ShapeType& shape_type)
{
    if (shape_type == ShapeType::carriage) {
        can_use = true;
        dead = true;
    }
    if(shape_type == ShapeType::wall)
        dead = true;
}

ShapeType Bonus::get_shape_type() const
{
	return ShapeType::bonus;
}
