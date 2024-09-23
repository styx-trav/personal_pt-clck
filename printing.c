#include "libby.h"

void  printer(char *str)
{
  int i;

  i = 0;
  while (str[i] != '\0')
  {
    write(1, &str[i], 1);
    i++;
  }
}

void  print_option(char *str)
{
  write(1, "|| ", 3);
  printer(str);
  write(1, "\n", 1);
}

