#pragma once

#include "question.h"

Question::Question(const std::string &t, const std::string &r): texte(t), reponse(r) {}

const std::string &Question::getReponse() const
{ return reponse; };

const std::string &Question::getTexte() const
{ return texte; }

void Question::setReponse(std::string &r) {
    reponse = r;
}
void Question::setTexte(std::string &t) {
    texte = t;
}
const void Question::afficherQuestion(const Question &q, int questionNumber) const
{
    std::cout << "Question " << questionNumber + 1 << ": " << q.getTexte() << "\n";
}

bool Question::verifierReponse(const std::string &utilisateur) const
 {
    return utilisateur == reponse;
};

