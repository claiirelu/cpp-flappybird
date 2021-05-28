#include "view.hxx"
#include "model.hxx"

static ge211::Color const obstacle_color{255, 255, 127};
static ge211::Color const bird_color{255, 255, 127};

View::View(Model const& model)
        : model_(model),
        //the height of the obstacle sprite needs to change
          obstacle_sprite({model.config.obstacle_width,
                           1},obstacle_color),
          bird_sprite({model.config.bird_radius,model.config.bird_radius},
                      bird_color),
          score_sprite("0",{"sans.ttf", 30})

{ }

void
View::draw(ge211::Sprite_set& set)
{


    for (Obstacle o: model_.obstacles){
        // std::cout<< o << std::endl;
        set.add_sprite(obstacle_sprite,o.top_left(),0,
                       ge211::Transform::scale_y(o.height));
    }

    auto p1 = model_.bird.top_left();
    auto p2 = p1.into<int>();
    set.add_sprite(bird_sprite, p2);


}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model_.config.scene_dims;
}
