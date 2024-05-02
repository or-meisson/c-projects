#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cipher.h"
#include "tests.h"
#include <string.h>


#define BASE 10
#define MAX_LINE_LEN 1024
#define MAX_ARG_LEN 5
#define MIN_ARG_LEN 2

/**
 * runs all tests in the encode and decode functions
 * @return EXIT_SUCCESS if passed all test, EXIT_FAILURE if failed
 */
int test_func() {
    int test1 = test_encode_non_cyclic_lower_case_positive_k();
    if (test1 == 1) { return EXIT_FAILURE; }
    int test2 = test_encode_cyclic_lower_case_special_char_positive_k();
    if (test2 == 1) { return EXIT_FAILURE; }
    int test3 = test_encode_non_cyclic_lower_case_special_char_negative_k();
    if (test3 == 1) { return EXIT_FAILURE; }
    int test4 = test_encode_cyclic_lower_case_negative_k();
    if (test4 == 1) { return EXIT_FAILURE; }
    int test5 = test_encode_cyclic_upper_case_positive_k();
    if (test5 == 1) { return EXIT_FAILURE; }
    int test6 = test_decode_non_cyclic_lower_case_positive_k();
    if (test6 == 1) { return EXIT_FAILURE; }
    int test7 = test_decode_cyclic_lower_case_special_char_positive_k();
    if (test7 == 1) { return EXIT_FAILURE; }
    int test8 = test_decode_non_cyclic_lower_case_special_char_negative_k();
    if (test8 == 1) { return EXIT_FAILURE; }
    int test9 = test_decode_cyclic_lower_case_negative_k();
    if (test9 == 1) { return EXIT_FAILURE; }
    int test10 = test_decode_cyclic_upper_case_positive_k();
    if (test10 == 1) { return EXIT_FAILURE; }
    return EXIT_SUCCESS;
}


enum Status {
    E_FAILURE,
    E_TEST,
    E_SUCCESS
};
/**
 * checks if the k argument given is a valid number
 * @param k
 * @return E_SUCCESS if valid, E_FAILURE if not.
 */
int check_k(char k[]) {
    if ((k[0] == '-' && strlen(k)>1)|| isdigit(k[0])) {
        int i = 1;
        while (k[i] != '\0') {
            if (!isdigit(k[i])) { return E_FAILURE; }
            i++;
        }
        return E_SUCCESS;
    }
    return E_FAILURE;
}

/**
 * chacks the validity of the given arguments
 * @param argc
 * @param argv
 * @return E_FAILURE if invalid, E_SUCCESS if valid,
 * E_TEST if given the 'test' command.
 */
int check_validity(int argc, char *argv[]) {
    char *command = argv[1];
    char *my_k = argv[2];
    if (argc != MIN_ARG_LEN && argc != MAX_ARG_LEN) {
        fprintf(stderr, "The program receives 1 or 4 arguments only.\n");
        return E_FAILURE;
    }
    if (argc == 2) {
        if (strcmp(command, "test") == 0) { return E_TEST; }
        fprintf(stderr, "Usage: cipher test\n");
        return E_FAILURE;
    }
    if (strcmp(command, "encode") != 0 && strcmp(command, "decode") != 0) {
        fprintf(stderr, "The given command is invalid.\n");
        return E_FAILURE;
    }
    if (check_k(my_k) == E_FAILURE) {
        fprintf(stderr, "The given shift value is invalid.\n");
        return E_FAILURE;
    }
    FILE *input_file = fopen(argv[3], "r");
    if (input_file == NULL) {
        fprintf(stderr, "The given file is invalid.\n");
        return E_FAILURE;
    }
    fclose(input_file);

    return E_SUCCESS;
}

/**
 * runs the whole program, receives input from user
 * @param argc
 * @param argv
 * @return EXIT_FAILURE if program failed, else EXIT_SUCCESS
 */
int main(int argc, char *argv[]) {

    int validity_status = check_validity(argc, argv);
    if (validity_status == E_FAILURE) { return EXIT_FAILURE; }
    if (validity_status == E_TEST) { return test_func(); }

    char *command = argv[1];
    int my_k = (int) strtol(argv[2], NULL, BASE);
    FILE *input_file = fopen(argv[3], "r");
    FILE *output_file = fopen(argv[4], "w");
    if (output_file == NULL) {
        fclose(input_file);
        fprintf(stderr, "The given file is invalid.\n");
        return E_FAILURE;
    }
    char buffer[MAX_LINE_LEN];
    if (strcmp(command, "encode") == 0) {
        while (fgets(buffer, MAX_LINE_LEN, input_file) != NULL) {
            encode(buffer, my_k);
            fprintf(output_file, "%s", buffer);
        }
    }
    if (strcmp(command, "decode") == 0) {
        while (fgets(buffer, MAX_LINE_LEN, input_file) != NULL) {
            decode(buffer, my_k);
            fprintf(output_file, "%s", buffer);
        }

    }
    fclose(input_file);
    fclose(output_file);
    return EXIT_SUCCESS;
}





