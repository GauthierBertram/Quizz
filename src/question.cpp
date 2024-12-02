#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "question.h"

Question::Question(const std::string &t, const std::string &r): texte(t), reponse(r) {}

const std::string &Question::getReponse() const
{ return reponse; };

const std::string &Question::getTexte() const
{ return texte; }

void Question::setReponse(std::string &r) {
    reponse = r;
}
void Question::setTexte(std::string &t) {
    texte = t;
}
void Question::afficherQuestion(sf::RenderWindow& window, sf::Font& font) const {
    sf::Text questionText(texte, font, 30);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(50, 50);
    window.draw(questionText);
}

bool Question::verifierReponse(const std::string &utilisateur) const
 {
    return utilisateur == reponse;
};

