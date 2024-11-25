//#include "Quiz.h"
#include <iostream>

int main() {
    //Quiz quiz;
    //quiz.chargerQuestions("questions.txt");

    int choix;
    do {
        std::cout << "1. Lancer le quiz\n2. Ajouter une question\n3. Quitter\nVotre choix : ";
        std::cin >> choix;
        std::cin.ignore(); // Ignorer le retour à la ligne
        if (choix == 1) {
            //quiz.lancerQuiz();
        } else if (choix == 2) {
            std::string question, reponse;
            std::cout << "Entrez la question : ";
            //std::getline(std::cin, question);
            std::cout << "Entrez la réponse : ";
            //std::getline(std::cin, reponse);
            //quiz.ajouterQuestion(question, reponse);
        }
    } while (choix != 3);

    //quiz.sauvegarderQuestions("questions.txt");
    return 0;
}