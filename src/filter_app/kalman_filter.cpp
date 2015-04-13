#include "kalman_filter.hpp"

using namespace filter_app;

kalman_filter::kalman_filter()
{
    targets = boost::shared_ptr<std::vector<boost::shared_ptr<target>>>(new std::vector<boost::shared_ptr<target>>);
    //follow by example: http://www.forbot.pl/forum/topics20/inne-filtr-kalmana-teoria-i-praktyka-vt7789.htm
    transition_matrix = boost::numeric::ublas::identity_matrix<double>(6);
    observation_model_matrix = boost::numeric::ublas::matrix<double>(3, 6);
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