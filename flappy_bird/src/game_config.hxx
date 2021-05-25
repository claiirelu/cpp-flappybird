

// Defines a struct to hold configuration parameters. You should try different
// values to ensure that your model and UI adjust appropriately. You can do this
// by creating an instance and then assigning its parameters before constructing
// a `Model`:
//
//     Game_config config;
//     config.brick_cols = 15;
//     config.ball_radius *= 2;
//     Model model(config);
//

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


    // The radius of the bird:
    int bird_radius;

    // The bird's initial center {width, height}:
    ge211::Posn<int> bird_center_0;

    // The bird's initial velocity {width, height}:
    ge211::Dims<int> bird_velocity_0;

    // The bird's initial acceleration {width, height}:
    ge211::Dims<float> bird_acceleration_0;

    // # of pixels between obstacles side to side
    int obstacle_side_spacing;

    // # of pixels between top obstacle and bottom obstacle,
    // aka the size of the hole/gap
    int obstacle_top_down_spacing;

    // width of obstacle
    int obstacle_width;

    // max height of obstacle
    int obstacle_max_height;
};

