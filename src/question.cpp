#include "question.h"

const std::string &Question::getReponse() const
{ return reponse; };

const std::string &Question::getTexte() const
{ return texte; };

bool Question::verifierReponse(const std::string &utilisateur) const
 {
    return utilisateur == reponse;
};

//void Question::displayQuestion(const Question& q, int questionNumber) {
    //std::cout << "Question " << questionNumber + 1 << ": " << q.questionText << "\n";
    //for (size_t i = 0; i < q.options.size(); ++i) {
        //std::cout << i + 1 << ". " << q.options[i] << "\n";
    //}
//}
