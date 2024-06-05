#include "ProcessInput.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "Carriage.h"

void ProcessInput::update(ImGuiIO& input, Carriage& carriage)
{
    // process user input
    if (input.KeysDown[GLFW_KEY_A])
        if(carriage.get_x_velocity() > 0.0f)
            carriage.change_x_velosity(-1 * speedStep * 5);
        else
            carriage.change_x_velosity(-1 * speedStep * 3);

        

    if (input.KeysDown[GLFW_KEY_D])
        if (carriage.get_x_velocity() < 0.0f)
            carriage.change_x_velosity(speedStep * 5);
        else
            carriage.change_x_velosity(speedStep * 3);


    
}


