/* sr, for Simple Random */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 4096
#define STRMATCH(a, b) (strcmp((a), (b)) == 0)
#define SIZE(A) (sizeof(A) / sizeof(A[0]))

char T[] = {'S', 'e', 'B', 'w', 'm', 'j', 'X', 't', 'Y', 'f', 'R', '7', 'I',
            'P', '6', 'U', '5', '3', 'K', 'r', '1', 'h', 'M', '2', 'A', 'L',
            'x', 'p', '0', 'o', 'a', 'Q', 'b', 'J', 'g', 'Z', 'u', 'y', 'O',
            'D', 'V', '8', 'H', 'z', 'E', 'c', '4', 'F', 'v', 'n', 'C', 'T',
            'W', 'k', 's', 'l', 'i', 'G', 'q', 'N', 'd', '9'};

void generate(int num) {
  int t[MAX];
  srand(time(NULL));

  for (int i = 0; i < SIZE(t); i++) {
    t[i] = rand();
  }

  char *ptr = (char *)malloc(num);
  ptr[num] = '\0';

  for (int i = 0; i < num - 1; i++) {
    int r = t[rand() % MAX];
    ptr[i] = T[r % SIZE(T)];
  }

  printf("%s\n", ptr);
  free(ptr);
}

typedef struct {
  int len;
  int help;
  // TODO: Maybe add some different modes.
} Args;

void parse(Args *args, int argc, char **argv) {
  // start with 1 to skip name
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    if (STRMATCH(arg, "-h")) {
      args->help = 1;
      return;
    }
    else if (STRMATCH(arg, "-n")) {
      if (argc < i + 1) {
        printf("Error: Missing number.\n");
      }
      args->len = atoi(argv[i + 1]);
      i++;
    }
    // ignore everything else (should be fine)
  }
}

int main(int argc, char **argv) {
  Args args = {6, 0};
  parse(&args, argc, argv);
  if (args.help) {
    printf("small random string generator of [a-zA-Z0-9]\nUsage sc: "
           "[options]\n  Options:\n  -h      print this message\n"
           "  -n num  set the random String to lenght of n\n");
    exit(1);
  }
  generate(args.len);
  return 0;
}
