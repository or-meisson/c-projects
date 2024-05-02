
#include "markov_chain.h"
#include "linked_list.h"
#include <string.h>

void *create_new_word (MarkovChain *markov_chain, void *data_ptr)
{
  void *new_data_copy = markov_chain->copy_func (data_ptr);
  if (!new_data_copy)
  {
	return NULL;
  }
  return new_data_copy;
}

MarkovNode *create_new_markov_node (void *new_word)
{
  MarkovNode *new_markov_node = malloc (sizeof (MarkovNode));
  if (!new_markov_node)
  {
	return NULL;
  }
  new_markov_node->data = new_word;
  new_markov_node->frequencies_list = NULL;
  new_markov_node->len_word = strlen (new_word);
  return new_markov_node;
}

MarkovNode *create_and_check_markov_node (MarkovChain *markov_chain, void
*data_ptr)
{
  void *new_word = create_new_word (markov_chain, data_ptr);
  if (!new_word)
  {
	return NULL;
  }
  MarkovNode *new_markov_node = create_new_markov_node (new_word);
  if (!new_markov_node)
  {
	markov_chain->free_data (new_word);
	new_word = NULL;
	return NULL;
  }
  return new_markov_node;
}

Node *add_to_database (MarkovChain *markov_chain, void *data_ptr)
{
  Node *my_node = get_node_from_database (markov_chain, data_ptr);
  if (my_node)
  {
	return my_node;
  }
  MarkovNode *new_markov_node = create_and_check_markov_node
	  (markov_chain, data_ptr);
  if (!new_markov_node) //if memory allocation failed
  {
	return NULL;
  }
  int has_adding_failed = add (markov_chain->database, \
                               new_markov_node);
  if (has_adding_failed)
  {
	
	markov_chain->free_data (new_markov_node->data);
	new_markov_node->data = NULL;
	free (new_markov_node);
	new_markov_node = NULL;
	return NULL;
  }
  return markov_chain->database->last;
}

Node *get_node_from_database (MarkovChain *markov_chain, void *data_ptr)
{
  Node *curr = markov_chain->database->first;
  while (curr)
  {
	if (markov_chain->
		comp_func (data_ptr, curr->data->data) == 0)
	{
	  return curr;
	}
	curr = curr->next;
  }
  return NULL;
}

bool add_node_to_frequencies_list (MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain)
{
  if (!(first_node->frequencies_list))
  {
	MarkovNodeFrequency *firsts_freq_list = malloc \
 (sizeof (MarkovNodeFrequency));
	if (!firsts_freq_list)
	{
	  return false;
	}
	first_node->frequencies_list = firsts_freq_list; //first element in
	// frequency list
	first_node->len_freq_list = 1;
	firsts_freq_list->markov_node = second_node;
	firsts_freq_list->frequency = 1;
	return true;
  }
  else
  {
	for (int i = 0; i < first_node->len_freq_list; i++)
	{
	  if (markov_chain->comp_func
		  (first_node->frequencies_list[i].markov_node->data,
		   second_node->data) == 0)
	  {
		((first_node->frequencies_list) + i)->frequency++;
		return true;
	  }
	}
	MarkovNodeFrequency *firsts_freq_list = realloc
		(first_node->frequencies_list,
		 ((first_node->len_freq_list) + 1) * sizeof (MarkovNodeFrequency));
	if (!firsts_freq_list)
	{
	  return false;
	}
	first_node->frequencies_list = firsts_freq_list;
	first_node->frequencies_list[first_node->len_freq_list].markov_node =
		second_node;
	first_node->frequencies_list[first_node->len_freq_list].frequency = 1;
	(first_node->len_freq_list)++;
	return true;
  }
  
}

void free_database (MarkovChain **markov_chain)
{
  Node *curr = (**markov_chain).database->first;
  while (curr)
  {
	free (curr->data->frequencies_list);
	curr->data->frequencies_list = NULL;
	(**markov_chain).free_data (curr->data->data);
	curr->data->data = NULL;
	free (curr->data);
	curr->data = NULL;
	Node *temp = curr;
	curr = curr->next;
	free (temp);
	temp = NULL;
  }
  free ((**markov_chain).database);
  (**markov_chain).database = NULL;
  free (*markov_chain);
  *markov_chain = NULL;
}

/**
 * get random number between 0 and max_number [0, max_number).
 * @param max_number maximal number to return
 * @return random number
 */
int get_random_number (int max_number)
{
  return (rand () % max_number);
}

MarkovNode *randomize_word (int max_num, MarkovChain *markov_chain)
{
  int num = get_random_number (max_num);
  Node *curr = markov_chain->database->first;
  for (int i = 0; i < num; i++)
  {
	curr = curr->next;
  }
  return curr->data;
}

MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
  int max_num = markov_chain->database->size;
  MarkovNode *chosen_word_markov_node = randomize_word (max_num,
														markov_chain);
  void *chosen_word = chosen_word_markov_node->data;
  while (markov_chain->is_last (chosen_word))
  {
	chosen_word_markov_node = randomize_word (max_num, markov_chain);
	chosen_word = chosen_word_markov_node->data;
  }
  return chosen_word_markov_node;
}

MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr)
{
  int sum_frequencies = 0;
  for (int i = 0; i < state_struct_ptr->len_freq_list; i++)
  {
	sum_frequencies += state_struct_ptr->frequencies_list[i].frequency;
  }
  int random_num = get_random_number (sum_frequencies);
  for (int j = 0; j < state_struct_ptr->len_freq_list; j++)
  {
	if (state_struct_ptr->frequencies_list[j].frequency > random_num)
	{
	  return state_struct_ptr->frequencies_list[j].markov_node;
	}
	random_num -= state_struct_ptr->frequencies_list[j].frequency;
  }
  return NULL;
}

void generate_tweet (MarkovChain *markov_chain, MarkovNode *first_node, int
max_length)
{
  if (!first_node)
  {
	first_node = get_first_random_node (markov_chain);
  }
  if (max_length > 0)
  {
	int counter = 0;
	markov_chain->print_func (first_node->data);
	counter++;
	MarkovNode *next_markov_node = get_next_random_node
		(first_node);
	void *chosen_word = next_markov_node->data;
	while (!markov_chain->is_last (chosen_word))
	{
	  if (counter >= max_length - 1)
	  {
		break;
	  }
	  markov_chain->print_func (chosen_word);
	  next_markov_node = get_next_random_node (next_markov_node);
	  chosen_word = next_markov_node->data;
	  counter++;
	}
	markov_chain->print_func (chosen_word);
  }
}



