#include "gtest/gtest.h"
#include "world.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

TEST(Vec3,AskedIfEqualsSelf_ReturnsTrue)
{
    phys::Vec3 a{-1,0,1};

    EXPECT_EQ(true,a==a);
}

TEST(Vec3,AskedIfDoesntEqualSelf_ReturnsFalse)
{
    phys::Vec3 a{-1,0,1};

    EXPECT_EQ(false,a!=a);
}

TEST(Vec3,AskedToAddSelf_AddsProperly)
{
    phys::Vec3 a{-1,0,1};
    a += a;

    phys::Vec3 expected_vec3{-2,0,2};

    EXPECT_EQ(expected_vec3,a);
}

TEST(Vec3,AskedToMinusSelf_ReturnsZero)
{
    phys::Vec3 a{-1,0,1};
    a -= a;

    phys::Vec3 expected_vec3{0,0,0};

    EXPECT_EQ(expected_vec3,a);
}

TEST(Vec3,AskedToTimesSelf_MultipliesProperly)
{
    phys::Vec3 a{-1,0,1};
    a *= a;

    phys::Vec3 expected_vec3{1,0,1};

    EXPECT_EQ(expected_vec3,a);
}

TEST(Vec3,AskedToAddDouble_AddsProperly)
{
    phys::Vec3 a{-1,0,1};
    double b{0.5};
    a += b;

    phys::Vec3 expected_vec3{-0.5,0.5,1.5};

    EXPECT_EQ(expected_vec3,a);
}

TEST(Vec3,AskedToMinusDouble_SubtractsProperly)
{
    phys::Vec3 a{-1,0,1};
    double b{0.5};
    a -= b;

    phys::Vec3 expected_vec3{-1.5,-0.5,0.5};

    EXPECT_EQ(expected_vec3,a);
}

TEST(Vec3,AskedToTimesDouble_MultipliesProperly)
{
    phys::Vec3 a{-1,0,1};
    double b{0.5};
    a *= b;

    phys::Vec3 expected_vec3{-0.5,0,0.5};

    EXPECT_EQ(expected_vec3,a);
}

TEST(Vec3,AskedForSign_ReturnsSignVector)
{
    phys::Vec3 a{-4,0,4};
    a = phys::Vec3::sign(a);

    phys::Vec3 expected_vec3{-1,1,1};

    EXPECT_EQ(expected_vec3,a);
}

TEST(Vec3,AskedForAbsoluteValue_ReturnsAbsoluteValue)
{
    phys::Vec3 a{-9.1,0,0.78};
    a = phys::Vec3::abs(a);

    phys::Vec3 expected_vec3{9.1,0,0.78};

    EXPECT_EQ(expected_vec3,a);
}

TEST(TwoVec3s,AskedToTakeDotProduct_ReturnsCorrectValue)
{
    phys::Vec3 a{-2,2,1};
    phys::Vec3 b{1,3,0};
    double c{phys::Vec3::dot(a,b)};

    double expected_value{4};

    EXPECT_EQ(expected_value,c);
}

//TEST(Vec3,AskedForNorm_ReturnsNorm)
//{
//    phys::Vec3 a{-1,0,3};
//    double norm_a{phys::Vec3::norm(a)};

//    double expected_value{10};

//    EXPECT_EQ(expected_value,norm_a);
//}

TEST(SphereWith0VelocityAnd0Acceleration,AskedToUpdate_InitialPosition)
{
    double radius{1};
    double mass{1};
    phys::Vec3 init_pos{0,0,0};
    phys::Vec3 init_vel{0,0,0};
    phys::Sphere sphere{radius,mass,init_pos,init_vel};

    double dt{0.1};
    phys::Vec3 gravity{0,0,0};
    sphere.update(dt,gravity);

    phys::Vec3 expected_pos{0,0,0};

    EXPECT_EQ(expected_pos,sphere.getPosition());
}

TEST(SphereWithVelocityAnd0Acceleration,AskedToUpdate_CorrectPosition)
{
    double radius{1};
    double mass{1};
    phys::Vec3 init_pos{0,0,0};
    phys::Vec3 init_vel{1,0,0};
    phys::Sphere sphere{radius,mass,init_pos,init_vel};

    double dt{0.1};
    phys::Vec3 gravity{0,0,0};
    sphere.update(dt,gravity);

    phys::Vec3 expected_pos{0.1,0,0};
    double buffer{0.00001};

    EXPECT_TRUE(phys::Vec3::isNear(expected_pos,sphere.getPosition(),buffer));

    phys::Vec3 init_pos2{-1,0,1};
    phys::Vec3 init_vel2{1,-1,0};
    phys::Sphere sphere2{radius,mass,init_pos2,init_vel2};
    sphere2.update(dt,gravity);

    phys::Vec3 expected_pos2{-0.9,-0.1,1};

    EXPECT_TRUE(phys::Vec3::isNear(expected_pos2,sphere2.getPosition(),buffer));
}

TEST(SphereWithGravityAndNoVelocity,AskedToUpdate_UpdatesCorrectly)
{
    double radius{1};
    double mass{1};
    phys::Vec3 init_pos{0,10,0};
    phys::Vec3 gravity{0,-9.81,0};
    phys::Sphere sphere{radius,mass,init_pos};

    double dt{0.1};
    sphere.update(dt,gravity);

    phys::Vec3 expected_pos{0,9.90189,0};
    double buffer{0.00001};

    EXPECT_TRUE(phys::Vec3::isNear(expected_pos,sphere.getPosition(),buffer));
}

TEST(EmptyWorld,AskedForNumberOfSpheres_ReturnsZero)
{
    phys::World world;
    EXPECT_EQ(0,world.getNumSpheres());
}

TEST(World,AskedForNumberOfSpheres_ReturnsCorrectNumber)
{
    double radius{1};
    double mass{1};
    phys::Vec3 init_pos{0,0,0};
    phys::Sphere *sphere{nullptr};
    phys::Sphere *sphere2{nullptr};
    sphere = new phys::Sphere{radius,mass,init_pos};
    sphere2 = new phys::Sphere{radius,mass,init_pos};

    phys::World world;

    EXPECT_EQ(0,world.getNumSpheres());

    world.addSphere(sphere);

    EXPECT_EQ(1,world.getNumSpheres());

    world.addSphere(sphere2);

    EXPECT_EQ(2,world.getNumSpheres());

    delete sphere;
    delete sphere2;
}

TEST(WorldWithNoGravityOrDensity,AskedToUpdate_UpdatesAllShperesCorrectly)
{
    double radius{1};
    double mass{1};
    phys::Vec3 init_pos1{0,0,0};
    phys::Vec3 init_vel1{0,0,0};
    phys::Sphere *sphere1{nullptr};
    sphere1 = new phys::Sphere{radius,mass,init_pos1,init_vel1};

    phys::Vec3 init_pos2{5,5,5};
    phys::Vec3 init_vel2{0,10,-10};
    phys::Sphere *sphere2{nullptr};
    sphere2 = new phys::Sphere{radius,mass,init_pos2,init_vel2};

    phys::World world;
    world.setDt(0.1);
    world.addSphere(sphere1);
    world.addSphere(sphere2);
    world.update();

    phys::Vec3 expected_pos1{0,0,0};
    phys::Vec3 expected_pos2{5,6,4};
    double buffer{0.00001};

    EXPECT_TRUE(phys::Vec3::isNear(expected_pos1,sphere1->getPosition(),buffer));
    EXPECT_TRUE(phys::Vec3::isNear(expected_pos2,sphere2->getPosition(),buffer));

    delete sphere1;
    delete sphere2;
}

TEST(WorldWithNoDensity,AskedToUpdate_UpdatesAllShperesCorrectly)
{
    double radius{1};
    double mass{1};
    phys::Vec3 init_pos1{0,0,0};
    phys::Vec3 init_vel1{0,0,0};
    phys::Sphere *sphere1{nullptr};
    sphere1 = new phys::Sphere{radius,mass,init_pos1,init_vel1};

    phys::Vec3 init_pos2{5,5,5};
    phys::Vec3 init_vel2{0,10,-10};
    phys::Sphere *sphere2{nullptr};
    sphere2 = new phys::Sphere{radius,mass,init_pos2,init_vel2};

    phys::Vec3 gravity{0,0,-9.81};
    phys::World world{gravity};
    world.setDt(0.1);
    world.addSphere(sphere1);
    world.addSphere(sphere2);
    world.update();

    phys::Vec3 expected_pos1{0,0,-0.0981};
    phys::Vec3 expected_pos2{5,6,3.901899};
    double buffer{0.00001};

    EXPECT_TRUE(phys::Vec3::isNear(expected_pos1,sphere1->getPosition(),buffer));
    EXPECT_TRUE(phys::Vec3::isNear(expected_pos2,sphere2->getPosition(),buffer));

    delete sphere1;
    delete sphere2;
}

TEST(World,AskedToUpdate_UpdatesAllShperesCorrectly)
{
    double radius{1};
    double mass{10};
    phys::Vec3 init_pos1{0,0,0};
    phys::Vec3 init_vel1{1,0,0};
    phys::Sphere *sphere1{nullptr};
    sphere1 = new phys::Sphere{radius,mass,init_pos1,init_vel1};

    phys::Vec3 init_pos2{2,-2,2};
    phys::Vec3 init_vel2{0,10,-10};
    phys::Sphere *sphere2{nullptr};
    sphere2 = new phys::Sphere{radius,mass,init_pos2,init_vel2};

    phys::Vec3 gravity{0,0,-9.81};
    double density{1.275};
    double dt{1/30.0};
    phys::World world{gravity,density};
    world.setDt(dt);
    world.addSphere(sphere1);
    world.addSphere(sphere2);
    world.update();

    phys::Vec3 expected_pos1{0.033299,0,-0.0109};
    phys::Vec3 expected_pos2{2,-1.67,1.659104};
    double buffer{0.00001};

    EXPECT_TRUE(phys::Vec3::isNear(expected_pos1,sphere1->getPosition(),buffer));
    EXPECT_TRUE(phys::Vec3::isNear(expected_pos2,sphere2->getPosition(),buffer));

    delete sphere1;
    delete sphere2;
}

TEST(WorldWithSphereAtBoundary,AskedToUpdate_CollisionOccursProperly)
{
    double radius{1};
    double mass{1};
    phys::Vec3 init_pos1{4,0,0};
    phys::Vec3 init_vel1{2,0,0};
    phys::Sphere *sphere1{nullptr};
    sphere1 = new phys::Sphere{radius,mass,init_pos1,init_vel1};

    phys::Vec3 init_pos2{-4,0,0};
    phys::Vec3 init_vel2{-2,0,0};
    phys::Sphere *sphere2{nullptr};
    sphere2 = new phys::Sphere{radius,mass,init_pos2,init_vel2};

    phys::Vec3 init_pos3{0,-4,0};
    phys::Vec3 init_vel3{0,-1,0};
    phys::Sphere *sphere3{nullptr};
    sphere3 = new phys::Sphere{radius,mass,init_pos3,init_vel3};

    phys::Vec3 init_pos4{0,0,-4};
    phys::Vec3 init_vel4{0,0,-1};
    phys::Sphere *sphere4{nullptr};
    sphere4 = new phys::Sphere{radius,mass,init_pos4,init_vel4};

    phys::World world;
    world.addSphere(sphere1);
    world.addSphere(sphere2);
    world.addSphere(sphere3);
    world.addSphere(sphere4);
    phys::Boundary* boundary{new phys::Boundary{5.0}};
    world.setBoundary(boundary);
    world.update();

    phys::Vec3 expected_pos1{4,0,0};
    phys::Vec3 expected_pos2{-4,0,0};
    phys::Vec3 expected_pos3{0,-4,0};
    phys::Vec3 expected_pos4{0,0,-4};
    double buffer{0.00001};

    EXPECT_TRUE(phys::Vec3::isNear(expected_pos1,sphere1->getPosition(),buffer));
    EXPECT_TRUE(phys::Vec3::isNear(expected_pos2,sphere2->getPosition(),buffer));
    EXPECT_TRUE(phys::Vec3::isNear(expected_pos3,sphere3->getPosition(),buffer));
    EXPECT_TRUE(phys::Vec3::isNear(expected_pos4,sphere4->getPosition(),buffer));

    delete sphere1;
    delete sphere2;
    delete sphere3;
    delete sphere4;
}

TEST(WorldWith0AccelerationAnd2SpheresColliding,AskedToUpdate_CollisionOccursProperly)
{
    double radius1{1};
    double mass1{10};
    double cr1{0.6};
    phys::Vec3 init_pos1{-0.5,0,0};
    phys::Vec3 init_vel1{2,0,0};
    phys::Sphere *sphere1{nullptr};
    sphere1 = new phys::Sphere{radius1,mass1,cr1,init_pos1,init_vel1};

    double radius2{0.5};
    double mass2{5};
    double cr2{0.8};
    phys::Vec3 init_pos2{0.25,0,0};
    phys::Vec3 init_vel2{-2,0,0};
    phys::Sphere *sphere2{nullptr};
    sphere2 = new phys::Sphere{radius2,mass2,cr2,init_pos2,init_vel2};

    phys::World world;
    world.setDt(0.1);
    world.addSphere(sphere1);
    world.addSphere(sphere2);
    world.update();

    phys::Vec3 expected_vel1{-.4,0,0};
    phys::Vec3 expected_vel2{2.666666,0,0};
    expected_vel1 = cr1*(init_vel1-(2*mass2*phys::Vec3::dot(init_vel1-init_vel2,init_pos1-init_pos2)/((mass1+mass2)*phys::Vec3::dot(init_pos1-init_pos2,init_pos1-init_pos2)))*(init_pos1-init_pos2));
    expected_vel2 = cr2*(init_vel2-(2*mass1*phys::Vec3::dot(init_vel2-init_vel1,init_pos2-init_pos1)/((mass1+mass2)*phys::Vec3::dot(init_pos2-init_pos1,init_pos2-init_pos1)))*(init_pos2-init_pos1));

    phys::Vec3 expected_pos1{-0.3,0,0};
    phys::Vec3 expected_pos2{1.2,0,0};

    double buffer{0.00001};

    EXPECT_TRUE(phys::Vec3::isNear(expected_vel1,sphere1->getVelocity(),buffer));
    EXPECT_TRUE(phys::Vec3::isNear(expected_vel2,sphere2->getVelocity(),buffer));

    EXPECT_TRUE(phys::Vec3::isNear(expected_pos1,sphere1->getPosition(),buffer));
    EXPECT_TRUE(phys::Vec3::isNear(expected_pos2,sphere2->getPosition(),buffer));

    delete sphere1;
    delete sphere2;
}
