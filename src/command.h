#pragma once
#include "Ball.h"
#include "Carriage.h"



class Command {
public:
	virtual ~Command() {}
	virtual void execute(std::vector<Ball>& balls, Carriage& car) {};
};


class CmdRadiusX2UP : public Command{
public:
	void execute(std::vector<Ball>& balls, Carriage& car) override;
};

class CmdSpeedX2UP : public Command {
public:
	void execute(std::vector<Ball>& balls, Carriage& car) override;
};

class CmdBallX5 : public Command {
public:
	void execute(std::vector<Ball>& balls, Carriage& car) override;
};