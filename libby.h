#ifndef LIBBY_H
# define LIBBY_H "libby.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct  scene_node
{
  int obj;
  int locked;
  char  *desc;
  char  *desc_obj;
  char  *desc_locked;
  char  *choose_one;
  char  *choose_two;
  char  *choose_obj;
  struct scene_node *option1;
  struct scene_node *option2;
  struct scene_node *back;
}               s_node;

typedef struct  user_node
{
  char  *name;
  int *obj_tab;
  char  **obj_names;
}               u_node;

//from game_read.c, my list reading function
void  read_game(s_node *head, u_node *user);

//from user.c, creation, reading and release
u_node  *create_user(void);
void  read_user(u_node  *user);
void  free_prot_u(u_node  *user);

//from printing.c, disp functions:
void  printer(char *str);
void  print_option(char *str);

//from user_interactions.c, the read and filter function
int  get_stdin(char *opt1, char *opt2, char *obj);

#endif
