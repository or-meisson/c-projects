.PHONY: tweets, snakes

tweets: tweets_generator.o markov_chain.o linked_list.o
	gcc -o tweets_generator tweets_generator.o markov_chain.o linked_list.o

tweets_generator.o: tweets_generator.c markov_chain.h linked_list.h
	gcc -Wall -Wvla -Wextra -std=c99 -c tweets_generator.c



snake: snakes_and_ladders.o markov_chain.o linked_list.o
	gcc -o snakes_and_ladders snakes_and_ladders.o markov_chain.o linked_list.o

snakes_and_ladders.o: snakes_and_ladders.c markov_chain.h linked_list.h
	gcc -Wall -Wvla -Wextra -std=c99 -c snakes_and_ladders.c


markov_chain.o: markov_chain.c markov_chain.h linked_list.h
	gcc -Wall -Wvla -Wextra -std=c99 -c markov_chain.c

linked_list.o: linked_list.c linked_list.h
	gcc -Wall -Wvla -Wextra -std=c99 -c linked_list.c