#include "view.hxx"
#include "model.hxx"
#include "bird.hxx"

static ge211::Color const obstacle_color{59, 163, 15};

View::View(Model& model)
        : model_(model),
          obstacle_sprite({model.config.obstacle_width,
                           1}, obstacle_color),
          bird_sprite("flappybird-2.png"),
          background_sprite("background.png"),
          end_background_sprite("end_background.png"),
          win_background_sprite("win_background.png"),
          score_sprite("0", {"sans.ttf", 30})
{ }

void
View::draw(ge211::Sprite_set& set)
{

    int score = model_.score();
    // std::cout<< score << std::endl;
    score_sprite.reconfigure(
            ge211::Text_sprite::Builder({"sans.ttf",30}) << score);
    set.add_sprite(score_sprite,{30,30}, 10);

    if (!model_.bird.live && model_.bird.started && model_.bird.win){
        set.add_sprite(win_background_sprite,{0,0},0);
    } else if (!model_.bird.live && model_.bird.started ){
        set.add_sprite(end_background_sprite,{0,0},0);
    } else {
        set.add_sprite(background_sprite,{0,0},0);
    }

    for (Obstacle o: model_.obstacles){
        // std::cout<< o << std::endl;
        set.add_sprite(obstacle_sprite,o.top_left(),5,
                       ge211::Transform::scale_y(o.height));
    }


    set.add_sprite(score_sprite,{30,30},5);

    auto p1 = model_.bird.top_left();
    auto p2 = p1.into<int>();
    set.add_sprite(bird_sprite, p2,5);


}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model_.config.scene_dims;
}
