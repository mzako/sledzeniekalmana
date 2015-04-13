#include "simulation_module.hpp"
using namespace generator_app;
int main(){
    simulation_module * instance = simulation_module::get_instance();
    instance->run();

    return 0;
}
