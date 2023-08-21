#include <string.h>
#include <time.h>
#include <iomanip>
#include <iostream>
int main()
{
    time_t now = time( NULL);

    struct tm now_tm = *localtime( &now);

    struct tm then_tm = now_tm;

    for (int i; i<120;i++){


    then_tm.tm_sec += 5;   // add 50 seconds to the time

    mktime( &then_tm);      // normalize it
    struct tm tm;
    char buf[255];

    memset(&tm, 0, sizeof(tm));
    strptime(asctime(&then_tm), "%a %b %e %H:%M:%S %Y\n", &tm);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    std::cout<<buf<<std::endl;
    }



    return 0;
}

