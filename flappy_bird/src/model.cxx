#include "model.hxx"

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

// Freebie.
void
Model::launch()
{
    if (!bird.started){
        bird.started = true;
        bird.live = true;
    }
}

void
Model::jump()
{
    if (bird.live) {
        bird.velocity.height = -400;
    }
}

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