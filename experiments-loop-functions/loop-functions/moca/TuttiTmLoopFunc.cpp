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

    CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
    CVector2 cBoxPosition;
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
            if (unBlocksID ==18){Tam7.SetX(cBoxPosition.GetX());}
            if (unBlocksID ==19){Tam7.SetY(cBoxPosition.GetY());}
            if (unBlocksID ==21){Tam8.SetX(cBoxPosition.GetX());}
            if (unBlocksID ==22){Tam8.SetY(cBoxPosition.GetY());}

        unBlocksID += 1; 
    }
    time_t now = time(0);
    file_name=std::to_string(now);

    

}

/****************************************/
/****************************************/
void TuttiTmLoopFunction::EventLog() {
    std::fstream CreateFile("/home/jazmin/tuttifrutti/log/ideales_no_repetidos_1/"+file_name+"data.csv");
    CreateFile<<"case_id;activity;time"<<std::endl;
    MyFile.open("/home/jazmin/tuttifrutti/log/ideales_no_repetidos_1/"+file_name+"data.csv", std::ios::app);
    time_S = std::to_string(GetSpace().GetSimulationClock());
    InitBoxStates();
    MyFile.close();
}

void TuttiTmLoopFunction::Reset() {
    CoreLoopFunctions::Reset();
    m_unClock = 0;
    m_unStopEdge = 2;
    m_unStopBox = 2;
    m_unStopTime = 0;
    m_fObjectiveFunction = 0;
    m_tRobotStates.clear();
    InitRobotStates();
    InitBoxStates();
}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::PostStep() {
    EventLog();
    //m_unClock = GetSpace().GetSimulationClock();
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

   // UpdateRobotPositions();
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


/****************************************/
/*********************************/


Real TuttiTmLoopFunction::GetTamControl() {
CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
CVector2 cEpuckPosition(0,0);
Real y_l=0.1,x_l=0.10, rob=0, lim=0.000005;

    for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it) {
        CEPuckEntity* pcEpuck = any_cast<CEPuckEntity*>(it->second);
        cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

        m_tRobotStates[pcEpuck].cLastPosition = m_tRobotStates[pcEpuck].cPosition;
        m_tRobotStates[pcEpuck].cPosition = cEpuckPosition;

        robot=std::to_string(rob);
        robot.erase ( robot.find_last_not_of('0') + 1, std::string::npos );
        robot.erase ( robot.find_last_not_of(',') + 1, std::string::npos );
        robot.erase ( robot.find_last_not_of('.') + 1, std::string::npos );

        //tam1 
        if (Tam1.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam1.GetY()
        and (Tam1.GetX())-x_l< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam1.GetX())
        {  
            robotT1=rob;
            if(tam1==0){
                actionT1="T1_enter";
                std::cout<<robot<<"T1_enter"<<std::endl;
                MyFile<<robot<<";"<<"T1_enter"<<";"<<time_S<<std::endl;
                tam1=1;
                }
            timer1+=1;
            if(timer1==50 and tam1==1){
                    timer1=0;
                    actionT1="T1_task1";
                    MyFile<<robot<<";"<<actionT1<<";"<<time_S<<std::endl;
                    std::cout<<robot<<actionT1<<std::endl;
                    tam1=2;
            }
        }
        if (rob==robotT1 and (actionT1=="T1_enter" or actionT1== "T1_task1" or actionT1== "T1_task2") and Tam1.GetX()-x_l> cEpuckPosition.GetX()){
            actionT1="T1_out";
            std::cout<<robotT1<<actionT1<<std::endl;
            MyFile<<robot<<";"<<actionT1<<";"<<time_S<<std::endl;
        }
        
        //tam2
        if (Tam2.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam2.GetY()
        and (Tam2.GetX())-x_l< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam2.GetX())
        {  
            robotT2=rob;
            if(tam2==0){
                actionT2="T2_enter";
                std::cout<<robot<<"T2_enter"<<std::endl;
                MyFile<<robot<<";"<<"T2_enter"<<";"<<time_S<<std::endl;
                tam2=1;
                }
            timer2+=1;
            if(timer2==50 and tam2==1){
                    timer2=0;
                    actionT2="T2_task2";
                    MyFile<<robot<<";"<<actionT2<<";"<<time_S<<std::endl;
                    std::cout<<robot<<actionT2<<std::endl;
                    tam2=2;
            }
        }
        if (rob==robotT2 and (actionT2=="T2_enter" or actionT2== "T2_task2" or actionT2== "T2_task1") and Tam2.GetX()-x_l> cEpuckPosition.GetX()){
            actionT2="T2_out";
            std::cout<<robotT2<<actionT2<<std::endl;
            MyFile<<robot<<";"<<actionT2<<";"<<time_S<<std::endl;
        }
        if (tam1==2 and tam2==2){
                tam1=3;
                tam2=3;
                timer12=0;
        }
        if ((actionT1=="T1_task2" or actionT2=="T2_task2") and tam1==3 and tam2==3){
                timer12+=1;

                if(timer12==100 and tam1==3 and tam2==3){
                    timer12=0;
                    actionT1="T1_task3";
                    actionT2="T2_task3";
                    MyFile<<robotT1<<";"<<actionT1<<";"<<time_S<<std::endl;
                    MyFile<<robotT2<<";"<<actionT2<<";"<<time_S<<std::endl;
                    std::cout<<robotT1<<actionT1<<std::endl;
                    std::cout<<robotT2<<actionT2<<std::endl;
                    tam1=4;
                    tam2=4 ;
                }
                
        }


        //tam3
        if (Tam3.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam3.GetY()
        and (Tam3.GetX()-x_l)< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam3.GetX())
        {  
            robotT3=rob;
            if(tam3==0){
                actionT3="T3_enter";
                std::cout<<robot<<"T3_enter"<<std::endl;
                MyFile<<robot<<";"<<"T3_enter"<<";"<<time_S<<std::endl;
                tam3=1;
                }
            timer3+=1;
            if(timer3==50 and tam3==1){
                    timer3=0;
                    actionT3="T3_task1";
                    MyFile<<robot<<";"<<actionT3<<";"<<time_S<<std::endl;
                    std::cout<<robot<<actionT3<<std::endl;
                    tam3=2;
            }
        }
        if (rob==robotT3 and (actionT3=="T3_enter" or actionT3== "T3_task1" or actionT3=="T3_task2") and Tam3.GetX()-x_l> cEpuckPosition.GetX()){
            actionT3="T3_out";
            std::cout<<robotT3<<actionT3<<std::endl;
            MyFile<<robot<<";"<<actionT3<<";"<<time_S<<std::endl;
        }

    //tam4
        if (Tam4.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam4.GetY()
        and (Tam4.GetX())-x_l< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam4.GetX())
        {  
            robotT4=rob;
            if(tam4==0){
                actionT4="T4_enter";
                std::cout<<robot<<"T4_enter"<<std::endl;
                MyFile<<robot<<";"<<"T4_enter"<<";"<<time_S<<std::endl;
                tam4=1;
                }
            timer4+=1;
            if(timer4==50 and tam4==1){
                    timer4=0;
                    actionT4="T4_task2";
                    MyFile<<robot<<";"<<actionT4<<";"<<time_S<<std::endl;
                    std::cout<<robot<<actionT4<<std::endl;
                    tam4=2;
            }
        }
        if (rob==robotT4 and (actionT4=="T4_enter" or actionT4== "T4_task1" or actionT4=="T4_task2") and Tam4.GetX()-x_l> cEpuckPosition.GetX()){
            actionT4="T4_out";
            std::cout<<robotT4<<actionT4<<std::endl;
            MyFile<<robot<<";"<<actionT4<<";"<<time_S<<std::endl;
        }
        //tam3 and tam4
        if (tam3==2 and tam4==2){
                tam3=3;
                tam4=3;
                timer9=0;
        }
        if ((actionT3=="T3_task2" or actionT4=="T4_task2") and tam3==3 and tam4==3){
                timer9+=1;

                if(timer9==100 and tam3==3 and tam4==3){
                    timer9=0;
                    actionT3="T3_task3";
                    actionT4="T4_task3";
                    MyFile<<robotT3<<";"<<actionT3<<";"<<time_S<<std::endl;
                    MyFile<<robotT4<<";"<<actionT4<<";"<<time_S<<std::endl;
                    std::cout<<robotT3<<actionT3<<std::endl;
                    std::cout<<robotT4<<actionT4<<std::endl;
                    tam3=4;
                    tam4=4;
                }
                
        }

        //tam5
        if (Tam5.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam5.GetY()
        and (Tam5.GetX())< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam5.GetX()+x_l)
        {  
            robotT5=rob;
            if(tam5==0){
                actionT5="T5_enter";
                std::cout<<robot<<"T5_enter"<<std::endl;
                MyFile<<robot<<";"<<"T5_enter"<<";"<<time_S<<std::endl;
                tam5=1;
                }
            timer5+=1;
            if(timer5==50 and tam5==1){
                    timer5=0;
                    actionT5="T5_task1";
                    MyFile<<robot<<";"<<actionT5<<";"<<time_S<<std::endl;
                    std::cout<<robot<<actionT5<<std::endl;
                    tam5=2;
            }
        }
        if (rob==robotT5 and (actionT5=="T5_enter" or actionT5== "T5_task1" or actionT5=="T5_task2") and  (Tam5.GetX()-(x_l))>= cEpuckPosition.GetX()){
            actionT5="T5_out";
            std::cout<<robotT5<<actionT5<<std::endl;
            MyFile<<robot<<";"<<actionT5<<";"<<time_S<<std::endl;
        }
    
        //tam6
        if (Tam6.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam6.GetY()
        and (Tam6.GetX())< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam6.GetX() +x_l)
        {  
            robotT6=rob;
            if(tam6==0){
                actionT6="T6_enter";
                std::cout<<robot<<"T6_enter"<<std::endl;
                MyFile<<robot<<";"<<"T6_enter"<<";"<<time_S<<std::endl;
                tam6=1;
                }
            timer6+=1;
            if(timer6==50 and tam6==1){
                    timer6=0;
                    actionT6="T6_task2";
                    MyFile<<robot<<";"<<actionT6<<";"<<time_S<<std::endl;
                    std::cout<<robot<<actionT6<<std::endl;
                    tam6=2;
            }
        }
        if (rob==robotT6 and (actionT6=="T6_enter" or actionT6== "T6_task1" or actionT6=="T6_task2") and (Tam6.GetX()-(x_l))>= cEpuckPosition.GetX()){
            actionT6="T6_out";
            std::cout<<robotT6<<actionT6<<std::endl;
            MyFile<<robot<<";"<<actionT6<<";"<<time_S<<std::endl;
        }
        //tam5 and tam6
        
        if (tam5==2 and tam6==2){
                tam5=3;
                tam6=3;
                timer10=0;
        }
        if ((actionT5=="T5_task2" or actionT6=="T6_task2") and tam5==3 and tam6==3){
                timer10+=1;

                if(timer10==100 and tam5==3 and tam6==3){
                    timer10=0;
                    actionT5="T5_task3";
                    actionT6="T6_task3";
                    MyFile<<robotT5<<";"<<actionT5<<";"<<time_S<<std::endl;
                    MyFile<<robotT6<<";"<<actionT6<<";"<<time_S<<std::endl;
                    std::cout<<robotT5<<actionT5<<std::endl;
                    std::cout<<robotT6<<actionT6<<std::endl;
                    tam5=4;
                    tam6=4 ;
                }
                
        }


        //tam7
        if (Tam7.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam7.GetY()
        and (Tam7.GetX())< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam7.GetX()+x_l)
        {  
            robotT7=rob;
            if(tam7==0){
                actionT7="T7_enter";
                std::cout<<robot<<"T7_enter"<<std::endl;
                MyFile<<robot<<";"<<"T7_enter"<<";"<<time_S<<std::endl;
                tam7=1;
                }
            timer7+=1;
            if(timer7==50 and tam7==1){
                    timer7=0;
                    actionT7="T7_task1";
                    MyFile<<robot<<";"<<actionT7<<";"<<time_S<<std::endl;
                    std::cout<<robot<<actionT7<<std::endl;
                    tam7=2;
            }
        }

        if (rob==robotT7 and (actionT7=="T7_enter" or actionT7== "T7_task1" or actionT7=="T7_task2") and  (Tam7.GetX()-(x_l))>= cEpuckPosition.GetX()){
            actionT7="T7_out";
            std::cout<<robotT7<<actionT7<<std::endl;
            MyFile<<robot<<";"<<actionT7<<";"<<time_S<<std::endl;
        }
        //tam8

        if (Tam8.GetY()-y_l< cEpuckPosition.GetY() and cEpuckPosition.GetY() <= Tam8.GetY()
            and (Tam8.GetX())< cEpuckPosition.GetX() and cEpuckPosition.GetX() <= Tam8.GetX()+x_l)
        {  
            robotT8=rob;
            if(tam8==0){
                actionT8="T8_enter";
                std::cout<<robot<<"T8_enter"<<std::endl;
                MyFile<<robot<<";"<<"T8_enter"<<";"<<time_S<<std::endl;
                tam8=1;
                }
            timer8+=1;
            if(timer8==50 and tam8==1){
                    timer8=0;
                    actionT8="T8_task2";
                    MyFile<<robot<<";"<<actionT8<<";"<<time_S<<std::endl;
                    std::cout<<robot<<actionT8<<std::endl;
                    tam8=2;
            }
        }
        if (rob==robotT8 and (actionT8=="T8_enter" or actionT8== "T8_task1" or actionT8=="T8_task2") and (Tam8.GetX()-(x_l))>= cEpuckPosition.GetX()){
            actionT8="T8_out";
            std::cout<<robotT8<<actionT8<<std::endl;
            MyFile<<robot<<";"<<actionT8<<";"<<time_S<<std::endl;
        }
        //tam7 and tam8
        
        if (tam7==2 and tam8==2){
                tam7=3;
                tam8=3;
                timer11=0;
        }
        if ((actionT7=="T7_task2" or actionT8=="T8_task2") and tam7==3 and tam8==3){
                timer11+=1;

                if(timer11==100 and tam7==3 and tam8==3){
                    
                    actionT7="T7_task3";
                    actionT8="T8_task3";
                    MyFile<<robotT7<<";"<<actionT7<<";"<<time_S<<std::endl;
                    MyFile<<robotT8<<";"<<actionT8<<";"<<time_S<<std::endl;
                    std::cout<<robotT7<<actionT7<<std::endl;
                    std::cout<<robotT8<<actionT8<<std::endl; 
                    timer11=0;
                }
        }

        if (actionT7=="T7_task3" and tam7==3 and tam8==3){
                    timer13+=1;
                    if (timer13==10){
                        tam7=4;
                        tam8=4;
                        actionT7="T7_task4";
                        actionT8="T8_task4";

                        MyFile<<robotT7<<";"<<actionT7<<";"<<time_S<<std::endl;
                        MyFile<<robotT8<<";"<<actionT8<<";"<<time_S<<std::endl;
                        std::cout<<robotT7<<actionT7<<std::endl;
                        std::cout<<robotT8<<actionT8<<std::endl;
                        timer13=0;

                    }


        }  

    
        rob+=1;
    }
    return tam2;
}



/****************************************/
/****************************************/


argos::CColor TuttiTmLoopFunction::GetFloorColor(const argos::CVector2& c_position_on_plane) {
    
        Real y_l=0.1, x_l=0.07;

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
    if (Tam4.GetY()-y_l< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam4.GetY()
    and (Tam4.GetX())-x_l< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam4.GetX()
    ){ return CColor::WHITE;    }
    
//tam5
    if (Tam5.GetY()-y_l< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam5.GetY()
    and (Tam5.GetX())< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam5.GetX()+x_l
    ){  return CColor::WHITE;}


//tam6
    if (Tam6.GetY()-y_l< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam6.GetY()
    and (Tam6.GetX())< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam6.GetX()+x_l
    ){  return CColor::WHITE;}


//tam7
    if (Tam7.GetY()-y_l< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam7.GetY()
    and (Tam7.GetX())< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam7.GetX()+x_l
    ){  return CColor::WHITE;}


//tam8
    if (Tam8.GetY()-y_l< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= Tam8.GetY()
    and (Tam8.GetX())< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= Tam8.GetX()+x_l
    ){  return CColor::WHITE;}

//else
    //if (0.45< c_position_on_plane.GetX()){return CColor::BLACK;}

    return CColor::GRAY50;

}

/****************************************/
/****************************************/

Real TuttiTmLoopFunction::UpdateRobotPositions() {
    CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
    CVector2 cEpuckPosition(0,0);
    for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it) {
        CEPuckEntity* pcEpuck = any_cast<CEPuckEntity*>(it->second);
        cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());


        m_tRobotStates[pcEpuck].cLastPosition = m_tRobotStates[pcEpuck].cPosition;

        m_tRobotStates[pcEpuck].cPosition = cEpuckPosition;
        

        if (abs((m_tRobotStates[pcEpuck].cPosition.GetX())- m_tRobotStates[pcEpuck].cLastPosition.GetX())<=0.000005 and
        abs((m_tRobotStates[pcEpuck].cPosition.GetY())- m_tRobotStates[pcEpuck].cLastPosition.GetY())<=0.000005){
            tam+=1;
        }


    }
    return tam;
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
/**Secuencial
void TuttiTmLoopFunction::InitBoxStates() {
        GetTamControl();
    
    CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
    CVector2 cBoxPosition(0,0);
    UInt32 unBlocksID1 = 0;
    for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
        CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);
            //std::cout<<"tam1:"<<tam1<<"tam2:"<<tam2<<std::endl;
            
            if (unBlocksID1 ==0 and tam1==1 and tam5==0 and tam6==0) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if (unBlocksID1 ==3 and tam2==1 and tam5==0 and tam6==0) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }

            if ((unBlocksID1 == 6) and tam1==1 and tam2==1 and tam3==0) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
            }

            if ((unBlocksID1 == 9) and tam1==1 and tam2==1 and tam3==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
            }


            if (unBlocksID1 == 6 and tam3==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
                
            }
            if (unBlocksID1 == 9 and tam4==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA); 

            }  
            if ((unBlocksID1 == 12) and tam3==1 and tam4==1 and tam5==0) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
                
            }
            if ((unBlocksID1 == 15) and tam3==1 and tam4==1 and tam5==1 and tam6==0) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
                
            }
            if (unBlocksID1 == 12 and tam5==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if (unBlocksID1 == 15 and tam6==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if ((unBlocksID1 == 18) and tam5==1 and tam6==1 and tam7==0) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
            }
            if ((unBlocksID1 == 21) and tam6==1 and tam7==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
            }
            if (unBlocksID1 == 18 and tam7==1) {
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);}

            if (unBlocksID1 == 21 and tam8==1) {
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);}


            if ((unBlocksID1 == 0 ) and tam3==1 ) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            }
            if ((unBlocksID1 == 3 ) and tam4==1 ) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            } 
            if ((unBlocksID1 == 6 ) and tam5==1 ) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            } 
            if ((unBlocksID1 == 9 ) and tam6==1 ) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            } 
            if ((unBlocksID1 == 12 ) and tam7==1 ) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            } 
            if ((unBlocksID1 == 15 ) and tam8==1 ) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            } 

            
        unBlocksID1+=1;
       // std::cout<<"bloque1:"<<unBlocksID1<<std::endl;
    }
}*/
/* Secuencial -Paralela*/

void TuttiTmLoopFunction::InitBoxStates() {
        GetTamControl();
    
    CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
    CVector2 cBoxPosition(0,0);
    UInt32 unBlocksID1 = 0;
    for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
        CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);
            //std::cout<<"tam1:"<<tam1<<"tam2:"<<tam2<<std::endl;
            if (unBlocksID1 ==0 and tam1==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLACK);
            }
            if (unBlocksID1 ==3 and tam2==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLACK);
            }
            if (unBlocksID1 ==0 and tam1==2) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
            }
            if (unBlocksID1 ==3 and tam2==2) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
            }
            if ((unBlocksID1 ==0 or unBlocksID1 ==3) and tam1==3 and tam2==3) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if ((unBlocksID1 ==0 or unBlocksID1 ==3) and tam1==4 and tam2==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::WHITE);
            }
            if ((unBlocksID1 ==6 or unBlocksID1 ==9) and tam1==4 and tam2==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
            }
            //segundo grupo
            if (unBlocksID1 ==6 and tam3==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLACK);
            }
            if (unBlocksID1 ==9 and tam4==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLACK);
            }
            if (unBlocksID1 ==6 and tam3==2) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
            }
            if (unBlocksID1 ==9 and tam4==2) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
            }
            if ((unBlocksID1 ==6 or unBlocksID1 ==9) and tam3==3 and tam4==3) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if ((unBlocksID1 ==6 or unBlocksID1 ==9) and tam3==4 and tam4==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::WHITE);
            }
            if ((unBlocksID1 ==12 or unBlocksID1 ==15) and tam3==4 and tam4==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
            }
            //tercergrupo
	        if (unBlocksID1 ==12 and tam5==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLACK);
            }
            if (unBlocksID1 ==15 and tam6==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLACK);
            }
            if (unBlocksID1 ==12 and tam5==2) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
            }
            if (unBlocksID1 ==15 and tam6==2) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
            }
            if ((unBlocksID1 ==12 or unBlocksID1 ==15) and tam5==3 and tam6==3) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if ((unBlocksID1 ==12 or unBlocksID1 ==15) and tam5==4 and tam6==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::WHITE);
            }
            if ((unBlocksID1 ==18 or unBlocksID1 ==21) and tam5==4 and tam6==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLUE);
            }
            //cuartogrupo

            if (unBlocksID1 ==18 and tam7==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLACK);
            }
            if (unBlocksID1 ==21 and tam8==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::BLACK);
            }
            if (unBlocksID1 ==18 and tam7==2) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
            }
            if (unBlocksID1 ==21 and tam8==2) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);
            }
            if ((unBlocksID1 ==18 or unBlocksID1 ==21) and tam7==3 and tam8==3) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if ((unBlocksID1 ==18 or unBlocksID1 ==21) and tam7==4 and tam8==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::WHITE);
            }

            if ((unBlocksID1 == 0 or unBlocksID1 == 3) and tam3==4 and tam4==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            }
            if ((unBlocksID1 == 6 or unBlocksID1 == 9) and tam5==4 and tam6==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            }
            if ((unBlocksID1 == 12 or unBlocksID1 == 15 or unBlocksID1 == 18 or unBlocksID1 == 21) and tam7==4 and tam8==4) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::RED);
            }

        unBlocksID1+=1;
       // std::cout<<"bloque1:"<<unBlocksID1<<std::endl;
    }
}
/* Paralela

void TuttiTmLoopFunction::InitBoxStates() {
        GetTamControl();
    
    CSpace::TMapPerType& tBlocksMap = GetSpace().GetEntitiesByType("box");
    CVector2 cBoxPosition(0,0);
    UInt32 unBlocksID1 = 0;
    for (CSpace::TMapPerType::iterator it = tBlocksMap.begin(); it != tBlocksMap.end(); ++it) {
        CBoxEntity* pcBlock = any_cast<CBoxEntity*>(it->second);
            //std::cout<<"tam1:"<<tam1<<"tam2:"<<tam2<<std::endl;
            if (unBlocksID1 ==0 and tam1==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if (unBlocksID1 ==3 and tam2==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if (unBlocksID1 == 6 and tam3==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);   
            }
            if (unBlocksID1 == 9 and tam4==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA); 
            }  
            if (unBlocksID1 == 12 and tam5==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            if (unBlocksID1 == 15 and tam6==1) {
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);
            }
            
            if (unBlocksID1 == 18 and tam7==1) {
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);}

            if (unBlocksID1 == 21 and tam8==1) {
            pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::MAGENTA);}

            if (tam1==1 and tam2==1 and tam3==1 and tam4==1 and tam5==1 and tam6==1 and tam7==1 and tam8==1){
                pcBlock->GetLEDEquippedEntity().SetAllLEDsColors(CColor::CYAN);}

            
        
        unBlocksID1+=1;
       // std::cout<<"bloque1:"<<unBlocksID1<<std::endl;
    }
}*/


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
