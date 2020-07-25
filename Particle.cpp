#include "Particle.h"

Particle::Particle(float x, float y){
    this->x=x;
    this->y=y;
}
Particle::Particle(const Particle& rhs){
    x=rhs.x;
    y=rhs.y;
}
float Particle::X() const { return x; }
float Particle::Y() const { return y; }
float Particle::FindDistance(const Particle& rhs) const {
    return (float) sqrt(((float) pow(rhs.y-y,2))+ ((float)pow(rhs.x-x,2)));
}
bool Particle::operator== (const Particle& rhs) const{
    return ((abs(rhs.y-y)<=EPSILON) && (abs(rhs.x-x)<=EPSILON));
}

ostream& operator<<(ostream& os, const Particle& rhs){
    os << "(" << rhs.x << "," << rhs.y << ")";
    return os;
}
