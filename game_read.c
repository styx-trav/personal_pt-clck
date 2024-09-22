#include "libby.h"

int cmp(char *str, char *str2)
{
  int i;

  if (str == NULL)
    return (1);
  i = 0;
  while (str[i] && str2[i] && str2[i] == str[i])
    i++;
  if (str[i] == '\0'
    && (str2[i] == '\0' || (str2[i] == '\n' && str2[i +1] == '\0')))
    return (0);
  else
    return (1);
}

int compare(char *opt1, char *opt2, char *read)
{
  char  *quit;
  char  *go_back;

  quit = malloc(sizeof(char) * 5);
  if (quit == NULL)
    return (-1);
  quit[0] = 'q';
  quit[1] = 'u';
  quit[2] = 'i';
  quit[3] = 't';
  quit[4] = '\0';
  go_back = malloc(sizeof(char) * 8);
  go_back[0] = 'g';
  go_back[1] = 'o';
  go_back[2] = ' ';
  go_back[3] = 'b';
  go_back[4] = 'a';
  go_back[5] = 'c';
  go_back[6] = 'k';
  go_back[7] = '\0';
  if (cmp(quit, read) == 0)
  {
    free(quit);
    free(go_back);
    return (-1);
  }
  free(quit);
  if (cmp(go_back, read) == 0)
  {
    free(go_back);
    return (4);
  }
  free(go_back);
  if (cmp(opt1, read) == 0)
    return (1);
  if (cmp(opt2, read) == 0)
    return (2);
  //if (cmp(opt3, read) == 0)
    //return (3);
  return (0);
}

int  get_stdin(char *opt1, char *opt2)
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
  i = compare(opt1, opt2, str);
  free(str);
  return (i);
}

void  read_game(s_node  *head)
{
  int choice;

  if (head->desc == NULL)
    return ;
  printf("\n\n%s\n\n", head->desc);
  if (head->desc_choices != NULL)
    printf("%s\n\n", head->desc_choices);
  choice = 0;
  choice = get_stdin(head->choose_one, head->choose_two);
  while (choice == 0)
  {
    write(1, "\n\nPlease choose one of the given options:\n", 42);
    if (head->desc_choices != NULL)
      printf("%s  go back  quit\n", head->desc_choices);
    else
      write(1, "go back  quit\n", 14);
    choice = get_stdin(head->choose_one, head->choose_two);
  }
  if (choice == 1 && head->option1 != NULL)
    read_game(head->option1);
  if (choice == 2 && head->option2 != NULL)
    read_game(head->option2);
  //if (choice == 3 && head->option3 != NULL)
    //read_game(head->option3);
  if (choice == 4)
  {
    if (head->back != NULL)
      read_game(head->back);
    else
    {
      printf("\nYou're at the start point.");
      read_game(head);
    }
  }
  return ;
}
