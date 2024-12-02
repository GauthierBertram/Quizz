#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <filesystem>

class Question {
protected:
    std::string texte;
    std::string reponse;

public:
    Question(const std::string& t, const std::string& r);
    const std::string& getReponse() const;
    const std::string& getTexte() const;
    void setReponse(std::string& r);
    void setTexte(std::string& t);
    void afficherQuestion(sf::RenderWindow& window, sf::Font& font) const;
    bool verifierReponse(const std::string& utilisateur) const;
};