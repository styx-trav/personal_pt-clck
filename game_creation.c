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
  if (head->desc != NULL)
    free(head->desc);
  if (head->desc_obj != NULL)
    free(head->desc_obj);
  if (head->choose_one != NULL)
    free(head->choose_one);
  if (head->choose_two != NULL)
    free(head->choose_two);
  if (head->choose_obj != NULL)
    free(head->choose_obj);
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

s_node  *create_game(u_node *user)
{
  s_node  *game_head;
  s_node  *current;

  game_head = create_snode(translate_str("This house is so beautiful. It's almost hard to believe I actually own it. Sure, the walls will need some renovations, but...\nStill. Beautiful."));
  if (game_head == NULL)
    return (NULL);
  game_head->option1 = create_snode(translate_str("Ah, that familiar old house smell.\nOr could it be mold ? Hm."));
  game_head->option1->choose_one = translate_str("corridor");
  game_head->option1->choose_two = translate_str("stairs");
  game_head->option1->option1 = create_snode(translate_str("I'm pretty sure this looked less decrepit when I visited, but hey, I can still see the vision !\nA little cleaning, some sky blue wallpaper... I could do something with this."));
  game_head->option1->option1->back = game_head->option1;
  game_head->option1->option2 = create_snode(translate_str("I... don't think I can climb that. That doesn't look structurally sound."));
  game_head->option1->option1->choose_one = translate_str("door");
  game_head->option1->option1->option1 = create_snode(translate_str("Okay. If I remember correctly, this should be the bathroom. Locked, though. Maybe there's a key around somewhere ?"));
  game_head->option1->option1->option1->locked = 1;
  game_head->option1->option2->back = game_head->option1;
  game_head->choose_one = translate_str("enter");
  game_head->choose_two = translate_str("window");
  game_head->option2 = create_snode(translate_str("Huh.\nYeah, that's... That's broken alright. I'll have to fix that."));
  game_head->option2->desc_obj = translate_str(" Wait, is that... a key ?");
  game_head->option1->option1->option1->option1 = create_snode(translate_str("So it might need a little visit from the plumber, okay. But the tiling is pretty cute, so...\nAt least there's that ?"));
  game_head->option1->option1->option1->option1->back = game_head->option1->option1;
  game_head->option1->option1->option1->back = game_head->option1->option1;
  game_head->option2->obj = 1;
  user->obj_names[0] = translate_str("key");
  game_head->option2->choose_obj = translate_str("key");
  game_head->option1->back = game_head;
  game_head->option2->back = game_head;
  game_head->option1->option1->option1->option1->desc_obj = translate_str(" There's a small ladder there, too.");
  current = game_head->option1->option1->option1->option1;
  current->obj = 2;
  current->choose_obj = translate_str("ladder");
  current = game_head->option1->option2;
  current->locked = 2;
  user->obj_names[1] = translate_str("ladder");
  current->option1 = create_snode(translate_str("Whew! That's one hell of an attic. Can't see a thing in here. I'll need a light source."));
  current->option1->back = game_head->option1;
  current->option1->locked = 3;
  user->obj_names[2] = translate_str("flashlight");
  current->option1->option1 = create_snode(translate_str("Wow. All these paintings, the old furnitures... Hey, there's even some curtains over there ! And... a door ?"));
  current = current->option1->option1;
  current->choose_one = translate_str("door");
  current->back = game_head->option1;
  current->option1 = create_snode(translate_str("Oh, my god ! Is that... ?\n\nBOOM!\n\n"));
  current->option1->obj = 13;
  current = game_head->option1->option1;
  current->option2 = create_snode(translate_str("Brr.\nThis place gives me the creeps..."));
  current->choose_two = translate_str("cellar");
  current->option2->back = current;
  current = current->option2;
  current->obj = 3;
  current->desc_obj = translate_str(" Ah! There, a flashlight.");
  current->choose_obj = (translate_str("flashlight"));
  return (game_head);
}

int main (void)
{
  s_node  *head;
  u_node  *user;

  user = create_user();
  head = create_game(user);
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
