#pragma once 


class ImGuiIO;
class Carriage;

class ProcessInput {
public:

	void update(ImGuiIO& input, Carriage& carriage);

	float speedStep = 5.0f;

};