#include "libby.h"

int  inv_cmparison(o_node **tab, int u_i)
{
  char  *str;
  char  buffer[37];
  int i;
  int choice;

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
  i = 0;
  if (cmp("quit", str) == 0)
  {
    free(str);
    return (-1);
  }
  if (cmp("go back", str) == 0)
  {
    free(str);
    return (-2);
  }
  choice = 1;
  while (choice != 0 && i < u_i)
  {
    choice = cmp(tab[i]->name, str);
    i++;
  }
  free(str);
  if (i == u_i + 1)
    return (0);
  return (i);
}

int  inventory(s_node *room, u_node *user)
{
  int obj;
  int i;
  char  a;

  i = 0;
  obj = 0;
  write(1, "\nYou currently have ", 20);
  while (user->objs[i] != NULL)
  {
    if (user->objs[i]->have_it == 1)
      obj++;
    i++;
  }
  a = obj + '0';
  write(1, &a, 1);
  write(1, " item", 5);
  if (obj > 1)
    write(1, "s", 1);
  if (obj == 0)
    write(1, ".\n", 2);
  else
    write(1, ":\n", 2);
  i = 0;
  while (user->objs[i] != NULL)
  {
    if (user->objs[i]->have_it == 1)
      print_option(user->objs[i]->name);
    i++;
  }
  obj = inv_cmparison(user->objs, user->i);
  if (obj == -1)
    return (-1);
  if (obj == 0)
    printer("Nothing by that name.\n");
  if (obj > 0 && room->locked != NULL && cmp(user->objs[obj - 1]->name, room->locked) == 0)
    room->locked = "unlocked\0";
  return (0);
}

int u_has_obj(o_node **tab, o_node *obj)
{
  int i;

  i = 0;
  while (tab[i] != NULL)
  {
    if (cmp(tab[i]->name, obj->name) == 0)
      return (0);
    i++;
  }
  return (-1);
}
