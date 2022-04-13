/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Arsam Samadi Bahrami
   Dated: 14/09/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/

/****************************************************************/

void format_input(int cells[], int unknowns_array[]);
int find_unknowns(int cells[], int unknowns_array[]);
void grid_check(int cells[], int set_tally[]);
void tally_set(int set_no, int cells[], int set_tally[]);
int find_violations(int set_tally[], int set_no);
int strategy_one_pass(int set_tally[], int cells[], int unknowns_array[], int unknowns);
int strategy_one_cell(int set_tally[], int cell_no, int cells[]);

/****************************************************************/

/* main program controls all the action
*/
int
main(int argc, char *argv[]) {
    
    /* to begin, the 'cell to set' array is filled*/
    fill_c2s();
    /* variables and arrays initialized and the table
    is scanned into an array */
    int i, val, pass;
    int cells[NCLL], unknowns_array[NCLL], set_tally[NDIG + 1];
    
    for (i = 0; i < NCLL; i++)
    {
        scanf("%d", &val);
        cells[i] = val;
    }
    
    /* using helper functions to format the table
    and check for violations */
    printf("\n");
    format_input(cells, unknowns_array);
    printf("\n");
    grid_check(cells, set_tally);

    /* repeatedly call two helper function to
    run passes of strategy one until no
    more changes can be completed */
    while (1)
    {
        pass = strategy_one_pass(set_tally, cells,
        unknowns_array, find_unknowns(cells, unknowns_array));
        if (pass == 0)
        {
            break;
        }
        printf("\n");
    }

    /* format the table again and display
    a message if the soduko is solved */
    format_input(cells, unknowns_array);

    if (find_unknowns(cells, unknowns_array) == 0)
    {
        printf("\nta daa!!!\n");
    }
    
    return 0;
}

/****************************************************************/

void
format_input(int cells[], int unknowns_array[]) {
    /* this helper function is used to display the
    soduko table in a different format */
    int i;
    for (i = 0; i < NCLL; i++)
    {
        /* create dividers every 27 cells
        or 3 rows */
        if (i % (NDIM * NDIG) == 0 && (i != 0))
        {
            printf("------+-------+------\n");
        }
        /* display unknowns as dots */
        if (cells[i] == 0)
        {
            printf(".");
        }
        else
        {
            printf("%d", cells[i]);
        }
        /* makes sure that a space isn't displayed
        at the end of the line */
        if ((i + 1) % NDIG != 0)
        {
            printf(" ");
        }
        /* inner square dividers every 3 cells and
        a new line at the end of every row */
        if ((i + 1) % NDIM == 0)
        {
            if ((i + 1) % NDIG == 0)
            {
                printf("\n");
                continue;
            }
        printf("| ");    
        }    
    }
    printf("\n");

    printf("%2d cells are unknown\n", find_unknowns(cells, unknowns_array));
}

/****************************************************************/

void
grid_check(int cells[], int set_tally[])
{
    /* this helper functions is used to record
    and display violations within the soduko */
    int i, violations = 0, sets_with_violations = 0, violations_found;

    for (i = 0; i < NSET; i++)
    {
        /* a helper function is called to alter the set_tally
        array to the current one being examined out of the total (27) */
        tally_set(i, cells, set_tally);
        /* a helper function is called for every set in the soduko
        to check for violations based on the tally */
        violations_found = find_violations(set_tally, i);
        if (violations_found)
        {
            sets_with_violations ++;
            violations = violations + violations_found;
        }
    }
    if (violations) {
        printf("\n%d different sets have violations\n", sets_with_violations);
        printf("%d violations in total\n", violations);
        exit(0);
    }
}

/****************************************************************/

void
tally_set(int set_no, int cells[], int set_tally[])
{
    /* this helper function is used to alter the set_tally
    array to match the provided set number */
    int i;
    /* tally reset */
    for (i = 0; i <= NDIG; i++)
    {
        set_tally[i] = 0;
    }
    
    for (i = 0; i < NDIG; i++)
    {
        /* for every cell in the set, the tally
        for its number is recorded */
        if (cells[s2c[set_no][i]] != 0){
            set_tally[cells[s2c[set_no][i]]] ++;
        }
    }
}

/****************************************************************/

int
find_violations(int set_tally[], int set_no)
{
    /* this helper function is used to find and 
    display violations in a given set number  */
    int i, violations = 0;
    char* types[] = {"row", "col", "sqr"};
    for (i = 0; i <= NDIG; i++)
    {
        if (set_tally[i] > 1)
        {
            /* if a tally of a number is invalid, its type is
            found from the types array

            ROW: set 0-8. set_no / 9 = 0
            COL: set 9-17. set_no / 9 = 1
            SQR: set 18-26. set_no / 9 = 2

            the type number (e.g. row 7) is also found through
            modulus calculations */
            
            printf("set %2d (%s %d): %d instances of %d\n", set_no,
            types[set_no / NDIG], (set_no % NDIG) + 1, set_tally[i], i);
            
            violations ++;
        }
    }
    return violations;
}

/****************************************************************/

int
strategy_one_pass(int set_tally[], int cells[], int unknowns_array[], int unknowns)
{
    /* this helper function is used to calculate one pass
    of strategy one */
    int i, result, row, col, changes = 0;
    /* the current array of cells are copied over to a new one */
    int new_cells[NCLL];
    for (i = 0; i < NCLL; i++)
    {
        new_cells[i] = cells[i];
    }
    /* attempt to solve every unknown cell by calling a helper function */
    for (i = 0; i < unknowns; i++)
    {
        result = strategy_one_cell(set_tally, unknowns_array[i], cells);
        if (result)
        {
            if (changes == 0)
            {
                printf("strategy one\n");
            }
            changes ++;
            /* if a change can be made, a message is displayed
            and the new array of cells is altered using
            the 'cell to sets' array */
            row = c2s[unknowns_array[i]][0] + 1;
            col = c2s[unknowns_array[i]][1] - NDIG + 1;
            printf("row %d col %d must be %d\n", row, col, result);
            new_cells[unknowns_array[i]] = result;
        }
    }
    /* copy over changes from the new array back to the
    globally used array */
    for (i = 0; i < NCLL; i++)
    {
        cells[i] = new_cells[i];
    }
    /* the number of changes made is returned to the main
    function to make sure formatting isn't affected
    if there is an unsuccessful pass */
    return changes;    
}

/****************************************************************/

int
strategy_one_cell(int set_tally[], int cell_no, int cells[])
{
    /* this helper function is used to attempt to find a solution
    to a single unknown cell using strategy one */
    int i, j, set, success, options = 0, final_option = 0;

    for (i = 1; i <= NDIG; i++)
    {
        success = 0;
        for (j = 0; (j < NGRP); j++)
        {
            /* create a tally for each set of the
            cell (row, col, and sqr) */
            set = c2s[cell_no][j];
            tally_set(set, cells, set_tally);
            if (set_tally[i] == 0)
            {
                success ++;
            }
            else
            {
                success = 0;
            }
        }
        /* if the same option is valid in all three
        sets, add to the possible options */
        if (success == NGRP)
        {
            final_option = i;
            options ++;
        }
    }
    /* solve the unknown if there is only one option */
    if (options == 1)
    {
        return final_option;
    }
    return 0;
}

/****************************************************************/

int find_unknowns(int cells[], int unknowns_array[])
{
    /* this helper function is used to find unknown cells
    in the soduko and alter the array of unknown cells 
    that is used by other functions */
    int i, unknowns = 0;  

    for (i = 0; i < NCLL; i++)
    {
       if (cells[i] == 0)
       {
           unknowns_array[unknowns] = i;
           unknowns ++;
       }       
    }
    return unknowns;
}

/****************************************************************/

/* algorithms are fun !!! */