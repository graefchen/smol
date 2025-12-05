#include <stdio.h>
#include <time.h>

int getSeason(struct tm *time) {
	int month = time->tm_mon;
	int day   = time->tm_mday;
	switch (month) {
		case  0: return 3;
		case  1: return day<5?3:0;
		case  2: return 0;
		case  3: return 0;
		case  4: return day<7?0:1; 
		case  5: return 1;
		case  6: return 1;
		case  7: return day<9?1:2;
		case  8: return 2;
		case  9: return 2;
		case 10: return day<8?2:3;
		case 11: return 3;
		default: return -1; // unreachable
	}
}

int main(int argc, char** argv) {
	time_t now = time(NULL);
	struct tm time;
	localtime_s(&time, &now);
	char* seasons[4] = {"Spring", "Summer", "Fall", "Winter"};

	printf("%s\n", seasons[getSeason(&time)]);
	return 0;
}

