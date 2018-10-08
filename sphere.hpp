#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "vec3.hpp"

namespace phys
{
    class Sphere
    {
    public:
        Sphere(float mass,vec3 position);
        Sphere(float mass,vec3 position,vec3 velocity);
        ~Sphere();
        float getMass() const;
        float getDt() const;
        void setDt(float dt);
        void update();
        vec3 getPosition() const;
        vec3 getVelocity() const;
        vec3 getAcceleration() const;
        void setAcceleration(const vec3 &acceleration);

    private:
        float m_mass{1};
        vec3 m_position{0,0,0};
        vec3 m_velocity{0,0,0};
        vec3 m_acceleration{0,0,0};
        float m_dt{0.1};
    };
}

#endif // SPHERE_HPP
