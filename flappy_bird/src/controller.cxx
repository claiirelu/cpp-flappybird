#include "controller.hxx"
#include "model.hxx"

// constructs controller
Controller::Controller(Model& model)
        : model_(model),
          view_(model)
{ }

// draws using view function
void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

// allows game to start using spacebar and all subsequent presses to
// correspond to the bird jumping
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

// sets window dims
ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

// moves the model on each frame
void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}