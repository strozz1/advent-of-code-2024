

#include <stdio.h>
#include <stdlib.h>
typedef struct {
  int num;
  int *before;
  int size;
} Restriction;

// create empty element
Restriction *init_restriction(int num) {
  Restriction *element = (Restriction *)malloc(sizeof(Restriction));
  element->num = num;
  element->size = 0;
  element->before = malloc(0);
  return element;
}
int is_before(Restriction *r,int n){
    int i;
    for(i=0;i<r->size;i++){
        if(r->before[i]==n){
            return 1;
        }
    }
    return 0;
}
void add_before(Restriction *element, int restriction) {
  element->before = (int *)realloc(element->before, sizeof(int)*(element->size + 1));
  element->before[element->size] = restriction;
  element->size++;
}

typedef struct {
  Restriction **elements;
  int size;
} Restrictions;

void print_restrictions(Restrictions *r) {
  int i, j;
  Restriction *e;
  for (i = 0; i < r->size; i++) {
    e = r->elements[i];
    printf("[%d]=[ ", e->num);
    for (j = 0; j < e->size; j++) {
      printf("%d ", e->before[j]);
    }
    printf("]\n");
  }
}
Restrictions *init_restrictions() {
  Restrictions *r = (Restrictions *)malloc(sizeof(Restrictions));
  r->elements = malloc(0);
  r->size = 0;
  return r;
}

// get element num from the restrictions
// NULL if not found
Restriction *get_restriction(Restrictions *res, int num) {
  int i;
  Restriction *e = NULL;
  for (i = 0; i < res->size; i++) {
    if (res->elements[i]->num == num) {
      e = res->elements[i];
      break;
    }
  }
  return e;
}
void add_restriction(Restrictions *rest, int num, int before) {
  Restriction *r = get_restriction(rest, num);
  // Check if restriction already exists
  if (r == NULL) {
    rest->elements = (Restriction **)realloc(rest->elements, sizeof(Restriction*)*(rest->size+1));
    r = init_restriction(num);
    rest->elements[rest->size] = r;
    rest->size++;

  }
  add_before(r, before);
}

