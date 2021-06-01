// Defines a struct for modeling the bird.

#pragma once

#include <ge211.hxx>
#include "game_config.hxx"
#include <iostream>


///   struct Position
///   {
///       float x;   // pixel distance from left edge of window
///       float y;   // pixel distance from top edge of window
///   };
using Position = ge211::Posn<float>;


///   struct Velocity
///   {
///       float width;   // horizontal rate of change (px/s)
///       float height;  // vertical rate of change (px/s)
///   };
using Velocity = ge211::Dims<float>;

/// acceleration
using Acceleration = ge211::Dims<float>;


///   struct Obstacle
///   {
///       int x;       // x coordinate of left side of rectangle
///       int y;       // y coordinate of top side of rectangle
///       int width;
///       int height;
///   };
using Obstacle = ge211::Rect<int>;



struct Bird
{
    //
    // CONSTRUCTOR
    //

    Bird(Game_config const&);

    //
    // MEMBER FUNCTIONS
    //
    Position top_left() const;

    /// Returns the state of the bird after `dt` seconds have passed
    Bird next(double dt) const;

    /// Detects collision with the bottom of the screen
    bool hits_bottom(Game_config const&) const;

    /// Detects collision with obstacles
    bool hits_obstacle(std::vector<Obstacle>& obstacles) const;

    /// Detects when passing an obstacle
    bool gains_point(std::vector<Obstacle>& obstacles) const;


    ///
    /// MEMBER VARIABLES
    ///

    // radius of bird (the bird sprite is not symmetric so detecting collision
    // gets kind of wonky so this is used to reduce the number of adjusted
    // offsets
    int rad_width;
    int rad_height;

    Position center;

    Velocity velocity;

    Acceleration acceleration;

    // when the bird is live, it is moving
    bool live;

    // when started is true, the game has passed the initial state
    bool started;

    // when the player passes enough obstacles, it is considered a win
    bool win;
};


bool
operator==(Bird const&, Bird const&);


bool
operator!=(Bird const&, Bird const&);


std::ostream&
operator<<(std::ostream&, Bird const&);
