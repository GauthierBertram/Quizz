#include "Qcm.h"

// Constructeur
Qcm::Qcm(const std::string& t, const std::vector<std::string>& o, const std::string& r)
    : Question(t, r), options(o) {}

// Méthode pour obtenir les options 
const std::vector<std::string>& Qcm::getOptions() const {
    return options;
}

// Méthode pour afficher une question et ses options
void Qcm::afficherQuestion(int questionNumber) const {
    cout << "Question " << questionNumber << ": " << texte << endl;
    cout << "Choisissez une option :\n";
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }
}