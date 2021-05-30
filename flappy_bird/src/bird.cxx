

#include "bird.hxx"
#include "game_config.hxx"


// It won't compile without this, so you get it for free.

//Model
Bird::Bird(Game_config const& config)
        : rad_width(config.bird_rad_width),
          rad_height(config.bird_rad_height),
          center(Position(config.bird_center_0)),
          velocity(Velocity(config.bird_velocity_0)),
          acceleration(Acceleration(config.bird_acceleration_0)),
          live(false),
          started(false),
          win(false)
{ }

Position
Bird::top_left() const
{

    return {center.x - rad_width, center.y - rad_height};
}


bool
Bird::hits_bottom(Game_config const& config) const
{

    if (center.y + rad_height > config.scene_dims.height) {
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
    // result.velocity = result.velocity + acceleration*dt;
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
    for (Obstacle & o : obstacles) {
        if (center.x - rad_width < o.top_left().x + o.width &&
            center.x + rad_width > o.top_left().x &&
            center.y - rad_height < o.top_left().y + o.height &&
            center.y + rad_height > o.top_left().y) {
            // std::cout<< "hit" << std::endl;
            // std::cout << center.x << " , " << center.y << std::endl;
            // std::cout << o.top_left().x << " , " << o.top_left().y << std::endl;
            return true;
        }


        // if (center.x + 0 > o.top_left().x &&
        //     center.x - 0 < o.top_left().x + o.width &&
        //     center.y + 0 > o.top_left().y &&
        //     center.y - 0 > o.top_left().y + o.height){
        //     return true;
        // }
        // if (center.x + radius < o.top_left().x ||
        //     o.top_right().x < center.x - radius ||
        //     center.y + radius < o.top_left().y ||
        //     o.bottom_left().y < center.y - radius) {
        //     false
        // }
    }
    return false;
}

bool
Bird::gains_point(std::vector<Obstacle>& obstacles) const
{
    if (live){
        for (Obstacle& o : obstacles) {
            if (center.x - rad_width == o.top_right().x &&
                !hits_obstacle(obstacles)){
                // center.y - radius > o.top_left().y + o.height &&
                //   center.y + radius < o.top_left().y) {
                return true;
            }
        }
    }
    return false;
}

bool
operator==(Bird const& a, Bird const& b)
{
    if (a.rad_height == b.rad_height &&
        a.rad_width == b.rad_width &&
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
    o << bird.rad_width;
    o << bird.rad_height;
    o << bird.center;
    o << bird.velocity;
    o << bird.acceleration;
    return o << "}";
}
