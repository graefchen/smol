#include <stdio.h>
#include <time.h>

inline int getSeason(struct tm *t) {
    return t->tm_mon % 4;
}

short getDayTime(struct tm *t) {
    short time[96] = {
        0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,0,0,0,0,
        0,0,0,0,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,0,0,0,
        0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,0,0,0,0,
        0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,3,3,0,0,0,0,0
    };
    return time[(t->tm_mon % 4) * 24 + t->tm_hour];
}

int main(void) {
    time_t now = time(NULL);
    struct tm *t;
    localtime_s(t, &now);
    char* seasons[4] = {"spring", "summer", "autumn", "winter"};
    char* daytime[4] = {"night", "morning", "day", "evening"};

    printf("%s, %s-time\n", seasons[getSeason(t)], daytime[getDayTime(t)]);
    return 0;
}
