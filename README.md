<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">

<h3 align="center">COMP10002 Sudoku Solver</h3>
</div>



<!-- TABLE OF CONTENTS -->
<details>
<summary>Table of Contents</summary>
  
- [1. About The Project](#1-about-the-project)
- [2. Project Description](#2-project-description)
  * [Background](#background)
  * [Stage 1. Reading and Printing](#stage-1-reading-and-printing)
  * [Stage 2. Grid Checking](#stage-2-grid-checking)
  * [Stage 3. Implementing Strategy One](#stage-3-implementing-strategy-one)
  
</details>

## 1. About The Project
This was the first project for COMP10002 (Foundations of Algorithms) at the University of Melbourne. Descriptions for various functions were provided via Grok Learning and checked against various inputs. The <a href="#2-project-description">Project Description</a> will be below. <b> Final mark: 100% </b>

## 2. Project Description
### Background
In this assignment you will demonstrate your understanding of arrays, strings, functions, and the typedef facility. You must not make any use of malloc() (Chapter 10) or file operations (Chap- ter 11) in this project. You may use struct types (Chapter 8) if you wish, but are not required to. (Plus, you might even learn something about sudoku puzzles.)

The goal of sudoku is to complete a square grid of 9×9 = 81 cells using only the numbers from 1 to 9, in a way that has exactly one instance of each digit appearing in each column, in each row, and in each 3 × 3 sub-square. For example, in Figure 1 the cell marked with the red circle must be a “7”, since every other possible value appears in at least one of the three sets (row, purple; column, blue; and sub-square, green) that cell is a member of. All of the other cells in the example can be determined using the same strategy.
Your task in this assignment is to develop a sudoku assistant, to help people solve their sudoku puzzles. You will
use a one-dimensional C array to store a linearized version of the sudoku matrix (see Figure 4), and will write functions that carry out useful operations, including checking for numbering violations, identifying any “it must be that value” cells, and perhaps even solving some easy puzzles through to completion.

Start by copying the skeleton program ass1-skel.c and sample data file data1.txt from the LMS Assignment 1 page, and check that you can compile the program via either grok or gcc. Note that if you plan to use grok, you will need to learn how to execute programs in grok via the “terminal” interface that it provides. There is a handout linked from the LMS that provides guidance.

The skeleton file provides an empty main program that includes a very important authorship declaration. Substantial mark penalties apply if you do not include it in your submission, or do not sign it. The skeleton program also includes two very useful pre-filled “constant” matrices. Make sure that you understand their roles, described below (and in more detail in the Assignment 1 video). Those global matrices are intended to be constant, and you should not change their values in any way.

### Stage 1. Reading and Printing
The input to your program will always be a set of 81 one-digit numbers, laid out as a sudoku grid, and with “0” used to represent empty cells. For example, the sudoku in Figure 1 is represented in the test file data1.txt in the manner shown on the left of Figure 2. You should read the input using a sequence of 81 calls (in a loop, of course) to scanf("%d", &val), to avoid the need to deal with blank and newline characters.

You are encouraged to use a one-dimensional array of 81 values in your program, rather than a 9 × 9 two-dimensional array; and to map the sudoku grid into that array in row-major order, as shown in Figure 4. Using a one-dimensional arrangement allows you to employ single-nested loops instead of always needing double loops, and to make use of the constant arrays that are part of the skeleton program: c2s[] (cell-to-set) has eighty-one rows and three columns, with c2s[c] listing the ordinal numbers of the three sets that include c; and s2c[] (set-to-cell) has twenty-seven rows and nine columns, with s2c[s] listing the cells that make up set number s. For example, in Figure 4 cell number 51 is a member of set number 5 (a row-based set); of set number 15 (a column-based set); and of set number 23 (a square-based set). That means that the three elements in c2s[51] will be 5, 15, and 23. In the inverse mapping, s2c[15] contains the nine cells in set 15, namely 6, 15, 24, 33, 42, 51, 60, 69, and 78. You’ll need to be able to manipulate these two arrays in Stage 2 and Stage 3.

The required output from a Stage 1 program is a neatly-formatted representation of the input data, plus a summary line, see the center part of Figure 2. Note that “%NDIM” and “%NDIG” and %(NDIM*NDIG) operations can be used to identify places where formatting is required to output the required grid.

### Stage 2. Grid Checking
Extend your program so that it checks the input grid for mistakes, to ensure that none of the 27 sets in the supplied puzzle have duplicate elements. Report any errors according to their set number, from 0 to 26, and also by the set type (“row”, “col”, or “sqr”) and the ordinal (counting from one) number of that set. For example, on the (incorrect) input file data2.txt (see the right side of Figure 2), the Stage 2 output must be as shown in Figure 3. Other examples are available on the LMS. If any errors are detected in the input, your program should exit once it has printed out its Stage 2 diagnostic messages.

### Stage 3. Implementing Strategy One
Solving a sudoku involves application of several different strategies. Your program must implement the simplest of those, let’s call it “Strategy One”, which is sufficient to solve “Easy”-grade sudokus. (Further strategies must be added before even “Medium”-grade puzzles can be solved. Your program will not be able solve all sudokus.) The red circle in Figure 1 is an example where Strategy One can be applied to determine a cell label.

In Strategy One, each cell c should be considered in turn. The three sets that cell is a member of (found using array c2s[c]) should be examined, accumulating label counts from the (up to) 24 labeled cells in those three sets (found using array s2c[c]). Each of those labels is a number between 1 and 9. Hence, if there is only one of those nine possible numbers that does not yet occur anywhere in c’s three sets, then it must be the label for cell c.

To implement this strategy you should iterate over all cells, in row-major order, computing the valid options for each cell. Then go through again, using that information, looking for cells that only have one valid option available, assigning those labels. If any cells did get assigned during that pass, you should recompute all the options, and make another pass. Each pass is shown separately in the output (see Figure 5). Only when a complete pass takes place with no new cells being labeled, or when every cell has been labeled, should your program print the current state of the puzzle, and then end. If the sudoku has been solved, your program should celebrate by also printing “ta daa!!!”. The Assignment 1 LMS page has detailed examples showing the output that is required for a range of input files.

If you want a challenge you can also implement “Strategy Two”, which determines which values remain possible options for every unlabeled cell c, eliminating based on the labeled cells in each of c’s three sets; and then checks each of the 27 sets in order. If a set has only one unlabeled cell able to take on one of that set’s unused labels, then that label can be assigned to that cell (see the Assignment 1 video). Strategy One and Strategy Two should be alternated, iterating until no further changes occur. This combined approach will be able to solve puzzles beyond the ability of Strategy One alone, but will not earn any more marks. Only consider implementing Strategy Two when your Strategy One is working.


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/arsamsamadi/
