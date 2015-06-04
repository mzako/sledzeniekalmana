#include "filter_module.hpp"

#include <sstream>
#include <fstream>
#include <memory>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "sensor.hpp"

using namespace std;

namespace filter_app {

filter_module* filter_module::instance_ = nullptr;

filter_module* filter_module::get_instance()
{
    if (instance_ == nullptr){
        instance_ = new filter_module;
    }
    return instance_;
}

filter_module::filter_module()
{
    filter_ = std::shared_ptr<kalman_filter>(new kalman_filter);
}

void filter_module::run()
{
    vector<sensor> sensors;
    fstream fs;
    fs.open("../bufor.txt", fstream::in);
    {

        cereal::JSONInputArchive farchive(fs);
        farchive(
                /*cereal::make_nvp("sensors", */sensors /*)*/
        );
    }
    stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(
                cereal::make_nvp("sensors", sensors )
        );
    }
    cout << ss.str() << endl;
    while(true)
    {
        //Code hard to implement with mocking network module
        //1. Try to lock product_empty sempaphore or block
        //2. add new snapshot to kalman filter
        //3. estimate state
        //4. send_data
    }
}


void filter_module::receive_data(std::vector<vect3f> point)
{
    //Get data (async receive_data) save data somewhere  into the buffer (adding protected by lock) and unlock product_empy semaphore
}

void filter_module::send_data()
{
    //invoke code generating json and sending it furher
}

} /* namespase filter_app */
