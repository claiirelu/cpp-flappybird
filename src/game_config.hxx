

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


    // Number of columns of bricks:
    int num_obstacles;

    // The number of pixels of space between each column and row of
    // bricks:
    int obstacle_spacing;

    // The radius of the ball:
    int bird_radius;

    // The ball's initial center {width, height}:
    ge211::Posn<int> bird_center_0;

    // The ball's initial velocity {width, height}:
    ge211::Dims<int> bird_velocity_0;

    // The ball's initial acceleration {width, height}:
    ge211::Dims<int> bird_acceleration_0;

    // Number of pixels from top of screen to top of brick formation:
    int top_margin;

    // Number of pixels from sides of screen to sides of brick formation:
    int side_margin;

    // Number of pixels from bottom of screen to bottom of paddle.
    int bottom_margin;

    // The dimensions of each brick. Also computed from the other properties.
    //
    // PRECONDITIONS (asserted):
    //  - brick_cols > 0
    //  - brick_rows > 0
    ge211::Dims<int> obstacle_dims;
};

