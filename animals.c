#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_utils.h"

#define BOOL int
#define TRUE 1
#define FALSE 0

NODE *root = NULL;

// Returns true if user types "yes" or "y" (upper or lower case)
// and returns false if user types "no" or "n". Keeps
// prompting otherwise.

BOOL yes_response()
{
  char str[50];

  scanf("%s", str);

    if (strcasecmp(str,"yes")==0 || strcasecmp(str,"y")==0) {
      return 1;
    }

    else if (strcasecmp(str,"no")==0 || strcasecmp(str,"n")==0) {
      return 0;
    }

    else {
      printf("\n Please enter \"yes\" or \"no\" >\n");
      yes_response();
    }
}

// This procedure creates a new NODE and copies
// the contents of string s into the
// question_or_animal field.  It also initializes
// the left and right fields to NULL.
// It should return a pointer to the new node

NODE *new_node(char *s)
{
  NODE *new_n =(NODE*) malloc(sizeof(NODE));
  strcpy(new_n->question_or_animal, s);
  new_n->left = NULL;
  new_n->right = NULL;
  return new_n;

}

// This is the procedure that performs the guessing.
// If the animal is not correctly guessed, it prompts
// the user for the name of the animal and inserts a
// new node for that animal into the tree.

void guess_animal()
{  // If the root is NULL, then there are no animals in
  // the tree. Prompt the player for the name of an
  // animal, create a node for that animal, and make
  // that node the root of the tree.
  char str[200];
  char strg[200];
  char strq[200];
  char strn[200];
  int check =3;
  int checkloop=9;
  int checkroot=3;
  if (root==NULL) {
    printf("\nWhat animal were you thinking of: \n");
    scanf("%s", str);
    NODE *new = new_node(str);
  }

  /*
    Otherwise (i.e. if the root is not NULL)
    Then descend down the tree. At each node encountered:

    If the left and right fields of the node are not NULL, i.e. the node
    is an interior node and must contain a question, then:
    - print the question_or_answer field, which will be a yes/no question.
    - read the response from the user
    - If the response is yes, follow the left field to the next node. Otherwise,
      follow the right field.
  */

  else if (root!= NULL ) {
    //printf(root->question_or_animal);
    while (checkloop==9) {

      if (root->left!=NULL && root->right!=NULL) {

            printf(root->question_or_animal);
            scanf("%s", str);
            if (strcasecmp(str,"yes")==0 || strcasecmp(str,"y")==0) {
              root = root->left;

            }
            else if (strcasecmp(str,"no")==0 || strcasecmp(str,"n")==0) {
              root=root->right;

            }

            else {
              printf("\n Please enter \"yes\" or \"no\" >\n");
            }

      }

      /*
          Otherwise, if the left and right fields are NULL (i.e. the node is a leaf),
          then the question_or_animal field contains an animal. Print the
          the question_or_animal field as the guess and prompt the user
          if the guess was correct. If the guess was correct, then
          return. Otherwise, do the following:
               - prompt the user for the name of the new animal she was thinking of
               - prompt the user for a yes or no question distinguishing the new animal from the guessed animal
         - ask the user what the answer for the new animal would be (yes or no)
               - create a new node with the new animal in the question_or_animal field
         - create another new node that has the guessed animal in the question_or_animal field
               - make the two new nodes the children of the current node, where the animal for which the
                 answer to the question is "yes" is the left child and the other animal is the right child.
               - overwrite the question_or_animal field of the current node with the new question.

          Note that the tree is a stricly binary tree, i.e. left and right fields of each node are either both NULL or
          both valid pointers to child nodes (in other words, each node is a leaf or has exactly two children).
        */

      else if (root->left==NULL && root->right==NULL) {
                    while (check==3) {
                    printf("\nI'm guessing: %s\n", root->question_or_animal);
                    printf("\nAm I right?\n");
                    scanf("%s", strg);
                    if (strcasecmp(strg,"yes")==0 || strcasecmp(strg,"y")==0) {
                      printf("\nYay!\n");
                      check =4;
                      checkloop=8;

                    }

                              else if (strcasecmp(strg,"no")==0 || strcasecmp(strg,"n")==0) {
                                NODE *new = new_node(root->question_or_animal);
                                printf("\nWhat's the name of an animal you were thinking of: \n");
                                scanf("%s", str);

                                NODE *new1= new_node(str);

                                printf("\nPlease provide a yes or no question distinguishing %s from %s: \n", str, (root->question_or_animal));
                                scanf("\n%[^\n]s\n", strq);

                                printf("\nwhat is the answer for %s (yes or no): \n", str);
                                scanf("%s", strn);

                                if (strcasecmp(strn,"yes")==0 || strcasecmp(strn,"y")==0) {
                                  root->left = new1;
                                  root->right =new;
                                  strcpy(root->question_or_animal, strq);
                                  check=4;
                                  checkloop=8;

                                }

                                else {
                                  root->right = new1;
                                  root->left = new;
                                  strcpy(root->question_or_animal, strq);
                                  check=4;
                                  checkloop=8;

                                }

                              //  else {
                                //  printf("\n Please enter \"yes\" or \"no\" >\n");
                                //}

                              }

                      else {
                        printf("\n Please enter \"yes\" or \"no\" >\n");
                      }
              }
        }
    }
  }

}



//This code is complete. Just add comments where indicated.

int main()
{ int i;
  BOOL done = FALSE;

  //returns a file name pointed to, and opens "data.dat" file for reading
  FILE *datafile = fopen("data.dat", "r");

  if (datafile == NULL) {
    printf("data.dat not found\n");
    exit(1);
  }

  //returns a file name(data.dat.bak) pointed to, and open that file for writing
  FILE *backupfile = fopen("data.dat.bak", "w");

  //read the file "data.dat" from the pointer datafile, and create a binary tree based on the file
  root = read_tree(datafile);

  //call write_tree() to write the initial tree to the
  //backup file (i.e. to backup the tree data)
  write_tree(root,backupfile);

  //close both files (for now)
  fclose(backupfile);
  fclose(datafile);

  printf("Welcome to the animal guessing game (like 20 questions).\n");
  do {
    printf("\nThink of an animal...\n");
    guess_animal();  //guess what the animal is, and if wrong, create nodes and save them for later uses
    printf("\nDo you want to play again? (yes/no) >");
  } while (yes_response());  //if yes then do the repeat using do while loop and if not, exit


  //now open the "data.dat" file for writing
  datafile = fopen("data.dat", "w");

  //write to the datafile starting from the node root
  write_tree(root, datafile);

  //close the data.dat file
  fclose(datafile);

}
