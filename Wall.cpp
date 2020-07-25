#include "Wall.h"
Wall::Wall(float l) :start(0,0), end(0,0){
    length=l;
}
Wall::Wall(const Particle& lhs, const Particle& rhs) :start(lhs), end(rhs)
{
    length=lhs.FindDistance(rhs);
}
Wall::Wall(const Wall& rhs) :start(rhs.start), end(rhs.end) { length=rhs.length; }

const Particle& Wall::GetInitialParticle() const { return start;}

const Particle& Wall::GetFinalParticle() const { return end;}

float Wall::GetLength() const { return length;}
float Wall::FindAngleBetween(const Wall& rhs) const {
    double x1 = (float) rhs.end.X() - rhs.start.X();
    double y1 = (float) rhs.end.Y() - rhs.start.Y();
    double x2 = (float) end.X() - start.X();
    double y2 = (float) end.Y() - start.Y();;
    float angle1 , angle2 , angle;
    
    if (x1 != 0.0f) angle1 = atan(y1/x1);
    else angle1 = 3.14159 / 2.0;    // 90 degrees

    if (x2 != 0.0f)  angle2 = atan(y2/x2);
    else angle2 = 3.14159 / 2.0;    // 90 degrees
    
    angle = fabs(angle2-angle1);
    angle = angle * 180.0 / 3.14159;    // convert to degrees
    return angle;
}
void Wall::ComputeLength(){;}
Wall* Wall::Clone() const {
    Wall* ptr= new Wall(*this);
    return ptr;
}
bool Wall::IsContinuousLinear(const Wall& rhs) const {
    if(rhs.whoami()){
        if(rhs.start==end || rhs.end==start){
            if((abs( rhs.end.X()-rhs.start.X()))<=EPSILON && (abs(end.X()-start.X()))<=EPSILON) return true; //two vertical lines
            else if((abs( rhs.end.X()-rhs.start.X()))<=EPSILON) return false; //perpendicular lines
            else if((abs(end.X()-start.X()))<=EPSILON) return false; //perpendicular lines
            return ((abs((float) ((float)((float) rhs.end.Y()-rhs.start.Y())/( (float) rhs.end.X()-rhs.start.X()))-((float) ((float) end.Y()-start.Y())/((float) end.X()-start.X()))))<=EPSILON);
        }
    }
    return false;
}
const Wall& Wall::operator+(const Wall& rhs) const{
    const Wall *ptr;
    if(!rhs.whoami()) {
        
            throw ApplePearException();
        
        ptr = new Wall(start,end);
        return *ptr;
    }
    else{
    float m1,m2,angle1,angle2;
    if(rhs.start==end && rhs.end==start){ptr = new Wall(start,end);}
    else if(rhs.start==start && rhs.end==end){ptr = new Wall(start,end);}
    else if(rhs.start==end){ //calculate slopes now
        if (abs ((rhs.end.X() - rhs.start.X()))<=EPSILON && abs(end.X() - start.X())<=EPSILON) ptr = new Wall(start,rhs.end); //both vertical
        else if(abs(rhs.end.X() - rhs.start.X())<=EPSILON) ptr = new Wall(start,end);
        else if(abs(end.X() - start.X())<=EPSILON) ptr = new Wall(start,end);
        else{
            m1 = (rhs.end.Y() - rhs.start.Y()) / (rhs.end.X() - rhs.start.X());   // tan(A)
            m2 = (end.Y() - start.Y()) / (end.X() - start.X());
            if (abs(m1-m2)<=EPSILON) ptr = new Wall(start,rhs.end);
            else ptr = new Wall(start,end);
        }
    }
    else if(rhs.end==start){
         if (abs(rhs.end.X() - rhs.start.X())<=EPSILON && abs(end.X() - start.X())<=EPSILON) ptr = new Wall(rhs.start,end); //both vertical
               else if(abs(rhs.end.X() - rhs.start.X())<=EPSILON) ptr = new Wall(start,end);
               else if(abs(end.X() - start.X())<=EPSILON) ptr = new Wall(start,end);
               else{
                   m1 = (rhs.end.Y() - rhs.start.Y()) / (rhs.end.X() - rhs.start.X());   // tan(A)
                   m2 = (end.Y() - start.Y()) / (end.X() - start.X());
                   if(abs(m1-m2)<=EPSILON) ptr = new Wall(rhs.start,end);
                   else ptr = new Wall(start,end);
               }
    }
    else{
    throw ApplePearException();
    ptr = new Wall(start,end);
    }
    return *ptr;
    }
}
Wall::~Wall() { length=0; }
