/**
  * @file <loop-functions/example/PwLoopFunc.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef TUTTI_TM_LOOP_FUNC
#define TUTTI_TM_LOOP_FUNC

#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/e-puck/simulator/epuck_entity.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <argos3/plugins/robots/arena/simulator/arena_entity.h>
#include "../../src/CoreLoopFunctions.h"
#include <ctime>
using namespace argos;
std::fstream MyFile;


class TuttiTmLoopFunction: public CoreLoopFunctions {
  public:
    TuttiTmLoopFunction();
    TuttiTmLoopFunction(const TuttiTmLoopFunction& orig);
    virtual ~TuttiTmLoopFunction();

    virtual void Destroy();

    virtual argos::CColor GetFloorColor(const argos::CVector2& c_position_on_plane);
    virtual void PostExperiment();
    virtual void PostStep();
    virtual void Reset();
    virtual void Init(TConfigurationNode& t_tree);

    Real GetObjectiveFunction();

    CVector3 GetRandomPosition();
    UInt32 GetRandomTime(UInt32 unMin, UInt32 unMax);

    void ArenaControl();

    void InitRobotStates();

    void ScoreControl();
    void EventLog();
    Real GetStopScore();  
    Real GetMoveScore();
    void ActiveTamCount();
    void InitBoxStates();
    void InitBoxStates_Sec();
    void InitBoxStates_Par();


    Real GetTamControl();
    Real GetTamControl_Sec();
    Real GetTamControl_Par();


    /*cambio void a Real solo para probar*/
    Real UpdateRobotPositions();



  private:

    /*
     * Method used to create and distribute the Arena.
     */
    void PositionArena();

    /*
     * Method used to remove the arena from the arena.
     */
    void RemoveArena();

    /*
     * Method used to deternmine wheter a number is even.
     */
    bool IsEven(UInt32 unNumber);

    /*
     * Return the radious of the arena.
     */
    Real GetArenaRadious();

    /*
     * Build the arena with the arena_entity plugin.
     */
    bool m_bBuildArena;

    /*
     * The number of edges in the arena used in the experiment.
     */
    UInt32 m_unNumberEdges;

    /*
     * The number of boxes in each edge of the arena used in the experiment.
     */
    UInt32 m_unNumberBoxes;

    /*
     * The lenght of the boxes used in the experiment.
     */
    Real m_fLenghtBoxes;

    /*
     * The arena used in the experiment.
     */
    CArenaEntity* m_pcArena;

    /*
     * Transition time in sequence experiments
     */
    UInt32 m_unTrnTime;

    /*
     * Allows for score invertion in maximization algorithms.
     */
    bool m_bMaximization;

    UInt32 m_unClock;
    UInt32 m_unStopTime;
    UInt32 m_unStopEdge;
    UInt32 m_unStopBox;
    UInt32 tam;
    Real m_fObjectiveFunction;
    CVector2 Tam1, Tam2, Tam3, Tam4, Tam5, Tam6, Tam7, Tam8;
    UInt32  tam1=0, tam2=0, tam3=0, tam4=0, tam5=0, tam6=0, tam7=0, tam8=0;
    std::string actionT1, actionT2, actionT3, actionT4, actionT5, actionT6, actionT7, actionT8, robot, mision;
    Real robotT1, robotT2, robotT3, robotT4, robotT5, robotT6, robotT7, robotT8;
    UInt32 timer1=0, timer2=0, timer3=0,timer4=0,timer5=0,timer6=0,timer7=0,timer8=0, timer9=0, timer10=0, timer11=0, timer12=0, timer13=0;

    int time_saved;
    std::string time_S, file_name;
    int c=0;

    struct RobotStateStruct {
        CVector2 cLastPosition;
        CVector2 cPosition;
        UInt32 unItem;
    };

    typedef std::map<CEPuckEntity*, RobotStateStruct> TRobotStateMap;

    TRobotStateMap m_tRobotStates;

};

#endif