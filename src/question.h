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
    virtual ~Question() = default; // Destructeur virtuel pour la gestion correcte des classes dérivées

    const std::string& getReponse() const;
    const std::string& getTexte() const;
    void setReponse(const std::string& r);
    void setTexte(const std::string& t);

    virtual void afficherQuestion(sf::RenderWindow& window, sf::Font& font) const; // Méthode virtuelle
    bool verifierReponse(const std::string& utilisateur) const;
};