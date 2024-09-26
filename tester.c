#include "libby.h"

s_node  *create_game(u_node *user)
{
  s_node  *start;

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
  start->option1->obj = create_onode("red key\0", 0, 0);
  start->option1->back = start;
  start->option2 = create_snode("a red room. it's locked.");
  if (start->option2 == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  start->option2->back = start;
  start->option2->locked = "red key\0";
  start->option2->unlocks = create_snode("a chest !\ngood job.");
  if (start->option2->unlocks == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  start->option2->unlocks->back = start;
  return (start);
}
