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
    bool verifierReponse(const std::string& utilisateur) const;
    void displayQuestion(const Question &q, int questionNumber);
};