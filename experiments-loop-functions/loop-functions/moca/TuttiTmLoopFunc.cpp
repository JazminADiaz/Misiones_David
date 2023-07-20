//std::string time_saved= std::to_string(GetSpace().GetSimulationClock());

/**
  * @file <loop-functions/IcraLoopFunc.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @license MIT License
  */

#include "TuttiTmLoopFunc.h"

/****************************************/
/****************************************/

TuttiTmLoopFunction::TuttiTmLoopFunction() {
    m_unClock = 0;
    m_unStopTime = 0;
    m_unStopEdge = 2;
    m_unStopBox = 2;
    m_fObjectiveFunction = 0;
    tam = 0;
    
}

/****************************************/
/****************************************/

TuttiTmLoopFunction::TuttiTmLoopFunction(const TuttiTmLoopFunction& orig) {
}

/****************************************/
/****************************************/

TuttiTmLoopFunction::~TuttiTmLoopFunction() {}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::Destroy() {

    m_tRobotStates.clear();
    //RemoveArena();
    EventLog();
}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::Init(TConfigurationNode& t_tree) {

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
    //m_pcArena->SetArenaColor(CColor::BLACK);

    //if (m_unClock == m_unStopTime) {
        CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
        UInt32 unBlocksID = 0;
        for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
            CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);
            //std::cout << unBlocksID << std::endl;
            //pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            //if (unBlocksID == 0) {
              //  pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            //}
            unBlocksID += 1;
        }
    //}

}

/****************************************/
/****************************************/
void TuttiTmLoopFunction::EventLog() {
    std::fstream CreateFile("/home/jazmin/Documents/Ubuntu_personal/TESIS/intento2023/data.csv");
    CreateFile<<"id,activity,time"<<std::endl;
    MyFile.open("/home/jazmin/Documents/Ubuntu_personal/TESIS/intento2023/data.csv", std::ios::app);
    time_S = std::to_string(GetSpace().GetSimulationClock());

    c=0;
    TRobotStateMap::iterator it;
    for (it = m_tRobotStates.begin(); it != m_tRobotStates.end(); ++it) {
        MyFile<<c<<","<<"nose"<<","<<time_S<<std::endl;
        c=c+1;
    }

    MyFile.close();
}

void TuttiTmLoopFunction::Reset() {
    CoreLoopFunctions::Reset();

    //m_pcArena->SetArenaColor(CColor::BLACK);
    m_unClock = 0;
    m_unStopEdge = 2;
    m_unStopBox = 2;
    m_unStopTime = 0;
    m_fObjectiveFunction = 0;
    c=0;
    tam=0;

    m_tRobotStates.clear();

    InitRobotStates();
}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::PostStep() {
    EventLog();
    m_unClock = GetSpace().GetSimulationClock();
    
    ScoreControl();
    TamControl();
    //ArenaControl(); 
    

}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::PostExperiment() {
    if (m_bMaximization == true){
        LOG << -m_fObjectiveFunction << std::endl;
    }
    else {
        LOG << m_fObjectiveFunction << std::endl;
    }
}

/****************************************/
/****************************************/

Real TuttiTmLoopFunction::GetObjectiveFunction() {
    if (m_bMaximization == true){
        return -m_fObjectiveFunction;
    }
    else {
        return m_fObjectiveFunction;
    }
}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::ArenaControl() {

    if (m_unClock == m_unStopTime)
        m_pcArena->SetBoxColor(m_unStopBox,m_unStopEdge,CColor::GREEN);

    return;
}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::ScoreControl(){

    if (m_unClock == 1) {
        m_unStopTime = GetRandomTime(400, 601);
        m_unStopEdge = GetRandomTime(1, 9);
        m_unStopBox = GetRandomTime(1, 4);
    }


}

/****************************************/
/****************************************/

Real TuttiTmLoopFunction::GetStopScore() {

    UpdateRobotPositions();
    Real unScore = 0;
    TRobotStateMap::iterator it;
    for (it = m_tRobotStates.begin(); it != m_tRobotStates.end(); ++it) {
        Real d = (it->second.cPosition - it->second.cLastPosition).Length();
        if (d > 0.0005)
            unScore+=1;
    return unScore;
}
}




/****************************************/
/****************************************/

Real TuttiTmLoopFunction::GetMoveScore() {

    UpdateRobotPositions();

    Real unScore = 0;
    TRobotStateMap::iterator it;
    for (it = m_tRobotStates.begin(); it != m_tRobotStates.end(); ++it) {
        Real d = (it->second.cPosition - it->second.cLastPosition).Length();
        if (d <= 0.0005)
            unScore+=1;
    }

    return unScore;
}

Real TuttiTmLoopFunction::TamControl() {
    CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
    CVector2 cBoxPosition(0,0), Tam1(0,0), Tam2(0,0), Tam3(0,0), Tam4(0,0), Tam5(0,0), Tam6(0,0);
    Real y_l=0.11,x_l=0.08, rob=0;
    UInt32 unBlocksID = 0;
    std::string action, robot;

    for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
        CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);
        cBoxPosition.Set(pcBlock->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                        pcBlock->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

            if (unBlocksID ==0){Tam1.SetX(cBoxPosition.GetX());}
            if (unBlocksID ==1){Tam1.SetY(cBoxPosition.GetY());}
            if (unBlocksID ==3){Tam2.SetX(cBoxPosition.GetX());}
            if (unBlocksID ==4){Tam2.SetY(cBoxPosition.GetY());}
            if (unBlocksID ==6){Tam3.SetX(cBoxPosition.GetX());}
            if (unBlocksID ==7){Tam3.SetY(cBoxPosition.GetY());}
            if (unBlocksID ==9){Tam4.SetX(cBoxPosition.GetX());}
            if (unBlocksID ==10){Tam4.SetY(cBoxPosition.GetY());}
            if (unBlocksID ==12){Tam5.SetX(cBoxPosition.GetX());}
            if (unBlocksID ==13){Tam5.SetY(cBoxPosition.GetY());}
            if (unBlocksID ==15){Tam6.SetX(cBoxPosition.GetX());}
            if (unBlocksID ==16){Tam6.SetY(cBoxPosition.GetY());}
        unBlocksID += 1; 
    }

    CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
    CVector2 cEpuckPosition(0,0);
    UInt32  tam1=0, tam2=0, tam3=0, tam4=0, tam5=0, tam6=0;
 for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it) {
        CEPuckEntity* pcEpuck = any_cast<CEPuckEntity*>(it->second);
        cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

        m_tRobotStates[pcEpuck].cLastPosition = m_tRobotStates[pcEpuck].cPosition;

        m_tRobotStates[pcEpuck].cPosition = cEpuckPosition;

        robot=std::to_string(rob);
//tam1 
    if (Tam1.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam1.GetY()
    and (Tam1.GetX())-x_l< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam1.GetX()
    ){ 
        action=";T1_enter";
        action=robot+action;
        if (abs((m_tRobotStates[pcEpuck].cPosition.GetX())- m_tRobotStates[pcEpuck].cLastPosition.GetX())<=0.000005 and
         abs((m_tRobotStates[pcEpuck].cPosition.GetY())- m_tRobotStates[pcEpuck].cLastPosition.GetY())<=0.000005 and tam1==0){
            action=";T1_stop";
            action=robot+action;
            tam1=1;
        }
        

    }
//tam2
    if (Tam2.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam2.GetY()
    and (Tam2.GetX()-x_l)< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam2.GetX()
    ){  action=";T2_enter";
        action=robot+action;
        if (abs((m_tRobotStates[pcEpuck].cPosition.GetX())- m_tRobotStates[pcEpuck].cLastPosition.GetX())<=0.000005 and
         abs((m_tRobotStates[pcEpuck].cPosition.GetY())- m_tRobotStates[pcEpuck].cLastPosition.GetY())<=0.000005 and tam2==0){
            action=";T2_stop";
            action=robot+action;
            tam2=1;
        }
             }

//tam3
    if (Tam3.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam3.GetY()
    and (Tam3.GetX()-x_l)< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam3.GetX()
    ){  action=";T3_enter";
        action=robot+action;
        if (abs((m_tRobotStates[pcEpuck].cPosition.GetX())- m_tRobotStates[pcEpuck].cLastPosition.GetX())<=0.000005 and
         abs((m_tRobotStates[pcEpuck].cPosition.GetY())- m_tRobotStates[pcEpuck].cLastPosition.GetY())<=0.000005 and tam3==0){
            action=";T3_stop";
            action=robot+action;
            tam3=1;
        }   
             }
//tam4
    if (Tam4.GetY()< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam4.GetY()+y_l
    and (Tam4.GetX())-x_l< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam4.GetX()
    ){  action=";T4_enter";
        action=robot+action;
        if (abs((m_tRobotStates[pcEpuck].cPosition.GetX())- m_tRobotStates[pcEpuck].cLastPosition.GetX())<=0.000005 and
         abs((m_tRobotStates[pcEpuck].cPosition.GetY())- m_tRobotStates[pcEpuck].cLastPosition.GetY())<=0.000005 and tam4==0){
            action=";T4_stop";
            action=robot+action;
            tam4=1; 
        }
            }
//tam5
    if (Tam5.GetY()< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam5.GetY()+y_l
    and (Tam5.GetX()-x_l)< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam5.GetX()
    ){  
        action=";T5_enter";
        action=robot+action;
        if (abs((m_tRobotStates[pcEpuck].cPosition.GetX())- m_tRobotStates[pcEpuck].cLastPosition.GetX())<=0.000005 and
         abs((m_tRobotStates[pcEpuck].cPosition.GetY())- m_tRobotStates[pcEpuck].cLastPosition.GetY())<=0.000005 and tam5==0){
            action=";T5_stop";
            action=robot+action;
            tam5=1;
        }
           }
//tam6
    if (Tam6.GetY()< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam6.GetY()+y_l
    and (Tam6.GetX()-x_l)< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam6.GetX()
    ){  action=";T5_enter";
        action=robot+action;
        if (abs((m_tRobotStates[pcEpuck].cPosition.GetX())- m_tRobotStates[pcEpuck].cLastPosition.GetX())<=0.000005 and
         abs((m_tRobotStates[pcEpuck].cPosition.GetY())- m_tRobotStates[pcEpuck].cLastPosition.GetY())<=0.000005 and tam6==0){
            action=";T6_stop";
            action=robot+action;
            tam6=1;
        }
          }

    rob +=1;

    }
//        CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
        UInt32 unBlocksID1 = 0;
        for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
            CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);

//            std::cout<<"tam:"<<tam1<<"bloque"<<unBlocksID<<std::endl;
            
            if (unBlocksID1 ==0 and tam1==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }

            if (unBlocksID1 ==3 and tam2==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }

            if ((unBlocksID1 == 6 or unBlocksID1 == 9) and tam1==1 and tam2==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
            }


            if (unBlocksID1 == 6 and tam3==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
                
            }
            if (unBlocksID1 == 9 and tam4==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);   
            }  
            if ((unBlocksID1 == 12 or unBlocksID1 == 15) and tam3==1 and tam4==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
                
            }
            if ((unBlocksID1 == 12 or unBlocksID1 == 15) and tam5==1 and tam6==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }

            unBlocksID1 += 1;    
        }
}


/****************************************/
/****************************************/

///CONFIGURE FLOOR COLOR ACORDING TO TAM LOCATIONS 

argos::CColor TuttiTmLoopFunction::GetFloorColor(const argos::CVector2& c_position_on_plane) {
    

        CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
        CVector2 cBoxPosition(0,0), Tam1(0,0), Tam2(0,0), Tam3(0,0), Tam4(0,0), Tam5(0,0), Tam6(0,0);
        Real y_l=0.1, x_l=0.07;

        UInt32 unBlocksID = 0;
        for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
            CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);
            cBoxPosition.Set(pcBlock->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcBlock->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

                if (unBlocksID ==0){Tam1.SetX(cBoxPosition.GetX());}
                if (unBlocksID ==1){Tam1.SetY(cBoxPosition.GetY());}
                if (unBlocksID ==3){Tam2.SetX(cBoxPosition.GetX());}
                if (unBlocksID ==4){Tam2.SetY(cBoxPosition.GetY());}
                if (unBlocksID ==6){Tam3.SetX(cBoxPosition.GetX());}
                if (unBlocksID ==7){Tam3.SetY(cBoxPosition.GetY());}
                if (unBlocksID ==9){Tam4.SetX(cBoxPosition.GetX());}
                if (unBlocksID ==10){Tam4.SetY(cBoxPosition.GetY());}
                if (unBlocksID ==12){Tam5.SetX(cBoxPosition.GetX());}
                if (unBlocksID ==13){Tam5.SetY(cBoxPosition.GetY());}
                if (unBlocksID ==15){Tam6.SetX(cBoxPosition.GetX());}
                if (unBlocksID ==16){Tam6.SetY(cBoxPosition.GetY());}

            unBlocksID += 1; 
        }
//tam1 
    if (Tam1.GetY()-y_l< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam1.GetY()
    and (Tam1.GetX())-x_l< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam1.GetX()
    ){          return CColor::WHITE;    }
//tam2
    if (Tam2.GetY()-y_l< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam2.GetY()
    and (Tam2.GetX()-x_l)< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam2.GetX()
    ){  return CColor::WHITE;    }

//tam3
    if (Tam3.GetY()-y_l< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam3.GetY()
    and (Tam3.GetX()-x_l)< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam3.GetX()
    ){   return CColor::WHITE;    }
//tam4
    if (Tam4.GetY()< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam4.GetY()+y_l
    and (Tam4.GetX())-x_l< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam4.GetX()
    ){ return CColor::WHITE;    }
//tam5
    if (Tam5.GetY()< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam5.GetY()+y_l
    and (Tam5.GetX()-x_l)< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam5.GetX()
    ){  return CColor::WHITE;}
//tam6
    if (Tam6.GetY()< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam6.GetY()+y_l
    and (Tam6.GetX()-x_l)< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam6.GetX()
    ){  return CColor::WHITE;}
//else
    if (0.45< c_position_on_plane.GetX()){return CColor::BLACK;}

    return CColor::GRAY50;
}
//END FLOOR

/****************************************/
/****************************************/

//
Real TuttiTmLoopFunction::UpdateRobotPositions() {
    CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
    CVector2 cEpuckPosition(0,0);
    


    for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it) {
        CEPuckEntity* pcEpuck = any_cast<CEPuckEntity*>(it->second);
        cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());
        //std::cout<<"antesX:"<<(m_tRobotStates[pcEpuck].cLastPosition.GetX())<<" despuesX: "<< m_tRobotStates[pcEpuck].cPosition.GetX()<<std::endl;
        //std::cout<<"antesY:"<<(m_tRobotStates[pcEpuck].cLastPosition.GetY())<<" despuesY: "<< m_tRobotStates[pcEpuck].cPosition.GetY()<<std::endl;


        m_tRobotStates[pcEpuck].cLastPosition = m_tRobotStates[pcEpuck].cPosition;

        m_tRobotStates[pcEpuck].cPosition = cEpuckPosition;

    }
    
;
}



/****************************************/
/****************************************/

void TuttiTmLoopFunction::InitRobotStates() {

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
/****************************************/

CVector3 TuttiTmLoopFunction::GetRandomPosition() {
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

UInt32 TuttiTmLoopFunction::GetRandomTime(UInt32 unMin, UInt32 unMax) {
  UInt32 unStopAt = m_pcRng->Uniform(CRange<UInt32>(unMin, unMax));
  return unStopAt;

}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::PositionArena() {
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

void TuttiTmLoopFunction::RemoveArena() {
    std::ostringstream id;
    id << "arena";
    RemoveEntity(id.str().c_str());
}

/****************************************/
/****************************************/

Real TuttiTmLoopFunction::GetArenaRadious() {

    Real fRadious;
    //fRadious =  (m_fLenghtBoxes*m_unNumberBoxes) / (2 * Tan(CRadians::PI / m_unNumberEdges));
    //fRadious = fRadious - 0.10; // Avoids to place robots close the walls.
    fRadious = fRadious - 0.65; // Reduced cluster at the begining
    return fRadious;

    
}

/****************************************/
/****************************************/

bool TuttiTmLoopFunction::IsEven(UInt32 unNumber) {
    bool even;
    if((unNumber%2)==0)
       even = true;
    else
       even = false;

    return even;
}

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(TuttiTmLoopFunction, "tutti_tm_loop_function");