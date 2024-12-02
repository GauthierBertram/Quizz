#include "quizz.h"
#include <iostream>
#include <string> 
#include <vector>
using namespace std;





int main() {
    Quiz quiz;
    quiz.chargerQuestions("questions.txt");

    int choix;
    do {
        cout << "1. Lancer le quiz\n2. Ajouter une question\n3. Quitter\nVotre choix : ";
        cin >> choix;
        cin.ignore();
        if (choix == 1) {
            quiz.lancerQuiz();
        } else if (choix == 2) {
            std::string question, reponse;
            std::cout << "Entrez la question : ";
            std::cin >> question;
            std::cout << "Entrez la réponse : ";
            std::cin >> reponse;
            quiz.ajouterQuestion(question, reponse);

        }
    } while (choix != 3);
    cout << "1. Lancer le quiz\n2. Ajouter une question\n3. Quitter\nVotre choix : ";

    quiz.sauvegarderQuestions("questions.txt");

    return 0;
}
