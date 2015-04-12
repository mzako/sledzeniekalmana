/**
*  \brief     target.cpp
*  \details   This file contains target class' functions definitions
*  \author    Michal Zakowski
*/
#include <vector>
#include "target.hpp"
using namespace std;
unsigned target::gId_ = 1;
/**
* Function update
* Updates target's position and notifies all observers to let them notice target's position change
*/
void target::update(unsigned time){
    current_position_ = curve_->get_position(time) + initial_position_;
    notify();
}
/**
* Function notify
* Notifies all observers by calling their update function
*/
void target::notify(){
    vector<sensor_observer*>::iterator it;
    for (it = observers_->begin(); it != observers_->end(); ++it){
        (*it)->update(this);
    }
}
/**
* Function set_sensor_observers
* Sets a pointer to vector to all observers available in current simulation
*/
void target::set_sensor_observers(std::vector<sensor_observer*>* observers){
    observers_ = observers;
}
/**
* Function get_current_position
* Return target's current position
*/
vect3f target::get_current_position() const{
    return current_position_;
}
/**
* Function get_initial_position
* Return target's initial position
*/
vect3f target::get_initial_position() const{
    return initial_position_;
}
/**
* Function get_id
* Return target's unique id
*/
unsigned target::get_id() const{
    return id_;
}
