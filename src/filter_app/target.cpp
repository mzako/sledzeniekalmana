#include "target.hpp"


target::target()
{
}


target::~target()
{
}

void target::set_id(int id)
{
    id_ = id;
}


void target::set_point(const vect3f & point)
{
    point_ = point;
}


vect3f target::get_point() const
{
    return point_;
}

int target::get_id() const
{
    return id_;
}
