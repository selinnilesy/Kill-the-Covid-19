#include "CurvyWall.h"

CurvyWall::CurvyWall(float l, float r) :Wall(l), center(0,0){
    radius=r;
}
CurvyWall::CurvyWall(const Particle& lhs, const Particle& rhs , const Particle& centerr) :Wall(lhs,rhs),center(centerr) {
    radius=lhs.FindDistance(center);
    Wall line1(center,lhs);
    Wall line2(center,rhs);
    length=2*PI*radius*((line1.FindAngleBetween(line2))/360);
}
CurvyWall::CurvyWall(const CurvyWall& rhs) :Wall(rhs.GetInitialParticle(),rhs.GetFinalParticle()),center(rhs.GetCenter()){
    radius=(rhs.GetCenter()).FindDistance(start);
    Wall line1(rhs.center,rhs.GetInitialParticle());
    Wall line2(rhs.center,rhs.GetFinalParticle());
    length=2*PI*radius*((line1.FindAngleBetween(line2))/360);
}
float CurvyWall::GetRadius() const{
    return radius;
}
const Particle& CurvyWall::GetCenter() const{
    return center;
}
void CurvyWall::ComputeLength(){;}
Wall* CurvyWall::Clone() const{
    Wall* ptr= new CurvyWall(*this);
    return ptr;
}
bool CurvyWall::IsContinuousLinear(const Wall& rhs) const { return false;}

const Wall& CurvyWall::operator+(const Wall& rhs) const{
    const CurvyWall *ptr;
    if(rhs.whoami()) { //if rhs straight wall
        throw ApplePearException();
     ptr = new CurvyWall(start,end,center);
     return *ptr;
    }
    else{
        const Wall * pba=&rhs;   //dynamic cast
        const CurvyWall * pd;
        pd = dynamic_cast<const CurvyWall*>(pba);
   
    if(rhs.start==end && rhs.end==start && pd->center==center && abs(pd->radius-radius)<=EPSILON ) //same curve
    ptr = new CurvyWall(start,end,center);
       
    else if(rhs.start==start && rhs.end==end && pd->center==center && abs(pd->radius-radius)<=EPSILON) //same curve
        ptr = new CurvyWall(start,end,center);
    else if(rhs.start==end && pd->center==center && abs(pd->radius-radius)<=EPSILON ){
        ptr = new CurvyWall(start,rhs.end,center);
    }
    else if(rhs.end==start && pd->center==center && abs(pd->radius-radius)<=EPSILON ){
        ptr = new CurvyWall(rhs.start,end,center);
    }
    else{
    throw ApplePearException();
    ptr = new CurvyWall(start,end,center);
    }
    return *ptr;
    }
}
CurvyWall::~CurvyWall() { radius=0; length=0;}
