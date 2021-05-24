/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "game_config.hxx"

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : scene_dims{1024, 768},
          num_obstacles{15},
          obstacle_spacing{10},
          bird_radius{5},
          bird_center_0{0,0},
          bird_velocity_0{0, 0},
          bird_acceleration_0{0, -9.8},
          top_margin{100},
          side_margin{170},
          bottom_margin{50},
          obstacle_dims{5,10}
{ }

