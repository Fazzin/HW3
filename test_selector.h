#ifndef TEST_SELECTOR_H
#define TEST_SELECTOR_H

#include <vector>
#include "problem.h"
#include "test_constraints.h"

std::vector<Problem> TestProblems(
    const std::vector<Problem>& bank,
    const TestConstraints& constraints
);

#endif