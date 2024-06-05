#pragma once 
#include "Wall.h"
#include "Brick.h"


class Level {


public:
	void init(const ArkanoidSettings& settings);
	void update();
	std::vector<std::unique_ptr<Wall>> walls;
	std::vector<std::unique_ptr<Brick>> bricks;

private:

	void AddWall(const Vect& point, const Vect& p_left, const Vect& p_right);


	int bricks_columns_count = 15;
	int bricks_rows_count = 7;

	float bricks_columns_padding = 5.f;
	float bricks_rows_padding = 5.f;

	float wall_width = 5.f;
	int walls_count = 4;
};