#ifndef WORLD_HPP
#define WORLD_HPP
#include <vector>
#include "vec3.hpp"

namespace phys
{
    class Sphere;

    struct Boundary
    {
    public:
        float max_x{5};
        float min_x{-5};
        float max_y{5};
        float min_y{-5};
        float max_z{5};
        float min_z{-5};
    };

    class World
    {
    public:
        World();
        World(vec3 gravity,float density);
        ~World();
        vec3 getGravity() const;
        void setGravity(const vec3 &gravity);
        float getDensity() const;
        void setDensity(float density);
        void addSphere(Sphere* sphere);
        unsigned int getNumSpheres() const;
        void update();
        float getDt();
        void setDt(float dt);
        void updateDynamics(Sphere* sphere);

    protected:
        vec3 m_gravity{0,0,0};
        float m_density{0};
        float m_dt{0.1};
        phys::Boundary m_boundary;

    private:
        unsigned int m_num_spheres{0};
        std::vector<Sphere*> m_spheres;
    };
}

#endif // WORLD_HPP
