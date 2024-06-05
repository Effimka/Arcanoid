#pragma once

#include "base.h"
#include <vector>

struct ArkanoidSettings
{
    static constexpr int bricks_columns_min = 10;
    static constexpr int bricks_columns_max = 30;
    static constexpr int bricks_rows_min = 3;
    static constexpr int bricks_rows_max = 10;

    static constexpr int walls_min = 4;
    static constexpr int walls_max = 10;

    static constexpr float bricks_columns_padding_min = 5.0f;
    static constexpr float bricks_columns_padding_max = 10.0f;
    static constexpr float bricks_rows_padding_min = 5.0f;
    static constexpr float bricks_rows_padding_max = 10.0f;

    static constexpr float ball_radius_min = 5.0f;
    static constexpr float ball_radius_max = 50.0f;
    static constexpr float ball_speed_min = 1.0f;
    static constexpr float ball_speed_max = 1000.0f;

    static constexpr float barrier_width_min = 15.f;
    static constexpr float barrier_width_max = 20.f;

    static constexpr float carriage_width_min = 50.0f;



    Vect world_size = Vect(1280.0f, 720.f);

    

    int bricks_columns_count = 15;
    int bricks_rows_count = 7;
    int walls_count = 4;

    float bricks_columns_padding = 5.0f;
    float bricks_rows_padding = 5.0f;

    float ball_radius = 10.0f;
    float ball_speed = 150.0f;

    float carriage_width = 100.0f;
    float barrier_width = 15.f;
};

struct ArkanoidDebugData
{
    struct Hit
    {
        Vect screen_pos;        // Hit position, in screen space
        Vect normal;            // Hit normal
        float time = 0.0f;      // leave it default
    };
    std::vector<Hit> hits;
};

enum class ShapeType {
    rect,
    ball,
    bonus,
    wall,
    carriage
};


class Arkanoid
{
public:
    virtual ~Arkanoid() = default;
    virtual void reset(const ArkanoidSettings& settings) = 0;
    virtual void draw(ImGuiIO& io, ImDrawList& draw_list) = 0;
    virtual void update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed) = 0;
};

extern Arkanoid* create_arkanoid();
