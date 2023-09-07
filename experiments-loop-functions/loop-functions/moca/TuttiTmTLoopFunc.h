/**
  * @file <loop-functions/example/PwLoopFunc.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef TUTTI_TMT_LOOP_FUNC
#define TUTTI_TMT_LOOP_FUNC

#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/e-puck/simulator/epuck_entity.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <argos3/plugins/robots/arena/simulator/arena_entity.h>
#include "../../src/CoreLoopFunctions.h"
#include <ctime>
#include <string.h>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>




using namespace argos;
std::fstream MyFile;

time_t now = time( NULL);
struct tm now_tm = *localtime( &now);
struct tm then_tm = now_tm;

// num_Tam (# Tam in the mision)- T_n (# Tam per activity)- A_n (#Activities in the map)
int num_Tam=8, T_n=2, A_n=4, flag_a=0, flag_b=0, cont=0, t=0, boxa=0;

std::vector<int> Tam_color(num_Tam, 0); // Indicates the color displaying in each TAM is use to register any change on the tam
std::vector<Real> Tam_side1_x, Tam_side1_y, Tam_side2_x, Tam_side2_y, Tam_back_x, Tam_back_y, Tam_front_f, Tam_front_e, T_l, T_r, T_u, T_b;  
void print2 (std::vector <Real> const &a);
Real sides (Real s1_x, Real s1_y, Real s2_x, Real s2_y, Real b_x, Real b_y, Real c);
Real left, right, up, down;


//a map called activities is created which stores keys of type strings which indicate the order and the nature of the activity
//(secuencial or concurrent) and corresponding vector of the TAM's each activity will ocupy
std::map <std::string, std::vector<Real> > activities;   
//We store the keys of each activity into a list (key) and each vector into a matrix (value) so we can further on manipulate them
std::vector<std::string> key;
std::vector<std::vector<Real> > value;

//a map called activities is created which stores keys of type strings which indicate the order and the nature of the activity
//(secuencial or concurrent) and corresponding vector of the TAM's each activity will ocupy




class TuttiTmTLoopFunction: public CoreLoopFunctions {
  public:
    TuttiTmTLoopFunction();
    TuttiTmTLoopFunction(const TuttiTmTLoopFunction& orig);
    virtual ~TuttiTmTLoopFunction();
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

    void Boxes(Real box, Real color);
    void Gates();
    Real robots_sec(Real a);
    Real robots_con(Real a);
    Real sec(std::vector <Real> const &a);
    Real con(std::vector <Real> const &a);
    Real timing();



    /*


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

    UInt32 m_unClock, m_unStopTime, m_unStopEdge, m_unStopBox;
    Real m_fObjectiveFunction;
    std::string time_S, file_name, mision;
    float mils;

    struct RobotStateStruct {
        CVector2 cLastPosition;
        CVector2 cPosition;
        UInt32 unItem;
    };

    typedef std::map<CEPuckEntity*, RobotStateStruct> TRobotStateMap;

    TRobotStateMap m_tRobotStates;

};

#endif

