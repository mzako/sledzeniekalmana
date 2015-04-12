#include "kalman_filter.hpp"

kalman_filter::kalman_filter()
{
    targets = boost::shared_ptr<std::vector<boost::shared_ptr<target>>>(new std::vector<boost::shared_ptr<target>>);
}


kalman_filter::~kalman_filter()
{
    targets.reset();
}

void kalman_filter::estimate()
{
}

void kalman_filter::add_new_snapshot(std::vector<target> targets)
{
}

std::vector<target> kalman_filter::get_data()
{
    std::vector < target > result;
    return result;
}