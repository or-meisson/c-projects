#include <stdlib.h>
#include <stdio.h>
#include "markov_chain.h"
#include "linked_list.h"
#include <string.h>

#define MAX_ARG 5
#define MIN_ARG 4
#define MAX_LINE_LEN 1000
#define BASE 10
#define MAX_TWEET_LEN 20
#define SPECIAL_NUM (-1)

enum Status
{
    E_FAILURE,
    E_SUCCESS,
};

/**
 * creates the markov chain by the file given and the num of words asked to
 * read
 * @param fp
 * @param words_to_read
 * @param markov_chain
 * @return 1 if failed, 0 of success.
 */
 
int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
  int word_counter = 0;
  char line[MAX_LINE_LEN];
  
  while ((words_to_read == -1 || word_counter < words_to_read) &&
		 fgets(line, MAX_LINE_LEN, fp) != NULL)
  {
	if (line[0] == '\n' || line[0] == '\r')
	{
	  continue;
	}
	char *prev_word = strtok(line, " \n\t");
	if (prev_word == NULL)
	{
	  break;
	}
	
	Node *prev_node = add_to_database(markov_chain, prev_word);
	if (!prev_node)
	{
	  return 1;
	}
	
	word_counter++;
	
	char *word;
	while ((words_to_read == -1 || word_counter < words_to_read) &&
		   (word = strtok(NULL, " \n\r\t")) != NULL)
	{
	  Node *current_node = add_to_database(markov_chain, word);
	  if (!current_node)
	  {
		return 1;
	  }
	  
	  if (!is_word_ending_sentence(prev_word, strlen (prev_word)))
	  {
		bool is_ok = add_node_to_frequencies_list(prev_node->data, current_node->data);
		if (!is_ok)
		{
		  return 1;
		}
	  }
	  
	  prev_word = word;
	  prev_node = current_node;
	  word_counter++;
	}
  }
  
  return 0;
}


/**
 * takes the arguments given by the user and checks if the are valid
 * @param argc
 * @param argv
 * @return E_SUCCESS if args are valid, E_FAILURE otherwise
 */
int validate_args (int argc, char *argv[])
{
  if (argc > MAX_ARG || argc < MIN_ARG)
  {
    fprintf (stdout, "USAGE: Wrong argument number\n");
    return E_FAILURE;
  }
  char *filename = argv[3];
  FILE *file = fopen (filename, "r");
  if (file == NULL)
  {
    fprintf (stdout, "ERROR: can not open file");
    return E_FAILURE;
  }
  else
  {
    fclose (file);
  }
  return E_SUCCESS;
}

/**
 * gets parameters from the user, learns the text file, builds a markov chain
 * and generates tweets.
 * @param argc
 * @param argv
 * @return E_SUCCESS if program ran ok, E_FAILURE otherwise
 */
int main (int argc, char *argv[])
{
  int is_ok_args = validate_args (argc, argv);
  if (!is_ok_args)
  {
    return EXIT_FAILURE;
  }
  unsigned int seed = strtol (argv[1], NULL, BASE);
  srand (seed);
  char *filename = argv[3];
  int num_word_to_read = SPECIAL_NUM; // if we want to read the entire file
  if (argc == MAX_ARG)
  {
    num_word_to_read = (int) strtol (argv[4], NULL, BASE);
  }
  FILE *file = fopen (filename, "r");
  MarkovChain *my_markov_chain = malloc (sizeof (MarkovChain));
  LinkedList *my_linked_list = malloc (sizeof (LinkedList));
  my_linked_list->first = NULL;
  my_linked_list->last = NULL;
  my_linked_list->size = 0;
  my_markov_chain->database = my_linked_list;
  int has_fill_database_failed = fill_database \
 (file, num_word_to_read, my_markov_chain);
  if (has_fill_database_failed)
  {
    fprintf (stdout, ALLOCATION_ERROR_MASSAGE);
    free_database (&my_markov_chain);
    fclose (file);
    return EXIT_FAILURE;
  }
  int num_of_tweets = (int) strtol (argv[2], NULL, BASE);
  int counter11 =0;
  Node * first = my_markov_chain->database->first;
  while (first!=NULL){
	fprintf (stdout, "%s ", first->data->data);
	fprintf (stdout, "%d\n", counter11);

	counter11++;
	first=first->next;
  }
  int counter = 0;
  while (counter < num_of_tweets)
  {
    fprintf (stdout, "Tweet %d: ", counter + 1);
    generate_tweet (my_markov_chain, NULL, \
                    MAX_TWEET_LEN);
    counter++;
    fprintf (stdout, "\n");
  }
  free_database (&my_markov_chain);
  fclose (file);
  return EXIT_SUCCESS;
}


