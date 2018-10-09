#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "vec3.hpp"
#include "world.hpp"

namespace phys
{
    class Sphere
    {
    public:
        Sphere(float radius,float mass,vec3 position);
        Sphere(float radius,float mass,vec3 position,vec3 velocity);
        ~Sphere();
        float getMass() const;
        void update(float dt,vec3 acceleration);
        vec3 getPosition() const;
        vec3 getVelocity() const;
        vec3 getAcceleration() const;
//        void setAcceleration(const vec3 &acceleration);
        float getDragCoef() const;

    private:
        float m_radius{0};
        float m_mass{1};
        vec3 m_position{0,0,0};
        vec3 m_velocity{0,0,0};
        vec3 m_acceleration{0,0,0};
        float m_coef_restitution{0.8};
        float m_drag_coef{0};
    };
}

#endif // SPHERE_HPP
