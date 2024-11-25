//#include "Quiz.h"
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
    //Quiz quiz;
    //quiz.chargerQuestions("questions.txt");

    int choix;
    do {
        cout << "1. Lancer le quiz\n2. Ajouter une question\n3. Quitter\nVotre choix : ";
        cin >> choix;
        cin.ignore(); // Ignorer le retour à la ligne
        if (choix == 1) {
            //quiz.lancerQuiz();
            //En admettant qu'on ai un vector "quiz" de type Question 
            int score = 0;
            int userChoice;
            cout << "Bienvenue au quiz ! Répondez aux questions ci-dessous :\n\n";
            for (size_t i = 0; i < quiz.size(); ++i) {
                displayQuestion(quiz[i], i);
                cout << "Votre réponse (entrez le numéro) : ";
                cin >> userChoice;
                if (userChoice - 1 == quiz[i].reponse) {
                    cout << "Correct !\n\n";
                    ++score;} 
                else {
                    cout << "Incorrect. La bonne réponse était : " << quiz[i].options[quiz[i].reponse] << "\n\n";}
            }
            cout << "Quiz terminé ! Vous avez obtenu un score de " << score << " sur " << quiz.size() << ".\n";
            
        } else if (choix == 2) {
            string question, reponse;
            cout << "Entrez la question : ";
            //std::getline(std::cin, question);
            cout << "Entrez la réponse : ";
            //getline(std::cin, reponse);
            //quiz.ajouterQuestion(question, reponse);
        }
    } while (choix != 3);
    cout << "1. Lancer le quiz\n2. Ajouter une question\n3. Quitter\nVotre choix : ";

    //quiz.sauvegarderQuestions("questions.txt");

    return 0;
}
