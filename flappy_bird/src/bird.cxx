

#include "bird.hxx"
#include "game_config.hxx"

int const offset = 12;

// constructs bird
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

// finds the bird's top left coordinate
Position
Bird::top_left() const
{

    return {center.x - rad_width, center.y - rad_height};
}

// detects collision with floor
bool
Bird::hits_bottom(Game_config const& config) const
{

    if (center.y + rad_height > config.scene_dims.height) {
        return true;
    }
    return false;
}

// moves the bird to the next position
Bird
Bird::next(double dt) const
{
    Bird result(*this);
    result.center = result.center + velocity*dt;
    return result;
}

// detects collision with obstacles
bool
Bird::hits_obstacle(std::vector<Obstacle>& obstacles) const {
    // note, the bird sprite is not perfectly round and is not symmetric in
    // regards to both x and y so an offset has to be added so it doesn't
    // look too misleading for the user but it is not perfect.
    for (Obstacle & o : obstacles) {
        if (center.x - rad_width < o.top_left().x + o.width &&
            center.x + rad_width > o.top_left().x &&
            center.y - (rad_height - offset) < o.top_left().y + o.height &&
            center.y + (rad_height + offset) > o.top_left().y) {
            return true;
        }
    }
    return false;
}

// detects if the bird has moved past an obstacle
bool
Bird::gains_point(std::vector<Obstacle>& obstacles) const
{
    if (live){
        for (Obstacle& o : obstacles) {
            if (center.x - rad_width == o.top_right().x &&
                !hits_obstacle(obstacles)){
                return true;
            }
        }
    }
    return false;
}

// compares two birds
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

// not compares two birds
bool
operator!=(Bird const& a, Bird const& b)
{
    return !(a == b);
}

// prints bird
std::ostream&
operator<<(std::ostream& o, Bird const& bird)
{
    o << "Bird{";
    o << bird.rad_width;
    o << bird.rad_height;
    o << bird.center;
    o << bird.velocity;
    o << bird.acceleration;
    return o << "}";
}
