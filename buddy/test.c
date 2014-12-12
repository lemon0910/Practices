#include "mybuddy.h"
#include <stdio.h>
int main() {
  char cmd[80];
  int arg;
  struct mybuddy* buddy = mybuddy_new(32);
  mybuddy_dump(buddy);
  for (;;) {
    scanf("%s %d", cmd, &arg);
    if (strcmp(cmd, "alloc") == 0) {
      printf("allocated@%d\n", mybuddy_alloc(buddy, arg));
      mybuddy_dump(buddy);
    } else if (strcmp(cmd, "free") == 0) {
      mybuddy_free(buddy, arg);
      mybuddy_dump(buddy);
    } else if (strcmp(cmd, "size") == 0) {
      printf("size: %d\n", mybuddy_size(buddy, arg));
      mybuddy_dump(buddy);
    } else
      mybuddy_dump(buddy);
  }
}
