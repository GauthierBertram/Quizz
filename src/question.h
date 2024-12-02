

#include <string>
#include <iostream>

class Question {
protected:
    std::string texte;
    std::string reponse;

public:
    Question(const std::string& t, const std::string& r);
    const std::string& getReponse() const;
    const std::string& getTexte() const;
    void setReponse(std::string& r);
    void setTexte(std::string& t);
    const void afficherQuestion(const Question& q, int questionNumber) const;
    bool verifierReponse(const std::string& utilisateur) const;
};