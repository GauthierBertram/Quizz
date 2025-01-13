#include "quizz.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

std::string filePath = "questions.txt";
void Quiz::chargerQuestions() {
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filePath << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue; // Ignorer les lignes vides

        // Vérifier si c'est un QCM
        if (line.rfind("QCM :", 0) == 0) {
            // Traiter un QCM
            std::string texte = line.substr(5); // Extraire la question après "QCM :"
            std::vector<std::string> options;

            std::getline(inputFile, line);
            std::string reponse = line;

            // Lire les options jusqu'à "END"
            while (std::getline(inputFile, line) && line != "END") {
                if (!line.empty()) {
                    options.push_back(line);
                }
            }


            // Ajouter le QCM à la liste des questions
            questions.push_back(std::make_shared<Qcm>(texte, options, reponse));
            std::cout << "QCM chargé : " << texte << ", Réponse : " << reponse << std::endl;

        } else {
            // Traiter une question standard
            std::string texte = line; // Ligne actuelle est la question
            std::string reponse;

            if (std::getline(inputFile, reponse)) {
                // Ajouter la question standard à la liste des questions
                questions.push_back(std::make_shared<Question>(texte, reponse));
                std::cout << "Question standard chargée : " << texte << ", Réponse : " << reponse << std::endl;
            }
        }
    }

    inputFile.close();
    std::cout << "Chargement terminé. Total des questions : " << questions.size() << std::endl;
}


void Quiz::sauvegarderQcm(const Qcm q) const {
    std::ofstream outputFile(filePath, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour la sauvegarde de la question !" << std::endl;
        return;
    }

    // Sauvegarder le texte et la réponse de la question
    outputFile << "\n";
    outputFile << "\n";
    outputFile << "QCM : " + q.getTexte() ;
    outputFile << q.getReponse();
    std::vector<std::string> options = q.getOptions();
    for (int i = 0; i < options.size(); ++i) {
        outputFile << options[i];
    }
    outputFile << "\n";
    outputFile << "END";
    outputFile << "\n";
    std::cout << "La question a été sauvegardee" << std::endl;
}

// Sauvegarder les questions dans un fichier
void Quiz::sauvegarderQuestion(const Question q) const {
    std::ofstream outputFile(filePath, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour la sauvegarde de la question !" << std::endl;
        return;
    }
    // Sauvegarder le texte et la réponse de la question
    outputFile << "\n";
    outputFile << "\n" << q.getTexte();
    outputFile << q.getReponse();
    outputFile << "\n";
    outputFile.close();
    std::cout << "La question a été sauvegardée dans" << std::endl;
}

// Lancer le quiz avec gestion graphique
void Quiz::lancerQuiz(sf::RenderWindow& window, sf::Font& font, sf::Sprite backgroundSprite) {
    int score = 0;
    for (int i = 0; i < questions.size(); ++i) {
        const auto& q = questions[i];

        // Affichage de la question
        q->afficherQuestion(window, font);

        // Si c'est une question de type QCM, afficher les options sous forme de boutons
        bool answered = false;
        std::string res;
        if (auto qcm = std::dynamic_pointer_cast<Qcm>(q)) {
            // Créer un bouton pour chaque option de réponse
            std::vector<sf::RectangleShape> buttons;
            std::vector<sf::Text> buttonTexts;
            float buttonYPosition = 250;
            std::cout << qcm->getOptions().size() << std::endl;

            for (int j = 0; j < qcm->getOptions().size(); ++j) {
                sf::RectangleShape button(sf::Vector2f(300, 50));
                button.setPosition(250, buttonYPosition);
                button.setFillColor(sf::Color(100, 200, 100)); // Couleur verte pour le bouton

                sf::Text buttonText(qcm->getOptions()[j], font, 24);
                
                std::cout << qcm->getOptions()[j] << std::endl;
                buttonText.setPosition(300, buttonYPosition + 10); // Décalage pour centrer le texte
                buttonText.setFillColor(sf::Color::White);

                buttons.push_back(button);
                buttonTexts.push_back(buttonText);

                buttonYPosition += 70; // Espacement entre les boutons
            }

            // Boucle pour gérer l'entrée de l'utilisateur et la sélection de la réponse
            while (window.isOpen() && !answered) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            // Vérification si un bouton est cliqué
                            for (int j = 0; j < buttons.size(); ++j) {
                                if (buttons[j].getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                                    // Si un bouton est cliqué, vérifier la réponse
                                    res = qcm->getOptions()[j];
                                    
                                    answered = true; // Terminer la boucle
                                    break;
                                }
                            }
                        }
                    }
                }

                // Afficher la fenêtre avec la question et les boutons
                window.clear();
                window.draw(backgroundSprite);
                q->afficherQuestion(window, font);

                // Affichage des boutons
                for (int j = 0; j < buttons.size(); ++j) {
                    window.draw(buttons[j]);
                    window.draw(buttonTexts[j]);
                }

                window.display();
            }
        }
        else {
            // Si la question n'est pas un QCM, traiter comme une question simple
            sf::Text inputPrompt("Votre reponse : ", font, 30);
            inputPrompt.setFillColor(sf::Color::White);
            inputPrompt.setPosition(50, 200);
            window.draw(inputPrompt);

            sf::String inputString;
            sf::Text inputText(inputString, font, 30);
            inputText.setFillColor(sf::Color::White);
            inputText.setPosition(285, 200);
            window.draw(inputText);

            while (window.isOpen() && !answered) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode == 13) { // Entrée = Valider la réponse
                            answered = true;
                            res = inputString;
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
                window.draw(backgroundSprite);
                q->afficherQuestion(window, font);
                window.draw(inputPrompt);
                window.draw(inputText);
                window.display();
            }

            // Vérification de la réponse
            
        };
        if (q->verifierReponse(res)) {
            score++;
        };
    }

    // Affichage du score final
    std::string scoreMessage = "Score final : " + std::to_string(score) + " / " + std::to_string(questions.size());
    sf::Text scoreText(scoreMessage, font, 30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(50, 300);
    window.clear();
    window.draw(backgroundSprite);
    window.draw(scoreText);
    window.display();
    sf::sleep(sf::seconds(3)); // Afficher le score pendant 3 secondes avant de fermer
}


// Ajouter une question simple
void Quiz::ajouterQuestionOuverte(sf::RenderWindow& window, sf::Font& font, bool afficherChoixType, sf::Sprite backgroundSprite) {
    // Création des éléments d'affichage
    sf::Text questionText("Entrez la question : ", font, 30);
    questionText.setPosition(50, 50);
    sf::Text answerText("Entrez la reponse : ", font, 30);
    answerText.setPosition(50, 150);
    sf::Text instructionText("Appuyez sur Entree pour valider chaque champ.", font, 20);
    instructionText.setPosition(50, 250);

    // Variables pour stocker les entrées de l'utilisateur
    sf::String userInputQuestion;  // Question
    sf::String userInputAnswer;    // Réponse

    bool isInputtingQuestion = true; // Indique si on est en train de demander la question
    bool isInputtingAnswer = false;  // Indique si on est en train de demander la réponse

    // Boucle d'entrée utilisateur
    while (isInputtingQuestion || isInputtingAnswer) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::TextEntered) {
                // Ajouter un caractère saisi
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b') {
                        // Suppression d'un caractère (Backspace)
                        if (isInputtingQuestion && !userInputQuestion.isEmpty()) {
                            userInputQuestion.erase(userInputQuestion.getSize() - 1, 1);
                        } else if (isInputtingAnswer && !userInputAnswer.isEmpty()) {
                            userInputAnswer.erase(userInputAnswer.getSize() - 1, 1);
                        }
                    } else if (event.text.unicode != '\b') {
                        // Ajouter un caractère
                        if (isInputtingQuestion) {
                            userInputQuestion += static_cast<char>(event.text.unicode);
                        } else if (isInputtingAnswer) {
                            userInputAnswer += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Si l'utilisateur appuie sur Entrée
                if (isInputtingQuestion) {
                    // Valider la question et passer à la réponse
                    isInputtingQuestion = false;
                    isInputtingAnswer = true;
                } else if (isInputtingAnswer) {
                    // Valider la réponse et ajouter la question-réponse au quiz
                    isInputtingAnswer = false;

                    // Ajouter la question et la réponse dans le vecteur de questions
                    questions.push_back(std::make_shared<Question>(userInputQuestion.toAnsiString(), userInputAnswer.toAnsiString()));

                    
                
                    

                }
            }
        }

        // Effacer la fenêtre
        window.clear();
        window.draw(backgroundSprite);

        // Afficher les instructions et les entrées de l'utilisateur
        window.draw(questionText);
        window.draw(answerText);
        window.draw(instructionText);

        // Afficher la question en cours et la réponse en cours
        if (isInputtingQuestion) {
            questionText.setString("Entrez la question : " + userInputQuestion);
        }
        if (isInputtingAnswer) {
            answerText.setString("Entrez la reponse : " + userInputAnswer);
        }

        // Afficher la fenêtre
        window.display();
    }
    sauvegarderQuestion(Question(userInputQuestion.toAnsiString(), userInputAnswer.toAnsiString()));
    afficherChoixType = false;
}

// Ajouter un QCM
void Quiz::ajouterQcm(sf::RenderWindow& window, sf::Font& font, bool afficherChoixType, sf::Sprite backgroundSprite) {
    // Textes pour les instructions
    sf::Text questionText("Entrez la question : ", font, 30);
    questionText.setPosition(50, 50);

    sf::Text instructionText("Appuyez sur Entrée pour valider chaque champ.", font, 20);
    instructionText.setPosition(50, 150);

    sf::Text optionsText("Ajoutez une option (max 4) : ", font, 30);
    optionsText.setPosition(50, 250);

    sf::Text correctAnswerText("Entrez la reponse correcte (parmi les options) : ", font, 30);
    correctAnswerText.setPosition(50, 350);

    // Variables pour stocker les entrées utilisateur
    sf::String userInputQuestion;
    std::vector<std::string> userOptions;
    sf::String userInputOption;
    sf::String userCorrectAnswer;

    bool isInputtingQuestion = true;
    bool isAddingOptions = false;
    bool isChoosingCorrectAnswer = false;

    // Compteur pour limiter le nombre d'options
    const int maxOptions = 4;
    int i = 0;

    // Boucle d'entrée utilisateur
    while (isInputtingQuestion || isAddingOptions || isChoosingCorrectAnswer) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::TextEntered) {
                // Gestion des caractères saisis
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b') { // Backspace
                        if (isInputtingQuestion && !userInputQuestion.isEmpty()) {
                            userInputQuestion.erase(userInputQuestion.getSize() - 1, 1);
                        } else if (isAddingOptions && userInputOption.isEmpty()) {
                            userInputOption.erase(userInputOption.getSize() - 1, 1);
                        } else if (isChoosingCorrectAnswer && !userCorrectAnswer.isEmpty()) {
                            userCorrectAnswer.erase(userCorrectAnswer.getSize() - 1, 1);
                        }
                    } else { // Autres caractères
                        if (isInputtingQuestion) {
                            userInputQuestion += static_cast<char>(event.text.unicode);
                        } else if (isAddingOptions) {
                            userInputOption += static_cast<char>(event.text.unicode);
                        } else if (isChoosingCorrectAnswer) {
                            userCorrectAnswer += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }
            

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (isInputtingQuestion) {
                    // Valider la question et passer à l'ajout des options
                    isInputtingQuestion = false;
                    isAddingOptions = true;
                } else if (isAddingOptions) {
                    userOptions.push_back(userInputOption.toAnsiString());
                    i++;
                    userInputOption.clear();
                    if (i==4){
                        // Limite des options atteinte, passer au choix de la réponse correcte
                        isAddingOptions = false;
                        isChoosingCorrectAnswer = true;
                    }

                } else if (isChoosingCorrectAnswer) {
                    // Valider la réponse correcte et terminer
                    isChoosingCorrectAnswer = false;

                    // Ajouter la question au quiz
                    questions.push_back(std::make_shared<Qcm>(userInputQuestion.toAnsiString(), userOptions, userCorrectAnswer.toAnsiString()));
                    std::cout << "On ajoute le QCM :" << std::endl;
                    std::cout << userInputQuestion.toAnsiString() << std::endl;
                    std::cout << userCorrectAnswer.toAnsiString() << std::endl;
                    for (std::string option : userOptions){
                        std::cout << option<< std::endl;

                    }
                    sauvegarderQcm(Qcm(userInputQuestion.toAnsiString(), userOptions, userCorrectAnswer.toAnsiString()));

                }
            }
        }

        // Affichage de la fenêtre
        window.clear();
        window.draw(backgroundSprite);

        // Affichage des instructions et des champs d'entrée
        window.draw(questionText);
        if (isInputtingQuestion) {
            questionText.setString("Entrez la question : " + userInputQuestion);
        }

        if (isAddingOptions) {
            optionsText.setString("Ajoutez l'option " +std::to_string(i)+ " (max 5) : " + userInputOption);
            window.draw(optionsText);

            // Afficher toutes les options saisies
            for (int j = 0; j < i; j++) {
                sf::Text optionText("Option " + std::to_string(j + 1) + ": " + userOptions[j], font, 25);
                optionText.setPosition(50, 300 + static_cast<float>(j) * 40); // Décalage vertical pour chaque option
                window.draw(optionText);
            }
        }

        if (isChoosingCorrectAnswer) {
            correctAnswerText.setString("Entrez la reponse correcte : " + userCorrectAnswer);
            window.draw(correctAnswerText);
        }

        window.display();
    }

    afficherChoixType = false;
}



void Quiz::ajouterQuestion(sf::RenderWindow& window, sf::Font& font, bool afficherChoixType, sf::Sprite backgroundSprite)
{
    // Boutons pour choisir le type de question
    sf::Text textQCM("QCM", font, 30);
    sf::Text textQuestionOuverte("Question Ouverte", font, 30);
    sf::Text textRetour("Retour", font, 30);
    textQCM.setPosition(300, 150);
    textQuestionOuverte.setPosition(300, 250);
    textRetour.setPosition(300, 350);

    sf::RectangleShape buttonQCM(sf::Vector2f(250, 50));
    buttonQCM.setPosition(300, 150);
    buttonQCM.setFillColor(sf::Color(100, 100, 255));

    sf::RectangleShape buttonQuestionOuverte(sf::Vector2f(250, 50));
    buttonQuestionOuverte.setPosition(300, 250);
    buttonQuestionOuverte.setFillColor(sf::Color(100, 255, 100));

    sf::RectangleShape buttonRetour(sf::Vector2f(250, 50));
    buttonRetour.setPosition(300, 350);
    buttonRetour.setFillColor(sf::Color(255, 100, 100));


    // Boucle pour gérer l'interaction avec l'utilisateur

    sf::Event event;
    while (afficherChoixType){

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (buttonQCM.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                        ajouterQcm(window,font,afficherChoixType,backgroundSprite);
                        afficherChoixType = false;
                    }
                    else if (buttonQuestionOuverte.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))){
                        ajouterQuestionOuverte(window,font,afficherChoixType,backgroundSprite);
                        afficherChoixType = false;
                        
                    }
                    else if (buttonRetour.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))){
                        afficherChoixType = false;
                    
                    }
                }
            }
        }
        if (afficherChoixType){
            window.clear();
            window.draw(backgroundSprite);
            window.draw(buttonQCM);
            window.draw(textQCM);
            window.draw(buttonQuestionOuverte);
            window.draw(textQuestionOuverte);
            window.draw(buttonRetour);
            window.draw(textRetour);
            window.display();
        }
    }


};
 