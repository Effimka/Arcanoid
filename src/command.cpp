#include "command.h"

void CmdRadiusX2UP::execute(std::vector<Ball>& balls, Carriage& car)
{
	for (int i = 0; i < balls.size(); ++i)
		balls[i].change_state(States::radiusX2);
};

void CmdSpeedX2UP::execute(std::vector<Ball>& balls, Carriage& car)
{
	for (int i = 0; i < balls.size(); ++i)
		balls[i].change_state(States::speedX2);
};

void CmdBallX5::execute(std::vector<Ball>& balls, Carriage& car)
{
	if (balls.size() > 6)
		return;
	balls.push_back(balls[0].clone());
};