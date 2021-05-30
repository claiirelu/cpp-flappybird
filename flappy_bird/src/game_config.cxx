/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "game_config.hxx"

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : scene_dims{1000, 750},
          num_obstacles{30},
          bird_rad_height{18},
          bird_rad_width{30},
          bird_center_0{scene_dims.width/2,scene_dims.height/2},
          bird_velocity_0{0, -600},
          bird_acceleration_0{0, 20},
          obstacle_side_spacing{200},
          obstacle_top_down_spacing{200},
          obstacle_width{100},
          obstacle_max_height{400}
{ }

