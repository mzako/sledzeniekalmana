#ifndef _VECT3_HPP
#define _VECT3_HPP

/**
 * \brief Class provides a simple point implementation
 * \author Adam Mościcki
 */
class vect3f
{
public:
    vect3f(float = 0.0f, float = 0.0f, float = 0.0f);
    float get_x() const;
    float get_y() const;
    float get_z() const;
    vect3f& operator=(const vect3f & a);
    ~vect3f();
private:
    float x_;
    float y_;
    float z_;
};

#endif //_VECT3F_HPP