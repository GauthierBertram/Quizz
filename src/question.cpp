#include "question.h"

Question::Question(const std::string &t, const std::string &r): texte(t), reponse(r) {}

const std::string &Question::getReponse() const
{ return reponse; };

const std::string &Question::getTexte() const
{ return texte; };

bool Question::verifierReponse(const std::string &utilisateur) const
 {
    return utilisateur == reponse;
};

void Question::displayQuestion(const Question& q, int questionNumber){
    std::cout << "Question " << questionNumber + 1 << ": " << q.questionText << "\n";
};
