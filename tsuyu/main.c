#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

enum month {
  January = 0,
  February,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November,
  December
};

enum season { Spring = 0, Summer, Fall, Winter };

int getSeason(struct tm *time) {
  int month = time->tm_mon;
  int day = time->tm_mday;
  switch (month) {
  case January:
    return Winter;
  case February:
    return day < 5 ? Winter : Spring;
  case March:
    return Spring;
  case April:
    return Spring;
  case May:
    return day < 7 ? Spring : Summer;
  case June:
    return Summer;
  case July:
    return Summer;
  case August:
    return day < 9 ? Summer : Fall;
  case September:
    return Fall;
  case October:
    return Fall;
  case November:
    return day < 8 ? Fall : Winter;
  case December:
    return Winter;
  default:
    return -1; // unreachable
  }
}

enum sekki {
  Risshun = 0,
  Usui,
  Keichitsu,
  Shunbun,
  Seimei,
  Kokuu,
  Rikka,
  Shooman,
  Booshu,
  Geshi,
  Shoosho,
  Taisho,
  Risshuu,
  Shosho,
  Hakuro,
  Shuubun,
  Kanro,
  Sookoo,
  Rittoo,
  Shoosetsu,
  Taisetsu,
  Tooji,
  Shookan,
  Daikan
};

// A very complicated way to get the seasons, but anyway it will be fine.
int getSolarSeason(struct tm *time) {
  int month = time->tm_mon;
  int day = time->tm_mday;
  switch (month) {
  case January: {
    if (day < 5)
      return Tooji;
    else if (day < 20)
      return Shookan;
    else
      return Daikan;
  }
  case February: {
    if (day < 4)
      return Daikan;
    else if (day < 19)
      return Risshun;
    else
      return Usui;
  }
  case March: {
    if (day < 5)
      return Usui;
    else if (day < 21)
      return Keichitsu;
    else
      return Shunbun;
  }
  case April: {
    if (day < 5)
      return Shunbun;
    else if (day < 20)
      return Seimei;
    else
      return Kokuu;
  }
  case May: {
    if (day < 4)
      return Kokuu;
    else if (day < 21)
      return Rikka;
    else
      return Shooman;
  }
  case June: {
    if (day < 6)
      return Shooman;
    else if (day < 21)
      return Booshu;
    else
      return Geshi;
  }
  case July: {
    if (day < 7)
      return Geshi;
    else if (day < 23)
      return Shoosho;
    else
      return Taisho;
  }
  case August: {
    if (day < 8)
      return Taisho;
    else if (day < 23)
      return Risshuu;
    else
      return Shosho;
  }
  case September: {
    if (day < 8)
      return Shosho;
    else if (day < 23)
      return Shuubun;
  }
  case October: {
    if (day < 8)
      return Shuubun;
    else if (day < 23)
      return Kanro;
    else
      return Sookoo;
  }
  case November: {
    if (day < 7)
      return Sookoo;
    else if (day < 22)
      return Rittoo;
    else
      return Shoosetsu;
  }
  case December: {
    if (day < 7)
      return Shoosetsu;
    else if (day < 22)
      return Taisetsu;
    else
      return Tooji;
  }
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
  printf("tsuyu, get the current season of the japanese calender\n"
         "Usage: tsuyu [options]\n\n"
         "options:\n"
         "  -e, --english       print the english name\n"
         "  -j, --japanese      print the japanese name\n"
         "  -r, --romanisation  print the romanisation\n"
         "  -s, --solar         use the solar term\n"
         "  -m, --microseason   use the microseason\n"
         "  -h, --help          the help message\n");
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
    int season = getSolarSeason(&time);

    if (season < 0) {
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
        "立春", "雨水", "啓蟄", "春分", "清明", "穀雨", "立夏", "小満",
        "芒種", "夏至", "小暑", "大暑", "立秋", "処暑", "白露", "秋分",
        "寒露", "立冬", "小雪", "小雪", "大雪", "冬至", "小寒", "大寒",
    };
    char *rseasons[24] = {
        "Risshun", "Usui",     "Keichitsu", "Shunbun ", "Seimei", "Kokū",
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
      printf("  %s", rseasons[season]);
    }
    if (arg.romanisation) {
      printf("  %s", jseasons[season]);
    }
    printf("\n");

  } else {
    int season = getSeason(&time);

    if (season < 0) {
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
