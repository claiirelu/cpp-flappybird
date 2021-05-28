#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(Game_config const&);

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_key(ge211::Key) override;

private:
    Model model_;
    View view_;
    Bird bird;
};
