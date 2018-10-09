#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "vec3.hpp"
#include "world.hpp"

namespace phys
{
    class Sphere
    {
    public:
        Sphere(float radius,float mass,Vec3 position);
        Sphere(float radius,float mass,Vec3 position,Vec3 velocity);
        ~Sphere();
        float getMass() const;
        void update(float dt,Vec3 acceleration);
        void update(float dt,Vec3 acceleration,Boundary* box);
        Vec3 getPosition() const;
        Vec3 getVelocity() const;
        Vec3 getAcceleration() const;
        float getDragCoef() const;

    private:
        float m_radius{0};
        float m_mass{1};
        Vec3 m_position{0,0,0};
        Vec3 m_velocity{0,0,0};
        Vec3 m_acceleration{0,0,0};
        float m_coef_restitution{0.8};
        float m_drag_coef{0};
    };
}

#endif // SPHERE_HPP
