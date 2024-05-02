cmake_minimum_required(VERSION 3.22)
project(ex3b_or_meisso1 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(ex3b_or_meisso1
        linked_list.c
        linked_list.h
        markov_chain.c
        markov_chain.h
        tweets_generator.c
)
