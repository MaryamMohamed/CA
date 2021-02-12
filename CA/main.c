#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

/*Function to replace a string with another string*/
//-----------------------------1----------------------------- mmdouh
char *replace_word(const char *s, const char *old, const char *new1)
{
    char *ret;
    int a, count = 0;
    int newlen = strlen(new1);
    int oldlen = strlen(old);

    for (a = 0; s[a] != '\0'; a++)
    {
        if (strstr(&s[a], old) == &s[a])
        {
            count++;
            a += oldlen - 1;
        }
    }
    ret = (char *)malloc(a + count * (newlen - oldlen));
    if (ret == NULL)
        exit(EXIT_FAILURE);
    a = 0;
    while (*s)
    {
        if (strstr(s, old) == s) //compare the substring with the newstring
        {
            strcpy(&ret[a], new1);
            a += newlen; //adding newlength to the new string
            s += oldlen;//adding the same old length the old string
        }
        else
        ret[a++] = *s++;
    }
    ret[a] = '\0';
    return ret;
}

// function that calculate frequency of each charachter
//-----------------------------2----------------------------- mmdouh
void char_frequency(char para[], int count[]) {
   int charac = 0;
   while (para[charac]) {
      if (para[charac] >= 'a' && para[charac] <= 'z' )
         count[para[charac]-'a']++;
      charac++;
   }
}

int main()
{
    //-----------------------------3----------------------------- //hossam
    char para[150];
    char  c1[10], d[10];
    int i, c, count[26] = {0};

   printf("Enter Your Paragraph:");
   gets(para);

   //-----------------------------4----------------------------- hamada
   //convert paragraph to lowercase
   for(i=0; i<= strlen(para) ; i++){
      if(para[i]>=65&&para[i]<=90)
         para[i]=para[i]+32;
   }

   //print paragraph after converting it to lowercase
   printf("Your Entered Paragraph is: %s \n", para);

   //-----------------------------5----------------------------- shawky
    printf("\n////////////// characters frequency ////////////// \n");
   //count all characters
   char_frequency(para, count);

   //print characters that count not equal 0
   printf("\n\nCharacter Frequency:\n");
   for (c = 0 ; c < 26 ; c++){
    if(count[c] != 0){
        printf("%c \t  %d\n", c + 'a', count[c]);
    }
   }

   //-----------------------------6.1----------------------------- maryam
    printf("\n\n////////////// words frequency ////////////// \n");
   int space = 0;

   // count number of spaces or dots or commas
    for (i = 0;i<strlen(para);i++)
    {
        if ((para[i] == ' ')||(para[i] == ',' && para[i+1] == ' ')||(para[i] == '.')||(para[i] == ',')||(para[i] == ':')||(para[i] == ':' && para[i+1] == ' '))
        {
            space++;
        }
    }

    int character=0, words=0, j=0;
    char listOfWords [25][100]={0};
    // split each word of paragraph on 2D array
    for (character = 0, j = 0, words = 0;j < strlen(para);j++)
    {
        if ((para[j] == ' ')||(para[j] == ',')||(para[j] == '.')||(para[j] == ':')||(para[j] == ',' && para[j+1] == ' ')||(para[j] == ':' && para[j+1] == ' '))
        {
            listOfWords[character][words] = '\0';
            character++;
            words = 0;
        }
        else
             listOfWords[character][words++] = para[j];
    }

    //-----------------------------6.2----------------------------- maryam
    // count number of each word
    int k = 0, counter=0;
    char copyOfListOfWords[25][100]={0};
    for (i = 0;i <= space;i++)
    {
        for (j = 0;j <= space;j++)
        {
            if (i == j)
            {
                strcpy(copyOfListOfWords[k], listOfWords[i]);
                k++;
                counter++;
            }
            else
            {
                if (strcmp(copyOfListOfWords[j], listOfWords[i]) != 0)
                    continue;
                else
                    break;
            }
        }
    }

    //print frequency of each word
    printf("\nWord Frequency:\n");
    int c2=0;
    for (i = 0;i < counter;i++)
    {
        for (j = 0;j <= space;j++)
        {
            if (strcmp(copyOfListOfWords[i], listOfWords[j]) == 0)
                c2++;
        }
        printf("%s %d \n", copyOfListOfWords[i], c2);
        c2 = 0;
    }

    //-----------------------------7----------------------------- mahmoud
    printf("\n////////////// all characters with frequency 1 and 2 and 3 ////////////// \n");
    for (c = 0 ; c < 26 ; c++){
    if(count[c] == 1 || count[c] == 2 || count[c] == 3){
        printf("%c \t  %d\n", c + 'a', count[c]);
    }
   }

   //-----------------------------8----------------------------- shawky
   printf("\n////////////// all words with frequency 1 and 2 and 3 ////////////// \n");
   for (i = 0;i < counter;i++)
    {
        for (j = 0;j <= space;j++)
        {
            if (strcmp(copyOfListOfWords[i], listOfWords[j]) == 0)
                c2++;
        }
        if(c2 == 1 || c2 == 2 || c2 == 3)
        {
            printf("%s %d \n", copyOfListOfWords[i], c2);
            c2 = 0;
        }
    }

    //-----------------------------9----------------------------- mahmoud
    printf("\n////////////// search for a word or character ////////////// \n");
     //search on a specific word/character and get all results
    char word[MAX_SIZE];
    int x, y, found;
    int strLen, wordLen;

    /* Input string and word from user */
    printf("\nEnter any word or character to search: ");
    gets(word);

    strLen  = strlen(para);  // Find length of string
    wordLen = strlen(word); // Find length of word

    /*
     * Run a loop from starting index of string to
     * length of string - word length
     */
    for(x=0; x<=(strLen - wordLen); x++)
    {
        // Match word at current position
        found = 1;
        for(y=0; y<wordLen; y++)
        {
            // If word is not matched
            if(para[x + y] != word[y])
            {
                found = 0;
                break;
            }
        }

        // If word have been found then print found message
        if(found == 1)
        {
            printf("'%s' found at index: %d \n", word, x);
        }
    }

    //-----------------------------10----------------------------- mmdouh
    printf("\n////////////// find and replace a word or character ////////////// \n");

     //find and replace for a character or word
     printf("\nEnter the character or word to be replaced:\n");
    scanf(" %s",c1);
    printf("Enter the new character:\n");
    scanf(" %s",d);
    char *newstr = NULL;

    newstr = replace_word(para, c1,d);
    printf("\nThe new paragraph is: %s\n", newstr);
    free(newstr);

    /////////////////////////////////////////////////////////////////////
   return 0;
}
