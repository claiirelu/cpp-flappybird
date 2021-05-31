#pragma once

#include "model.hxx"
#include <ge211.hxx>

struct Model;

class View
{
public:
    explicit View(Model& model);

    void draw(ge211::Sprite_set& set);
    ge211::Dims<int> initial_window_dimensions() const;

private:
    Model& model_;
    ge211::Rectangle_sprite obstacle_sprite;

    ge211::Image_sprite const bird_sprite;
    ge211::Image_sprite const background_sprite;
    ge211::Image_sprite const end_background_sprite;
    ge211::Image_sprite const win_background_sprite;

    ge211::Text_sprite score_sprite;
    ge211::Text_sprite small_score_sprite;
    ge211::Text_sprite const end_text_sprite;
    ge211::Text_sprite const win_text_sprite;
};
