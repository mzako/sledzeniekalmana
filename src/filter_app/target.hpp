#ifndef _TARGET_HPP
#define _TARGET_HPP

#include "vect3f.hpp"

class target
{
public:
    target();
    ~target();
    void set_point(const vect3f&);
    vect3f get_point() const;
    void set_id(int id);
    int get_id() const;
private:
    vect3f point_;
    int id_;
};

#endif //_TARGET_HPP
