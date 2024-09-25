#include "libby.h"

int  use_inventory(s_node *room, u_node *user)
{
  int obj;
  int i;
  char  a;

  i = 0;
  obj = 0;
  write(1, "\nYou currently have ", 20);
  while (i < 3)
  {
    if (user->obj_tab[i] == 1)
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
  while (i < 3)
  {
    if (user->obj_tab[i] == 1)
      print_option(user->obj_names[i]);
    i++;
  }
  obj = get_stdin(user->obj_names[0], user->obj_names[1], user->obj_names[2]);
  if (obj == -1)
    return (-1);
  if (obj == room->locked && user->obj_tab[obj - 1] == 1)
  {
    room->locked = -1;
    return (0);
  }
  if (obj == 4)
    return (0);
  if (obj == 0
    || (obj == room->locked && user->obj_tab[obj - 1] != 1))
    write(1, "|| Nothing by that name\n", 25);
  else
    write(1, "|| This can't be used here.\n", 26);
  use_inventory(room, user);
  return (0);
}

void  read_game(s_node *head, u_node *user)
{
  int choice;

  if (head == NULL)
    return ;
  if (head->locked == -1)
  {
    read_game(head->option1, user);
    return ;
  }
  if (head->damage != 0)
    damage_printer(user, head->damage, head->damage_msg);
  if (head->unlocks != NULL && head->unlocks->locked_desc != NULL)
    head->unlocks->desc = head->unlocks->locked_desc;
  if (head->desc == NULL)
    return ;
  write(1, "\n\n", 2);
  name_printer(head->desc, user->name);
  if (user->hp == 0)
    return ;
  if (head->obj == 13)
    return ;
  if (head->choose_obj != NULL && user->obj_tab[head->obj - 1] == 0)
    printer(head->desc_obj);
  write(1, "\n\n", 2);
  if (head->choose_one != NULL)
      print_option(head->choose_one);
  if (head->choose_two != NULL)
    print_option(head->choose_two);
  if (head->choose_obj != NULL && user->obj_tab[head->obj - 1] == 0)
    print_option(head->choose_obj);
  choice = get_stdin(head->choose_one, head->choose_two, head->choose_obj);
  while (choice == 0)
  {
    write(1, "\n|| Please choose one of the given options:\n", 44);
    if (head->choose_one != NULL)
      print_option(head->choose_one);
    if (head->choose_two != NULL)
      print_option(head->choose_two);
    if (head->choose_obj != NULL)
      print_option(head->choose_obj);
    printer("|| inventory\n|| go back\n|| quit\n");
    choice = get_stdin(head->choose_one, head->choose_two, head->choose_obj);
  }
  if (choice == 1 && head->option1 != NULL)
    read_game(head->option1, user);
  if (choice == 2 && head->option2 != NULL)
    read_game(head->option2, user);
  if (choice == 3)
  {
    user->obj_tab[head->obj - 1] = 1;
    write(1, "|| You now have: ", 17);
    printer(head->choose_obj);
    read_game(head, user);
  }
  if (choice == 5)
  {
    read_user(user);
    read_game(head, user);
  }
  if (choice == 4)
  {
    if (head->back != NULL)
      read_game(head->back, user);
    else
    {
      printer("\n|| You cannot go back.");
      read_game(head, user);
    }
  }
  if (choice == 6)
  {
    if (use_inventory(head, user) == -1)
      return ;
    read_game(head, user);
  }
  if (choice == 7)
  {
    help(1);
    read_game(head, user);
  }
  if (choice == 8)
  {
    if (user->checkpoint == head)
      read_game(head, user);
    else
      read_game(user->checkpoint, user);
  }
  return ;
}
