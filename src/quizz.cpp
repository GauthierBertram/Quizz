#include "quizz.h"

void Quiz::chargerQuestions(const std::string &fichier)
{
    std::ifstream inputFile(fichier);
    std::string line;
    while (std::getline(inputFile, line)) {
        std::string texte = line;
        if (std::getline(inputFile, line)) {
            questions.emplace_back(texte, line);
        }
    }
}

void Quiz::sauvegarderQuestions(const std::string &fichier) const
{
    std::ofstream outputFile(fichier);
    for (const auto& q : questions) {
        outputFile << q.getTexte() << "\n" << q.getReponse() << "\n";
    } 
}

void Quiz::lancerQuiz()
{
    int score = 0;
    for (const auto& q : questions) {
        std::cout << q.getTexte() << "\nVotre réponse : ";
        std::string reponse;
        std::getline(std::cin, reponse);
        if (q.verifierReponse(reponse)) {
            std::cout << "Correct !\n";
            score++;
        } else {
            std::cout << "Faux. La bonne réponse était : " << q.getReponse() << "\n";
        }
    }
    std::cout << "Score final : " << score << " / " << questions.size() << "\n";
}

void Quiz::ajouterQuestion(const std::string &texte, const std::string &reponse)
{
    questions.emplace_back(texte, reponse);
}
