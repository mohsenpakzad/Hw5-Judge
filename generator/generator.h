#pragma once
#define MAXIMUM_NUMBER_OF_TEST_CASES 500


struct inputs
{
    char inputsPath[500];
    char inputsNames[MAXIMUM_NUMBER_OF_TEST_CASES + 1][100];
};

/*
 * This structure used for storing the path of inputs and the names of inputs
*/
struct inputs InputsPathsAndNames;

/*
 * Used for store number of inputs
 */
int numberOfInputs;

int compile();

int getInputsPath();

void loadScreen(int currentState);

int generate();

