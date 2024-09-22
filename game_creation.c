#include "libby.h"

s_node  *create_snode(char *desc)
{
  s_node  *new_item;

  new_item = (s_node *)malloc(sizeof(s_node));
  if (new_item == NULL)
    return (NULL);
  new_item->desc = desc;
  new_item->choose_one = NULL;
  new_item->choose_two = NULL;
  new_item->choose_three= NULL;
  new_item->desc_choices = NULL;
  new_item->option1 = NULL;
  new_item->option2 = NULL;
  new_item->back = NULL;
  return (new_item);
}

void  free_prot(s_node  *head)
{
  if (head->desc != NULL)
    free(head->desc);
  if (head->desc_choices != NULL)
    free(head->desc_choices);
  if (head->choose_one != NULL)
    free(head->choose_one);
  if (head->choose_two != NULL)
    free(head->choose_two);
  if (head->choose_three != NULL)
    free(head->choose_three);
  if (head->option1 != NULL)
    free_prot(head->option1);
  if (head->option2 != NULL)
    free_prot(head->option2);
  free(head);
}

char  *translate_str(char *str)
{
  char  *new_str;
  int i;
  int len;

  i = 0;
  while (str[i])
    i++;
  len = i;
  i = 0;
  new_str = malloc(sizeof(char) * (len + 1));
  if (new_str == NULL)
    return (NULL);
  while (i <= len)
  {
    new_str[i] = str[i];
    i++;
  }
  return (new_str);
}

s_node  *create_game(void)
{
  s_node  *game_head;
  char  *description;

  game_head = create_snode(translate_str("This house is so beautiful. It's almost hard to believe I actually own it. Sure, the walls will need some renovations, but...\nStill. Beautiful."));
  if (game_head == NULL)
    return (NULL);
  game_head->desc_choices = translate_str("enter  window");
  game_head->option1 = create_snode(translate_str("Ah, that familiar old house smell.\nOr could it be mold ? Hm."));
  game_head->option1->desc_choices = translate_str("corridor  stairs");
  game_head->option1->choose_one = translate_str("corridor");
  game_head->option1->choose_two = translate_str("stairs");
  game_head->option1->option1 = create_snode(translate_str("I'm pretty sure this looked less decrepit when I visited, but hey, I can still see the vision !\nA little cleaning, some sky blue wallpaper... I could do something with this."));
  game_head->option1->option1->back = game_head->option1;
  game_head->option1->option2 = create_snode(translate_str("I... don't think I can climb that. That doesn't look structurally sound."));
  game_head->option1->option2->back = game_head->option1;
  game_head->choose_one = translate_str("enter");
  game_head->choose_two = translate_str("window");
  game_head->option2 = create_snode(translate_str("Huh.\nYeah, that's... That's broken alright. I'll have to fix that."));
  game_head->option1->back = game_head;
  game_head->option2->back = game_head;
  return (game_head);
}

int main (void)
{
  s_node  *head;

  head = create_game();
  if (head != NULL)
  {
    read_game(head);
    free_prot(head);
  }
}
