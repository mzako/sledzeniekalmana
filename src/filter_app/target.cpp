/**
*  \brief     target.cpp
*  \details   This file contains target class' functions definitions
*  \author    Michal Zakowski
*/
#include <vector>
#include <memory>
#include "target.hpp"
#include "vect3f.hpp"
using namespace std;
using namespace filter_app;
unsigned target::gId_ = 1;
/**
* Function get_state
* Return target's current state vector
*/
const boost::numeric::ublas::matrix<float>& target::get_state() const
{
    return state_;
}
/**
* Function set_state
* Set target's current state vector
*/
void target::set_state(boost::numeric::ublas::matrix<float> state)
{
    track_.add_state(state_);
    state_ = state;
}
/**
* Function get_current_position
* Return target's current position
*/
vect3f target::get_current_position() const 
{
    return vect3f(state_(0, 0), state_(1, 0), state_(2, 0));
}
/**
* Function get_id
* Return target's unique id
*/
unsigned target::get_id() const{
    return id_;
}
/**
* Function get_p_factor
* Return target's current p_factor matrix
*/
const boost::numeric::ublas::matrix<float>& target::get_p_factor() const
{
    return p_factor_;
}
/**
* Function set_p_factor
* Set target's p_factor matrix
*/
void target::set_p_factor(boost::numeric::ublas::matrix<float> p_factor)
{
    p_factor_ = p_factor;
}
