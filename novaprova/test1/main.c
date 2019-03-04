#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "my_add.h"

int main(int ac, char **av)
{
  int n1, n2, res;

  n1 = 1;
  n2 = 2;
  res = my_add(n1, n2);
  printf("%d\n", res);
  return(0);
}
