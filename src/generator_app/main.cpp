#include "simulation_module.hpp"

int main(){
    simulation_module * instance = simulation_module::get_instance();
    instance->run();
}