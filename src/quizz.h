#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "question.h"

class Quiz {
private:
    std::vector<Question> questions;

public:
    void chargerQuestions(const std::string& fichier);

    void sauvegarderQuestions(const std::string& fichier) const;

    void lancerQuiz();

    void ajouterQuestion(const std::string& texte, const std::string& reponse);
};