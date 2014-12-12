#include <assert.h>
#include <string.h>
#include "mybuddy.h"

struct mybuddy
{
    unsigned size;
    unsigned longest[1];
};

#define LEFT_LEAF(index) ((index) * 2 + 1)
#define RIGHT_LEAF(index) ((index) * 2 + 2)
#define PARENT(index) (((index) + 1) / 2 - 1)

#define IS_POWER_OF_2(x) (!((x)&((x) - 1)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define ALLOC malloc
#define FREE free

static unsigned fixsize(unsigned size)
{
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    return size + 1;
}

struct mybuddy* mybuddy_new(int size)
{
    struct mybuddy* self;
    unsigned node_size;
    int i;

    if(size < 1 || !IS_POWER_OF_2(size))
        return NULL;

    self = (struct mybuddy*)ALLOC(2 * size * sizeof(unsigned));
    self->size = size;
    node_size = size * 2;

    for(i = 0; i < 2 * size - 1; ++i)
    {
        if(IS_POWER_OF_2(i + 1))
            node_size /= 2;
        self->longest[i] = node_size;
    }
    return self;
}

void mybuddy_destroy(struct mybuddy* self)
{
    FREE(self);
}

int mybuddy_alloc(struct mybuddy* self, int size)
{
    unsigned index = 0;
    unsigned node_size;
    unsigned offset = 0;

    if(self == NULL)
        return -1;

    if(size <= 0)
        size = 1;
    else if(!IS_POWER_OF_2(size))
        size = fixsize(size);

    if(self->longest[index] < size)
        return -1;

    for(node_size = self->size; node_size != size; node_size /= 2)
    {
        if(self->longest[LEFT_LEAF(index)] >= size)
            index = LEFT_LEAF(index);
        else
            index = RIGHT_LEAF(index);
    }

    self->longest[index] = 0;
    offset = (index + 1) * node_size - self->size;
    while(index)
    {
        index = PARENT(index);
        self->longest[index] = MAX(self->longest[LEFT_LEAF(index)], self->longest[RIGHT_LEAF(index)]);
    }

    return offset;
}

void mybuddy_free(struct mybuddy* self, int offset)
{
    unsigned node_size, index = 0;
    unsigned left_longest, right_longest;

    assert(self && offset >= 0 && offset < self->size);

    node_size = 1;
    index = offset + self->size - 1;

    for(; self->longest[index]; index = PARENT(index))
    {
        node_size *= 2;
        if(index == 0)
            return;
    }

    self->longest[index] = node_size;

    while(index)
    {
        index = PARENT(index);
        node_size *= 2;
        
        left_longest = self->longest[LEFT_LEAF(index)];
        right_longest = self->longest[RIGHT_LEAF(index)];

        if(left_longest + right_longest == node_size)
            self->longest[index] = node_size;
        else
            self->longest[index] = MAX(left_longest, right_longest);
    }
}

int mybuddy_size(struct mybuddy* self, int offset) {
  unsigned node_size, index = 0;

  assert(self && offset >= 0 && offset < self->size);

  node_size = 1;
  for (index = offset + self->size - 1; self->longest[index] ; index = PARENT(index))
    node_size *= 2;

  return node_size;
}

void mybuddy_dump(struct mybuddy* self) {
  char canvas[65];
  int i,j;
  unsigned node_size, offset;

  if (self == NULL) {
    printf("mybuddy_dump: (struct mybuddy*)self == NULL");
    return;
  }

  if (self->size > 64) {
    printf("mybuddy_dump: (struct mybuddy*)self is too big to dump");
    return;
  }

  memset(canvas,'_', sizeof(canvas));
  node_size = self->size * 2;

  for (i = 0; i < 2 * self->size - 1; ++i) {
    if ( IS_POWER_OF_2(i+1) )
      node_size /= 2;

    if ( self->longest[i] == 0 ) {
      if (i >=  self->size - 1) {
        canvas[i - self->size + 1] = '*';
      }
      else if (self->longest[LEFT_LEAF(i)] && self->longest[RIGHT_LEAF(i)]) {
        offset = (i+1) * node_size - self->size;

        for (j = offset; j < offset + node_size; ++j)
          canvas[j] = '*';
      }
    }
  }
  canvas[self->size] = '\0';
  puts(canvas);
}
