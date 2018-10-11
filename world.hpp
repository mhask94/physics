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
        Boundary(float dim) :
            max_x{dim}, max_y{dim}, max_z{dim}, min_x{-dim}, min_y{-dim}, min_z{-dim} {}
        Boundary(float x,float y,float z) :
            max_x{x}, max_y{y}, max_z{z}, min_x{-x}, min_y{-y}, min_z{-z} {}
        float max_x{0};
        float max_y{0};
        float max_z{0};
        float min_x{0};
        float min_y{0};
        float min_z{0};
    };

    class World
    {
    public:
        World();
        World(Boundary* box);
        World(Vec3 gravity);
        World(Vec3 gravity,Boundary* box);
        World(Vec3 gravity,float density);
        World(Vec3 gravity,float density,Boundary* box);
        ~World();
        Vec3 getGravity() const;
        void setGravity(const Vec3 &gravity);
        float getDensity() const;
        void setDensity(float density);
        void addSphere(Sphere* sphere);
        unsigned int getNumSpheres() const;
        void update();
        float getDt();
        void setDt(float dt);
        void updateDynamics(Sphere* sphere);
        void setBoundary(Boundary *boundary);

    protected:
        Vec3 m_gravity{0,0,0};
        float m_density{0};
        float m_dt{0.1f};
        Boundary *m_boundary{nullptr};

    private:
        unsigned int m_num_spheres{0};
        std::vector<Sphere*> m_spheres;
    };
}

#endif // WORLD_HPP
