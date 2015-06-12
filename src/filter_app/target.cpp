/**
*  \file     target.cpp
*  \details   This file contains target class' functions definitions
*  \author    Michal Zakowski
*/
#include <vector>
#include <memory>

#include "../commons/vect3f.hpp"

#include "target.hpp"

using namespace std;
using namespace commons;

namespace filter_app {

unsigned target::gId_ = 1;

const boost::numeric::ublas::matrix<float>& target::get_state() const
{
    return state_;
}
void target::set_state(boost::numeric::ublas::matrix<float> state)
{
    state_ = state;
}
vect3f target::get_current_position() const 
{
    return vect3f(state_(0, 0), state_(1, 0), state_(2, 0));
}
unsigned target::get_id() const{
    return id_;
}
const boost::numeric::ublas::matrix<float>& target::get_p_factor() const
{
    return p_factor_;
}
void target::set_p_factor(boost::numeric::ublas::matrix<float> p_factor)
{
    p_factor_ = p_factor;
}

} /* namespace filter_app */
