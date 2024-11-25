#include "quizz.h"
#include <iostream>
#include <string> 
#include <vector>
using namespace std;





int main() {
    string reponse;
    std::cout << "aaaaaaaaaaa ";
    std::cin >> reponse;
    
    Quiz quiz;
    quiz.chargerQuestions(".txt/questions.txt");

    int choix;
    do {
        cout << "1. Lancer le quiz\n2. Ajouter une question\n3. Quitter\nVotre choix : ";
        cin >> choix;
        cin.ignore(); // Ignorer le retour à la ligne
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

    quiz.sauvegarderQuestions(".txt/questions.txt");

    return 0;
}
