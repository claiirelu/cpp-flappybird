/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "game_config.hxx"

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : scene_dims{500, 1000},
          num_obstacles{15},
          bird_radius{50},
          bird_center_0{0,0},
          bird_velocity_0{0, 0},
          bird_acceleration_0{0, -9.8},
          obstacle_side_spacing{100},
          obstacle_top_down_spacing{200},
          obstacle_width{100},
          obstacle_max_height{700}
{ }

