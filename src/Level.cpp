#include "Level.h"
#include "Colaiders.h"


void Level::init(const ArkanoidSettings& settings)
{
	wall_width = settings.barrier_width;
	walls_count = settings.walls_count;

	bricks_columns_count = settings.bricks_columns_count;
	bricks_rows_count = settings.bricks_rows_count;

	bricks_columns_padding = settings.bricks_columns_padding;
	bricks_rows_padding = settings.bricks_rows_padding;

	walls.clear();
	walls.push_back(std::make_unique<Wall>(Vect(0.0f, settings.world_size.y - wall_width), settings.world_size.x, wall_width));
	walls.push_back(std::make_unique<Wall>(Vect(0.0f), wall_width, settings.world_size.y));
	walls.push_back(std::make_unique<Wall>(Vect(0.0f), settings.world_size.x, wall_width));
	walls.push_back(std::make_unique<Wall>(Vect(settings.world_size.x - wall_width, 0.0f), wall_width, settings.world_size.y));

	Vect p_left = Vect(settings.world_size.x * 0.1f, settings.world_size.y * 0.1f);
	Vect p_right = Vect(settings.world_size.x * 0.9f, settings.world_size.y * 0.45f);
	Vect point;
	Vect size;

	for (int i = 4; i < walls_count; ++i)
	{
		point = get_rand_point_in_range(p_left, p_right);
		size = get_rand_point_in_range(Vect(25, 25), Vect(100, 100));
		for (int j = 4; j < walls.size();)
		{
			Wall wall = *walls[j];
			
			if (is_collision_aabb(wall.get_shape_as_aabb(), Rect(point, size)))
				point = get_rand_point_in_range(p_left, p_right);
			else
				++j;
		}
		AddWall(point, p_left, p_right);
	}

	bricks.clear();

	float stepX = (settings.world_size.x - bricks_columns_padding - wall_width) / bricks_columns_count;
	float stepY = settings.world_size.y * 0.65f / bricks_rows_count;

	bool is_wall = false;

	for (int i = 0; i < bricks_rows_count; ++i) {
		for (int j = 0; j < bricks_columns_count; ++j) {
			point = Vect(bricks_columns_padding + wall_width / 2 + (j * stepX),
						 bricks_rows_padding + wall_width + (i * stepY));
			
			size = Vect(stepX - bricks_columns_padding, stepY - 2 * bricks_rows_padding);
			for (int k = 4; k < walls.size(); ++k)
			{
				Wall wall = *walls[k];
				if (is_collision_aabb(wall.get_shape_as_aabb(), Rect(point.x, point.y, size.x, size.y))) {
					is_wall = true;
					break;
				}
			}
			if (!is_wall) {
				bricks.push_back(std::make_unique<Brick>(point, size.x, size.y));
			}
			is_wall = false;
		}
	}

	
}

void Level::update()
{
	auto sz = bricks.size();
	for (int i = 0; i < sz; ++i) {
		bricks[i]->update();
		if (bricks[i]->is_dead())
		{
			auto it = bricks.begin() + i;
			bricks.erase(it);
			--i;
			sz = bricks.size();
		}
	}
}

void Level::AddWall(const Vect& point, const Vect& p_left, const Vect& p_right)
{
	Vect size = get_rand_point_in_range(Vect(25, 25), Vect(100, 100));
	walls.push_back(std::make_unique<Wall>(point, size.x, size.y));
}
