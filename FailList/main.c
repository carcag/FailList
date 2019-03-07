#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    if (av[1] != NULL)
      printf(av[1]);
    return 0;
}
