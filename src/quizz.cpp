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

void Quiz::lancerQuiz(sf::RenderWindow& window, sf::Font& font) {
    int score = 0;
    for (const auto& q : questions) {
        // Affichage de la question
        q.afficherQuestion(window, font);

        // Champ de texte pour la réponse
        sf::Text inputPrompt("Votre reponse : ", font, 30);
        inputPrompt.setFillColor(sf::Color::White);
        inputPrompt.setPosition(50, 200);
        window.draw(inputPrompt);

        sf::String inputString;
        sf::Text inputText(inputString, font, 30);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(265, 200);
        window.draw(inputText);

        sf::Clock clock;
        bool answered = false;
        while (window.isOpen() && !answered) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                // Capture des saisies au clavier
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 13) { // Entrée = Valider la réponse
                        answered = true;
                    } else if (event.text.unicode == 8) { // Backspace = effacer
                        if (!inputString.isEmpty()) {
                            inputString.erase(inputString.getSize() - 1);
                        }
                    } else {
                        inputString += event.text.unicode;
                    }
                }
            }
            inputText.setString(inputString);
            window.clear();
            q.afficherQuestion(window, font);
            window.draw(inputPrompt);
            window.draw(inputText);
            window.display();
        }

        // Vérification de la réponse
        if (q.verifierReponse(inputString)) {
            score++;
        }
    }

    // Affichage du score
    std::string scoreMessage = "Score final : " + std::to_string(score) + " / " + std::to_string(questions.size());
    sf::Text scoreText(scoreMessage, font, 30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(50, 300);
    window.clear();
    window.draw(scoreText);
    window.display();
    sf::sleep(sf::seconds(3)); // Afficher le score pendant 3 secondes avant de fermer
}

void Quiz::ajouterQuestion(const std::string &texte, const std::string &reponse)
{
    questions.emplace_back(texte, reponse);
}
