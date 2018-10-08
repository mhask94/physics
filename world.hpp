#ifndef WORLD_HPP
#define WORLD_HPP
#include <vector>
#include "vec3.hpp"

namespace phys
{
    class Sphere;

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

    protected:
        vec3 m_gravity{0,0,0};
        float m_density{0};
        float m_dt{0.1};

    private:
        unsigned int m_num_spheres{0};
        std::vector<Sphere*> m_spheres;
    };
}

#endif // WORLD_HPP
