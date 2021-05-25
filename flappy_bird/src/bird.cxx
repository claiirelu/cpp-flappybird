

#include "bird.hxx"
#include "game_config.hxx"


// It won't compile without this, so you get it for free.

Bird::Bird(Game_config const& config)
        : radius(config.bird_radius),
          center(Position(0,0)),
          velocity(Velocity(config.bird_velocity_0)),
          acceleration(Acceleration(config.bird_acceleration_0)),
          live(false)
{ }

Position
Bird::top_left() const
{

    return {center.x - radius, center.y - radius};
}


bool
Bird::hits_bottom(Game_config const& config) const
{

    if (center.y + radius > config.scene_dims.height) {
        return true;
    }
    return false;
}



// Recall that `this` is a `const Ball*`, and you can create a copy of a ball
// with the copy constructor. So to get a new `Ball` to return, you can write
//
//     Ball result(*this);
//
Bird
Bird::next(double dt) const
{
    Bird result(*this);
    result.velocity = result.velocity + acceleration*dt;
    result.center = result.center + velocity*dt;
    return result;
}

// As with the edge collision functions, we want to use the ball's
// bounding box. That is, the box whose top is center.y - radius, whose
// left is center.x - radius, whose bottom is center.y + radius, and
// whose right is center.x + radius.
//
// That way, we are checking for the intersection of two rectangles.
//
// One way to think of that is that the rectangles *don't* intersect if
// either of these is true:
//
//  - The right side of one rectangle is to the left of the left side of
//  the other.
//
//  - The bottom of one rectangle is above the top of the other
//
// Otherwise, they do.
//
bool
Bird::hits_obstacle(std::vector<Obstacle>& obstacles) const {
    for (size_t i = 0; i < obstacles.size(); i++) {
        if (center.x + radius < obstacles[i].top_left().x ||
            obstacles[i].top_right().x < center.x - radius ||
            center.y + radius < obstacles[i].top_left().y ||
            obstacles[i].bottom_left().y < center.y - radius) {
            return false;
        } else {
            return true;
        }
    }
    return true;
}




bool
operator==(Bird const& a, Bird const& b)
{
    if (a.radius == b.radius &&
        a.acceleration == b.acceleration &&
        a.velocity == b.velocity &&
        a.center == b.center &&
        a.live == b.live) {
        return true;
    }
    return false;
}

bool
operator!=(Bird const& a, Bird const& b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream& o, Bird const& bird)
{
    // You may have seen this message when running your tests. It
    // would be more helpful if it showed the contents of each ball,
    // right? So you can make that happen by making this print the
    // contents of the ball (however you like).
    o << "Bird{";
    o << "TODO: see the bottom of ball.cxx for more info";
    return o << "}";
}
