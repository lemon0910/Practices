#ifndef __MYBUDDY__
#define __MYBUDDY__

#include <stdlib.h>
#include <stdio.h>

struct mybuddy;
struct mybuddy* mybuddy_new(int size);
void mybuddy_destroy(struct mybuddy *self);

int mybuddy_alloc(struct mybuddy* self, int size);
void mybuddy_free(struct mybuddy* self, int offset);

int mybuddy_size(struct mybuddy *selft, int offset);
void mybuddy_dump(struct mybuddy* self);

#endif
