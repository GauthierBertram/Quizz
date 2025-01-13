#include "Qcm.h"

// Constructeur
Qcm::Qcm(const std::string& t, const std::vector<std::string>& o, const std::string& r)
    : Question(t, r), options(o) {}

// Méthode pour obtenir les options sous forme de chaîne
const std::string& Qcm::getOptions() const {
    static std::string concatenatedOptions;
    concatenatedOptions.clear(); // Réinitialiser à chaque appel
    for (size_t i = 0; i < options.size(); ++i) {
        concatenatedOptions += std::to_string(i + 1) + ". " + options[i] + "\n";
    }
    return concatenatedOptions;
}

// Méthode pour afficher une question et ses options
void Qcm::afficherQuestion(int questionNumber) const {
    cout << "Question " << questionNumber << ": " << texte << endl;
    cout << "Choisissez une option :\n";
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }
}