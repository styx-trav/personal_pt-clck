#include "libby.h"

c_node  *create_cnode(char  *name, int lines, int strikes, int hp)
{
  c_node  *cre;
  int i;

  cre = (c_node *)malloc(sizeof(c_node));
  if (!cre)
  {
    free(cre);
    return (NULL);
  }
  cre->name = name;
  if (lines > 0)
  {
    cre->lines = malloc(sizeof(char *) * (lines + 1));
    if (!cre->lines)
    {
      free(cre);
      return (NULL);
    }
    i = 0;
    while (i <= lines)
    {
      cre->lines[i] = NULL;
      i++;
    }
    cre->dialogue = malloc(sizeof(char *) * (lines + 1));
    if (!cre->dialogue)
    {
      free_prot_c(cre);
      return (NULL);
    }
    i = 0;
    while (i <= lines)
    {
      cre->dialogue[i] = NULL;
      i++;
    }
  }
  if (strikes > 0)
  {
    cre->c_strikes = malloc(sizeof(char *) * (strikes + 1));
    if (!cre->c_strikes)
    {
      free_prot_c(cre);
      return (NULL);
    }
    i = 0;
    while (i <= strikes)
    {
      cre->c_strikes[i] = NULL;
      i++;
    }
    cre->u_strikes = malloc(sizeof(char *) * (strikes + 1));
    if (!cre->u_strikes)
    {
      free_prot_c(cre);
      return (NULL);
    }
    i = 0;
    while (i <= strikes)
    {
      cre->u_strikes[i] = NULL;
      i++;
    }
  }
  cre->att = 0;
  cre->def = 0;
  cre->strike = 0;
  cre->hp = hp;
  cre->obj = NULL;
  cre->line = 0;
  cre->c_death = NULL;
  cre->u_death = NULL;
  return (cre);
}

void  free_prot_c(c_node *cre)
{
  if (cre && cre != NULL)
  {
    if (cre->lines && cre->lines != NULL)
      free(cre->lines);
    if (cre->dialogue && cre->dialogue != NULL)
      free(cre->dialogue);
    if (cre->c_strikes && cre->c_strikes != NULL)
      free(cre->c_strikes);
    if (cre->u_strikes && cre->u_strikes != NULL)
      free(cre->u_strikes);
    free(cre);
  }
}

int fight(c_node *cre, u_node *user)
{
  int choice;
  char  a;

  while (cre->c_strikes[cre->strike] != NULL
    && cre->u_strikes[cre->strike] != NULL)
  {
    printer("\n\nUsing your ");
    if (user->equipped != NULL && user->equipped->mod > 0)
      printer(user->equipped->name);
    else
      printer("bare fists");
    printer(", ");
    printer(cre->u_strikes[cre->strike]);
    printer("\n|| You deal ");
    printer(cre->name);
    printer(" ");
    choice = user->att;
    if (user->equipped != NULL && user->equipped->mod > 0)
      choice = choice + user->equipped->mod;
    choice = choice - cre->def;
    a = (choice / 10) + 48;
    write(1, &a, 1);
    a = (choice % 10) + 48;
    write(1, &a, 1);
    printer("pts of damage.\n");
    cre->hp = cre->hp - choice;
    if (cre->hp <= 0)
    {
      if (cre->c_death != NULL)
        printer(cre->c_death);
      printer("\n|| ");
      printer(cre->name);
      printer(" is now dead.\n");
      return (2);
    }
    printer("\n\n");
    printer(cre->c_strikes[cre->strike]);
    choice = cre->att;
    if (user->equipped != NULL && user->equipped->mod < 0)
    {
      printer("\n|| Thanks to your ");
      printer(user->equipped->name);
      printer(", you only take ");
      choice = choice + user->equipped->mod;
    }
    else
      printer("\n|| They deal you ");
    a = (choice / 10) + 48;
    write(1, &a, 1);
    a = (choice % 10) + 48;
    write(1, &a, 1);
    printer("pts of damage.\n");
    user->hp = user->hp - choice;
    if (user->hp <= 0)
    {
      if (cre->u_death != NULL)
        printer(cre->u_death);
      printer("\n|| You are now dead.\n\n");
      return (0);
    }
    else
    {
      printer("|| You now have ");
      a = (user->hp / 10) + 48;
      write(1, &a, 1);
      a = (user->hp % 10) + 48;
      write(1, &a, 1);
      printer("hp.\n");
    }
    print_option("attack");
    choice = get_stdin_cmp("attack", cre->dialogue[cre->line], "go back", "quit");
    if (choice == 2 || choice == 3)
    {
      printer("\n\nWhat. Thought you could weasel your way out of this one ?\nI gave you a choice.\nYou wanted a fight. Now fight.\n");
      choice = 0;
    }
    while (choice == 0)
    {
      printer("Please pick one of the available options: \n");
      print_option("attack");
      printer("|| go back\n|| quit\n");
      choice = get_stdin_cmp("attack", cre->dialogue[cre->line], "go back", "quit");
      if (choice == 2 || choice == 3)
      {
        printer("\n\n|| What. Thought you could weasel your way out of this one ?\n|| I gave you a choice.\n|| You wanted a fight. Now fight.");
        choice = 0;
      }
    }
    if (choice == 4)
      return (0);
  }
  printer("\n\nBy some miracle, you manage to limp away from the fight while ");
  printer(cre->name);
  printer(" is distracted by their own pain.\n");
  return (1);
}

int interact(c_node *cre, u_node *user)
{
  int choice;

  printer("\nYou come face to face with ");
  printer(cre->name);
  printer(".\n");
  while (cre->lines[cre->line] != NULL)
  {
    print_option(cre->dialogue[cre->line]);
    print_option("attack");
    choice = get_stdin_cmp(cre->dialogue[cre->line], "attack", "go back", "quit");
    while (choice == 0)
    {
      printer("Please pick one of the available options: \n");
      print_option(cre->dialogue[cre->line]);
      print_option("attack");
      printer("|| go back\n|| quit");
      choice = get_stdin_cmp(cre->dialogue[cre->line], "attack", "go back", "quit");
    }
    if (choice == 4)
      return (0);
    if (choice == 3)
      return (-1);
    printer("\n\n");
    if (choice == 1)
    {
      printer(cre->lines[cre->line]);
      printer("\n");
    }
    else
      return (fight(cre, user));
    cre->line++;
  }
  return (1);
}
