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
  printer("Currently equipped: ");
  if (user->equipped == NULL)
    printer("nothing.\n");
  else
  {
    printer(user->equipped->name);
    printer(".\n");
    if (user->equipped->mod != 0)
    {
      printer("It grants you +");
      obj = user->equipped->mod;
      if (obj < 0)
        obj = -obj;
      a = (obj / 10) + 48;
      write(1, &a, 1);
      a = (obj % 10) + 48;
      write(1, &a, 1);
      if (user->equipped->mod < 0)
        printer(" in protection against attacks.\n");
      else
        printer(" in attack.\n");
    }
  }
  obj = inv_cmparison(user->objs, user->i);
  if (obj == -1)
    return (-1);
  if (obj == 0)
    printer("Nothing by that name.\n");
  if (obj > 0 && room->locked != NULL && cmp(user->objs[obj - 1]->name, room->locked) == 0)
  {
    if (room->locked_desc != NULL)
      printer(room->locked_desc);
    room->locked = "unlocked\0";
  }
  else if (obj > 0)
  {
    if (user->objs[obj - 1] == user->equipped)
    {
      printer("|| You have unequipped: ");
      printer(user->equipped->name);
      printer(".\n");
      user->equipped = NULL;
      return (0);
    }
    printer("|| You now have equipped: ");
    printer(user->objs[obj - 1]->name);
    printer(".\n|| It grants you ");
    user->equipped = user->objs[obj - 1];
    if (user->equipped->mod == 0)
      printer("no modified stats.\n");
    else
    {
      printer("+");
      i = user->equipped->mod;
      if (i < 0)
        i = -i;
      a = (i / 10) + 48;
      write(1, &a, 1);
      a = (i % 10) + 48;
      write(1, &a, 1);
      if (user->equipped->mod < 0)
        printer(" protection against any damage.\n");
      else
        printer(" attack against any creature or object.\n");
    }
  }
  return (0);
}
