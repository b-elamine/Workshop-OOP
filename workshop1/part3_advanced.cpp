#include <iostream>
#include <string>
#include <fstream>  // For file handling
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()

using namespace std;

// Creature class
class Creature {
private:
    int pv;
    int pa;
    int niveau;

public:
    Creature() : pv(5), pa(1), niveau(1) {}
    Creature(int pv, int pa, int niveau) : pv(pv), pa(pa), niveau(niveau) {}

    void affiche() const {
        cout << "CREATURE PV: " << pv << " PA: " << pa << " Niveau: " << niveau << endl;
    }

    int attaque() const {
        int facteurAleatoire = rand() % 10 + 1;
        int degats = (pa * niveau * facteurAleatoire) / 10;
        cout << "CREATURE attaque et inflige " << degats << " degats" << endl;
        return degats;
    }

    void subitDegats(int degats) {
        pv -= degats;
        cout << "CREATURE subit " << degats << " degats" << endl;
    }

    bool estVivant() const {
        return pv > 0;
    }

    void save(ofstream &file) const {
        file << "Creature_PV: " << pv << endl;
        file << "Creature_PA: " << pa << endl;
        file << "Creature_Niveau: " << niveau << endl;
    }

    void load(ifstream &file) {
        string label;
        file >> label >> pv;
        file >> label >> pa;
        file >> label >> niveau;
    }
};

// Heros class with weapon and potion functionality
class Heros {
private:
    int pv;
    int pa;
    int niveau;
    string nom;
    int potions;      // Number of magical potions
    int weaponDamage; // Extra damage from weapon

public:
    Heros() : pv(5), pa(1), niveau(1), nom("Hrun"), potions(2), weaponDamage(5) {}
    Heros(int pv, int pa, int niveau, string nom) : pv(pv), pa(pa), niveau(niveau), nom(nom), potions(2), weaponDamage(5) {}

    void affiche() const {
        cout << "HEROS " << nom << " PV: " << pv << " PA: " << pa << " Niveau: " << niveau
             << " Potions: " << potions << " Weapon Damage: " << weaponDamage << endl;
    }

    int attaque() const {
        int facteurAleatoire = rand() % 10 + 1;
        int degats = (pa * niveau * facteurAleatoire) / 10;
        cout << "HEROS " << nom << " attaque et inflige " << degats << " degats" << endl;
        return degats;
    }

    int attaqueAvecArme() const {
        int facteurAleatoire = rand() % 10 + 1;
        int degats = ((pa + weaponDamage) * niveau * facteurAleatoire) / 10;
        cout << "HEROS " << nom << " attaque avec arme et inflige " << degats << " degats" << endl;
        return degats;
    }

    void utiliserPotion() {
        if (potions > 0) {
            pv += 10;
            potions--;
            cout << "HEROS " << nom << " utilise une potion magique et gagne 10 PV" << endl;
        } else {
            cout << "HEROS " << nom << " n'a plus de potions magiques !" << endl;
        }
    }

    void subitDegats(int degats) {
        pv -= degats;
        cout << "HEROS " << nom << " subit " << degats << " degats" << endl;
    }

    bool estVivant() const {
        return pv > 0;
    }

    void save(ofstream &file) const {
        file << "Heros_Nom: " << nom << endl;
        file << "Heros_PV: " << pv << endl;
        file << "Heros_PA: " << pa << endl;
        file << "Heros_Niveau: " << niveau << endl;
        file << "Heros_Potions: " << potions << endl;
        file << "Heros_WeaponDamage: " << weaponDamage << endl;
    }

    void load(ifstream &file) {
        string label;
        file >> label >> nom;
        file >> label >> pv;
        file >> label >> pa;
        file >> label >> niveau;
        file >> label >> potions;
        file >> label >> weaponDamage;
    }
};

void afficherMenu() {
    cout << "\nActions disponibles:" << endl;
    cout << "1. Attaquer" << endl;
    cout << "2. Attaquer avec une arme" << endl;
    cout << "3. Utiliser une potion magique" << endl;
    cout << "4. Sauvegarder la partie" << endl;
    cout << "5. Charger la partie" << endl;
    cout << "6. Quitter" << endl;
    cout << "Choisissez une action: ";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Heros heros(20, 10, 5, "Hrun");
    Creature creature(15, 8, 3);

    cout << "Début de la bataille entre le héros et la créature !" << endl;
    heros.affiche();
    creature.affiche();

    while (heros.estVivant() && creature.estVivant()) {
        afficherMenu();

        int choix;
        cin >> choix;

        int degats = 0;
        switch (choix) {
            case 1:  // Attaquer
                degats = heros.attaque();
                creature.subitDegats(degats);
                break;
            case 2:  // Attaquer avec une arme
                degats = heros.attaqueAvecArme();
                creature.subitDegats(degats);
                break;
            case 3:  // Utiliser une potion magique
                heros.utiliserPotion();
                break;
            case 4: { // Sauvegarder la partie
                ofstream saveFile("sauvegarde_partie.txt");
                if (saveFile) {
                    heros.save(saveFile);
                    creature.save(saveFile);
                    saveFile.close();
                    cout << "Partie sauvegardée avec succès !" << endl;
                } else {
                    cout << "Erreur lors de la sauvegarde de la partie." << endl;
                }
                break;
            }
            case 5: { // Charger la partie
                ifstream loadFile("sauvegarde_partie.txt");
                if (loadFile) {
                    heros.load(loadFile);
                    creature.load(loadFile);
                    loadFile.close();
                    cout << "Partie chargée avec succès !" << endl;
                } else {
                    cout << "Erreur lors du chargement de la partie." << endl;
                }
                break;
            }
            case 6:  // Quitter
                cout << "Vous quittez le jeu." << endl;
                return 0;
            default:
                cout << "Choix invalide, réessayez." << endl;
                continue;
        }

        if (creature.estVivant()) {
            degats = creature.attaque();
            heros.subitDegats(degats);
        }

        heros.affiche();
        creature.affiche();

        if (!heros.estVivant()) {
            cout << "Le HEROS est mort. Vous avez perdu la bataille." << endl;
            break;
        }
        if (!creature.estVivant()) {
            cout << "La CREATURE est morte. Vous avez gagné la bataille !" << endl;
            break;
        }
    }

    return 0;
}
