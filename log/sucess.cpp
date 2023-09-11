#include <cstdlib>
#include <iostream>




bool yesOrNo() {
    srand((unsigned)time(0)); 
    float probabilityOfYes=1;
    return rand()%100 <= (probabilityOfYes * 100);
}

int main() {
    bool prob=yesOrNo();
    if (prob==1){
    std::cout<<"respuesta"<<prob;
    }
}