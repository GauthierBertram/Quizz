#pragma once

#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "qcm.h"

class Quiz {
private:
    std::vector<std::shared_ptr<Question>> questions;

public:
    // Méthodes de gestion du quiz
    void chargerQuestions();
    void sauvegarderQcm(const Qcm q) const;
    void sauvegarderQuestion(const Question q) const;
    void lancerQuiz(sf::RenderWindow& window, sf::Font& font, sf::Sprite backgroundSprite);
    
    // Méthodes pour ajouter des questions
    void ajouterQuestionOuverte(sf::RenderWindow& window, sf::Font& font, bool afficherChoixType, sf::Sprite backgroundSprite);
    void ajouterQcm(sf::RenderWindow& window, sf::Font& font, bool afficherChoixType, sf::Sprite backgroundSprite);
    void ajouterQuestion(sf::RenderWindow& window, sf::Font& font, bool afficherChoixType,sf::Sprite backgroundSprite);
};
