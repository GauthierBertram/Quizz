#include "question.h"

const std::string &Question::getReponse() const
{ return reponse; };

const std::string &Question::getTexte() const
{ return texte; };

bool Question::verifierReponse(const std::string &utilisateur) const
 {
    return utilisateur == reponse;
};
