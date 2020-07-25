#include "Squadratic.h"

Squadratic::Squadratic(int idd, float length) :edge_length(length), MicroOrganism(idd, length) {}
Squadratic::Squadratic(const Squadratic& rhs) :MicroOrganism(rhs.id, rhs.cell_wall){
    edge_length=rhs.edge_length;
    attached_cell=rhs.attached_cell;
    located=rhs.located;
}
Squadratic::~Squadratic(){
    if(cell_wall.size()){ //kendini sil
        for(int i=0; i<cell_wall.size();i++) if(cell_wall.at(i)) {
            delete cell_wall.at(i);
            cell_wall.at(i)=NULL;
        }
    }
    if(children.size()){ //cocuklarini sil
        for(int i=0; i<children.size();i++) if(children.at(i)) {
            delete children.at(i);
            children.at(i)=NULL;
        }
    }
    edge_length=0;
    located=false;
    id=0;
    attached_cell=NULL;
}
void Squadratic::ConnectToCell(Cell* const cell){
    cell->StrengthenCellWall();
   if(cell_wall.size()){ //clean ex micro-wall
        int size=cell_wall.size();
       for(int i=0; i<cell_wall.size();i++) if(cell_wall.at(i)) {
           delete cell_wall.at(i);
           cell_wall.at(i)=NULL;
       }
       for(int i=0; i<size;i++) cell_wall.erase(cell_wall.begin());
   }
   if(cell->GetCellWall().size()){
        for(int i=0; i<cell->GetCellWall().size();i++) if((cell->GetCellWall()).at(i)) {
           cell_wall.push_back(new Wall(*(cell->GetCellWall()).at(i))); //starts at same vertice now
        }
    }
   located=true;
   attached_cell=cell;
}
bool Squadratic::DoesFitInto(const Cell& cell) const{
    if((cell.GetCellWall()).size()){
        Cell *temp = new Cell(cell);
        temp->StrengthenCellWall();
        if((temp->GetCellWall()).size()==4){
            if((temp->GetCellWall()).at(0)->FindAngleBetween(*((temp->GetCellWall()).at(1)))==90 && (temp->GetCellWall()).at(1)->FindAngleBetween(*((temp->GetCellWall()).at(2)))==90 && (temp->GetCellWall()).at(2)->FindAngleBetween(*((temp->GetCellWall()).at(3)))==90 && (temp->GetCellWall()).at(3)->FindAngleBetween(*((temp->GetCellWall()).at(0)))==90){
            if(abs((((temp->GetCellWall()).at(0))->GetLength())-edge_length)<=EPSILON && abs((((temp->GetCellWall()).at(1))->GetLength())-edge_length)<=EPSILON && abs((((temp->GetCellWall()).at(2))->GetLength())-edge_length)<=EPSILON && abs((((temp->GetCellWall()).at(3))->GetLength())-edge_length)<=EPSILON){ //always same lengths
                        delete temp;  temp=NULL;return true;
           }
            }}
    delete temp;
    temp=NULL;
    }
    return false;
}

void Squadratic::React(){
    if(cell_wall.size()==4){ //hucre icine girmisse
        float new_length= edge_length/2;
        vector<Wall*> temp; //new pieces
        vector<Particle*> center_vec; //particles of edge centers
        for(int i=0;i<cell_wall.size();i++){
        float initial_x=(cell_wall.at(i)->GetInitialParticle()).X();
        float initial_y=(cell_wall.at(i)->GetInitialParticle()).Y();
        float final_x=(cell_wall.at(i)->GetFinalParticle()).X();
        float final_y=(cell_wall.at(i)->GetFinalParticle()).Y();
        center_vec.push_back(new Particle((float)(final_x+initial_x)/2,(float)(final_y+initial_y)/2));
        temp.push_back(new Wall((cell_wall.at(i)->GetInitialParticle()),*center_vec.at(i)));
        temp.push_back(new Wall(*center_vec.at(i),(cell_wall.at(i)->GetFinalParticle())));
        }
        const Particle  center((float)((float)(cell_wall.at(0)->GetInitialParticle()).X()+(cell_wall.at(2)->GetInitialParticle()).X())/2,(float)((float)(cell_wall.at(0)->GetInitialParticle()).Y()+(cell_wall.at(2)->GetInitialParticle()).Y())/2);
        vector<Wall*> child1_wall;
        vector<Wall*> child2_wall;
        vector<Wall*> child3_wall;
        vector<Wall*> child4_wall;
        child1_wall.push_back(new Wall (*temp.at(0)));
        child1_wall.push_back(new Wall (*center_vec.at(0),center));
        child1_wall.push_back(new Wall (center,*center_vec.at(3)));
        child1_wall.push_back(new Wall (*temp.at(7)));
       
        child2_wall.push_back(new Wall (*temp.at(1)));
        child2_wall.push_back(new Wall (*temp.at(2)));
        child2_wall.push_back(new Wall (*center_vec.at(1),center));
        child2_wall.push_back(new Wall (center,*center_vec.at(0)));
        
        child3_wall.push_back(new Wall (*temp.at(3)));
        child3_wall.push_back(new Wall (*temp.at(4)));
        child3_wall.push_back(new Wall (*center_vec.at(2),center));
        child3_wall.push_back(new Wall (center,*center_vec.at(1)));
        
        child4_wall.push_back(new Wall (*temp.at(5)));
        child4_wall.push_back(new Wall (*temp.at(6)));
        child4_wall.push_back(new Wall (*center_vec.at(3),center));
        child4_wall.push_back(new Wall (center,*center_vec.at(2)));
        
        children.push_back( new Squadratic(0,child1_wall,new_length,attached_cell));
        children.push_back( new Squadratic(1,child2_wall,new_length,attached_cell));
        children.push_back( new Squadratic(2,child3_wall,new_length,attached_cell));
        children.push_back( new Squadratic(3,child4_wall,new_length,attached_cell));
       
        for(int i=0;i<temp.size();i++) if(temp.at(i)) {
            delete temp.at(i);
            temp.at(i)=NULL;}
        for(int i=0;i<child1_wall.size();i++) if(child1_wall.at(i)) {
        delete child1_wall.at(i);
        child1_wall.at(i)=NULL;}
        for(int i=0;i<child2_wall.size();i++) if(child2_wall.at(i)) {
        delete child2_wall.at(i);
        child2_wall.at(i)=NULL;}
        for(int i=0;i<child3_wall.size();i++) if(child3_wall.at(i)) {
        delete child3_wall.at(i);
        child3_wall.at(i)=NULL;}
        for(int i=0;i<child4_wall.size();i++) if(child4_wall.at(i)) {
        delete child4_wall.at(i);
        child4_wall.at(i)=NULL;}
        for(int i=0;i<center_vec.size();i++) if(center_vec.at(i)) {
        delete center_vec.at(i);
        center_vec.at(i)=NULL;}
    }
}
Squadratic& Squadratic::GetChild(float min_x, float max_x, float min_y, float max_y) const{
    if(!(children.size())) {
        throw NotBornChildException();
        Squadratic *ptr = new Squadratic(0,0);
        return *ptr;
    }
    else{
        for(int i=0;i<children.size();i++){ //her cocugu ve subcocuklarini ara
                float x_min=10000.0;
                float y_min=10000.0;
                float x_max=-10000.0;
                float y_max=-10000.0;
                for(int j=0; j<4;j++) {
                    if(((((children.at(i))->cell_wall).at(j))->GetInitialParticle().X())<x_min)
                        x_min=(((children.at(i))->cell_wall).at(j))->GetInitialParticle().X();
                }
                 for(int j=0; j<4;j++) {
                    if(((((children.at(i))->cell_wall).at(j))->GetInitialParticle().Y())<y_min)
                        y_min=(((children.at(i))->cell_wall).at(j))->GetInitialParticle().Y();
                } for(int j=0; j<4;j++) {
                    if(((((children.at(i))->cell_wall).at(j))->GetInitialParticle().X())>x_max)
                        x_max=(((children.at(i))->cell_wall).at(j))->GetInitialParticle().X();
                }
                 for(int j=0; j<4;j++) {
                    if(((((children.at(i))->cell_wall).at(j))->GetInitialParticle().Y())>y_max)
                        y_max=(((children.at(i))->cell_wall).at(j))->GetInitialParticle().Y();
                }
                if(abs(x_min-min_x)<=EPSILON && abs(y_min-min_y)<=EPSILON && abs(x_max-max_x)<=EPSILON && abs(y_max-max_y)<=EPSILON) return *(children.at(i)); //not the child we look for
               
                else {
                    if(((children.at(i))->children).size()) {
                         Squadratic *ptr = &((children.at(i))->GetChild( min_x,  max_x,  min_y,  max_y));
                        if (ptr->edge_length==0) delete ptr;
                        else return *ptr;
                    } //if children down there, look down recursively
            }
        } //if cannot find
        
        throw NotBornChildException();
        Squadratic *ptr = new Squadratic(0,0);
        return *ptr;
        
    }
}
