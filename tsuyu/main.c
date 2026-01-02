#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// TODO: Add missing mcroseasons.

int getSeason(struct tm *time) {
  int month = time->tm_mon;
  int day = time->tm_mday;
  switch (month) {
  case 0:
    return 3;
  case 1:
    return day < 5 ? 3 : 0;
  case 2:
    return 0;
  case 3:
    return 0;
  case 4:
    return day < 7 ? 0 : 1;
  case 5:
    return 1;
  case 6:
    return 1;
  case 7:
    return day < 9 ? 1 : 2;
  case 8:
    return 2;
  case 9:
    return 2;
  case 10:
    return day < 8 ? 2 : 3;
  case 11:
    return 3;
  default:
    return -1; // unreachable
  }
}

bool checkString(char *original, char *expected) {
  int orig_len = strlen(original);
  int expe_len = strlen(expected);
  if (expe_len != orig_len)
    return false;
  // going backwards, hoping it is faster
  for (int i = orig_len; i != 0; i--) {
    if (expected[i] != original[i])
      return false;
  }
  // got through everything
  return true;
}

typedef struct {
  bool english;
  bool japanese;
  bool romanisation;
  bool solar;
  bool microseason;
  bool help;
} Args;

bool parse(Args *args, int argc, char **argv) {
  // start with 1 to skip name
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    // parse long
    if (arg[0] == '-' && arg[1] == '-') {
      if (checkString(arg + 2, "help")) {
        args->help = true;
      } else if (checkString(arg + 2, "solar")) {
        args->solar = true;
      } else if (checkString(arg + 2, "english")) {
        args->english = true;
      } else if (checkString(arg + 2, "japanese")) {
        args->japanese = true;
      } else if (checkString(arg + 2, "microseason")) {
        args->microseason = true;
      } else if (checkString(arg + 2, "romanisation")) {
        args->romanisation = true;
      } else {
        printf("Unknown command: \"%s\"", arg + 2);
        return true;
      }
    }
    // parse short
    else if (arg[0] == '-') {
      for (int j = 1; arg[j] != '\0'; j++) {
        switch (arg[j]) {
        case 'e': {
          args->english = true;
          break;
        }
        case 'm': {
          args->microseason = true;
          break;
        }
        case 'j': {
          args->japanese = true;
          break;
        }
        case 'r': {
          args->romanisation = true;
          break;
        }
        case 's': {
          args->solar = true;
          break;
        }
        case 'h': {
          args->help = true;
          break;
        }
        default:
          printf("Unknown command: \"%c\"", arg[j]);
          return true;
        }
      }
    } else {
      printf("Unknown argument: %s\n", arg);
      return true;
    }
  }
  return false;
}

void usage() {
  printf("tsuyu, print the current season of the japanese calender\n"
         "Usage: tsuyu [options]\n\n"
         "options:\n"
         "  -e, --english       Print the english name\n"
         "  -j, --japanese      Print the japanese name\n"
         "  -r, --romanisation  Print the romanisation\n"
         "  -s, --solar         Use the solar term\n"
         "  -m, --microseason   Use the microseason\n"
         "  -h, --help          The help message\n");
}

// https://en.wikipedia.org/wiki/Japanese_calendar
int main(int argc, char **argv) {
  Args arg = {false};
  bool err = parse(&arg, argc, argv);
  if (err)
    return 1;

  if (arg.help) {
    usage();
    return 1;
  }

  time_t now = time(NULL);
  struct tm time;
  localtime_s(&time, &now);

  if (arg.solar) {
    int season = (time.tm_yday - 40) / 15;
    if (season == -1) {
      printf("Something went very wrong.\n");
      return 1;
    }

    char *eseasons[24] = {
        "Spring", "Spring", "Spring", "Spring", "Spring", "Spring",
        "Summer", "Summer", "Summer", "Summer", "Summer", "Summer",
        "Autumn", "Autumn", "Autumn", "Autumn", "Autumn", "Autumn",
        "Winter", "Winter", "Winter", "Winter", "Winter", "Winter",
    };
    char *jseasons[24] = {
        "立春", "雨水", "啓蟄", "春分",  "清明", "穀雨", "立夏", "小満",
        "芒種", "夏至", "小暑", "大暑,", "立秋", "処暑", "白露", "秋分",
        "寒露", "立冬", "小雪", "小雪",  "大雪", "冬至", "小寒", "大寒",
    };
    char *rseasons[24] = {
        "Risshun", "Usui",     "Keichitsu", "Shunbun ", "Seimei", "Kokuu",
        "Rikka",   "Shōman",   "Bōshu",     "Geshi",    "Shōsho", "Taisho",
        "Risshū",  "Shosho",   "Hakuro",    "Shūbun",   "Kanro",  "Sōkō",
        "Rittō",   "Shōsetsu", "Taisetsu",  "Tōji",     "Shōkan", "Daikan",
    };

    if (!arg.english && !arg.japanese && !arg.romanisation)
      printf("  %s  %s  %s", eseasons[season], jseasons[season],
             rseasons[season]);
    if (arg.english) {
      printf("  %s", eseasons[season]);
    }
    if (arg.japanese) {
      printf("  %s", jseasons[season]);
    }
    if (arg.romanisation) {
      printf("  %s", rseasons[season]);
    }
    printf("\n");

  } else {
    int season = getSeason(&time);
    if (season == -1) {
      printf("Something went very wrong.\n");
      return 1;
    }

    char *eseasons[4] = {"Spring", "Summer", "Fall", "Winter"};
    char *jseasons[4] = {"春", "夏", "秋", "冬"};
    char *rseasons[4] = {"haru", "natsu", "aki", "fuyu"};

    if (!arg.english && !arg.japanese && !arg.romanisation)
      printf("  %s  %s  %s", eseasons[season], jseasons[season],
             rseasons[season]);
    if (arg.english) {
      printf("  %s", eseasons[season]);
    }
    if (arg.japanese) {
      printf("  %s", jseasons[season]);
    }
    if (arg.romanisation) {
      printf("  %s", rseasons[season]);
    }
    printf("\n");
  }

  return 0;
}
