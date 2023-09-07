//std::string time_saved= std::to_string(GetSpace().GetSimulationClock());

/**
  * @file <loop-functions/IcraLoopFunc.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @license MIT License
  */

#include "TuttiTmTLoopFunc.h"

/****************************************/
/****************************************/

TuttiTmTLoopFunction::TuttiTmTLoopFunction() {
    m_unClock = 0;
    m_unStopTime = 0;
    m_unStopEdge = 2;
    m_unStopBox = 2;
    m_fObjectiveFunction = 0;

    
}

/****************************************/
/****************************************/

TuttiTmTLoopFunction::TuttiTmTLoopFunction(const TuttiTmTLoopFunction& orig) {
}

/****************************************/
/****************************************/

TuttiTmTLoopFunction::~TuttiTmTLoopFunction() {}

/****************************************/
/****************************************/

void TuttiTmTLoopFunction::Destroy() {

    m_tRobotStates.clear();
    
    //RemoveArena();
    EventLog();
}

/****************************************/
/****************************************/

void TuttiTmTLoopFunction::Init(TConfigurationNode& t_tree) {

    CoreLoopFunctions::Init(t_tree);
    TConfigurationNode cParametersNode;
    try {
      cParametersNode = GetNode(t_tree, "params");
      GetNodeAttributeOrDefault(cParametersNode, "build_arena", m_bBuildArena, (bool) false);
      GetNodeAttributeOrDefault(cParametersNode, "number_edges", m_unNumberEdges, (UInt32) 3);
      GetNodeAttributeOrDefault(cParametersNode, "number_boxes_per_edge", m_unNumberBoxes, (UInt32) 1);
      GetNodeAttributeOrDefault(cParametersNode, "lenght_boxes", m_fLenghtBoxes, (Real) 0.25);
      GetNodeAttributeOrDefault(cParametersNode, "maximization", m_bMaximization, (bool) false);
    } catch(std::exception e) {
    }

    if (m_bBuildArena == true)
    {
        m_fDistributionRadius = GetArenaRadious();
        PositionArena();
    }

    InitRobotStates();

    CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
    CVector2 cBoxPosition;
    UInt32 Blocks=0;
    //Here we save the coordanates for the center of the walls of the tams.
    for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
        CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);
        cBoxPosition.Set(pcBlock->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                        pcBlock->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());
        if (Blocks<num_Tam*3){

            if ((Blocks)%3==0 ){
                Tam_back_x.push_back(cBoxPosition.GetX());
                Tam_back_y.push_back(cBoxPosition.GetY());
            }
            if ((Blocks-1)%3==0 and Blocks>0 ){
                Tam_side1_x.push_back(cBoxPosition.GetX());
                Tam_side1_y.push_back(cBoxPosition.GetY());
            }
            if ((Blocks-2)%3==0 and Blocks>1 ){
                Tam_side2_x.push_back(cBoxPosition.GetX());
                Tam_side2_y.push_back(cBoxPosition.GetY());
            }
        }
        Blocks += 1; 
    }
    activities["0_sec"] = {0,1,6};
    activities["1_con"] = {2,3};
    activities["2_sec"] ={4,5};
    activities["3_con"] ={0,1};

    for(std::map<std::string,std::vector<Real>>::iterator it = activities.begin(); it != activities.end(); ++it) {
    key.push_back(it->first);
    value.push_back(it->second);
    }

    time_t now = time(0);
    file_name=std::to_string(now);

}

/****************************************/
/****************************************/
Real sides (Real s1_x, Real s1_y, Real s2_x, Real s2_y, Real b_x, Real b_y, Real c){
if (s1_x==s2_x){
        //The tam is vertical
        if (s1_x<b_x){
            //Entry of the tam is down
            left=s1_y;
            right=s2_y;
            up=b_x;
            down=b_x-c;
        }
        if (s1_x>b_x){
            //Entry of the tam is up
            left=s1_y;
            right=s2_y;
            up=b_x+c;
            down=b_x;
        }
    }
    if (s1_y==s2_y){
        //The tam is horizontal
        if (s1_y<b_y){
            //Entry of the tam is to the right
            left=b_y;
            right=b_y-c;
            up=s1_x;
            down=s2_x;            
        }
        if (s1_y>b_y){
            //Entry of the tam is to the left
            left=b_y+c;
            right=b_y;
            up=s1_x;
            down=s2_x;      
        }
    }

return left, right, up, down;

}
/****************************************/
void print(std::vector <int> const &a) {
    std::cout<<"vec : ";
   for(int i=0; i < a.size(); i++)
   std::cout<< a.at(i) << ' ';
    std::cout <<";"<<std::endl;

}
/****************************************/
void print2(std::vector <Real> const &a) {
    std::cout<<"vec : ";
   for(int i=0; i < a.size(); i++)
   std::cout<< a.at(i) << ' ';
    std::cout <<";"<<std::endl;
}
/****************************************/

/****************************************/

void TuttiTmTLoopFunction::EventLog() {
    mision="Compuertas/";
    //mision="paralela/";
    //mision="secuencial/";
    std::fstream CreateFile("/home/jazmin/tuttifrutti/log/Tesis/"+mision+file_name+"data.csv");
    CreateFile<<"mision;activity;time;robot"<<std::endl;
    MyFile.open("/home/jazmin/tuttifrutti/log/Tesis/"+mision+file_name+"data.csv", std::ios::app);
    float time_Sim = (GetSpace().GetSimulationClock());
    then_tm.tm_sec += ((GetSpace().GetSimulationClock())/1000);   // add 50 seconds to the time
    double a = time_Sim/10;
    mils=a-floor(a);
    mils = round(mils * 1000.0);
    then_tm.tm_sec += time_Sim/10;
    mktime( &then_tm);      // normalize it
    struct tm tm;
    char buf[255];

    memset(&tm, 0, sizeof(tm));
    strptime(asctime(&then_tm), "%a %b %e %H:%M:%S %Y\n", &tm);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    then_tm = now_tm;
    time_S=buf;
    std::cout<<"buf"<<buf<<std::endl;
    Gates();
    //InitBoxStates_Sec();
    //InitBoxStates_Par();

    MyFile.close();
}

void TuttiTmTLoopFunction::Reset() {
    CoreLoopFunctions::Reset();
    m_unClock = 0;
    m_unStopEdge = 2;
    m_unStopBox = 2;
    m_unStopTime = 0;
    m_fObjectiveFunction = 0;
    m_tRobotStates.clear();
    InitRobotStates();
    Gates();
}

/****************************************/
/****************************************/

void TuttiTmTLoopFunction::PostStep() {
    EventLog();
}

/****************************************/
/****************************************/

void TuttiTmTLoopFunction::PostExperiment() {
    if (m_bMaximization == true){
        LOG << -m_fObjectiveFunction << std::endl;
    }
    else {
        LOG << m_fObjectiveFunction << std::endl;
    }
}

/****************************************/
/****************************************/

Real TuttiTmTLoopFunction::GetObjectiveFunction() {
    if (m_bMaximization == true){
        return -m_fObjectiveFunction;
    }
    else {
        return m_fObjectiveFunction;
    }
}

/****************************************/
/****************************************/

void TuttiTmTLoopFunction::ArenaControl() {

    if (m_unClock == m_unStopTime)
        m_pcArena->SetBoxColor(m_unStopBox,m_unStopEdge,CColor::GREEN);
    return;
}


/*******************************************/
void TuttiTmTLoopFunction::Gates(){
    for (int i = 0; i < key.size(); i++) {
        if (key[i].find(std::to_string(flag_a))!= std::string::npos){
            if(key[i].find("sec")!= std::string::npos){
                flag_a+=sec(value[i]);
            }
            if(key[i].find("con")!= std::string::npos){
                flag_a+=con(value[i]);
            }
            if((key[i].find("con")== std::string::npos) and (key[i].find("sec")== std::string::npos)) {
                std::cout<<"The activiy "<<flag_a<<"is not set to be secuential or concurrent"<<std::endl;
            }
        }
    }

}

/*******************************************/
Real TuttiTmTLoopFunction::timing(){

    float time_Sim = (GetSpace().GetSimulationClock());

    //then_tm.tm_sec += ((GetSpace().GetSimulationClock())/1000);   // add seconds to the time
    //double a = time_Sim/10;
    //mils=a-floor(a);
    //mils = round(mils * 1000.0);
    then_tm.tm_sec += time_Sim/10;
    mktime( &then_tm);      // normalize it
    struct tm tm;
    char buf[255];

    memset(&tm, 0, sizeof(tm));
    strptime(asctime(&then_tm), "%a %b %e %H:%M:%S %Y\n", &tm);

    //std::cout<<"tm: "<<asctime(&tm)<<std::endl;

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    //std::cout<<"buf: "<<buf<<std::endl;

    then_tm = now_tm;
    time_S=buf;

    return 0;
} 

/*******************************************/

Real TuttiTmTLoopFunction::con(std::vector <Real> const &a){

    int check;
    check= 0;
    // Iterate the vector of each secuential activity 
    for(int i=0; i <=a.size(); i++){
        if (i<a.size() and ((Tam_color.at(a.at(i))==0) or (Tam_color.at(a.at(i))==3))){
        //if (i<a.size()){
            Boxes(a.at(i), 1);
            Tam_color.at(a.at(i))=1;
        }}
        flag_b=0;
    for(int i=0; i <a.size(); i++){
        flag_b+=robots_con(a.at(i));
    }
    if (flag_b==a.size()){
        cont+=1;
        if (cont==50){
            for(int i=0; i <a.size(); i++){
            if (Tam_color.at(a.at(i))==2){
                Tam_color.at(a.at(i))=3;
                Boxes(a.at(i),3);
            }
            }
            cont=0;
            check= 1;
        }
        flag_b=0;   
    }
    return check;
}

/*******************************************/
/*******************************************/

Real TuttiTmTLoopFunction::robots_con(Real Tm){
    //this simulates when a robot enter a TAM (t=1), r is going to be the robot 
    CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
    CVector2 cEpuckPosition(0,0);
    Real y_l=0.1,x_l=0.10, rob=0, lim=0.000005, enter, check=0;

    for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it) {
        CEPuckEntity* pcEpuck = any_cast<CEPuckEntity*>(it->second);
        cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

        for(int i=0; i < Tam_back_x.size(); i++){        
        left, right, up, down= sides (Tam_side1_x.at(i), Tam_side1_y.at(i), Tam_side2_x.at(i), Tam_side2_y.at(i), Tam_back_x.at(i), Tam_back_y.at(i), 0.10);
        if (right<cEpuckPosition.GetY() and cEpuckPosition.GetY()<=left and down <cEpuckPosition.GetX() and cEpuckPosition.GetX()<up){
            enter=i;
            if (enter==Tm){
                if( Tam_color.at(Tm)==1){
                timing();
                MyFile<<";"<<"Task"<<Tm<<";"<<GetSpace().GetSimulationClock()<<";"<<rob<<std::endl;

                Tam_color.at(Tm)=2;
                Boxes(Tm,2);}
                check = 1;
            }
        }
        }
        m_tRobotStates[pcEpuck].cLastPosition = m_tRobotStates[pcEpuck].cPosition;
        m_tRobotStates[pcEpuck].cPosition = cEpuckPosition;
        rob+=1;
    }
    return check;
}

/*******************************************/

Real TuttiTmTLoopFunction::sec(std::vector <Real> const &a){

    int check;
    // Iterate the vector of each secuential activity 
    for(int i=0; i <=a.size(); i++){
        if (i<a.size()){
                if (flag_b==i){
                    if ( Tam_color.at(a.at(i))==0){
                    Boxes(a.at(i), 1);
                    Tam_color.at(a.at(i))=1;
                    print(Tam_color);
                    }
                    flag_b+=robots_sec(a.at(i));
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
/*******************************************/
/*******************************************/


Real TuttiTmTLoopFunction::robots_sec(Real Tm){
    //this simulates when a robot enter a TAM (t=1), r is going to be the robot 
    CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
    CVector2 cEpuckPosition(0,0);
    Real y_l=0.1,x_l=0.10, rob=0, lim=0.000005, enter, check=0;

    for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it) {
        CEPuckEntity* pcEpuck = any_cast<CEPuckEntity*>(it->second);
        cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

        for(int i=0; i < Tam_back_x.size(); i++){        
        left, right, up, down= sides (Tam_side1_x.at(i), Tam_side1_y.at(i), Tam_side2_x.at(i), Tam_side2_y.at(i), Tam_back_x.at(i), Tam_back_y.at(i), 0.10);
        if (right<cEpuckPosition.GetY() and cEpuckPosition.GetY()<=left and down <cEpuckPosition.GetX() and cEpuckPosition.GetX()<up){
            enter=i;
            if (enter==Tm){
                if( Tam_color.at(Tm)==1){
                Boxes(enter,2);

                Tam_color.at(Tm)=2;}
                cont+=1;
                if (cont==50 and Tam_color.at(Tm)==2){
                    timing();
                    MyFile<<";"<<"Task"<<Tm<<";"<<GetSpace().GetSimulationClock()<<";"<<rob<<std::endl;

                    Tam_color.at(Tm)=3;
                    Boxes(enter,3);
                    cont=0;
                    check = 1;
                }
            }
        }
        }
        m_tRobotStates[pcEpuck].cLastPosition = m_tRobotStates[pcEpuck].cPosition;
        m_tRobotStates[pcEpuck].cPosition = cEpuckPosition;
        rob+=1;
    }
    return check;
}

/*******************************************/
/*******************************************/

argos::CColor TuttiTmTLoopFunction::GetFloorColor(const argos::CVector2& c_position_on_plane) {
    
    for(int i=0; i < Tam_back_x.size(); i++){        
    left, right, up, down= sides (Tam_side1_x.at(i), Tam_side1_y.at(i), Tam_side2_x.at(i), Tam_side2_y.at(i), Tam_back_x.at(i), Tam_back_y.at(i), 0.07);
    if (right<c_position_on_plane.GetY() and c_position_on_plane.GetY()<=left and down <c_position_on_plane.GetX() and c_position_on_plane.GetX()<up){
        return CColor::WHITE;
    }
    }
    return CColor::GRAY50;

}

/****************************************/
/****************************************/

void TuttiTmTLoopFunction::InitRobotStates() {

    CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
    CVector2 cEpuckPosition(0,0);
    int x;
    for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it) {
        CEPuckEntity* pcEpuck = any_cast<CEPuckEntity*>(it->second);
        cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

        m_tRobotStates[pcEpuck].cLastPosition = cEpuckPosition;
        m_tRobotStates[pcEpuck].cPosition = cEpuckPosition;
        m_tRobotStates[pcEpuck].unItem = 0;
        
    }
}

/****************************************/
void TuttiTmTLoopFunction::Boxes(Real boxa, Real color){
    
    CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
    CVector2 cBoxPosition(0,0);
    UInt32 box = 0;
    for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
        CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);

        if (box==(boxa*3) and color ==0){
            std::cout<<"Apagado "<<"Tam: "<<boxa<<std::endl;
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::GREEN);
        }
        if (box==(boxa*3) and color ==1 ){
            std::cout<<"Disponible "<<"Tam: "<<boxa<<std::endl;
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
        }
        if (box==(boxa*3) and color ==2 ){
            std::cout<<"Ocupado "<<"Tam: "<<boxa<<std::endl;
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::PURPLE);
        }
        if (box==(boxa*3) and color ==3){
            std::cout<<"No-disponible "<<"Tam: "<<boxa<<std::endl;
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
        }
        if (box==(boxa*3) and color ==4){
            std::cout<<"Waiting"<<"Tam: "<<boxa<<std::endl;
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
        }

        box+=1;
    }

}

/****************************************/

CVector3 TuttiTmTLoopFunction::GetRandomPosition() {
  Real temp;
  Real a = m_pcRng->Uniform(CRange<Real>(0.0f, 1.0f));
  Real b = m_pcRng->Uniform(CRange<Real>(0.0f, 1.0f));
  Real c = m_pcRng->Uniform(CRange<Real>(-1.0f, 1.0f));
  Real d = m_pcRng->Uniform(CRange<Real>(-1.0f, 1.0f));
  // If b < a, swap them
  if (b < a) {
    temp = a;
    a = b;
    b = temp;
  }
  m_fDistributionRadius = 0.4;
  Real fPosX = (c * m_fDistributionRadius / 2) + m_fDistributionRadius * cos(2 * -CRadians::PI_OVER_TWO .GetValue() * (a/b));
  Real fPosY = -0.20 + (d * m_fDistributionRadius / 2) + m_fDistributionRadius * sin(2 * -CRadians::PI_OVER_TWO.GetValue() * (a/b));

  return CVector3(fPosX, fPosY, 0);
}

/****************************************/
/****************************************/

UInt32 TuttiTmTLoopFunction::GetRandomTime(UInt32 unMin, UInt32 unMax) {
  UInt32 unStopAt = m_pcRng->Uniform(CRange<UInt32>(unMin, unMax));
  return unStopAt;

}

/****************************************/
/****************************************/

void TuttiTmTLoopFunction::PositionArena() {
  CArenaEntity* pcArena;
  /*
    pcArena = new CArenaEntity("arena",
                               CVector3(0,0,0),
                               CQuaternion().FromEulerAngles(CRadians::ZERO,CRadians::ZERO,CRadians::ZERO), // TODO
                               CVector3(0.01,m_fLenghtBoxes,0.1),
                               "leds",
                               m_unNumberBoxes,
                               m_unNumberEdges,
                               0.017f,
                               1.0f);   */ // arena with 12 leds per block

  pcArena = new CArenaEntity("arena",
                             CVector3(0,0,0),
                             CQuaternion().FromEulerAngles(CRadians::ZERO,CRadians::ZERO,CRadians::ZERO), // TODO
                             CVector3(0.01,m_fLenghtBoxes,0.1),
                             "leds",
                             m_unNumberBoxes,
                             m_unNumberEdges,
                             0.125f,
                             1.0f);

  AddEntity(*pcArena);
  m_pcArena = pcArena;
}

/****************************************/
/****************************************/

void TuttiTmTLoopFunction::RemoveArena() {
    std::ostringstream id;
    id << "arena";
    RemoveEntity(id.str().c_str());
}

/****************************************/
/****************************************/

Real TuttiTmTLoopFunction::GetArenaRadious() {

    Real fRadious;
    //fRadious =  (m_fLenghtBoxes*m_unNumberBoxes) / (2 * Tan(CRadians::PI / m_unNumberEdges));
    //fRadious = fRadious - 0.10; // Avoids to place robots close the walls.
    fRadious = fRadious - 0.65; // Reduced cluster at the begining
    return fRadious;

    
}

/****************************************/
/****************************************/

bool TuttiTmTLoopFunction::IsEven(UInt32 unNumber) {
    bool even;
    if((unNumber%2)==0)
       even = true;
    else
       even = false;

    return even;
}

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(TuttiTmTLoopFunction, "tutti_tmt_loop_function");
