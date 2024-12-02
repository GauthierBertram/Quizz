#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "question.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <filesystem>
class Quiz {
private:
    std::vector<Question> questions;

public:
    void chargerQuestions(const std::string& fichier);

    void sauvegarderQuestions(const std::string& fichier) const;

    void lancerQuiz(sf::RenderWindow& window, sf::Font& font);

    void ajouterQuestion(const std::string& texte, const std::string& reponse);
};