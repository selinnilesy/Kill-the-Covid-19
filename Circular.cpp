#include "Circular.h"

Circular::Circular(int idd, float radiuss) :MicroOrganism(radiuss), radius(radiuss) {
    id=idd;
}
Circular::~Circular(){
    if(cell_wall.size()){
        for(int i=0; i<cell_wall.size();i++) if(cell_wall.at(i)) {
            delete cell_wall.at(i);
            cell_wall.at(i)=NULL;
        }
    }
    id=0;
    radius=0;
    located=false;
    attached_cell=NULL;
}
void Circular::React(){
if(attached_cell->GetCellWall().size()==1){
            Wall * wall1=attached_cell->GetCellWall().at(0);   //dynamic cast
            CurvyWall *curvy_wall1;
            curvy_wall1 = dynamic_cast< CurvyWall*>(wall1);
 if(curvy_wall1){
            float center_x=(curvy_wall1->GetCenter()).X();
            float center_y=(curvy_wall1->GetCenter()).Y();
            float initial_x=(curvy_wall1->GetInitialParticle()).X();
            float initial_y=(curvy_wall1->GetInitialParticle()).Y();
            float end_x=(curvy_wall1->GetFinalParticle()).X();
            float end_y=(curvy_wall1->GetFinalParticle()).Y();
const Particle nw_initial(initial_x+(initial_x-center_x),initial_y+(initial_y-center_y));
const Particle nw_final(end_x+(end_x-center_x),end_y+(end_y-center_y));
Wall *nw= new CurvyWall(nw_initial, nw_final, curvy_wall1->GetCenter());
vector<Wall*> my_new_cell_wall;
my_new_cell_wall.push_back(nw);
attached_cell->RenewCellWall(my_new_cell_wall); //gonna deep copy
     delete nw;
     nw=NULL;}
}
}
bool Circular::DoesContain(const Particle& rhs) const{
    if(cell_wall.size()){
        Wall *nw= cell_wall.at(0);
        CurvyWall * temp=dynamic_cast< CurvyWall*>(nw);
        if(temp){
        if((temp->GetCenter()).FindDistance(rhs)<=radius) return true;
        else if((temp->GetCenter()).FindDistance(rhs)>radius && (abs((temp->GetCenter()).FindDistance(rhs))-radius)<=EPSILON ) return true;
        return false;}
    }
    return false;
}
bool Circular::DoesFitInto(const Cell& rhs) const{
    Cell *al = new Cell(rhs);
    al->StrengthenCellWall();
    if(al->GetCellWall().size()==1){
        Wall *nw= (al->GetCellWall()).at(0);
        CurvyWall * temp=dynamic_cast< CurvyWall*>(nw);
        if(temp){ //need a circular cell
        if(abs((temp->GetRadius())-radius)<=EPSILON){ //check the only curvywall == microorgnsm
        delete al;
        al=NULL;
        return true;
        }}
    }
    delete al;
    al=NULL;
    return false;
}
void Circular::ConnectToCell(Cell* const cell){
   
    cell->StrengthenCellWall();
    Wall *nw= ((cell->GetCellWall()).at(0))->Clone();
    CurvyWall * temp=dynamic_cast< CurvyWall*>(nw);
    if(temp){
    int size=cell_wall.size();
    if(cell_wall.size()){ //clean ex microo-wall
        for(int i=0; i<cell_wall.size(); i++) if(cell_wall.at(i)) {
            delete cell_wall.at(i);
            cell_wall.at(i)=NULL;
        }
        for(int i=0; i<size; i++) { //empty the vector !!!
            cell_wall.erase(cell_wall.begin());
        }
    }
        cell_wall.push_back(nw); //new circle
    }
    located=true;
    attached_cell=cell;
}
