#pragma once

#include <iostream> 
#include "question.h"
#include <string>
#include <vector>
using namespace std;

class Qcm : public Question
{
private:
    std::vector<string> options;
public:
    Qcm(const std::string& t, vector<string> o,const std::string& r);
    const std::string& getOptions() const;
    const void afficherQuestion(Question& q, int questionNumber) const;
};