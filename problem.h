#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

class Problem {
public:
    virtual ~Problem() = default;
    virtual std::string getQuestion() const = 0;
    virtual std::string getAnswer() const = 0;
};

class BankProblem : public Problem {
    public:
        explicit BankProblem(const std::string& rawProblem);
        std::string getQuestion() const override;
        std::string getAnswer() const override;
        std::string getTopic() const;
        int getDifficulty() const;
        static std::vector<BankProblem> problemList(const std::string& filename);
    private:
        std::string question;
        std::string answer;
        std::string topic;
        int difficulty;
};

#endif