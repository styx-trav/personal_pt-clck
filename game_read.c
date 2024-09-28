#include "libby.h"

void  read_game(s_node *head, u_node *user)
{
  int choice;
  char  *str;

  if (head == NULL)
    return ;
  if (head->unlocks != NULL && cmp(head->locked, "unlocked\0") == 0)
  {
    read_game(head->unlocks, user);
    return ;
  }
  if (head->char_cre != NULL && head->char_cre->lines[head->char_cre->line] == NULL)
  {
    if (head->option1 != NULL)
      read_game(head->option1, user);
    return;
  }
  if (head->locked != NULL && user->equipped != NULL && cmp(user->equipped->name, head->locked) == 0)
  {
    if (head->locked_desc != NULL)
      printer(head->locked_desc);
    head->locked = "unlocked\0";
    read_game(head->unlocks, user);
    return ;
  }
  if (head->damage != 0)
    damage_printer(user, head->damage, head->damage_msg);
  if (head->desc == NULL)
    return ;
  write(1, "\n\n", 2);
  name_printer(head->desc, user->name);
  if (user->hp == 0)
    return ;
  if (head->obj != NULL && head->obj->have_it == 0)
    printer(head->desc_obj);
  write(1, "\n\n", 2);
  if (head->choose_one != NULL)
      print_option(head->choose_one);
  if (head->choose_two != NULL)
    print_option(head->choose_two);
  if (head->obj != NULL && head->obj->have_it == 0)
    print_option(head->obj->name);
  if (head->char_cre != NULL)
      print_option("interact");
  str = NULL;
  if (head->obj != NULL)
    str = head->obj->name;
  choice = get_stdin(head->choose_one, head->choose_two, str);
  while (choice == 0
    || (choice == 3 && head->obj->have_it == 1)
    || (choice == 9 && head->char_cre == NULL))
  {
    write(1, "\n|| Please choose one of the given options:\n", 44);
    if (head->choose_one != NULL)
      print_option(head->choose_one);
    if (head->choose_two != NULL)
      print_option(head->choose_two);
    if (head->obj != NULL && head->obj->have_it == 0)
      print_option(head->obj->name);
    printer("|| inventory\n");
    if (head->back != NULL)
      printer("|| go back\n");
    if (head->char_cre != NULL && head->char_cre->hp > 0)
      print_option("interact");
    printer("|| help\n|| quit\n");
    choice = get_stdin(head->choose_one, head->choose_two, str);
  }
  if (choice == 1 && head->option1 != NULL)
    read_game(head->option1, user);
  if (choice == 2 && head->option2 != NULL)
    read_game(head->option2, user);
  if (choice == 3 && head->obj != NULL)
  {
    user->objs[user->i] = create_onode(head->obj->name, head->obj->mod, 1);
    head->obj->have_it = 1;
    user->i++;
    printer("|| You now have: ");
    printer(head->obj->name);
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
    if (inventory(head, user) == -1)
      return ;
    read_game(head, user);
  }
  if (choice == 7)
  {
    help(1);
    read_game(head, user);
  }
  if (choice == 8)
    read_game(user->checkpoint, user);
  if (choice == 9)
  {
    choice = interact(head->char_cre, user);
    if (choice == 1)
      read_game(head->option1, user);
    if (choice == 2)
    {
      head->locked = "unlocked\0";
      read_game(head, user);
    }
    if (choice == -1 && head->back != NULL)
      read_game(head->back, user);
  }
  return ;
}
