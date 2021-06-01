// Defines a struct to hold configuration parameters.

#pragma once
#include <ge211.hxx>


struct Game_config
{
    // Constructs an instance with the default parameters.
    Game_config();

    // The dimensions of the whole window:
    ge211::Dims<int> scene_dims;


    // number of obstacles
    int num_obstacles;


    // The radius of the bird (bird is round but not symmetric):
    int bird_rad_width;
    int bird_rad_height;

    // The bird's initial center {width, height}:
    ge211::Posn<int> bird_center_0;

    // The bird's initial velocity {width, height}:
    ge211::Dims<int> bird_velocity_0;

    // The bird's initial acceleration {width, height}:
    ge211::Dims<float> bird_acceleration_0;

    // # of pixels between obstacles side to side
    int obstacle_side_spacing;

    // width of obstacle
    int obstacle_width;

    // max height of obstacle
    int obstacle_max_height;
};

