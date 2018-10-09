#include "gtest/gtest.h"
#include "world.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

bool vec3ExpectNear(phys::Vec3 a,phys::Vec3 b,float delta)
{
    phys::Vec3 c = phys::Vec3::abs(a - b);
    return(c.getX()<delta && c.getY()<delta && c.getZ()<delta);
}

TEST(SphereWith0VelocityAnd0Acceleration,AskedToUpdate_InitialPosition)
{
    float radius{1};
    float mass{1};
    phys::Vec3 init_pos{0,0,0};
    phys::Vec3 init_vel{0,0,0};
    phys::Sphere sphere{radius,mass,init_pos,init_vel};

    float dt{0.1};
    phys::Vec3 gravity{0,0,0};
    sphere.update(dt,gravity);

    phys::Vec3 expected_pos{0,0,0};

    EXPECT_EQ(expected_pos,sphere.getPosition());
}

TEST(SphereWithVelocityAnd0Acceleration,AskedToUpdate_CorrectPosition)
{
    float radius{1};
    float mass{1};
    phys::Vec3 init_pos{0,0,0};
    phys::Vec3 init_vel{1,0,0};
    phys::Sphere sphere{radius,mass,init_pos,init_vel};

    float dt{0.1};
    phys::Vec3 gravity{0,0,0};
    sphere.update(dt,gravity);

    phys::Vec3 expected_pos{0,0,0};
    expected_pos = init_pos + init_vel*dt;

    EXPECT_EQ(expected_pos,sphere.getPosition());

    phys::Vec3 init_pos2{-1,0,1};
    phys::Vec3 init_vel2{1,-1,0};
    phys::Sphere sphere2{radius,mass,init_pos2,init_vel2};
    sphere2.update(dt,gravity);

    phys::Vec3 expected_pos2{0,0,0};
    expected_pos2 = init_pos2 + init_vel2*dt;

    EXPECT_EQ(expected_pos2,sphere2.getPosition());
}

TEST(SphereWithGravityAndNoVelocity,AskedToUpdate_UpdatesCorrectly)
{
    float radius{1};
    float mass{1};
    phys::Vec3 init_pos{0,10,0};
    phys::Vec3 gravity{0,-9.81,0};
    phys::Sphere sphere{radius,mass,init_pos};

    float dt{0.1};
    sphere.update(dt,gravity);

    phys::Vec3 expected_pos{0,0,0};
    phys::Vec3 expected_vel{0,0,0};
    expected_vel = gravity*dt;
    expected_pos = init_pos + expected_vel*dt;

    EXPECT_TRUE(vec3ExpectNear(expected_pos,sphere.getPosition(),.001f));
}

TEST(EmptyWorld,AskedForNumberOfSpheres_ReturnsZero)
{
    phys::World world;
    EXPECT_EQ(0,world.getNumSpheres());
}

TEST(WorldWithSphere,AskedForNumberOfSpheres_ReturnsOne)
{
    float radius{1};
    float mass{1};
    phys::Vec3 init_pos{0,0,0};
    phys::Sphere *sphere{nullptr};
    sphere = new phys::Sphere{radius,mass,init_pos};

    phys::World world;
    world.addSphere(sphere);

    EXPECT_EQ(1,world.getNumSpheres());

    delete sphere;
}

TEST(WorldWithNoGravityOrDensity,AskedToUpdate_UpdatesAllShperesCorrectly)
{
    float radius{1};
    float mass{1};
    phys::Vec3 init_pos1{0,0,0};
    phys::Vec3 init_vel1{1,-1,0};
    phys::Sphere *sphere1{nullptr};
    sphere1 = new phys::Sphere{radius,mass,init_pos1,init_vel1};

    phys::Vec3 init_pos2{5,5,5};
    phys::Vec3 init_vel2{0,10,-10};
    phys::Sphere *sphere2{nullptr};
    sphere2 = new phys::Sphere{radius,mass,init_pos2,init_vel2};

    phys::World world;
    world.addSphere(sphere1);
    world.addSphere(sphere2);
    world.update();

    phys::Vec3 expected_pos1{0.1,-0.1,0};
    phys::Vec3 expected_pos2{5,4,6};

    EXPECT_TRUE(vec3ExpectNear(expected_pos1,sphere1->getPosition(),.001f));
    EXPECT_TRUE(vec3ExpectNear(expected_pos2,sphere2->getPosition(),.001f));

    delete sphere1;
    delete sphere2;
}

TEST(WorldWithNoDensity,AskedToUpdate_UpdatesAllShperesCorrectly)
{
    float radius{1};
    float mass{1};
    phys::Vec3 init_pos1{0,0,0};
    phys::Vec3 init_vel1{0,0,0};
    phys::Sphere *sphere1{nullptr};
    sphere1 = new phys::Sphere{radius,mass,init_pos1,init_vel1};

    phys::Vec3 init_pos2{5,5,5};
    phys::Vec3 init_vel2{0,10,-10};
    phys::Sphere *sphere2{nullptr};
    sphere2 = new phys::Sphere{radius,mass,init_pos2,init_vel2};

    phys::Vec3 gravity{0,-9.81,0};
    float density{0};
    phys::World world{gravity,density};
    world.addSphere(sphere1);
    world.addSphere(sphere2);
    world.update();

    phys::Vec3 expected_pos1{0,0,0};
    phys::Vec3 expected_pos2{0,0,0};
    expected_pos1 = init_pos1 + (init_vel1+gravity*world.getDt())*world.getDt();
    expected_pos2 = init_pos2 + (init_vel2+gravity*world.getDt())*world.getDt();

    EXPECT_TRUE(vec3ExpectNear(expected_pos1,sphere1->getPosition(),.001f));
    EXPECT_TRUE(vec3ExpectNear(expected_pos2,sphere2->getPosition(),.001f));

    delete sphere1;
    delete sphere2;
}
