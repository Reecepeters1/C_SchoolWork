#include <stdio.h>
#include <string.h>

#define MAX_ARGS 3
#define MAX_LINE_LENGTH 1002
#define BUFFER 2

void printHelp()
{
   printf("\nUsage: ./heapify [OPTION(S)] [FILE]\n\n");
   printf("Reads from an optional [FILE], or stdin by default, to convert the\n");
   printf("input into a max heap array based on ASCII character codes.\n");
   printf("Will sort all characters input. Separating said character is not necessary.\n");
   printf("Lines of input greater than 1000 characters are not accepted.\n\n");
   printf("Options: \n");
   printf("\t-h\tprints the help page and exits.\n");
   printf("\t-v\tprints the specifc heap building insert by insert.\n");
   printf("\t-p\tswitches the array default implentation to using pointers.\n");
   printf("To use multiple options, use one argument with the \"-\"prefix\n");
   printf("followed by a combined string of option characters. The \"-h\" option\n");
   printf("will override the other arguments. Press Ctrl+D on an empty line to exit.\n");
}

int main(int argc, char *argv[])
{

   if (argc > MAX_ARGS)
   {
      printf("Please input less arguments.\n");
      printf("See \"./heapify -h\" for more help\n");
      return 0;
   }

   int pointer = 0;
   int verbose = 0;
   char *rdfile = NULL;

   if (argc > 1)
   {
      char *options = argv[1];

      if (options[0] == '-' && strlen(options) > 1)
      {
         //Iterates through the possible argument options
         for (unsigned long i = 1; i < strlen(options); i++)
         {
            if (options[i] == 'v')
            {
               verbose = 1;
            }
            else if (options[i] == 'p')
            {
               pointer = 1;
            }
            else if (options[i] == 'h')
            {
               printHelp();
               return 0;
            }
            else
            {
               printf("Unrecognized argument.\n");
               printf("See \"./heapify -h\" for more help\n");
               return 0;
            }
         }
         if (argc > 2)
         {
            rdfile = argv[2];
         }
      }
      else
      {
         rdfile = argv[1];
      }
   }

   FILE *fp;
   if (rdfile)
   {
      fp = fopen(rdfile, "r");
      if (fp == NULL)
      {
         printf("Could not open file %s\n", rdfile);
         printf("See \"./heapify.c -h\" for more help.\n");
         return 0;
      }
   }
   else
   {
      fp = stdin;
   }

   char currline[MAX_LINE_LENGTH];
   char heapy[MAX_LINE_LENGTH];

   while (fgets(currline, MAX_LINE_LENGTH, fp) != NULL)
   {
      if (strlen(currline) > MAX_LINE_LENGTH - BUFFER)
      {
         printf("Sorry, heapify doesn't accept line inputs greater than 1000 characters.\n");
         printf("Remember that this includes newlines (\\n)\n");
         printf("See \"./heapify -h\" for more help.\n");
         return 0;
      }

      int ind = 0;
      char workingchar;
      if (pointer)
      {
         while ((workingchar = *(currline + ind)) != 0 && (workingchar != '\n'))
         {

            *(heapy + ind) = workingchar;
            if (verbose)
            {
               printf("Inserting %c...\n", workingchar);
            }
            char swap;
            int lastind = ind;
            while (*(heapy + lastind) > *(heapy + ((lastind - 1) / 2)))
            {
               if (verbose)
               {
                  printf("Percolating %c up...\n", *(heapy + lastind));
               }
               swap = *(heapy + ((lastind - 1) / 2));
               *(heapy + ((lastind - 1) / 2)) = *(heapy + lastind);
               *(heapy + lastind) = swap;
               lastind = (lastind - 1) / 2;
            }

            ind++;
         }

         printf("\n[");
         for (int i = 0; i < ind; i++)
         {
            if (i != ind - 1)
            {
               printf("%c,", *(heapy + i));
            }
            else
            {
               printf("%c]\n", *(heapy + i));
            }
         }
      }
      else
      {
         while ((workingchar = currline[ind]) != 0 && (workingchar != '\n'))
         {
            heapy[ind] = workingchar;
            if (verbose)
            {
               printf("Inserting %c...\n", workingchar);
            }
            char swap;
            int lastind = ind;
            while (heapy[lastind] > heapy[(lastind - 1) / 2])
            {
               if (verbose)
               {
                  printf("Percolating %c up...\n", heapy[lastind]);
               }
               swap = heapy[(lastind - 1) / 2];
               heapy[(lastind - 1) / 2] = heapy[lastind];
               heapy[lastind] = swap;
               lastind = (lastind - 1) / 2;
            }

            ind++;
         }

         printf("\n[");
         for (int i = 0; i < ind; i++)
         {
            if (i != ind - 1)
            {
               printf("%c,", heapy[i]);
            }
            else
            {
               printf("%c]\n", heapy[i]);
            }
         }
      }
   }
}
