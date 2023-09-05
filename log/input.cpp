//the headers map, string and iostream are used to be able to make use of map function, cin, cout and strings
#include <iostream>
#include <map>
#include <string>
#include <vector>
int Tam=6; //number of Tams
int T_n=2; // number of Tam's in each activity
int A_n=4; // numer of activitys
int flag_a=0; // Checks for all activity groups
int flag_b=0; // Checks for each activity of the secuential groups
int flag_c=0; // Checks for each activity of the concurrent groups
int cont=0;
int r=5;
int t=0;
int boxa=0;

std::vector<int> Tam_color(Tam, 0); // Indicates the color displaying in each TAM is use to register any change on the tam

void print(std::vector <int> const &a) {
    std::cout<<"printing given vector : ";
   for(int i=0; i < a.size(); i++)
   std::cout<< a.at(i) << ' ';
    std::cout <<";"<<std::endl;

}
int boxes(int box, int color){
    if (color ==0 and boxa==(box*3)){
        std::cout<<"Apagado"<<std::endl;
    }
    if (color ==1 and boxa==(box*3)){
        std::cout<<"Encendido"<<std::endl;
    }
    if (color ==2 and boxa==(box*3)){
        std::cout<<"Ocupado"<<std::endl;
    }
    if (color ==3 and boxa==(box*3)){
        std::cout<<"No-disponible"<<std::endl;
    }
    return 0;
}

int robots(int Tm){
    //this simulates when a robot enter a TAM (t=1), r is going to be the robot 

    if (t==Tm){
        if( Tam_color.at(Tm)==1){
        Tam_color.at(Tm)=2;
        boxes(t,2);}
        cont+=1;
        if (cont==50 and Tam_color.at(Tm)==2){

            Tam_color.at(Tm)=3;
            boxes(t,3);
            cont=0;
            t=1;
            boxa=3;
            return 1;
        }
        else{
        return 0;

        }

        //print(Tam_color);

    }
}


int sec(std::vector <int> const &a) {
    int check;
    // Iterate the vector of each secuential activity 
    for(int i=0; i <=a.size(); i++){
        if (i<a.size()){
                //std::cout<< a.at(i)<<' ';
                if (flag_b==i){
                    if ( Tam_color.at(a.at(i))==0){
                    std::cout<<"primer filtro"<<std::endl;
                    boxes(a.at(i), 1);
                    Tam_color.at(a.at(i))=1;
                    print(Tam_color);

                    }

                    flag_b+=robots(a.at(i));
                    //std::cout<<"flag_b"<<flag_b<<std::endl;


                }
            check= 0;

        }
        if (flag_b==a.size()){

            check= 1;
            flag_b=0;
        }
        
    }
    return check;
}

int con(std::vector <int> const &a) {

    int check;
    // Iterate the vector of each secuential activity 
    for(int i=0; i <=a.size(); i++){
        if (i<a.size()){
                //std::cout<< a.at(i)<<' ';
                if ( Tam_color.at(a.at(i))==0){
                std::cout<<"primer filtro con"<<std::endl;
                boxes(a.at(i), 1);
                Tam_color.at(a.at(i))=1;
                print(Tam_color);
                }

                flag_b+=robots(a.at(i));
                //std::cout<<"flag_b"<<flag_b<<std::endl;


                
            check= 0;

        }
        if (flag_b==a.size()){

            check= 1;
            flag_b=0;
        }
        
    }
    return check;
}


//main method is called
int main()
{
//a map called activities is created which stores keys of type strings which indicate the order and the nature of the activity
//(secuencial or concurrent) and corresponding vector of the TAM's each activity will ocupy
std::map <std::string, std::vector<int> > activities;   
//the elements are added to the created map
activities["0_sec"] = {0,1};
activities["1_con"] = {2,3};
activities["2_sec"] ={4,5};
activities["3_con"] ={0,1};
//We store the keys of each activity into a list (key) and each vector into a matrix (value) so we can further on manipulate them

std::vector<std::string> key;
std::vector<std::vector<int> > value;
for(std::map<std::string,std::vector<int>>::iterator it = activities.begin(); it != activities.end(); ++it) {

  key.push_back(it->first);
  value.push_back(it->second);
  //std::cout << "Key: " << it->first << std::endl;
  //print( it->second);
  //std::cout << "Value: " << it->second << std::endl;
}
//std::cout<<"vector_size:"<<value.size()<<"vector[0]: "<<value[0][0];

//Iterate the list of activities to check if they are secuential or concurrent

for (int timer=0; timer<=1000; timer++){

for (int i = 0; i < key.size(); i++) {
    if (key[i].find(std::to_string(flag_a))!= std::string::npos){
        if(key[i].find("sec")!= std::string::npos){
            flag_a+=sec(value[i]);
            std::cout<<"flag_a"<<flag_a<<std::endl;
            //std::cout << "Element " << key[i] << " flag_a: "<<flag_a<< " nature sec "<<std::endl;
        }
        if(key[i].find("con")!= std::string::npos){
//            std::cout<<"sigue algo con";
            //std::cout << "Element " << key[i] << " flag_a: "<<flag_a<< " nature con "<<std::endl;
            flag_a+=con(value[i]);


        }
        if((key[i].find("con")== std::string::npos) and (key[i].find("sec")== std::string::npos)) {
            std::cout<<"The activiy "<<flag_a<<"is not set to be secuential or concurrent"<<std::endl;
        }
    }
}

}

std::cout<<" # of activ: "<<activities.size();
int c=2;
//std::cout<<" second element: "<< c: activities;

return 0;
}

    //g++ time2.cpp -o time2
    // ./time2
