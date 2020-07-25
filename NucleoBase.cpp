#include "NucleoBase.h"

NucleoBase::NucleoBase(string new_rna, NucleoBase* old_sequence){
    nucleobase=new_rna[0];
    next=NULL;
    prev=NULL;
    size=new_rna.size();
    NucleoBase* my_old_sequence=this;
    for(int i=1;i<size;i++){
      NucleoBase* new_node2 = new NucleoBase(new_rna[i],my_old_sequence,NULL);
        new_node2->size=1;
      if(my_old_sequence) new_node2->prev->next=new_node2;
      my_old_sequence=new_node2;
    }
}
NucleoBase::NucleoBase(const NucleoBase& rhs){
       const NucleoBase* temp =&rhs;
       nucleobase=temp->nucleobase;
       size=rhs.size;
       next=NULL;
       prev=NULL;
       temp=temp->next;
       NucleoBase* my_old_sequence=this;
       for(int i=1;i<rhs.size;i++){
         NucleoBase* new_node2 = new NucleoBase(temp->nucleobase,my_old_sequence,NULL);
            new_node2->size=1;
         if(my_old_sequence) new_node2->prev->next=new_node2;
         my_old_sequence=new_node2;
        temp=temp->next;
       }
}

NucleoBase::~NucleoBase(){
    NucleoBase* current=this;
    if(current->size>1){
    while(current->next) current=current->next;
    while(current){
    NucleoBase* temp=current->prev;
        if(temp){
            delete current;
            temp->next=NULL;
        }
        else { next=NULL;
        prev=NULL;
        size=0;
            break;
        }
    
    current=temp;
    }
   
    }
    else{
        next=NULL;
        prev=NULL;
        size=0;
    }
    size=0;
}

NucleoBase* NucleoBase::GetLast(){
    NucleoBase* current=this;
    if(current){
        while(current->next!=NULL) current=current->next; //en ucun bi gerisine git
        return current;
    }
    else return NULL;
}
ostream& operator<<(ostream& os, const NucleoBase& rhs){
    if(rhs.size){
    const NucleoBase* current=&rhs;
    while(current){
        os << current->nucleobase;
        current=current->next;
        }}
    return os;
}
