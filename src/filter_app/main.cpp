#include "filter_module.hpp"
using namespace filter_app;
int main(){
    filter_module * instance = filter_module::get_instance();
    instance->run();

    return 0;
}