#include "arkanoid_impl.h"
#include "Colaiders.h"
#include <GLFW/glfw3.h>
#include "BonusHandler.h"
#include "Score.h"

#ifdef USE_ARKANOID_IMPL
Arkanoid* create_arkanoid()
{
    return new ArkanoidImpl();
}
#endif

void ArkanoidImpl::reset(const ArkanoidSettings &settings)
{
    saved = settings;
    world_size.x = saved.world_size[0];
    world_size.y = saved.world_size[1];
    is_win = false;

    BonusHandler::instance().init();
    
    balls.clear();
    Vect pos = Vect(saved.world_size.x * 0.5f, saved.world_size.y * 0.8f);
    Ball ball(pos,saved.ball_speed, saved.ball_radius, saved.ball_speed_max, saved.ball_radius_max);
    balls.push_back(ball);
    
    carriage.init(saved);
    level.init(saved);
    Score::intstance().score = 0;
    
}

void ArkanoidImpl::update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed)
{
    world_to_screen = Vect(io.DisplaySize.x / world_size.x, io.DisplaySize.y / world_size.y);
    discrete_elapsed = elapsed / discrete_step;
    // process user input
    
    input.update(io, carriage);
    int i = 0;
    while (i < discrete_step) {
        for (int i = 0; i < balls.size(); ++i)
            balls[i].update(discrete_elapsed);

        carriage.update(discrete_elapsed);

        resolve_collision(debug_data);
        BonusHandler::instance().update(discrete_elapsed, balls, carriage);
        level.update();
        i++;
    }
    

    
    
    if (level.bricks.size() == 0)
        is_win = true;
    

}

void ArkanoidImpl::draw(ImGuiIO& io, ImDrawList &draw_list)
{
    Vect screen_pos;
    float screen_radius;

    //balls
    int sz = balls.size();
    for (int i = 0; i < sz; ++i) {
        screen_pos = balls[i].get_position() * world_to_screen;
        screen_radius = balls[i].get_radius() * world_to_screen.x;
        draw_list.AddCircleFilled(screen_pos, screen_radius, ImColor(0, 191, 255));
    }

    //carriage
    Rect rect = rect_to_screen(carriage.get_shape_as_aabb(), world_to_screen);
    draw_list.AddRectFilled(rect.pos, rect.size, ImColor(255, 255, 0));
    score_str = itoa(Score::intstance().score, buffer_score, 10);
    Vect score_pos = Vect(rect.pos.x + (rect.size.x - rect.pos.x) / 2, rect.pos.y);
    draw_list.AddText(io.FontDefault, 20.f, score_pos, ImColor(255, 0, 0), score_str);
    //walls
    sz = level.walls.size();
    for (int i = 0; i < sz; ++ i)
    {
        rect = rect_to_screen(level.walls[i]->get_shape_as_aabb(), world_to_screen);
        draw_list.AddRectFilled(rect.pos, rect.size, ImColor(255, 0, 255));
    }

    //bricks
    sz = level.bricks.size();
    for (int i = 0; i < level.bricks.size(); ++i)
    {
        rect = rect_to_screen(level.bricks[i]->get_shape_as_aabb(), world_to_screen);
        draw_list.AddRectFilled(rect.pos, rect.size, level.bricks[i]->get_color());
    }

    //bonuses
    sz = BonusHandler::instance().get_size();
    BonusHandler& handler = BonusHandler::instance();
    for (int i = 0; i < sz; ++i)
    {
        screen_pos = handler.bonuses[i]->position * world_to_screen;
        screen_radius = handler.bonuses[i]->radius * world_to_screen.x;
        draw_list.AddCircleFilled(screen_pos, screen_radius, handler.bonuses[i]->color);
    }

    if (is_win)
        draw_list.AddText(io.FontDefault, 50.f, Vect(world_size.x * 0.4, world_size.y * 0.5), ImColor(255, 0, 0),
                          "You Win!!!");
}

void ArkanoidImpl::resolve_collision(ArkanoidDebugData& debug_data)
{
    Vect debug_pos(0.f);
    Vect debug_normal(0.f);

    int sz = balls.size();

    for (int i = 0; i < balls.size(); ++i) {
        if (collision_collaider(balls[i], *level.walls[0], balls[i].get_dir(), debug_pos, debug_normal)) {
            if (balls.size() != 1) {
                auto it = balls.begin() + i;
                balls.erase(it);
                --i;
                --sz;
            }
            else {
                reset(saved);
            }
            add_debug_hit(debug_data, debug_pos, debug_normal);
        }
    }

    for (int i = 0; i < sz; ++i) {
        collision_collaider(balls[i], carriage, balls[i].get_dir(), debug_pos, debug_normal);

        for (int j = 1; j < level.walls.size(); ++j)
        {
            collision_collaider(balls[i], *level.walls[j], balls[i].get_dir(), debug_pos, debug_normal);
        }

        for (int j = 0; j < level.bricks.size(); ++j)
        {
            collision_collaider(balls[i], *level.bricks[j], balls[i].get_dir(), debug_pos, debug_normal);
        }
        add_debug_hit(debug_data, debug_pos, debug_normal);
    }

    collision_collaider(carriage, *level.walls[1]);
    collision_collaider(carriage, *level.walls[3]);

    
    sz = BonusHandler::instance().get_size();
    BonusHandler& handler = BonusHandler::instance();

    for (int i = 0; i < sz; ++i)
    {
        collision_collaider(carriage, *handler.bonuses[i]);
        collision_collaider(*level.walls[3], *handler.bonuses[i]);

    }


    
}


void ArkanoidImpl::add_debug_hit(ArkanoidDebugData& debug_data, const Vect& world_pos, const Vect& normal)
{
    ArkanoidDebugData::Hit hit;
    hit.screen_pos = world_pos * world_to_screen;
    hit.normal = normal;

    debug_data.hits.push_back(std::move(hit));
}


