#ifndef LIBBY_H
# define LIBBY_H "libby.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct  scene_node
{
  int obj;
  char  *desc;
  char  *desc_choices;
  char  *choose_one;
  char  *choose_two;
  char  *choose_three;
  struct scene_node *option1;
  struct scene_node *option2;
  struct scene_node *back;
}               s_node;

//from game_read, my list reading function
void  read_game(s_node  *head);

#endif
