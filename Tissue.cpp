#include "Tissue.h"

Tissue::Tissue(): cell_count(0) {ptr=NULL;}
Tissue::Tissue(float a, float b, float c, float d){
    float* ptr= new float[4];
    ptr[0]=a;
    ptr[1]=b;
    ptr[2]=c;
    ptr[3]=d;
    cell_count=0;
}
Tissue::Tissue(const Tissue& rhs){
    ptr=rhs.ptr;
    cell_count=rhs.cell_count;
    for(int i=0; i<rhs.cell_count; i++)  cells.push_back(rhs.cells.at(i));
}
Tissue::~Tissue(){
    if(ptr) delete [] ptr;
    ptr=NULL;
    for(int i=0; i<cell_count; i++){ if(cells[i]) {delete cells.at(i);
        cells.at(i)=NULL;}}
    cell_count=0;
}
float* Tissue::GetCoordinates() {return ptr;}
void Tissue::AddCell(Cell& rhs){
    cell_count++;
    Cell *temp= &rhs;
    cells.push_back(temp);
}
void Tissue::RemoveCell(Cell& rhs){
    for(int i=0; i<cell_count; i++) {
        if(cells.at(i)){
        if(rhs.GetCellID()==((cells.at(i))->GetCellID()))
        {   cell_count--;
            delete cells.at(i);
            cells.at(i)=NULL;
            cells.erase(cells.begin()+i);
            break;
        }}
    }
}

const Cell& Tissue::GetCell(int a) const{
    for(int i=0; i<cell_count; i++) { if((cells.at(i))->GetCellID()==a) return *(cells.at(i));}
    throw DeadCellException();
}
void Tissue::Interact(const vector<MicroOrganism*>& rhs){
    if(cells.size()){
        for(int j=0; j<rhs.size(); j++){
            for(int k=0; k<cell_count; k++){
                if(rhs.at(j)->DoesFitInto(*(cells.at(k)))) {
                    Cell* const mycell= cells.at(k);
                    rhs.at(j)->ConnectToCell(mycell); //bind the microorganism
                    if(mycell==NULL) {
                        cells.erase(cells.begin()+k);}
                    break;
                }
                else continue;
            }
        }
    }
}

//void Tissue::CreatePartitions(const vector<MicroOrganism*>& rhs){;}
//void Tissue::TreatByPlasma(Tissue rhs){;}
