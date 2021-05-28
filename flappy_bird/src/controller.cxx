#include "controller.hxx"
#include "model.hxx"

// Controller::Controller(Game_config const& model)
//         : view_(model_),
//         bird(model)
//
// { }
Controller::Controller(Model& model)
        : model_(model),
          view_(model)
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
        if (model_.bird.live) {
            model_.jump();
        }
        else{
            model_.launch();
        }
    }
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}


void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}