#include "libby.h"

int get_stdin_cmp(char *str1, char *str2, char *str3, char* str4)
{
  char  *str;
  char  buffer[37];
  int i;

  i = 0;
  while (i < 37)
  {
    buffer[i] = '\0';
    i++;
  }
  read(1, buffer, 36);
  i = 0;
  while (buffer[i] != '\0')
    i++;
  str = malloc(sizeof(char) * (i + 1));
  i = 0;
  if (str == NULL)
    return (0);
  while (buffer[i] != '\0')
  {
    str[i] = buffer[i];
    i++;
  }
  str[i] = '\0';
  if (cmp(str1, str) == 0)
  {
    free(str);
    return (1);
  }
  if (cmp(str2, str) == 0)
  {
    free(str);
    return (2);
  }
  if (cmp(str3, str) == 0)
  {
    free(str);
    return (3);
  }
  if (cmp(str4, str) == 0)
  {
    free(str);
    return (4);
  }
  free(str);
  return (0);
}

void  disp_help(int choice)
{
  if (choice == 1)
    printer("\nTo use an item, you must first travel to where you want to use it.\nOnce that's done, you can type check your inventory for the item, and then type that in the terminal to use it !\n\n\0");
  if (choice == 2)
    printer("\nTo quit, at any time, simply type 'quit' until the game closes.\n\n\0");
  if (choice == 3)
    printer("\nThough it is not always displayed on the screen, you can always go back from a room or inventory by typing 'go back'.\n\n\0");
  if (choice == 4)
    printer("\nTo use your inventory, or an item inside of it, simply type 'inventory'. The game will tell you which items you have, just type them in to use them !\n\n\0");
}

void  help(int once)
{
  int choice;

  if (once == 0)
  {
    printer("\n\nWelcome to the rulebook !\nTo play, you can type in the options on the screen, for example:\n|| continue\n\0");
    if (get_stdin_cmp("continue", NULL, NULL, NULL) == 1)
      printer("\nGreat job ! Let's see what else you can do.\n\0");
    else
      help(0);
  }
  choice = 0;
  while (choice == 0)
  {
    printer("\nYou can access this book any time, just type 'help'.\n\nHow can I help ?\n\0");
    print_option("items\0");
    print_option("quit\0");
    print_option("going back\0");
    print_option("inventory\0");
    choice = get_stdin_cmp("items", "quit", "going back", "inventory");
  }
  disp_help(choice);
}
