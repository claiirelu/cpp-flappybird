#include "controller.hxx"
#include "model.hxx"

int
main()
{
    Model model;
    Controller controller(model);
    controller.run();
}
