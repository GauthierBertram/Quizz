#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "quizz.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

// Fonction pour afficher un message
void afficherMessage(sf::RenderWindow& window, const std::string& message, float x, float y) {


    
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\gauth\\OneDrive\\Documents\\GitHub\\Quizz\\build\\Debug\\fonts\\arial.ttf")) {
        std::cout << "Erreuuuuuuuuur de chargement de la police" << std::endl;
        return;
    }

    sf::Text text(message, font, 30);
    text.setPosition(static_cast<float>(x), static_cast<float>(y));
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

int main() {
    // Chargement du quiz
    Quiz quiz;
    quiz.chargerQuestions("questions.txt");

    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Quiz - Interface Graphique");

    std::string fontPath = "C:/Users/gauth/OneDrive/Documents/GitHub/Quizz/build/Debug/fonts/arial.ttf";

    // Vérification de l'existence du fichier et de la lecture
    if (std::filesystem::exists(fontPath) && std::filesystem::is_regular_file(fontPath)) {
        std::cout << "Le fichier de police existe et est accessible." << std::endl;
    } else {
        std::cout << "Le fichier de police n'est pas accessible ou n'existe pas." << std::endl;
    }

    // Chargement de la police une seule fois
    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        std::cout << "Erreur de chargement de la police depuis : " << fontPath << std::endl;
        return -1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        std::cerr << "Erreur : Impossible de charger l'image de fond !" << std::endl;
        return -1;
    }

    // Créer un sprite pour afficher la texture
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Création des boutons
    sf::Text textStart("1. Lancer le quiz", font, 30);
    sf::Text textAddQuestion("2. Ajouter une question", font, 30);
    sf::Text textQuit("3. Quitter", font, 30);
    textStart.setPosition(300, 150);
    textAddQuestion.setPosition(300, 250);
    textQuit.setPosition(300, 350);

    sf::RectangleShape buttonStart(sf::Vector2f(250, 50));
    buttonStart.setPosition(300, 150);
    buttonStart.setFillColor(sf::Color(100, 100, 255));

    sf::RectangleShape buttonAdd(sf::Vector2f(250, 50));
    buttonAdd.setPosition(300, 250);
    buttonAdd.setFillColor(sf::Color(100, 255, 100));

    sf::RectangleShape buttonQuit(sf::Vector2f(250, 50));
    buttonQuit.setPosition(300, 350);
    buttonQuit.setFillColor(sf::Color(255, 100, 100));


    


    bool quizLance = false;
    int choix = 0;
    std::string question, reponse;

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (buttonStart.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                        // Lancer le quiz
                        window.draw(backgroundSprite);
                        quiz.lancerQuiz(window, font);
                        quizLance = true;
                    }
                    else if (buttonAdd.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                        // Ajouter une question
                        std::cout << "Entrez la question : ";
                        std::getline(std::cin, question);
                        std::cout << "Entrez la réponse : ";
                        std::getline(std::cin, reponse);
                        if (!question.empty() && !reponse.empty()) {
                            quiz.ajouterQuestion(question, reponse);
                        } else {
                            std::cout << "La question et la réponse ne peuvent pas être vides." << std::endl;
                        }
                    }
                    else if (buttonQuit.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                        // Quitter
                        window.close();
                    }
                }
            }
        }

        window.clear();

        // Affichage des boutons et du texte
        window.draw(backgroundSprite);
        window.draw(buttonStart);
        window.draw(textStart);
        window.draw(buttonAdd);
        window.draw(textAddQuestion);
        window.draw(buttonQuit);
        window.draw(textQuit);

        window.display();
    }

    // Sauvegarder les questions à la fin
    quiz.sauvegarderQuestions("questions.txt");

    return 0;
}
