#include "model.hxx"

Model::Model(Game_config const& config)
        : config(config),
          bird(config),
          random_obstacle_height(0, config.obstacle_max_height)
{
    for (int i = 0; i < config.num_obstacles/2; i++) {
            int x = ((config.scene_dims().width * 0.75) +
                     (i * config.obstacle_width) +
                     (i * config.obstacle_side_spacing));
            int height = random_obstacle_height.next();
            int y = height + config.obstacle_top_down_spacing;
            // top obstacle
            Obstacle top_obstacle{x, 0,
                        config.obstacle_dims().width,
                        height};
            obstacles.push_back(top_obstacle);
            // bottom obstacle
            Obstacle bottom_obstacle{x, y,
                          config.obstacle_dims().width,
                          height};
            obstacles.push_back(bottom_obstacle);
    }
}

// Freebie.
void
Model::launch()
{
    bird.live = true;
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
        bird.velocity.height += 5;
    } else {
        Bird new_bird(config);
        bird = new_bird;
    }
}

// The description in model.hxx is pretty detailed. What I will add here:
// You probably just want to call `Ball::next(double) const` twice: once
// speculatively as soon as you know that the ball is live, and again at the
// end, storing the result back to the ball that time.
void
Model::on_frame(double dt)
{
    if (bird.live){
        Bird next = bird.next(dt);
        if (bird.hits_bottom(config) || next.hits_obstacle(obstacles)){
            ball.live = false;
            return;
        } else {
            ball.velocity.height -= ball.acceleration.height;
            for (int i = 0; i < config.num_obstacles; i++) {
                obstacles[i].top_left -= {10,0};
            }
            }
        }
        ball = ball.next(dt);
    }
}
