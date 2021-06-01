#pragma once

#include <ge211.hxx>
#include "bird.hxx"
#include "game_config.hxx"
#include <vector>

struct Model
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
    // 3. if the bird passes the number of sets of obstacles, set bird to be
    // dead, game ends
    // 4. if bird is still alive, move it to next posn (change in y only)
    // and move all bricks to the left
    void on_frame(double dt);


    ///
    /// MEMBER VARIABLES
    ///

    // random obstacle height
    ge211::Random_source<float> random_obstacle_height;

    // random obstacle offset
    ge211::Random_source<float> random_offset;



    Game_config const config;

    explicit Model(Game_config const& config = Game_config());

    std::vector<Obstacle> obstacles;

    /// MEMBER FUNCTIONS
    // resets bird velocity to simulate a jump
    void jump();

    // starts the game
    void launch();

    // keeps track of score
    int score();
    int scorevalue = 0;

    Bird bird;
};
