#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Create a char and an int to calculate ASCII number
    char c;
    int result = 0;
    // Get a random number between 92 and 125
    while(result == 0) {
      int ascii = (rand() % 94 + 32);
      if (ascii == 32 || ascii == 40 || ascii == 41 || ascii == 91 || ascii == 93
          || ascii == 97 || ascii == 120 || ascii == 123 || ascii == 125) {
            // Assign the char to that ASCII number
            c = ascii;
            result = 1;
      }

    }
    return c;
}

char *inputString()
{
    char *string = malloc(6*sizeof(char));
    int i, ascii;
    for (i = 0; i < 5; i++) {
      ascii = (rand() % 17 + 101);
      string[i] = ascii;
    }
    string[5] = '\0';
    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
