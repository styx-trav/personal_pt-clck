#include "libby.h"

s_node  *create_game3(u_node *user)
{
  s_node  *start;
  s_node  *current;
  s_node  *current2;

  start = create_snode("It's dark.\nHow long have you been here - days, months ? Time went blurry eons ago - it always does. You know nothing now but the waiting, the never-ending loop of reaching for freedom only to be denied it, again, and again.\nAnd again.\nAnd again.\nAnd again.\nAnd -\n\nFootsteps. Faint, muffled, but coming.");
  start->choose_one = "struggle";
  start->choose_two = "wait";
  start->option2 = create_snode("You stay.\nQuiet and still, you listen to the steps as they grow louder, and louder...\nSomeone knocks on what must be the door holding you hostage.\n\"Someone in here ?\"they ask.");
  current = start->option2;
  current->choose_one = "struggle";
  current->choose_two = "wait";
  current->option1 = create_snode("Mind changed, you try to move, fight against your chains, alert them in some way.\nBut your body is slow, as though moving through molasses. You try to scream instead,\nbut your mouth is dry, and by the time a whimper comes out, the steps have gone. You listen as they fade away,\nfarther,\nfarther...\nuntil it is quiet again.");
  current->option2 = create_snode("You wait them out. They knock again,\nand again,\nand again,\nbut you have waited this long. You will wait them out if it's the last thing you do.\nEventually, though, they give up.\nYou hear the steps, getting fainter and fainter,\nuntil it is quiet again.");
  current->option1->choose_one = "wait";
  current->option2->choose_one = "wait";
  current->option1->option1 = create_snode("It's dark still.\nQuiet.\nYou're starting to wonder if maybe this is what death feels like.");
  current->option2->option1 = create_snode("It's dark still.\nQuiet.\nYou're starting to wonder if maybe this is what death feels like.");
  current2 = current->option2->option1;
  current = current->option1->option1;
  current->choose_one = "wait";
  current->option1 = create_snode("It is.\n");
  current = current->option1;
  current->damage = 25;
  current->damage_msg = "|| Hunger gnaws at you from the inside.\n|| It isn't long before your organs start failing,\ndehydrated as they are.\n|| Hallucinations start soon after.";
  current2->choose_one = "wait";
  current2->option1 = create_snode("It is.\n");
  current2 = current2->option1;
  current2->damage = 25;
  current2->damage_msg = "|| Hunger gnaws at you from the inside.\n|| It isn't long before your organs start failing,\ndehydrated as they are.\n|| Hallucinations start soon after.\n|| Your entire body grows numb, your breathing gets thinner...\n|| Everything goes dark.";
  start->option1 = create_snode("You attempt to scream, but not a sound comes out. Thankfully, the drag of metal against stone is enough to alert whoever is walking out there, because the steps are getting closer. You struggle even harder against your bonds, but you're running out of steam, and it's getting hard to breathe, and... and...\n...\n..\n.");
  current = start->option1;
  current->damage = 6;
  current->damage_msg = "|| You fight the chains holding you captive.\n|| It's hard, and slow - your muscles are atrophied, numb,\n|| and using so much energy is quickly draining you.";
  current->choose_one = "wake up";
  current->option1 = create_snode("Everything hurts. Ugh, even opening your eyelids is a hassle.\nIt's still dark, but...\nThere's enough light to see.\nThe ceiling looks like it's rocks - a cave, maybe ? And there's a shadow, moving across it, like someone's moving next to you.");
  current = current->option1;
  current->choose_one = "look left";
  current->choose_two = "look right";
  current->option1 = create_snode("That motherfucker.\nRight, next time.\n");
  current->option1->damage = 25;
  current->option1->damage_msg = "|| As you fight to turn your head to the side,\n|| a knife plunges into the side of your neck.\n|| Blood pours out of the wound,\n|| into your throat,\n|| into your lungs.";
  current->option2 = create_snode("end here for now.");
  current->option2->obj = 13;

  user->checkpoint = start;
  return (start);
}
