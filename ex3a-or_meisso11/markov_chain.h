#ifndef _MARKOV_CHAIN_H_
#define _MARKOV_CHAIN_H_

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool



#define ALLOCATION_ERROR_MASSAGE "Allocation failure: Failed to allocate new"\
" memory\n"



/**
 * holds the markov nodes inside the frequency list, and the corresponding
 * frequency
 */
typedef struct MarkovNodeFrequency
{
    struct MarkovNode* markov_node;
    int frequency;

}MarkovNodeFrequency;

/**
 * represents a word, holds the frequency list , the word length and the
 * frequency's list length.
 */
typedef struct MarkovNode
{
    char* data;
    MarkovNodeFrequency* frequencies_list;
    int len_freq_list;
    int len_word;
}MarkovNode;




/**
 * the entire data structure that holds all the nodes in a linked list
 */
typedef struct MarkovChain
{
    LinkedList* database;
}MarkovChain;




/**
 * allocates space for new word and copies it to a new string
 * @param data_ptr
 * @return new pointer to the copy of the word, NULL if memory allocation
 * of new word failed
 */
char *create_new_word (char *data_ptr);


/**
 * allocates space for new markov node and returns it with the new_word given
 * @param new_word
 * @return markov node without frequency list and a pointer to
 * the new word (data), NULL if memory allocation of new_markov_node
 * failed
 */
MarkovNode *create_new_markov_node (char *new_word);





/**
 * creates new word out of the data_ptr using create_new_word
 * gives it to the create_new_markov_node function and returns the new
 * markov node
 * @param data_ptr
 * @return NULL if any of the other functions failed, the new markov node
 * otherwise
 */
MarkovNode *create_and_check_markov_node (char *data_ptr);


/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */
Node* add_to_database(MarkovChain *markov_chain, char *data_ptr);









/**
* Check if data_ptr is in database. If so, return the markov_node wrapping it
 * in the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr);










/**
 * Add the second markov_node to the frequency list of the first markov_node.
 * If already in list, update it's occurrence frequency value.
 * @param first_node
 * @param second_node
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_frequencies_list(MarkovNode *first_node, MarkovNode
*second_node);









/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_database(MarkovChain ** ptr_chain);


/**
 * checks if a given word is ending a sentence
 * @param word
 * @param word_len
 * @return 1 if endinf sentence. 0 otherwise.
 */
int is_word_ending_sentence (const char *word, unsigned long word_len);



/**
 * get random number between 0 and max_number [0, max_number).
 * @param max_number maximal number to return
 * @return random number
 */
int get_random_number (int max_number);



/**
 * randomizes a random number and returns the corresponding node of that
 * number in the markov chain
 * @param max_num
 * @param markov_chain
 * @return  corresponding markov node
 */
MarkovNode *randomize_word (int max_num, MarkovChain *markov_chain);


/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode* get_first_random_node(MarkovChain *markov_chain);






/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr);







/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_tweet(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);




#endif /* _MARKOV_CHAIN_H_ */
