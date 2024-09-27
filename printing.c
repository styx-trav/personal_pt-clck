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

void  name_printer(char *str, char *name)
{
  char  u_name[] = "u_name\0";
  int i;
  int j;

  i = 0;
  while (str[i] != '\0')
  {
    j = 0;
    while (u_name[j] != '\0' && str[i + j] == u_name[j])
      j++;
    if (u_name[j] == '\0')
    {
      printer(name);
      i = i + j;
    }
    write(1, &str[i], 1);
    i++;
  }
}

void  damage_printer(u_node *user, int damage, char *msg)
{
  char  a;
  int i;

  write(1, "\n", 1);
  printer(msg);
  write(1, "\n", 1);
  if (damage > 0)
  {
    if (user->equipped != NULL && user->equipped->mod < 0)
    {
      printer("|| Protected by your ");
      printer(user->equipped->name);
      printer(", you only take ");
      damage = damage + user->equipped->mod;
      if (damage < 0)
        damage = 0;
    }
    else
      printer("|| You take ");
    i = damage;
  }
  else
  {
    printer("|| You gain ");
    i = -damage;
  }
  a = (i /  10) + 48;
  write(1, &a, 1);
  a = (i %  10) + 48;
  write(1, &a, 1);
  if (damage < 0)
    printer("hp.");
  else
    printer("pts of damage.\n");
  user->hp = user->hp - damage;
  if (user->hp < 0)
    user->hp = 0;
  if (user->hp > 25)
    user->hp = 25;
  if (user->hp == 0)
  {
    printer("\n|| You are now dead.");
    return ;
  }
  printer("|| You now have ");
  a = (user->hp / 10) + 48;
  write(1, &a, 1);
  a = (user->hp % 10) + 48;
  write(1, &a, 1);
  printer("hp.");
}

void  print_option(char *str)
{
  write(1, "|| ", 3);
  printer(str);
  write(1, "\n", 1);
}
