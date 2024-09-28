#include "libby.h"

s_node  *create_game(u_node *user)
{
  s_node  *start;
  s_node  *current;
  c_node  *cre;

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
  current = current->option2;
  current->char_cre = create_cnode("The Hydra", 3, 2, 12);
  if (current->char_cre == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  current->option1 = create_snode("Aaand that's it. The Hydra lets you through, you reach a door, you open it.\n|| now quit.");
  if (current->option1 == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  current->option1->back = current->back;
  cre = current->char_cre;
  cre->dialogue[0] = "approach";
  cre->lines[0] = "You attempt to communicate to the creature that you mean no harm. With your hands held up, you approach it slowly.\nIt gurgles.";
  cre->dialogue[1] = "reach";
  cre->lines[1] = "Though you are still so afraid, you lower your hands, slowly extending one towards the creature. Two of the heads lean closer to sniff it, curious.";
  cre->dialogue[2] = "touch";
  cre->lines[2] = "You cup the palm of your hand on the... ridge of a head's nose, you think. It's slimey, and gross.\nIt nuzzles up to you, though.\nFriendly.";
  cre->u_strikes[0] = "you go for the throat closest to you. You strike it hard, and fast.\nThe impact of it ripples through your arm and spreads searing pain into your shoulder.";
  cre->c_strikes[0] = "One of the heads descends upon you, slicing through the air with harrowing precision.\nIn one clean movement, it opens its maw big enough to swallow you whole.\nYou can see the back of its throat, every overly long, overly sharp fang, drool dripping onto its gums...\nIt bites right into to meat of your right shoulder.";
  cre->att = 13;
  cre->def = 0;
  cre->u_strikes[1] = "You struggle against the hold of the jaw clapsed into your quickly shattering shoulder blade to try and land a blow on your foe.\nAlthough wonky, you manage to land a hit straight into another head's eye. The surface of it breaks under the pressure.\nBlood sprays everywhere like an impromptu fountain, some of it getting into your mouth.\nTastes like copper and death.";
  cre->c_strikes[1] = "Enraged, the head already chomping through your bones shakes, ripping through every existing layer of flesh and blood.\nWith one last, enormously strong swing, the head throws you across the room. Your back cracks ominously against the wall right before you drop to the ground.\nYour arms are numb.\nSo too your legs, and your back.\nYour face.";
  cre->u_death = "It's a gruesome death for the likes of us.";
  cre->c_death = "In a howl of pain, the hydra drops dead, into a sad, angry pile of slimey necks, broken fangs, and blood.";
  current->unlocks = create_snode("The hydra lies at your feet, defeated. In the dead remnants of it, you catch a glimpse of a soft, pink glow.\nYou bleed still from your shoulder and back, but you live.\nFor now.");
  if (current->unlocks == NULL)
  {
    free_prot(start);
    return(NULL);
  }
  current->unlocks->back = current->back;
  return (start);
}
