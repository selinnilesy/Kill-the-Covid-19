#include "MicroOrganism.h"

MicroOrganism::MicroOrganism(int idd, const vector<Wall*>& edges){
    id=idd;
    attached_cell=NULL;
    located=false;
    if(edges.size()){
    for(int i=0; i<edges.size();i++){
        if(edges[i]){
        Wall * wall1=&(*(edges.at(i)));   //dynamic cast
        CurvyWall * curvy_wall1;
        curvy_wall1 = dynamic_cast< CurvyWall*>(wall1);
        if(curvy_wall1) {
            const CurvyWall *temp=curvy_wall1; //sum
            cell_wall.push_back(new CurvyWall(*temp));
        }
        else{
            const Wall *temp=wall1; //sum
            cell_wall.push_back(new Wall(*temp));
        }
        }}}
}
ostream& operator<<(ostream& os, const MicroOrganism& microorganism){
    if(microorganism.located) {
        os<<"The microorganism " <<microorganism.id << " was successfully placed into the cell " << (microorganism.attached_cell)->GetCellID() ;
    }
   else os<< "The microorganism " <<microorganism.id << " could not be placed into any cell!";
   return os;
}
MicroOrganism::~MicroOrganism(){;}
