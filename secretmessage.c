#include <stdio.h>
#include <string.h>

#define MAX_ARGS 4

#define MIN_ARGS 2

#define MAX_LINE_LENGTH 1002

#define BUFFER 2

//Prints the help message when the "-h" argument is passed.
void printHelp() {
   printf("\nUsage: ./secretmessage [OPTION(S)] [SECRET MESSAGE] [FILE]\n\n");
   printf("Reads from an optional [FILE], or stdin by default, to find whether the\n");
   printf("[SECRET MESSAGE] can be found within the input. If it can be found,\n");
   printf("outputs the message within the input, omitting the characters not within the mesagge.\n\n");
   printf("If the message can't be found, outputs as much of the secret\n");
   printf("message as found and outputs \"Can't be found. :(\"\n\n");
   printf("Only looks for the alphabetic and numeric characters in the secret message.\n");
   printf("Lines of input greater than 1000 characters are not accepted.\n\n");
   printf("Options: \n");
   printf("\t-h\tprints the help page and exits.\n");
   printf("\t-v\tprints the line number and character index for each found line.\n");
   printf("\t-c\tprints the found output without empty lines.\n");
   printf("\t-e\tlook for EVERY character in the secret message.\n\n");
   printf("To use multiple options, use one argument with the \"-\"prefix\n");
   printf("followed by a combined string of option characters. The \"-h\" option\n");
   printf("will override the other arguments.\n");
}

//Checks to see if the character is alphabetic
int isalph(char suspect) {
   if ( (suspect >= 'A' && suspect <= 'Z') || (suspect >= 'a' && suspect <= 'z') ) {
      return 1;
   }
   return 0;
}

//Checks to see if the character is a numeric digit
int isdig(char suspect) {
   if (suspect >= '0' && suspect <= '9') {
      return 1;
   }
   return 0;
}


int main(int argc, char* argv[]) {
   if (argc < MIN_ARGS) {
      printf("Please pass a \"secret message\" to find as an argument\n");
      printf("See \"./secretmessage --help\" for more help\n");
      return 0;
   } else if (argc > MAX_ARGS) {
      printf("More than two arguments found \n");
      printf("See \"./secretmessage --help\" for more help\n");
      return 0;
   }
   char* options = argv[1];
   int verbose = 0;
   int condensed = 0;
   int includeall = 0;
   char* message;
   char* rdfile = NULL;
   //Checks if the first argument is an option
   if (options[0] == '-') {
      //Iterates through the possible argument options
      for (unsigned long i = 1; i < strlen(options); i++) {
         if (options[i] == 'v') {
            verbose = 1;
         } else if (options[i] == 'c') {
            condensed = 1;
         } else if (options[i] == 'e') {
            includeall = 1;
         } else if (options[i] == 'h') {
            printHelp();
            return 0;
         } else {
            printf("Unrecognized argument.\n");
            printf("See \"./secretmessage --help\" for more help\n");
            return 0;
         }
      }
      message = argv[2];
      if (argc > 3) {
         rdfile = argv[3];
      }
   } else {
      message = options;
      if (argc > 2) {
         rdfile = argv[2];
      }
   }

   //This is the current line of the input
   char currline[MAX_LINE_LENGTH];

   //This is the current character in the message we're checking against (mostly for clarity)
   char currval = message[0];

   //This is the current index of the character in the message we're checking
   unsigned long currindex = 0;

   //This is the eventual string we will print
   char prinlin[MAX_LINE_LENGTH] = { 0 };

   //These are all trackers for printing the verbose argument
   int linetrack = 0;
   int chartrack[MAX_LINE_LENGTH];
   unsigned long chartracksize = 0;

   //This is the file that the user can pass as an arg
   FILE* fp;
   if (rdfile) {
      fp = fopen(rdfile, "r");
      if (fp == NULL) {
         printf("Could not open file %s\n", rdfile);
         printf("See \"\\.secretmessage -h\" for more help.\n");
         return 0;
      }
   } else {
      fp = stdin;
   }

   //Iterates over all the lines in the input
   while (fgets(currline, MAX_LINE_LENGTH, fp) != NULL) {

      //Here, the BUFFER refers to the difference between the necessary line length needed to handle inputs
      //that are greater than 1000 characters (1002 since we need one for the null terminating char and one
      //to actaully check if there are any more than 1000 chars). 
      if (strlen(currline) > MAX_LINE_LENGTH - BUFFER) {
         printf("Sorry, secretmessage doesn't accept line inputs greater than 1000 characters.\n");
         printf("Remember that this includes newlines (\\n)\n");
         printf("See \".\\secretmessage -h\" for more help.\n");
         return 0;
      }

      //Iterates over all the characters in each line
      for (unsigned long i = 0; i < strlen(currline); i++) {

         //If the current char we're searching for in the input is found
         if (currline[i] == currval) {
            //Add that value to what we will print
            prinlin[i] = currval;

            //Track which index in the line it occurred at
            chartrack[chartracksize] = i;

            //Iterate the index of the message for the next value we're searching for
            currindex++;

            //Make the next currval equal to the message at this index
            currval = message[currindex];

            //Track how many times to print an index per line for the verbose arg
            chartracksize++;

            //If we want exclude grammatical characters
            if (!includeall) {
               //While we aren't at the end of the message and while we haven't hit a good currval
               while (currval > 0 && (!isalph(currval) && !isdig(currval))) {
                  //Iterate currval again
                  currindex++;
                  currval = message[currindex];
               }
            }
            //If we've hit the end of the message
            if (currval == 0) {
               break;
            }

         } else {
            //Add a space for the character in the input which isn't in the message (omitting it)
            prinlin[i] = ' ';
         }
      }
      linetrack++;
      //Checks how to format the output depending on arguments
      if(!condensed || chartracksize) {
         printf("%s\n", prinlin);
         if (verbose && chartracksize) {
	    printf("Line: %d\nChar Index(es): [", linetrack);
            for (unsigned long i = 0; i < chartracksize; i++) {
	       if (i == chartracksize - 1) {
                  printf("%d]\n", chartrack[i]);
               } else {
                  printf("%d,", chartrack[i]);
               }
	    }
	 }
      }
      //Resetting some values
      for (unsigned long i = 0; i < strlen(currline); i++) {
         prinlin[i] = ' ';
      }
      chartracksize = 0;
      if (currval == 0) {
         printf("Message found!\n");
         fclose(fp);
         return 0;
      }
   }
   printf("Can't be found. :(\n");
   fclose(fp);
   return 0;
}
