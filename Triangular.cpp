#include "Triangular.h"

Triangular::Triangular(int id, const vector<Wall*> &edges, const NucleoBase& rnaa) :MicroOrganism(id, edges)
{
     RNA= new NucleoBase(rnaa); //deep copy
}
Triangular::~Triangular(){
    if(cell_wall.size()){
           for(int i=0; i<cell_wall.size();i++) if(cell_wall.at(i)) {
               delete cell_wall.at(i);
               cell_wall.at(i)=NULL;
           }
    }
    id=0;
    located=false;
    attached_cell=NULL;
    if(RNA){
        delete RNA; //first nucleobase node destroys its own chain
        RNA=NULL;}
}
void Triangular::ConnectToCell(Cell* const cell){
    cell->StrengthenCellWall();
    
    if(cell_wall.size()){ //clean ex micro-wall
        int temp=cell_wall.size();
        for(int i=0; i<cell_wall.size();i++) if(cell_wall.at(i)) {
            delete cell_wall.at(i);
            cell_wall.at(i)=NULL;
        }
        for(int i=0; i<temp;i++) cell_wall.erase(cell_wall.begin());
        
    }
    if(cell->GetCellWall().size()){
        for(int i=0; i<cell->GetCellWall().size();i++){
            Wall *nw= ((cell->GetCellWall()).at(i))->Clone();
            cell_wall.push_back(nw);} //starts at same vertice now
     located=true;
     attached_cell=cell;
    }
}
bool Triangular::DoesFitInto(const Cell& cell) const{
        if((cell.GetCellWall()).size()){ //argument is not empty
            Cell *temp = new Cell(cell);
            temp->StrengthenCellWall();
            if(temp->GetCellWall().size()==3){ //we need 3-edged cell
                for(int i=0; i<this->cell_wall.size();i++){ //as soon as one angle and lengths matches then check rest
                    if(abs((((temp->GetCellWall()).at(0))->GetLength())-cell_wall.at(i%3)->GetLength())<=EPSILON && abs((((temp->GetCellWall()).at(1))->GetLength())-cell_wall.at((i+1)%3)->GetLength())<=EPSILON && abs((((temp->GetCellWall()).at(2))->GetLength())-cell_wall.at((i+2)%3)->GetLength())<=EPSILON) {delete temp;  temp=NULL;return true;}
                       else if(abs((((temp->GetCellWall()).at(0))->GetLength())-cell_wall.at(i%3)->GetLength())<=EPSILON && abs((((temp->GetCellWall()).at(1))->GetLength())-cell_wall.at((i+2)%3)->GetLength())<=EPSILON && abs((((temp->GetCellWall()) .at(2))->GetLength())-cell_wall.at((i+1)%3)->GetLength())<=EPSILON) {delete temp;  temp=NULL;return true;}
                   }
                 }
        delete temp;
        temp=NULL;
        }
        return false;
}
void Triangular::React(){
    if(this->cell_wall.size()){ //if located
        attached_cell->GetTissue()->RemoveCell(*attached_cell); //remove the cell from tissue
        attached_cell=NULL;
        located=false;
    }
}
const NucleoBase& Triangular::GetRNA() const{
    if(RNA) return *RNA;
}
void Triangular::Mutate(Triangular& rhs){
    NucleoBase *rna1= new NucleoBase(*RNA); //deep copy
   NucleoBase *rna2= new NucleoBase(*(rhs.RNA)); //deep copy
    NucleoBase *temp1=rna1; //start pointers
    NucleoBase *temp2=rna2;
    NucleoBase *head1=rna1; //start pointers
    NucleoBase *head2=rna2;
    NucleoBase *temp3=rna1; //end pointers
    NucleoBase *temp4=rna2;
    NucleoBase *end1;  //marking pointer
    NucleoBase *end2;
    while(temp3->next && temp4->next){  //go to end
                  temp3=temp3->next;
                  temp4=temp4->next;
    }
    while(temp3->prev && temp4->prev){  //come towards back
        if(temp3->nucleobase==temp4->nucleobase){
                  temp3=temp3->prev;
                  temp4=temp4->prev;
        }
        else break;
    }
    end1=temp3->next; //record the tail's starting point
    end2=temp4->next;
    while(temp1->next && temp2->next){
        if(temp1->nucleobase==temp2->nucleobase){  //pass the matching nucleobases
                temp1=temp1->next;
                temp2=temp2->next;
        }
        else break;
    }
    while(temp1 && temp2){
            if(temp1!=end1 && temp2!=end2){
                if((temp1->nucleobase=='A' && temp2->nucleobase=='U') || (temp1->nucleobase=='U' && temp2->nucleobase=='A') || (temp1->nucleobase=='G' && temp2->nucleobase=='S') ||(temp1->nucleobase=='S' && temp2->nucleobase=='G')) {
                    NucleoBase *mine_rna=temp2; //i stole her node
                    temp1->prev->next=mine_rna;
                    temp1->next->prev=mine_rna;
                    NucleoBase *left=temp2->prev;
                    NucleoBase *right=temp2->next;
                    mine_rna->prev=temp1->prev; //i connected it with my prev and next
                    mine_rna->next=temp1->next;
                    NucleoBase *her_rna=temp1; //she stole my node
                    her_rna->prev=left; //she connectod it with her own prev and next
                    her_rna->next=right;
                    left->next=her_rna;
                    right->prev=her_rna;
                    temp1=mine_rna;
                    temp2=her_rna;
                }
                else{ //delete non-matching bases
                    NucleoBase *tobedeleted1=temp1;
                    NucleoBase *tobedeleted2=temp2;
                    if (temp1->prev) temp1->prev->next=tobedeleted1->next;
                    if (temp1->next) tobedeleted1->next->prev=tobedeleted1->prev;
                    if (temp2->prev) temp2->prev->next=tobedeleted2->next;
                    if (temp2->next) tobedeleted2->next->prev=tobedeleted2->prev;
                    tobedeleted1->next=NULL;
                    tobedeleted2->next=NULL;
                    temp1=tobedeleted1->prev; //one step back before deletion
                    temp2=tobedeleted2->prev;
                   
                    delete tobedeleted1;
                    delete tobedeleted2;
                    tobedeleted1=NULL;
                    tobedeleted2=NULL;
                    (head1->size)--;
                    (head2->size)--;
                }
                temp1=temp1->next;
                temp2=temp2->next;
            }
            else  break; //we arrived tails' starting points
        }
    
       delete RNA;
       NucleoBase *rnaa=rna1;
       RNA=new NucleoBase(*rnaa);
       delete rhs.RNA;
       NucleoBase *naa=rna2;
       rhs.RNA=new NucleoBase(*naa);
    delete rna1;
    delete rna2;
}

   
