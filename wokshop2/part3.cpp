#include <iostream>
#include <string>
#include <cstdlib> // For rand() function

using namespace std;

// Declaration of the Creature class
class Creature {
private:
    int pv;     // Health Points (Points de Vie)
    int pa;     // Attack Points (Points d'Attaque)
    int niveau; // Level (Niveau)

public:
    static int cpt; // Static counter to track the number of creatures

    // Default constructor
    Creature() : pv(5), pa(1), niveau(1) {
        Creature::cpt++;
    }

    // Copy constructor
    Creature(Creature const &c) : pv(c.pv), pa(c.pa), niveau(c.niveau) {
        Creature::cpt++;
    }

    // Parameterized constructor
    Creature(int pv, int pa, int niveau) : pv(pv), pa(pa), niveau(niveau) {
        Creature::cpt++;
    }

    // Destructor
    ~Creature() {
        Creature::cpt--;
    }

    // Display the stats of the creature
    void affiche() {
        cout << "CREATURE PV: " << pv << " PA: " << pa << " Niveau: " << niveau << endl;
    }

    // Attack method
    int attaque() {
        int facteurAleatoire = rand() % 10 + 1; // Random factor between 1 and 10
        int degats = (this->pa * this->niveau * facteurAleatoire) / 10;
        cout << "CREATURE attaque et inflige " << degats << " degats" << endl;
        return degats;
    }

    // Method to take damage
    void subitDegats(int degats) {
        this->pv -= degats;
        cout << "CREATURE subit " << degats << " degats" << endl;
    }

    // Check if the creature is still alive
    bool estVivant() {
        return this->pv > 0;
    }
};

// Initialize the static attribute
int Creature::cpt = 0;

// Declaration of the Heros class
class Heros {
private:
    int pv;
    int pa;
    int niveau;
    string nom;

public:
    // Default constructor
    Heros() : pv(5), pa(1), niveau(1), nom("Hrun") {}

    // Parameterized constructor
    Heros(int pv, int pa, int niveau, string nom) : pv(pv), pa(pa), niveau(niveau), nom(nom) {}

    // Destructor
    ~Heros() {}

    // Display the stats of the hero
    void affiche() {
        cout << "HEROS " << nom << " PV: " << pv << " PA: " << pa << " Niveau: " << niveau << endl;
    }

    // Attack method
    int attaque() {
        int facteurAleatoire = rand() % 10 + 1; // Random factor between 1 and 10
        int degats = (this->pa * this->niveau * facteurAleatoire) / 10;
        cout << "HEROS " << nom << " attaque et inflige " << degats << " degats" << endl;
        return degats;
    }

    // Method to take damage
    void subitDegats(int degats) {
        this->pv -= degats;
        cout << "HEROS " << nom << " subit " << degats << " degats" << endl;
    }

    // Check if the hero is still alive
    bool estVivant() {
        return this->pv > 0;
    }
};

// Function to demonstrate the static counter
void foo() {
    Creature c3; // Creates a temporary Creature object
    cout << "Nombre de créatures: " << Creature::cpt << endl;
}

// Test function 1
void test1() {
    cout << "Test 1: \n";
    Creature c1; // Default constructor
    Creature c2(10, 2, 2); // Parameterized constructor
    cout << "Nombre de créatures: " << Creature::cpt << endl;
    foo(); // Calls foo(), which creates and destroys a temporary Creature
    cout << "Nombre de créatures: " << Creature::cpt << endl;
}

// Function to demonstrate object copying
void bar(Creature c1) {
    Creature c2; // Default constructor
    cout << "Nombre de créatures: " << Creature::cpt << endl;
}

// Test function 2
void test2() {
    cout << "Test 2: \n";
    Creature c1; // Default constructor
    Creature c2(10, 2, 2); // Parameterized constructor
    cout << "Nombre de créatures: " << Creature::cpt << endl;
    bar(c2); // Calls bar(), which creates a temporary Creature
    cout << "Nombre de créatures: " << Creature::cpt << endl;
}

int main() {
    test1(); // Run test 1
    test2(); // Run test 2
    return 0;
}
