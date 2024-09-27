#include "libby.h"

s_node  *create_game(u_node *user)
{
  s_node  *start;
  s_node  *current;

  start = create_snode("a blank room. escape.");
  if (start == NULL)
    return (NULL);
  user->checkpoint = start;
  start->choose_one = "left";
  start->choose_two = "right";
  start->option1 = create_snode("a yellow room.");
  if (start->option1 == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  start->option1->desc_obj = " and a key, there. in the corner.";
  start->option1->obj = create_onode("red key\0", -2, 0);
  start->option1->back = start;
  start->option2 = create_snode("a red room. it's locked.");
  if (start->option2 == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  start->option2->back = start;
  start->option2->locked = "red key\0";
  start->option2->locked_desc = "You open the door using your red key.";
  start->option2->unlocks = create_snode("a chest ! and a blue door.");
  if (start->option2->unlocks == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  start->option2->unlocks->back = start;
  start->option2->unlocks->choose_one = "chest";
  current = start->option2->unlocks;
  current->obj = create_onode("sword\0", 6, 0);
  current->desc_obj = " and a... sword ? right there, in the corner.";
  current->option1 = create_snode("it's a trap !");
  if (current->option1 == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  current->option1->back = current;
  current = current->option1;
  current->damage = 12;
  current->damage_msg = "|| there was a bomb in the chest.";
  current = start->option2->unlocks;
  current->choose_two = "blue door";
  current->option2 = create_snode("the door opens on a shadowy figure.\nthey look...\nthe creature appears to have multiple heads and too-long necks, covered in some weird purple slime. It gurgles at you as you instinctively step back.");
  if (current->option2 == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  current->option2->back = current;
  return (start);
}
