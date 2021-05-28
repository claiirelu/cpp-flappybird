#pragma once

#include <ge211.hxx>
#include "bird.hxx"
#include "game_config.hxx"
#include <vector>

class Model
{
    ///
    /// CONSTRUCTOR
    ///

    ///
    /// MEMBER FUNCTIONS
    ///

    // updates state of game for one frame
    // 1. if the bird is going to hit an obstacle, set bird to be dead, game ends
    // 2. if the bird is going to hit the ground, set bird to be dead, game ends
    // 3. if bird is still alive, move it to next posn (change in y only)
    // and move all bricks to the left
    void on_frame(double dt);


    ///
    /// MEMBER VARIABLES
    ///

    // random obstacle height
    ge211::Random_source<float> random_obstacle_height;


public:


    // The state of the ball. Much of the model's business actually
    // happens in there, so see ball.hxx for that.
    // All of the bricks, in no particular order. `Block` is a type
    // alias for `ge211::Rect<float>`, which means it gives both the
    // position of the top-left corner of each brick and the dimensions.
    Game_config const config;
    // Constructs a model from a game configuration.
    //
    // The `= Game_config()` syntax makes the argument optional, in which case
    // it defaults to the default `Game_config`. That is, you can explicitly
    // create a `Game_config` to pass the `Model` constructor like so:
    //
    //     Game_config config;
    //     config.ball_radius = 2;
    //     Model model(config);
    //
    // Or you can omit the constructor argument, in which case you get
    // the default `Game_config` (as defined in game_config.cpp):
    //
//         Model model;
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby C++ would automatically convert
    // `Game_config`s into `Model`s if needed. You don't want that.
    explicit Model(Game_config const& config = Game_config());

    //this causes errors
    std::vector<Obstacle> obstacles;

///MEMBER FUNCTIONS
    // jump??
    void jump();
    // starts the game??
    void launch();

    // The state of the bird. Much of the model's business actually
    // happens in there, so see ball.hxx for that.
    //error
    Bird bird;
};
