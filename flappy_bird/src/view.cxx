#include "view.hxx"
#include "model.hxx"
#include "bird.hxx"

static ge211::Color const obstacle_color{59, 163, 15};
static ge211::Color const black{0, 0, 0};
static ge211::Color const white{255,255,255};

View::View(Model& model)
        : model_(model),
          obstacle_sprite({model.config.obstacle_width,
                           1}, obstacle_color),
          bird_sprite("flappybird-2.png"),
          background_sprite("background.png"),
          end_background_sprite("end_background.png"),
          win_background_sprite("win_background.png"),
          end_text_sprite("GAME OVER", {"font.ttf", 50}),
          win_text_sprite("YOU WIN", {"font.ttf", 50})
{
    win_text_sprite.reconfigure(
            ge211::Text_sprite::Builder({"font.ttf",50}).color(black)
            << "YOU WIN");
}

void
View::draw(ge211::Sprite_set& set)
{

    // score sprite
    int score = model_.score();
    score_sprite.reconfigure(
            ge211::Text_sprite::Builder({"font.ttf",60}).color(black) << score);
    set.add_sprite(score_sprite,{497,34}, 10);
    small_score_sprite.reconfigure(
            ge211::Text_sprite::Builder({"font.ttf",50}).color(white) << score);
    set.add_sprite(small_score_sprite,{500,39}, 12);

    // alter background based on game state
    if (!model_.bird.live && model_.bird.started && model_.bird.win){
        set.add_sprite(win_background_sprite,{0,0},0);
        set.add_sprite(win_text_sprite,{400,375},30);
    } else if (!model_.bird.live && model_.bird.started ){
        set.add_sprite(end_background_sprite,{0,0},0);
        set.add_sprite(end_text_sprite,{400,375},30);
    } else {
        set.add_sprite(background_sprite,{0,0},0);
    }

    // draws obstacles
    for (Obstacle o: model_.obstacles){
        set.add_sprite(obstacle_sprite,o.top_left(),5,
                       ge211::Transform::scale_y(o.height));
    }

    // draws bird
    auto p1 = model_.bird.top_left();
    auto p2 = p1.into<int>();
    set.add_sprite(bird_sprite, p2,5);


}

// sets window dims
ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model_.config.scene_dims;
}
