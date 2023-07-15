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

    m_tRobotStates.clear();

    InitRobotStates();
}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::PostStep() {
    EventLog();
    m_unClock = GetSpace().GetSimulationClock();
    
    ScoreControl();
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

    if (m_unClock <= m_unStopTime)
        m_fObjectiveFunction += GetMoveScore();
    else
        m_fObjectiveFunction += GetStopScore();
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
    }

    return unScore;
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
/****************************************/

argos::CColor TuttiTmLoopFunction::GetFloorColor(const argos::CVector2& c_position_on_plane) {
    //tam1
    if (-0.05< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= 0.05 
    and 0.68< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= 0.75
    ){
        return CColor::WHITE;
    }
//tam2
    if (-0.25< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= -0.15 

    and 0.68< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= 0.75
    ){
        return CColor::WHITE;
    }
    
    //else if (c_position_on_plane.GetX() >= 0.60){
    //    return CColor::BLACK;
    //}
//tam2
    if (-0.45< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= -0.35 

    and 0.7< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= 0.75
    ){
        return CColor::WHITE;
    }
//tam4
    if (-0.65< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= -0.55 

    and 0.7< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= 0.75
    ){
        return CColor::WHITE;
    }
//tam5
    if (0.15< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= 0.25 

    and 0.68< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= 0.75
    ){
        return CColor::WHITE;
    }

//tam6
    if (0.35< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= 0.45 

    and 0.68< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= 0.75
    ){
        return CColor::WHITE;
    }

    

//tam7
    //if (0.55< c_position_on_plane.GetY() and c_position_on_plane.GetY() <= 0.65 

    //and 0.68< c_position_on_plane.GetX() and c_position_on_plane.GetX() <= 0.75)
    //{        return CColor::WHITE;    }

if (0.45< c_position_on_plane.GetX()){

            return CColor::BLACK;}

    return CColor::GRAY50;
}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::UpdateRobotPositions() {
    CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
    CVector2 cEpuckPosition(0,0);
    for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it) {
        CEPuckEntity* pcEpuck = any_cast<CEPuckEntity*>(it->second);
        cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                           pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

        m_tRobotStates[pcEpuck].cLastPosition = m_tRobotStates[pcEpuck].cPosition;
        m_tRobotStates[pcEpuck].cPosition = cEpuckPosition;
    }
}

/****************************************/
/****************************************/

void TuttiTmLoopFunction::InitRobotStates() {

    CSpace::TMapPerType& tEpuckMap = GetSpace().GetEntitiesByType("epuck");
    CVector2 cEpuckPosition(0,0);
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