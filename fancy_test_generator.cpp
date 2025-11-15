#include <ranges>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <map>
#include <set>
#include "problem.h"
#include "test_constraints.h"
#include "test_selector.h"

// ****************************************************************************
// Configuration details

// Variable information to be printed on the test
std::string CLASS = "Arithmetic";
std::string TERM = "Fall 2025";
std::string EXAM = "925";
std::string TIME = "Day";
std::string TITLE = "Final Exam";
std::string FORM = "A";

// Source file for problem bank
std::string BANK = "arithmetic_problems.tex";

// Filename for the created test
std::string FILENAME = "fancy_test.tex";

// Constraints on the problem choice.
int NUM_PROBLEMS = 20; // The test must have 20 problems.
int MIN_TOPIC = 3; // Each topic must be covered 
int MAX_TOPIC = 7; // by 3-7 problems.
int MIN_DIFFICULTY = 65; // Total difficulty (using the difficulty defined 
int MAX_DIFFICULTY = 75; // in the problem bank) must be 65-75.

// tex files to include in the test file
std::string TEX_HEADER = "fancy_tex_header.tex";
std::string CONTENT_HEADER = "fancy_content_header.tex";

// ****************************************************************************
int main() {
    // Read in problem list and convert to Problem objects
    std::vector<Problem> bank = Problem::problemList(BANK);

    TestConstraints constraints{
        NUM_PROBLEMS,
        MIN_TOPIC,
        MAX_TOPIC,
        MIN_DIFFICULTY,
        MAX_DIFFICULTY
    };

    // Open the file to write the test to
    std::ofstream outputFile(FILENAME); 
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    // Generate the test problems
    std::vector<Problem> test = testProblems(bank, constraints);

    // Open the file to write the test to
    std::ofstream outputFile(FILENAME); 
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << FILENAME << std::endl;
        return 1;
    }

    // Write the tex header to the file
    outputFile << "\\input{" << TEX_HEADER << "}\n";

    // Include the manually-entered information
    outputFile << "\\newcommand{\\class}{" << CLASS << "}\n";
    outputFile << "\\newcommand{\\term}{" << TERM << "}\n";
    outputFile << "\\newcommand{\\examno}{" << EXAM << "}\n";
    outputFile << "\\newcommand{\\dayeve}{" << TIME << "}\n";
    outputFile << "\\newcommand{\\formletter}{" << FORM << "}\n";
    outputFile << "\\newcommand{\\numproblems}{" << NUM_PROBLEMS << " }\n";
    outputFile << "\\newcommand{\\testtitle}{" << TITLE << "}\n";

    // Write the content header to the file
    outputFile << "\\input{" << CONTENT_HEADER << "}\n";

    // Write the problems to the file
    int problem_number = 1;
    for (Problem problem : test) {
        if (problem_number % 2 == 1) {       // Start a new page before 
            outputFile << "\\pagebreak\n\n"; // each odd-numbered problem
        } else {                                 // Insert blank space before
            outputFile << "\\vspace{350pt}\n\n"; // each even-numbered problem
        }
        outputFile << "\\item\\begin{tabular}[t]{p{5in} p{.3in} p{.8in}}\n";
        outputFile << problem.getQuestion();
        outputFile << "& & \\arabic{enumi}.\\hrulefill\n\\end{tabular}\n";
        problem_number += 1;
    }

    // End the file
    outputFile << "\\end{enumerate}\n\\end{document}";
    outputFile.close();

    return 0;
}