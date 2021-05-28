#include "controller.hxx"
#include "model.hxx"

Controller::Controller(Game_config const& model)
        : view_(model_),
        bird(model)

{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code(' ')){
        if (bird.live) {
            model_.jump();
        }
        else{
            model_.launch();
        }
    }
}
