#include "gtest/gtest.h"
#include "world.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

bool vec3ExpectNear(phys::vec3 a,phys::vec3 b,float delta)
{
    phys::vec3 c = a - b;
    c = phys::vec3::abs(abs(c);
    return(c.getX()<delta && c.getY()<delta && c.getZ()<delta);
}

TEST(SphereWith0VelocityAnd0Acceleration,AskedToUpdate_InitialPosition)
{
    float mass{1};
    phys::vec3 init_pos{0,0,0};
    phys::vec3 init_vel{0,0,0};
    phys::Sphere sphere{mass,init_pos,init_vel};
    sphere.update();

    phys::vec3 expected_pos{0,0,0};

    EXPECT_EQ(expected_pos,sphere.getPosition());
}

TEST(SphereWithVelocityAnd0Acceleration,AskedToUpdate_CorrectPosition)
{
    float mass{1};
    phys::vec3 init_pos{0,0,0};
    phys::vec3 init_vel{1,0,0};
    phys::Sphere sphere{mass,init_pos,init_vel};
    sphere.update();

    float dt{0.1};
    phys::vec3 expected_pos{0,0,0};
    expected_pos = init_pos + init_vel*dt;

    EXPECT_EQ(expected_pos,sphere.getPosition());

    phys::vec3 init_pos2{-1,0,1};
    phys::vec3 init_vel2{1,-1,0};
    phys::Sphere sphere2{mass,init_pos2,init_vel2};
    sphere2.update();

    phys::vec3 expected_pos2{0,0,0};
    expected_pos2 = init_pos2 + init_vel2*dt;

    EXPECT_EQ(expected_pos2,sphere2.getPosition());
}

TEST(SphereWithGravityAndNoVelocity,AskedToUpdate_UpdatesCorrectly)
{
    float mass{1};
    phys::vec3 init_pos{0,10,0};
    phys::vec3 gravity{0,-9.81,0};
    phys::Sphere sphere{mass,init_pos};
    sphere.setAcceleration(gravity);
    sphere.update();

    phys::vec3 expected_pos{0,0,0};
    phys::vec3 expected_vel{0,0,0};
    float dt{0.1};
    expected_vel = gravity*dt;
    expected_pos = init_pos + expected_vel*dt;

    phys::vec3 actual_pos = sphere.getPosition();

    EXPECT_TRUE(vec3ExpectNear(expected_pos,sphere.getPosition(),.001f));
}

TEST(EmptyWorld,AskedForNumberOfSpheres_ReturnsZero)
{
    phys::World world;
    EXPECT_EQ(0,world.getNumSpheres());
}

TEST(WorldWithSphere,AskedForNumberOfSpheres_ReturnsOne)
{
    float mass{1};
    phys::vec3 init_pos{0,0,0};
    phys::Sphere *sphere{nullptr};
    sphere = new phys::Sphere{mass,init_pos};

    phys::World world;
    world.addSphere(sphere);

    EXPECT_EQ(1,world.getNumSpheres());
}

TEST(WorldWithNoGravityOrDensity,AskedToUpdate_UpdatesAllShperesCorrectly)
{
    float mass{1};
    phys::vec3 init_pos1{0,0,0};
    phys::vec3 init_vel1{1,-1,0};
    phys::Sphere *sphere1{nullptr};
    sphere1 = new phys::Sphere{mass,init_pos1,init_vel1};

    phys::vec3 init_pos2{5,5,5};
    phys::vec3 init_vel2{0,10,-10};
    phys::Sphere *sphere2{nullptr};
    sphere2 = new phys::Sphere{mass,init_pos2,init_vel2};

    phys::World world;
    world.addSphere(sphere1);
    world.addSphere(sphere2);
    world.update();

    phys::vec3 expected_pos1{0.1,-0.1,0};
    phys::vec3 expected_pos2{5,4,6};
//    float dt{world.getDt()};
//    phys::vec3 expected_pos1{0,0,0};
//    phys::vec3 expected_vel1{0,0,0};
//    phys::vec3 expected_pos2{0,0,0};
//    phys::vec3 expected_vel2{0,0,0};
//    expected_vel1 = world.getGravity()*dt;
//    expected_pos1 = init_pos1 + expected_vel1*dt;
//    expected_vel2 = world.getGravity()*dt;
//    expected_pos2 = init_pos2 + expected_vel2*dt;

    phys::vec3 test1 = sphere1->getPosition();
    phys::vec3 test2 = sphere2->getPosition();

    EXPECT_TRUE(vec3ExpectNear(expected_pos1,sphere1->getPosition(),.001f));
    EXPECT_TRUE(vec3ExpectNear(expected_pos2,sphere2->getPosition(),.001f));
}
