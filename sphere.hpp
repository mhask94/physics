#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "vec3.hpp"

namespace phys
{
    class Sphere
    {
    public:
        Sphere(vec3 position,vec3 velocity);
        ~Sphere();
        float getDt() const;
        void setDt(float dt);
        void update();

    private:
        float m_radius{0};
        vec3 m_position{0,0,0};
        vec3 m_velocity{0,0,0};
        vec3 m_acceleration{0,0,0};
        float m_dt{0.1};
    };
}

#endif // SPHERE_HPP
