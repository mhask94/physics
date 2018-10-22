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
        Boundary(double dim) :
            max_x{dim}, max_y{dim}, max_z{dim}, min_x{-dim}, min_y{-dim}, min_z{-dim} {}
        Boundary(double x,double y,double z) :
            max_x{x}, max_y{y}, max_z{z}, min_x{-x}, min_y{-y}, min_z{-z} {}
        double max_x{0};
        double max_y{0};
        double max_z{0};
        double min_x{0};
        double min_y{0};
        double min_z{0};
    };

    class World
    {
    public:
        World();
        World(Boundary* box);
        World(Vec3 gravity);
        World(Vec3 gravity,Boundary* box);
        World(Vec3 gravity,double density);
        World(Vec3 gravity,double density,Boundary* box);
        ~World();
        Vec3 getGravity() const;
        void setGravity(const Vec3 &gravity);
        double getDensity() const;
        void setDensity(double density);
        double getDt();
        void setDt(double dt);
        void setBoundary(Boundary *boundary);
        Boundary *getBoundary() const;
        unsigned int getNumSpheres() const;
        void addSphere(Sphere* sphere);
        void update();
        void updateDynamics(Sphere* sphere);
        void checkForSphereCollision(Sphere* sphere1,Sphere* sphere2);
        void clearWorld();

    protected:
        Vec3 m_gravity{0,0,0};
        double m_density{0};
        double m_dt{0};
        Boundary *m_boundary{nullptr};

    private:
        int m_num_spheres{0};
        std::vector<Sphere*> m_spheres;
    };
}

#endif // WORLD_HPP
