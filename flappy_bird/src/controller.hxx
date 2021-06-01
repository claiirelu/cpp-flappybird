#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

struct Controller : ge211::Abstract_game
{
    explicit Controller(Model&);

    void draw(ge211::Sprite_set& set) override;
    void on_key(ge211::Key) override;

    void on_frame(double dt) override;
    ge211::Dims<int> initial_window_dimensions() const override;

    Model& model_;
    View view_;
};
