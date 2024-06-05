#pragma once

#include "arkanoid.h"
#include "Ball.h"
#include "Carriage.h"
#include "ProcessInput.h"
#include "Level.h"

#define USE_ARKANOID_IMPL



class ArkanoidImpl : public Arkanoid
{
public:
    void reset(const ArkanoidSettings& settings) override;
    void update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed) override;
    void draw(ImGuiIO& io, ImDrawList& draw_list) override;

private:

    void resolve_collision(ArkanoidDebugData& debug_data);

    //debug
    void add_debug_hit(ArkanoidDebugData& debug_data, const Vect& pos, const Vect& normal);
    int discrete_step = 6;
    float discrete_elapsed;
    ArkanoidSettings saved;
    Vect world_size = Vect(0.0f);
    Vect world_to_screen = Vect(0.0f);
    std::vector<Ball> balls;
    Carriage carriage;
    ProcessInput input;
    Level level;
    bool is_win = false;
    char buffer_score[33];
    char* score_str;
};
