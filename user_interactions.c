#include "libby.h"

int cmp(char *str, char *str2)
{
  int i;

  if (str == NULL)
    return (1);
  i = 0;
  while (str[i] && str2[i] && str2[i] == str[i])
    i++;
  if (str[i] == '\0'
    && (str2[i] == '\0' || (str2[i] == '\n' && str2[i +1] == '\0')))
    return (0);
  else
    return (1);
}

int compare(char *opt1, char *opt2, char *obj, char *read)
{
  if (cmp("quit", read) == 0)
    return (-1);
  if (cmp("go back", read) == 0)
    return (4);
  if (cmp(opt1, read) == 0)
    return (1);
  if (cmp(opt2, read) == 0)
    return (2);
  if (cmp("stats", read) == 0)
    return (5);
  if (cmp("inventory", read) == 0)
    return (6);
  if (cmp(obj, read) == 0)
    return (3);
  return (0);
}

int  get_stdin(char *opt1, char *opt2, char *obj)
{
  char  *str;
  char  buffer[37];
  int i;

  i = 0;
  while (i < 37)
  {
    buffer[i] = '\0';
    i++;
  }
  read(1, buffer, 36);
  i = 0;
  while (buffer[i] != '\0')
    i++;
  str = malloc(sizeof(char) * (i + 1));
  i = 0;
  if (str == NULL)
    return (0);
  while (buffer[i] != '\0')
  {
    str[i] = buffer[i];
    i++;
  }
  str[i] = '\0';
  i = compare(opt1, opt2, obj, str);
  free(str);
  return (i);
}
