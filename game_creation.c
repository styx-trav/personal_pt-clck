#include "libby.h"

s_node  *create_snode(char *desc)
{
  s_node  *new_item;

  new_item = (s_node *)malloc(sizeof(s_node));
  if (new_item == NULL)
    return (NULL);
  new_item->desc = desc;
  new_item->locked = 0;
  new_item->obj = 0;
  new_item->locked_desc = NULL;
  new_item->damage = 0;
  new_item->damage_msg = NULL;
  new_item->unlocks = NULL;
  new_item->choose_one = NULL;
  new_item->choose_two = NULL;
  new_item->choose_obj = NULL;
  new_item->desc_obj = NULL;
  new_item->option1 = NULL;
  new_item->option2 = NULL;
  new_item->back = NULL;
  return (new_item);
}

void  free_prot(s_node  *head)
{
  if (head != NULL)
  {
    if (head->option1 != NULL)
      free_prot(head->option1);
    if (head->option2 != NULL)
      free_prot(head->option2);
    free(head);
  }
}

int main (void)
{
  s_node  *head;
  u_node  *user;

  user = create_user(3);
  //head = create_game(user);
  //head = create_game2(user);
  head = create_game3(user);
  if (head != NULL)
  {
    if (user == NULL)
    {
      free_prot(head);
      return (0);
    }
    help(0);
    read_game(head, user);
    free_prot(head);
    free_prot_u(user);
  }
  else if (user != NULL)
    free_prot_u(user);
}
