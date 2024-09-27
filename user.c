#include "libby.h"

o_node  *create_onode(char *name, int mod, int have_it)
{
  o_node  *obj;

  obj = NULL;
  obj = (o_node *)malloc(sizeof(o_node));
  if (obj == NULL)
    return (NULL);
  obj->name = name;
  obj->mod = mod;
  obj->have_it = have_it;
  return (obj);
}

void  free_prot_u(u_node  *user)
{
  int i;

  i = 0;
  if (user->name != NULL)
    free(user->name);
  if (user->objs != NULL)
  {
    while (user->objs[i] != NULL)
    {
      free(user->objs[i]);
      i++;
    }
    free(user->objs);
  }
  free(user);
}

u_node  *create_user(int tab)
{
  u_node  *user;
  char  buffer[27];
  int len;
  int i;

  user = (u_node *)malloc(sizeof(u_node));
  if (user == NULL)
    return (NULL);
  user->objs = NULL;
  user->name = NULL;
  user->checkpoint = NULL;
  write(1, "\n|| Please enter a name (26 char max):\n\n", 40);
  len = read(1, buffer, 26);
  while (len == 0)
  {
    write(1, "\n|| Please enter a name (26 char max):\n\n", 40);
    len = read(1, buffer, 26);
  }
  if (buffer[len - 1] == '\n')
    len--;
  user->name = malloc(sizeof(char) * (len + 1));
  if (user->name == NULL)
  {
    printer("freeing user for name allocation\n");
    free_prot_u(user);
    return (NULL);
  }
  i = 0;
  while (i < len)
  {
    user->name[i] = buffer[i];
    i++;
  }
  user->name[i] = '\0';
  user->objs = malloc(sizeof(o_node *) * (tab + 1));
  if (user->objs == NULL)
  {
    printer("freeing user for objs allocation\n");
    free_prot_u(user);
    return (NULL);
  }
  i = 0;
  while (i <= tab)
  {
    user->objs[i] = NULL;
    i++;
  }
  user->objs[0] = create_onode("chains", 4, 1);
  user->i = 1;
  user->equipped = NULL;
  user->hp = 25;
  return (user);
}

void  read_user(u_node  *user)
{
  char  a;
  int i;

  if (user == NULL)
    return ;
  printer("\n|| Current user stats:\n|| name: \0");
  printer(user->name);
  printer("\n|| hp: \0");
  a = user->hp / 10 + 48;
  write(1, &a, 1);
  a = user->hp % 10 + 48;
  write(1, &a, 1);
  printer("\n|| objects found: \0");
  a = user->i + 48;
  write(1, &a, 1);
  printer(".\n|| currently equipped: ");
  if (user->equipped == NULL)
    printer("nothing.");
  else
  {
    printer(user->equipped->name);
    if (user->equipped->mod == 0)
    {
      printer(", with no attack or defense mods.");
      return ;
    }
    printer(", with a +");
    i = user->equipped->mod;
    if (i < 0)
      i = -i;
    a = (i / 10) + 48;
    write(1, &a, 1);
    a = (i % 10) + 48;
    write(1, &a, 1);
    if (user->equipped->mod < 0)
      printer(" protection mod.");
    else
      printer(" attack mod.");
  }
}
