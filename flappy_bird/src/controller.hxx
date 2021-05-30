#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

struct Controller : ge211::Abstract_game
{
// public:
//     Controller(Game_config const&);
    explicit Controller(Model&);

// protected:
    void draw(ge211::Sprite_set& set) override;
    void on_key(ge211::Key) override;

    void on_frame(double dt) override;
    ge211::Dims<int> initial_window_dimensions() const override;
// private:
    Model& model_;
    View view_;
    // Bird bird;
};
