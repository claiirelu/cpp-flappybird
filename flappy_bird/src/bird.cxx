

#include "bird.hxx"
#include "game_config.hxx"



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



Bird
Bird::next(double dt) const
{
    Bird result(*this);
    result.center = result.center + velocity*dt;
    return result;
}

bool
Bird::hits_obstacle(std::vector<Obstacle>& obstacles) const {
    for (Obstacle & o : obstacles) {
        if (center.x - rad_width < o.top_left().x + o.width &&
            center.x + rad_width > o.top_left().x &&
            center.y - (rad_height - 12) < o.top_left().y + o.height &&
            center.y + (rad_height + 12) > o.top_left().y) {
            // std::cout<< "hit" << std::endl;
            // std::cout << center.x << " , " << center.y << std::endl;
            // std::cout << o.top_left().x << " , " << o.top_left().y << std::endl;
            return true;
        }
    }
    return false;
}

bool
Bird::gains_point(std::vector<Obstacle>& obstacles) const
{
    if (live){
        for (Obstacle& o : obstacles) {
            if (center.x - rad_width == o.top_right().x &&
            //if (center.x == o.top_left().x &&
                !hits_obstacle(obstacles)){
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
    o << "Bird{";
    o << bird.rad_width;
    o << bird.rad_height;
    o << bird.center;
    o << bird.velocity;
    o << bird.acceleration;
    return o << "}";
}
