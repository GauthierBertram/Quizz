#include "Qcm.h"




// Constructeur
Qcm::Qcm(const std::string& t, vector<string> o, const std::string& r)
    : Question(t, r), options(o) {}

// Méthode pour obtenir les options
const std::string& Qcm::getOptions() const {
    // Concaténer toutes les options en une seule chaîne (juste pour afficher)
    static std::string concatenatedOptions;
    concatenatedOptions.clear(); // On réinitialise à chaque appel
    for (size_t i = 0; i < options.size(); ++i) {
        concatenatedOptions += to_string(i + 1) + ". " + options[i] + "\n";
    }
    return concatenatedOptions;
}

// Méthode pour afficher une question
const void Qcm::afficherQuestion(Question& q, int questionNumber) const {
    cout << "Question " << questionNumber << ": " << texte << endl;
    cout << "Choisissez une option :\n";
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }
}