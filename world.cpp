#include "world.hpp"
#include <vector>
#include "sphere.hpp"

namespace phys
{
    World::World()
    {
    }

    World::World(vec3 gravity, float density):
        m_gravity{gravity},
        m_density{density}
    {
    }

    World::~World()
    {
    }

    vec3 World::getGravity() const
    {
        return m_gravity;
    }

    void World::setGravity(const vec3 &gravity)
    {
        m_gravity = gravity;
    }

    float World::getDensity() const
    {
        return m_density;
    }

    void World::setDensity(float density)
    {
        m_density = density;
    }

    void World::addSphere(Sphere *sphere)
    {
        m_num_spheres++;
        m_spheres.push_back(sphere);
    }

    unsigned int World::getNumSpheres() const
    {
        return m_num_spheres;
    }

    void World::update()
    {
        for (unsigned int i{0}; i < m_num_spheres; i++)
        {
            m_spheres[i]->update(m_dt,m_gravity,m_density);
        }
    }

    float World::getDt()
    {
        return m_dt;
    }

    void World::setDt(float dt)
    {
        m_dt = dt;
    }
}
