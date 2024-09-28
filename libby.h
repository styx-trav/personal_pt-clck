#ifndef LIBBY_H
# define LIBBY_H "libby.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct  obj_node
{
  char  *name;
  int mod;
  int have_it;
}               o_node;

typedef struct  charcre_node
{
  char  *name;
  char  **lines;
  char  **dialogue;
  char  **c_strikes;
  char  **u_strikes;
  char  *c_death;
  char  *u_death;
  o_node  *obj;
  int line;
  int strike;
  int att;
  int def;
  int hp;
}               c_node;

typedef struct  scene_node
{
  int damage;
  char  *damage_msg;
  char  *desc;
  char  *locked_desc;
  char  *desc_obj;
  char  *choose_one;
  char  *choose_two;
  char  *locked;
  struct scene_node *option1;
  struct scene_node *option2;
  struct scene_node *back;
  struct scene_node *unlocks;
  c_node  *char_cre;
  o_node  *obj;
}               s_node;

typedef struct  user_node
{
  char  *name;
  o_node  *equipped;
  o_node  **objs;
  s_node  *checkpoint;
  int hp;
  int att;
  int i;
}               u_node;

//from game_read.c, my list reading function
void  read_game(s_node *head, u_node *user);

//from user.c, creation, reading and release
u_node  *create_user(int tab);
void  read_user(u_node  *user);
void  free_prot_u(u_node  *user);

//from printing.c, disp functions:
void  printer(char *str);
void  print_option(char *str);
void  name_printer(char *str, char *name);
void  damage_printer(u_node *user, int damage, char *msg);

//from user_interactions.c, the read and filter function, and the cmp function
int  get_stdin(char *opt1, char *opt2, char *obj);
int cmp(char *str, char *str2);

//from help.c, my rulebook and the cmp for up tp 4 strings
void  help(int once);
int get_stdin_cmp(char *str1, char *str2, char *str3, char* str4);

//from game1.c, the haunted house
//s_node  *create_game1(u_node *user);
//from game2.c, the half-baked fantasy universe
//s_node  *create_game2(u_node *user);
//from game3.c, the prisoner
//s_node  *create_game3(u_node *user);
//from tester.c, a test
s_node  *create_game(u_node *user);

//from game_creation.c, elmt creating and freeing
s_node  *create_snode(char *desc);
void  free_prot(s_node  *head);

//from user.c, creating objects
o_node  *create_onode(char *name, int mod, int have_it);

//from inventory.c, usage
int  inventory(s_node *room, u_node *user);

//from char_cre.c, interacting (dialogue-only), creation and free
int interact(c_node *cre, u_node *user);
c_node  *create_cnode(char  *name, int lines, int strikes, int hp);
void  free_prot_c(c_node *cre);

#endif
