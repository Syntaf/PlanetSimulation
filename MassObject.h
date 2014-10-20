#ifndef MASSOBJECT_H_
#define MASSOBJECT_H_

class MassObject {
  public:
    float d_x, d_y, d_z;

    //get the gravitational pull between this
    //object and another object
    float gravitationalForce(MassObject otherObject);

    MassObject(float x, float y, float z, float mass);

  private:
    //mass is private because external objects should not be
    //able to modify an objects mass
    float d_mass;
};

#endif
