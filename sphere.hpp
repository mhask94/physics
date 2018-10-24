#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "vec3.hpp"
#include "world.hpp"

namespace phys
{
    class Sphere
    {
    public:
        Sphere(double radius,double mass,Vec3 position);
        Sphere(double radius,double mass,Vec3 position,Vec3 velocity);
        Sphere(double radius,double mass,double c_r,Vec3 position);
        Sphere(double radius,double mass,double c_r,Vec3 position,Vec3 velocity);
        ~Sphere();
        double getMass() const;
        void update(double dt,Vec3 acceleration,Boundary* box=nullptr);
        Vec3 getPosition() const;
        Vec3 getVelocity() const;
        double getDragCoef() const;
        double getRadius() const;
        bool isNearWall(Boundary* box);
        void handleSphereCollision(Sphere* other_sphere,Boundary* box=nullptr);
        void handleInitialSphereOverlap(Sphere* new_sphere,Boundary* box);

    private:
        double m_radius{0};
        double m_mass{0};
        Vec3 m_position{0,0,0};
        Vec3 m_velocity{0,0,0};
        double m_coef_restitution{0};
        double m_frontal_area{0};
        double m_drag_coef{0.15};
        void handleBoundaryCollision(Boundary* box);
        void handleCollisionVelocities(Sphere* other_sphere);
        void handleSphereOverlap(Sphere* other_sphere);
    };

    static double pi{3.14159};
}

#endif // SPHERE_HPP
