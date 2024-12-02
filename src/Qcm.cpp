#include "Qcm.h"


void Qcm::displayOptions(const Question &q, int questionNumber)
{
    int n,i;
    n = options.size();
    for (i=0;i<n;i++){
        std::cout << options[i] << std::endl ;
    };
};

Qcm::Qcm(const std::string &t, vector<string> o, const std::string &r): options(o), Question(t, r){};

const std::string &Qcm::getOptions() const
{
    // TODO: insert return statement here
}
