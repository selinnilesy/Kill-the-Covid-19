#include "Cell.h"

Cell::Cell(int i, const vector<Wall*>& shape, Tissue* tiss){
    id=i;
    for(int i=0; i<shape.size();i++){
        Wall * wall1=&(*(shape.at(i)));   //dynamic cast
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
    }
    belongs_to=tiss;
}
Cell::Cell(const Cell& rhs){
    id=rhs.id;
    for(int i=0; i<(rhs.cell_wall).size();i++){
        Wall * wall1=rhs.cell_wall.at(i);   //dynamic cast
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
    }
    belongs_to=rhs.belongs_to;
}
int Cell::GetCellID() const{ return id;}
Tissue* Cell::GetTissue() const {return belongs_to;}
const vector<Wall*>& Cell::GetCellWall() const { return cell_wall;}
    
Cell::~Cell(){
    if(cell_wall.size()){
        for(int i=0; i<cell_wall.size();i++) if(cell_wall.at(i)) {
            delete cell_wall.at(i);
            cell_wall.at(i)=NULL;
        }
    }
    id=0;
    belongs_to= NULL;
}
                            
void Cell::RenewCellWall(vector<Wall*>& rhs){
   int temp=cell_wall.size();
   if(temp){
       for(int i=0; i<temp;i++) if(cell_wall.at(i)){ delete cell_wall.at(i);}//clean
       for(int i=0; i<temp;i++) cell_wall.erase(cell_wall.begin()); //clean
   }
   for(int i=0; i<rhs.size();i++){ //rebuild
       Wall* coming = rhs.at(i);
       CurvyWall* my_new_walls= dynamic_cast< CurvyWall*>(coming);
       cell_wall.push_back(new CurvyWall(*my_new_walls));
   }
}
void Cell::StrengthenCellWall(){
    int tempsize=cell_wall.size();
    if(tempsize){
        bool flag=false;
        for(int i=0; i<tempsize;i++){
            if(tempsize==1) break;
             Wall * wall1=cell_wall.at(i);   //dynamic cast
             CurvyWall * curvy_wall1;
             curvy_wall1 = dynamic_cast< CurvyWall*>(wall1);
             Wall * wall2=cell_wall[((i+1)%tempsize)];   //dynamic cast
             CurvyWall * curvy_wall2;
             curvy_wall2 = dynamic_cast< CurvyWall*>(wall2);
            if(!curvy_wall1 && !curvy_wall2){ //straight
                if(wall1->IsContinuousLinear(*wall2)) {
                    flag=true;
                    const Wall * temp=&((*wall1)+(*wall2)); //sum
                    cell_wall.at(i)=temp->Clone(); //replace
                    delete temp;
                    temp=NULL;
                    cell_wall.erase(cell_wall.begin()+((i+1)%tempsize)); //delete next one
                    delete wall2;
                    wall2=NULL;
                    delete wall1;
                    wall1=NULL;
                    tempsize--;
                    i--;
                }
            }
            else if(curvy_wall1 && curvy_wall2){ //both curve
                 if(curvy_wall1->GetCenter() == curvy_wall2->GetCenter() && curvy_wall1->GetRadius()==curvy_wall2->GetRadius()){
                     flag=true;
                      const Wall * temp2=&((*curvy_wall1)+(*curvy_wall2));   //dynamic cast
                      cell_wall.at(i)=temp2->Clone();
                      delete temp2;
                      cell_wall.erase(cell_wall.begin()+((i+1)%tempsize));
                      delete curvy_wall2;
                     curvy_wall2=NULL;
                      delete curvy_wall1;
                      curvy_wall1=NULL;
                      tempsize--;
                      i--;
                 }
            }
        }
    }
}
ostream& operator<<(ostream& os, const Cell& rhs){
    int temp=rhs.cell_wall.size();
    if(temp){
        for(int i=0; i<temp;i++){
            if(i==temp-1 && rhs.cell_wall.at(i)) os<<(rhs.cell_wall.at(i))->GetInitialParticle() ;
            else {
                if(rhs.cell_wall.at(i))
                os<<(rhs.cell_wall.at(i))->GetInitialParticle() <<"-";
            }
        }
    }
    return os;
}
