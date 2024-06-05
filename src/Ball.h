#pragma once

#include "Shape.h"


enum class States {
    base,
    radiusX2,
    speedX2,
    radiusSpeedX2
};


class Ball : public Shape
{
public:
    Ball(const Vect& pos, float init_speed, float rad, float max_speed, float max_radius);
    
    void update(float elapsed);
    Rect get_shape_as_aabb() const override;
    void event_collision(Vect overlap, Vect dir, const ShapeType& shape_type) override;
     ShapeType get_shape_type() const override;
    
    float get_radius() const;
    Vect get_position() const;
    Vect get_dir() const;

    Ball clone();
    void change_state(States state);
    //void clear_state() { delete current_state; };

   

private:
    float time_to_use_bonus = 0.0f;
    float time_to_use_bonus_max = 15.0f;
    Vect position = Vect(0.0f);
    Vect velocity = Vect(0.0f);
    States current_state = States::base;

    float radius_max = 0;
    float speed_max = 0;
    float radius_init = 0;
    float speed_init = 0;
    float speed = 0.f;
    float radius = 0.f;
};

