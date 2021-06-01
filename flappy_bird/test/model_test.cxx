#include "model.hxx"
#include "bird.hxx"
#include <catch.hxx>

Game_config const config;

// FR1: The bird is initially placed in the center of the screen.
TEST_CASE("Bird::Bird")
{
    Bird bird(config);
    CHECK(bird.center.x == config.scene_dims.width/2);
    CHECK(bird.center.y  == config.scene_dims.height/2);
}

// FR2: The player can begin the game by pressing the spacebar.
TEST_CASE("Make sure launch sets the bird to started and live")
{
    Model m(config);
    m.launch();
    CHECK(m.bird.started);
    CHECK(m.bird.live);
}

// FR3: Pressing the spacebar after the game starts will make the bird “jump”
// or move up on the screen. Otherwise, the bird will fall downwards towards
// the ground.

// FR 3.1: Pressing the spacebar after the game starts will make the bird “jump”
// or move up on the screen.
TEST_CASE("Bird jumps")
{
    Model m(config);
    m.obstacles.clear();
    m.bird.live = true;

    Velocity expected_velocity = {0,-400};

    m.jump();
    CHECK(m.bird.velocity == expected_velocity);

}


// FR 3.2: Otherwise, the bird will fall downwards towards the ground.
TEST_CASE("Bird falls to floor")
{
    Model m(config);
    m.obstacles.clear();
    m.bird.live = true;

    // Copy bird's velocity and center
    Position expected_center = m.bird.center;
    Velocity expected_velocity = m.bird.velocity;

    // Move by 0.5s and check
    m.on_frame(0.5);
    expected_velocity += m.bird.acceleration;
    expected_center += 0.5 * expected_velocity;
    CHECK(m.bird.center == expected_center);

    // Move by 0.25s and check
    m.on_frame(0.25);
    expected_velocity+= m.bird.acceleration;
    expected_center += 0.25 * expected_velocity;
    CHECK(m.bird.center == expected_center);

    // Move by 0.125s and check
    m.on_frame(0.125);
    expected_velocity += m.bird.acceleration;
    expected_center += 0.125 * expected_velocity;
    CHECK(m.bird.center == expected_center);
}

// FR4: If the player hits an obstacle or the ground, the game ends.

// FR4.1: If the player hits an obstacle, the game ends.
TEST_CASE("Bird hits_obstacle")
{
    Model m(config);
    double const dt = 1;
    m.obstacles.clear();
    m.obstacles.push_back({530,0, 100, 700});
    m.bird.live = true;

    // ball doesn't move, obstacle moves
    m.bird.velocity = {0,0};
    m.bird.acceleration = {0,0};


    // Simulate the passage of 1 frame (10 s):
    m.on_frame(dt);
    m.bird = m.bird.next(dt);
    CHECK(m.bird.live);
    CHECK(m.bird.hits_obstacle(m.obstacles));

    // Simulate the passage of 1 frame (10 s):
    m.on_frame(dt);
    m.bird = m.bird.next(dt);
    CHECK_FALSE(m.bird.live);

}

// FR4.2: If the player hits the ground, the game ends.
TEST_CASE("Bird hits_bottom")
{
    Bird bird(config);

    CHECK_FALSE(bird.hits_bottom(config));
    bird.center.y = config.scene_dims.height - 1;
    CHECK(bird.hits_bottom(config));
    bird.center.y = config.scene_dims.height - bird.rad_height;
    CHECK_FALSE(bird.hits_bottom(config));
}

// FR 5: When the player passes through all obstacles
// (some set number of them), the game ends.
TEST_CASE("Player wins")
{
    Model m(config);
    m.obstacles.clear();
    m.bird.live = true;
    m.scorevalue = m.config.num_obstacles/2;

    m.on_frame(1);
    CHECK_FALSE(m.bird.live);
    CHECK(m.bird.win);
}

// FR6: If the player passes through an obstacle, the player gains a point.
TEST_CASE("Player gains point")
{
    Model m(config);

    m.obstacles.clear();
    m.obstacles.push_back({472,0, 2, 1});
    m.obstacles.push_back({474,0, 2, 1});
    m.bird.live = true;

    // ball doesn't move, obstacle moves
    m.bird.velocity = {0,0};
    m.bird.acceleration = {0,0};

    int expected_score = 0;

    m.bird.live = true;
    // Simulate the passage of 1 frame:
    m.on_frame(1);
    CHECK_FALSE(m.bird.hits_obstacle(m.obstacles));

    // Simulate the passage of 1 frame:
    CHECK(m.bird.live);
    m.on_frame(1);
    expected_score++;
    CHECK(m.bird.gains_point(m.obstacles));
    CHECK(m.score() == expected_score);

    // Simulate the passage of 1 frame:
    m.on_frame(1);
    expected_score++;
    CHECK(m.bird.gains_point(m.obstacles));
    CHECK(m.score() == expected_score);
}

// FR7: The obstacles protruding from the top and bottom of the screen
// will move from right to left on the screen.
TEST_CASE("Obstacles move")
{
    Model m(config);
    m.bird.live = true;

    // ball doesn't move, obstacle moves
    ge211::Posn<ge211::geometry::Rect<int>::Coordinate>
    expected_position = m.obstacles[0].top_left();

    // Simulate the passage of 1 frame:
    m.on_frame(1);
    expected_position -= {2, 0};
    CHECK(m.obstacles[0].top_left() == expected_position);

    m.on_frame(1);
    expected_position -= {2, 0};
    CHECK(m.obstacles[0].top_left() == expected_position);

    m.on_frame(1);
    expected_position -= {2, 0};
    CHECK(m.obstacles[0].top_left() == expected_position);
}
