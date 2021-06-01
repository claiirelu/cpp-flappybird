#include "model.hxx"

// constructs model with obstacles of random height and gaps
float const bird_reset_velocity = -400;
Model::Model(Game_config const& config)
        : random_obstacle_height(50, config.obstacle_max_height),
          random_offset(150, 300),
          config(config),
          bird(config)
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

// starts the game
void
Model::launch()
{
    if (!bird.started){
        bird.started = true;
        bird.live = true;
    }
}

// gives bird a velocity boost to look like a jump
void
Model::jump()
{
    if (bird.live) {
        bird.velocity.height = bird_reset_velocity;
    }
}

// details in hxx but basically moves everything to the next frame and checks
// for game ending
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
            bird.live = false;
            return;
        } else {
            bird.velocity.height += bird.acceleration.height;
            bird = bird.next(dt);
        }
        for (Obstacle & o : obstacles) {
            o.x -= 2;
        }

    }

}

// gets the current score
int
Model::score()
{
    if (bird.gains_point(obstacles)){
        scorevalue ++;
    }
    return scorevalue;
}