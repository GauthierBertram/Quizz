#pragma once

#include <iostream>
#include "question.h"
#include <string>
#include <vector>
using namespace std;

class Qcm : public Question
{
private:
    std::vector<std::string> options;
    
public:
    // Constructeur
    Qcm(const std::string& t, const std::vector<std::string>& o, const std::string& r);

    // Méthode pour obtenir les options 
    const std::vector<std::string>& getOptions() const;

    // Méthode pour afficher une question et ses options
    void afficherQuestion(int questionNumber) const;
};