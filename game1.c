#include "libby.h"

s_node  *create_game(u_node *user)
{
  s_node  *game_head;
  s_node  *current;

  game_head = create_snode("This house is so beautiful. It's almost hard to believe I actually own it. Sure, the walls will need some renovations, but...\nStill. Beautiful.");
  if (game_head == NULL)
    return (NULL);
  game_head->option1 = create_snode("Ah, that familiar old house smell.\nOr could it be mold ? Hm.");
  game_head->option1->choose_one = "corridor";
  game_head->option1->choose_two = "stairs";
  game_head->option1->option1 = create_snode("I'm pretty sure this looked less decrepit when I visited, but hey, I can still see the vision !\nA little cleaning, some sky blue wallpaper... I could do something with this.");
  game_head->option1->option1->back = game_head->option1;
  game_head->option1->option2 = create_snode("I... don't think I can climb that. That doesn't look structurally sound.");
  game_head->option1->option1->choose_one = "door";
  game_head->option1->option1->option1 = create_snode("Okay. If I remember correctly, this should be the bathroom. Locked, though. Maybe there's a key around somewhere ?");
  game_head->option1->option1->option1->locked = 1;
  game_head->option1->option2->back = game_head->option1;
  game_head->choose_one = "enter";
  game_head->choose_two = "window";
  game_head->option2 = create_snode("Huh.\nYeah, that's... That's broken alright. I'll have to fix that.");
  game_head->option2->desc_obj = " Wait, is that... a key ?";
  game_head->option1->option1->option1->option1 = create_snode("So it might need a little visit from the plumber, okay. But the tiling is pretty cute, so...\nAt least there's that ?");
  game_head->option1->option1->option1->option1->back = game_head->option1->option1;
  game_head->option1->option1->option1->back = game_head->option1->option1;
  game_head->option2->obj = 1;
  user->obj_names[0] = "key";
  game_head->option2->choose_obj = "key";
  game_head->option1->back = game_head;
  game_head->option2->back = game_head;
  game_head->option1->option1->option1->option1->desc_obj = " There's a small ladder there, too.";
  current = game_head->option1->option1->option1->option1;
  current->obj = 2;
  current->choose_obj = "ladder";
  current = game_head->option1->option2;
  current->locked = 2;
  user->obj_names[1] = "ladder";
  current->option1 = create_snode("Whew! That's one hell of an attic. Can't see a thing in here. I'll need a light source.");
  current->option1->back = game_head->option1;
  current->option1->locked = 3;
  user->obj_names[2] = "flashlight";
  current->option1->option1 = create_snode("Wow. All these paintings, the old furnitures... Hey, there's even some curtains over there ! And... a door ?");
  current = current->option1->option1;
  current->choose_one = "door";
  current->back = game_head->option1;
  current->option1 = create_snode("Oh, my god ! Is that... ?\n\nBOOM!\n\n");
  current->option1->obj = 13;
  current = game_head->option1->option1;
  current->option2 = create_snode("Brr.\nThis place gives me the creeps...");
  current->choose_two = "cellar";
  current->option2->back = current;
  current = current->option2;
  current->obj = 3;
  current->desc_obj = " Ah! There, a flashlight.";
  current->choose_obj = "flashlight";
  //user->checkpoint = game_head;
  return (game_head);
}
