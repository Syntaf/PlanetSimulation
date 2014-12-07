#ifndef PLANET_H_
#define PLANET_H_

const float G = 6.6700E-11;

class Planet {
  public:

    float d_x, d_y;

	Planet(float x, float y, float mass):d_x(x), d_y(y), d_mass(mass) {}

    //compute gravitational pull
    float gravitationalForce(Planet otherObject);



  private:
    //mass is private because external objects should not be
    //able to modify an objects mass
    float d_mass;
};

float Planet::gravitationalForce(Planet otherPlanet)
{
	//F = G m1*m2 / r^2
	// G = gravitational constant | G = 6.67300 x 10^-11
	//m1 = mass 1(kg)
	//m2 = mass 2(kg)
	//r = distance between the centers of the masses

	//find the distance between the x y and z pairs
	float x_dist = d_x - otherObject.d_x;
	float y_dist = d_y - otherObject.d_y;

	//calculate distance between the two objects r^2 = x^2 + y^2
	float r_Squared = ((x_dist * x_dist) + (y_dist * y_dist))

	return G * (((d_mass) * otherObject.d_mass) / r_Squared); //returns force in newtons
}

#endif
