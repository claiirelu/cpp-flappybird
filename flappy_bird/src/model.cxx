#include "model.hxx"

Model::Model(Game_config const& config)
        : config(config),
          bird(config),
          random_obstacle_height(50, config.obstacle_max_height),
          random_offset(150, 300)
{
    for (int i = 0; i < config.num_obstacles/2; i++) {
            int x = ((config.scene_dims.width * 0.8) +
                     (i * config.obstacle_width) +
                     (i * config.obstacle_side_spacing));
            int height = random_obstacle_height.next();
            int y = height + random_offset.next();
            // top obstacle
            Obstacle top_obstacle{x, 0,
                        config.obstacle_width,
                        height};
            obstacles.push_back(top_obstacle);
            // bottom obstacle
            Obstacle bottom_obstacle{x, y,
                          config.obstacle_width,
                          config.scene_dims.height-y};
            obstacles.push_back(bottom_obstacle);
    }
}

// Freebie.
void
Model::launch()
{
    if (!bird.started){
        bird.started = true;
        bird.live = true;
    }
}

// Warning! Until you write code inside these member functions
// that uses at least one member variable, CLion is likely to
// insist that you can make this function static. Don’t believe
// it! You’ll regret the change if you do once you want to
// access member variables, since a static member function
// doesn't have access to an instance. (You should delete this
// warning after you’ve read it.)
//
// TL;DR: Don't go adding `static` to members.

// If the ball isn't live then you need to make it track the paddle,
// which is best done by constructing a new `Ball` and assigning it to
// `ball`.
void
Model::jump()
{
    if (bird.live) {
        // std::cout << "I HATE IT HERE" << std::endl;
        // std::cout << bird.velocity.height  << std::endl;
        // bird.velocity.height -= 500;
        // bird.acceleration.height = 10;
        bird.velocity.height = -400;
        // std::cout << bird.velocity.height  << std::endl;
    }
}

// The description in model.hxx is pretty detailed. What I will add here:
// You probably just want to call `Ball::next(double) const` twice: once
// speculatively as soon as you know that the ball is live, and again at the
// end, storing the result back to the ball that time.
void
Model::on_frame(double dt)
{

    if (bird.live) {
        Bird next = bird.next(dt);
        if (next.hits_bottom(config) || next.hits_obstacle(obstacles)
            || scorevalue == config.num_obstacles/2) {
            if (scorevalue == config.num_obstacles/2){
                bird.win = true;
            }
            // std::cout<< "hit" << std::endl;
            bird.live = false;
            return;
        } else {
            bird.velocity.height += bird.acceleration.height;
            bird = bird.next(dt);
        }
        for (Obstacle & o : obstacles) {
            // std::cout<< o << std::endl;
            o.x -= 2;
            // std::cout<< o << std::endl;
        }

    }

}

int
Model::score()
{
    if (bird.gains_point(obstacles)){
        scorevalue ++;
    }
    return scorevalue;
}