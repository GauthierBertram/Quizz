#include "quizz.h"
#include <iostream>
#include <string> 
#include <vector>
using namespace std

struct Question {
    string questionText; //L'énoncé de la question
    vector<string> options; //Les différentes options proposées 
    int reponse; // Index de l'option correcte (0, 1, 2, ...) //La réponse correcte
};

void displayQuestion(const Question& q, int questionNumber) {
    std::cout << "Question " << questionNumber + 1 << ": " << q.questionText << "\n";
    for (size_t i = 0; i < q.options.size(); ++i) {
        std::cout << i + 1 << ". " << q.options[i] << "\n";
    }
}

int main() {
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
            std::getline(std::cin, question);
            std::cout << "Entrez la réponse : ";
            std::getline(std::cin, reponse);
            quiz.ajouterQuestion(question, reponse);

        }
    } while (choix != 3);
    cout << "1. Lancer le quiz\n2. Ajouter une question\n3. Quitter\nVotre choix : ";

    quiz.sauvegarderQuestions(".txt/questions.txt");

    return 0;
}
