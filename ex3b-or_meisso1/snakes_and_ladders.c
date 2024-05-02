#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20
#define NUM_ARGS 3
#define BASE 10

enum Status
{
	E_FAILURE,
	E_SUCCESS,
};

/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
							  {85, 17},
							  {95, 67},
							  {97, 58},
							  {66, 89},
							  {87, 31},
							  {57, 83},
							  {91, 25},
							  {28, 50},
							  {35, 11},
							  {8,  30},
							  {41, 62},
							  {81, 43},
							  {69, 32},
							  {20, 39},
							  {33, 70},
							  {79, 99},
							  {23, 76},
							  {15, 47},
							  {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell
{
	int number; // Cell number 1-100
	int ladder_to;  // ladder_to represents the jump of the
	// ladder in case there is one from this square
	int snake_to;  // snake_to represents the jump of the snake in case
	// there is one from this square
	//both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
static int handle_error (char *error_msg, MarkovChain **database)
{
  printf ("%s", error_msg);
  if (database != NULL)
  {
	free_database (database);
  }
  return EXIT_FAILURE;
}

static int create_board (Cell *cells[BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
	cells[i] = malloc (sizeof (Cell));
	if (cells[i] == NULL)
	{
	  for (int j = 0; j < i; j++)
	  {
		free (cells[j]);
	  }
	  handle_error (ALLOCATION_ERROR_MASSAGE, NULL);
	  return EXIT_FAILURE;
	}
	*(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
  }
  
  for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
  {
	int from = transitions[i][0];
	int to = transitions[i][1];
	if (from < to)
	{
	  cells[from - 1]->ladder_to = to;
	}
	else
	{
	  cells[from - 1]->snake_to = to;
	}
  }
  return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database (MarkovChain *markov_chain)
{
  Cell *cells[BOARD_SIZE];
  if (create_board (cells) == EXIT_FAILURE)
  {
	return EXIT_FAILURE;
  }
  MarkovNode *from_node = NULL, *to_node = NULL;
  size_t index_to;
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
	add_to_database (markov_chain, cells[i]);
  }
  
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
	from_node = get_node_from_database (markov_chain, cells[i])->data;
	
	if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
	{
	  index_to = MAX(cells[i]->snake_to, cells[i]->ladder_to) - 1;
	  to_node = get_node_from_database (markov_chain, \
                                             cells[index_to])
		  ->data;
	  add_node_to_frequencies_list (from_node, \
                                          to_node, markov_chain);
	}
	else
	{
	  for (int j = 1; j <= DICE_MAX; j++)
	  {
		index_to = ((Cell *) (from_node->data))->number + j - 1;
		if (index_to >= BOARD_SIZE)
		{
		  break;
		}
		to_node = get_node_from_database (markov_chain, cells[index_to])
			->data;
		add_node_to_frequencies_list (from_node,
									  to_node, markov_chain);
	  }
	}
  }
  // free temp arr
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
	free (cells[i]);
  }
  return EXIT_SUCCESS;
}

/**
 * checks if a given cell is the last one on board
 * @param cell
 * @return true if last, false otherwise
 */
static bool is_last_cell (Cell *cell)
{
//  Cell* my_cell = cell ;
  if (cell->number == BOARD_SIZE)
  {
	return true;
  }
  return false;
}

/**
 * compares if two cells are identical
 * @param cell1
 * @param cell2
 * @return 0 if identical 1 otherwise
 */
static int compare_func (Cell *cell1, Cell *cell2)
{
  if (cell1->number == cell2->number)
  {
	return 0;
  }
  else if (cell1->number > cell2->number)
  {
	return 1;
  }
  else if (cell1->number < cell2->number)
  {
	return -1;
  }
  return 0;
}

/**
 * allocates and copies one cell data to another
 * @param data
 * @return
 */
static Cell *copy_function (Cell *data)
{
  Cell *dest = malloc (sizeof (Cell));
  if (!dest)
  {
	return NULL;
  }
  memcpy (dest, data, sizeof (Cell));
  return dest;
}


/**
 * prints a cells content
 * @param cell
 */
static void print_function (void *cell)
{
  Cell *my_cell = cell;
  if (my_cell->number == BOARD_SIZE)
  {
	fprintf (stdout, "[%d]", my_cell->number);
	
  }
  else if (my_cell->ladder_to > 0)
  {
	fprintf (stdout, "[%d]-ladder to %d -> ", my_cell->number,
			 my_cell->ladder_to);
  }
  else if (my_cell->snake_to > 0)
  {
	fprintf (stdout, "[%d]-snake to %d -> ", my_cell->number,
			 my_cell->snake_to);
  }
  else
  {
	fprintf (stdout, "[%d] -> ", my_cell->number);
  }
}

/**
 * frees a cell's content
 * @param cell
 */
static void free_func (void *cell)
{
  Cell *my_cell = cell;
  free (my_cell);
}



/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main (int argc, char *argv[])
{
  if (argc != NUM_ARGS)
  {
	fprintf (stdout, "USAGE: Wrong argument number\n");
	return EXIT_FAILURE;
  }
  unsigned int seed = strtol (argv[1], NULL, BASE);
  srand (seed);
  MarkovChain *my_markov_chain = malloc (sizeof (MarkovChain));
  LinkedList *my_linked_list = malloc (sizeof (LinkedList));
  my_linked_list->first = NULL;
  my_linked_list->last = NULL;
  my_linked_list->size = 0;
  my_markov_chain->database = my_linked_list;
  my_markov_chain->is_last = (is_last) is_last_cell;
  my_markov_chain->comp_func = (comp_func) compare_func;
  my_markov_chain->print_func = (print_func) print_function;
  my_markov_chain->copy_func = (copy_func) copy_function;
  my_markov_chain->free_data = (free_data) free_func;
  int has_fill_database_failed = fill_database (my_markov_chain);
  if (has_fill_database_failed)
  {
	free_database (&my_markov_chain);
	return EXIT_FAILURE;
  }
  int num_of_tracks = (int) strtol (argv[2], NULL, BASE);
  int counter = 0;
  while (counter < num_of_tracks)
  {
	fprintf (stdout, "Random Walk %d: ", counter + 1);
	MarkovNode *first_node = my_markov_chain->database->first->data;
	generate_tweet (my_markov_chain, first_node,
					MAX_GENERATION_LENGTH);
	counter++;
	fprintf (stdout, "\n");
  }
  free_database (&my_markov_chain);
  return EXIT_SUCCESS;
}
