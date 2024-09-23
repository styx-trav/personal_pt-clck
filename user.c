#include "libby.h"

void  free_prot_u(u_node  *user)
{
  int i;

  i = 0;
  if (user->name != NULL)
    free(user->name);
  if (user->obj_tab != NULL)
    free(user->obj_tab);
  if (user->obj_names != NULL)
  {
    while (i < 3)
    {
      if (user->obj_names[i] != NULL)
        free(user->obj_names[i]);
      i++;
    }
    free(user->obj_names);
  }
  free(user);
}

u_node  *create_user(void)
{
  u_node  *user;
  char  buffer[27];
  int len;
  int i;

  user = (u_node *)malloc(sizeof(u_node));
  if (user == NULL)
    return (NULL);
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
  user->obj_tab = malloc(sizeof(int) * 3);
  if (user->obj_tab == NULL)
  {
    free_prot_u(user);
    return (NULL);
  }
  i = 0;
  while (i < 3)
  {
    user->obj_tab[i] = 0;
    i++;
  }
  user->obj_names = malloc(sizeof(char *) * 4);
  if (user->obj_names == NULL)
  {
    free_prot_u(user);
    return (NULL);
  }
  i = 0;
  while (i < 3)
  {
    user->obj_names[i] = NULL;
    i++;
  }
  return (user);
}

void  read_user(u_node  *user)
{
  int num;
  int i;

  num = 0;
  i = 0;
  while (i < 3)
  {
    if (user->obj_tab[i] != 0)
      num++;
    i++;
  }
  printf("\n|| Current user stats:\n|| name: %s\n|| objects found: %d\n", user->name, num);
}
