#include "MassObject.hpp"

const float G = 6.67400E-11;

MassObject::MassObject(float x, float y, float z, float mass):
d_x(x), d_y(y), d_z(z), d_mass(mass)
{

}

float MassObject::gravitationalForce(MassObject otherObject)
{
  //F = G m1*m2 / r^2
  // G = gravitational constant | G = 6.67300 x 10^-11
  //m1 = mass 1(kg)
  //m2 = mass 2(kg)
  //r = distance between the centers of the masses

  //find the distance between the x y and z pairs
  float x_dist = d_x - otherObject.d_x;
  float y_dist = d_y - otherObject.d_y;
  float z_dist = d_z - otherObject.d_z;

  //calculate distance between the two objects r^2 = x^2 + y^2 + z^2
  float r_Squared = ((x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist));

  return G * (((d_mass) * otherObject.d_mass) / r_Squared); //returns force in newtons
}
