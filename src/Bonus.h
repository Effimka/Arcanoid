#pragma once
#include "Shape.h"
#include "command.h"

class Bonus : public Shape {
public:
    Bonus(const Vect& pos, float radius_, float initial_speed_);
    void update(float elapsed);

    Rect get_shape_as_aabb() const override;
    void event_collision(Vect overlap, Vect dir, const ShapeType& shape_type) override;
    virtual ShapeType get_shape_type() const;

    Vect position = Vect(0.0f);
    float radius = 0.0f;

    bool can_use = false;
    bool dead = false;

    ImColor color;

    std::unique_ptr<Command> bonus;

private:
    Vect velocity = Vect(0.0f);
    float initial_speed = 0.0f;
};