#include <vector>
#include <set>
#include <map>
#include <random>
#include <algorithm>

#include "test_selector.h"
#include "test_constraints.h"
#include "problem.h"

static bool isValidTest(
    const std::vector<Problem>& test,
    const std::set<std::string>& topics,
    const TestConstraints& c
) {
    int totalDifficulty = 0;
    std::map<std::string, int> topicCounts;

    for (const std::string& topic : topics) {
        topicCounts[topic] = 0;
    }

    for (const Problem& p : test) {
        totalDifficulty += p.getDifficulty();
        topicCounts[p.getTopic()]++;
    }

    if(totalDifficulty < c.minDifficulty || totalDifficulty > c.maxDifficulty) {
        return false;
    }

    for (const std::string& topic : topics) {
        int count = topicCounts[topic];
        if (count < c.minTopicCount || count > c.maxTopicCount) {
            return false;
        }
    }
    return true;
}

std::vector<Problem> TestProblems(
    const std::vector<Problem>& bankIn,
    const TestConstraints& c
) {
    std::set<std::string> topics;
    for (const Problem& p : bankIn) {
        topics.insert(p.getTopic());
    }

    std::vector<Problem> bank = bankIn;
    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        std::shuffle(bank.begin(), bank.end(), gen);
        if (static_cast<int>(bank.size()) < c.numProblems) {
            return bank;
        }
        std::vector<Problem> test(bank.begin(), bank.begin() + c.numProblems);
        if (isValidTest(test, topics, c)) {
            return test;
        }
    }
}