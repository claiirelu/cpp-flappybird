#pragma once

#include "model.hxx"
#include <ge211.hxx>

struct Model;

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);
    ge211::Dims<int> initial_window_dimensions() const;

private:
    Model const& model_;
    ge211::Rectangle_sprite obstacle_sprite;

    //temp
    ge211::Rectangle_sprite const bird_sprite;

    ge211::Text_sprite const score_sprite;
};
