#include <string.h>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <cmath>

int main()
{
    time_t now = time( NULL);
    struct tm now_tm = *localtime( &now);
    struct tm now_save = *localtime( &now);

    struct tm then_tm = now_tm;


    for (float i; i<61;i++){
    
    double a = i/10;
    float mils=a-floor(a);
    mils = round(mils * 1000.0);
    std::cout<<"a:" <<a<<" a_round: " <<floor(a)<<" mils: "<<mils<<std::endl;



    
    //then_tm.tm_sec += 5;   // add 50 seconds to the time
    then_tm.tm_sec += i/10;   // add 50 seconds to the time
    mktime( &then_tm);      // normalize it
    struct tm tm;
    char buf[255];

    memset(&tm, 0, sizeof(tm));
    strptime(asctime(&then_tm), "%a %b %e %H:%M:%S %Y\n", &tm);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);

    std::cout<<"buf: " <<buf<<"."<<mils<<std::endl;
    then_tm=now_tm;
    }
    std::cout<<"now: " <<asctime( &now_save)<<std::endl;

    //g++ time2.cpp -o time2
    // ./time2



    return 0;
}

