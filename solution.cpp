#include <iostream>
#include <string>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()
#include <cmath>    // For M_PI

using namespace std;

//#define PART_1  // Use this to test the Circle and Rectangle main function
#define PART_2  // Use this to test the Fraction main function
//#define PART_3  // Use this to test the RPG game

/* ==================== */
/*    Circle Class      */
/* ==================== */
class Circle {
public:
    double x, y, r;

    // Constructor
    Circle(double x, double y, double r) : x(x), y(y), r(r) {}

    // Set position of the center
    void set_pos(double x, double y) {
        this->x = x;
        this->y = y;
    }

    // Calculate perimeter
    double perimeter() const {
        return 2 * M_PI * r;
    }

    // Calculate area
    double area() const {
        return M_PI * r * r;
    }
};

/* ==================== */
/*  Rectangle Class     */
/* ==================== */
class Rectangle {
public:
    double x, y, w, h;

    // Constructor
    Rectangle(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {}

    // Set position of the top-left corner
    void set_pos(double x, double y) {
        this->x = x;
        this->y = y;
    }

    // Calculate perimeter
    double perimeter() const {
        return 2 * (w + h);
    }

    // Calculate area
    double area() const {
        return w * h;
    }
};

/* ==================== */
/* Circle & Rectangle Main Test */
/* ==================== */
#ifdef PART_1
int main() {
    Circle c(0, 0, 1);
    cout << "Circle Perimeter: " << c.perimeter() << endl;
    c.set_pos(1, 1);
    cout << "Circle Coordinates of the center: (" << c.x << ", " << c.y << ")" << endl;
    cout << "Circle Area: " << c.area() << endl;

    Rectangle r(0, 0, 1, 2);
    cout << "Rectangle Perimeter: " << r.perimeter() << endl;
    r.set_pos(-1, -1);
    cout << "Rectangle Coordinates of the top-left corner: (" << r.x << ", " << r.y << ")" << endl;
    cout << "Rectangle Area: " << r.area() << endl;

    return 0;
}
#endif

/* ==================== */
/*    Fraction Class    */
/* ==================== */
class Fraction {
private:
    int numerateur;
    int denominateur;

public:
    Fraction() : numerateur(1), denominateur(1) {}
    Fraction(int n, int d) : numerateur(n), denominateur(d) {}

    void setNumerateur(int n) { this->numerateur = n; }
    void setDenominateur(int d) { this->denominateur = d; }

    int getNumerateur() const { return this->numerateur; }
    int getDenominateur() const { return this->denominateur; }

    Fraction add(const Fraction& f) const {
        Fraction result;
        result.setNumerateur(this->numerateur * f.denominateur + f.numerateur * this->denominateur);
        result.setDenominateur(this->denominateur * f.denominateur);
        //result.simplify();
        return result;
    }

    Fraction minus(const Fraction& f) const {
        Fraction result;
        result.setNumerateur(this->numerateur * f.denominateur - f.numerateur * this->denominateur);
        result.setDenominateur(this->denominateur * f.denominateur);
        //result.simplify();
        return result;
    }

    Fraction multiply(const Fraction& f) const {
        Fraction result;
        result.setNumerateur(this->numerateur * f.numerateur);
        result.setDenominateur(this->denominateur * f.denominateur);
        //result.simplify();
        return result;
    }

    Fraction divide(const Fraction& f) const {
        Fraction result;
        result.setNumerateur(this->numerateur * f.denominateur);
        result.setDenominateur(this->denominateur * f.numerateur);
        //result.simplify();
        return result;
    }

    void simplify() {
        int a = this->numerateur;
        int b = this->denominateur;
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        this->numerateur /= a;
        this->denominateur /= a;

        if (this->denominateur < 0) {
            this->denominateur = -this->denominateur;
            this->numerateur = -this->numerateur;
        }
    }

    void display() const {
        cout << numerateur << "/" << denominateur;
    }
};

/* ==================== */
/*  Fraction Main Test  */
/* ==================== */
#ifdef PART_2
int main() {
    Fraction f0;
    if (f0.getNumerateur() == 1 && f0.getDenominateur() == 1) {
        cout << "[OK] Default constructor works" << endl;
    } else {
        cout << "[FAILURE] Default constructor doesn't work" << endl;
    }

    Fraction f1(1, 2);
    if (f1.getNumerateur() == 1 && f1.getDenominateur() == 2) {
        cout << "[OK] Constructor with parameters works" << endl;
    } else {
        cout << "[FAILURE] Constructor with parameters doesn't work" << endl;
    }

    Fraction f2(3, 4);

    Fraction f3 = f1.add(f2);
    if (f3.getNumerateur() == 10 && f3.getDenominateur() == 8) {
        cout << "[OK] Add method works, Result : ";
        f3.display();
        cout << endl;
    } else {
        cout << "[FAILURE] Add method doesn't work, Result : ";
        f3.display();
        cout << endl;
    }

    f3 = f1.minus(f2);
    if (f3.getNumerateur() == -2 && f3.getDenominateur() == 8) {
        cout << "[OK] Minus method works, Result : ";
        f3.display();
        cout << endl;
    } else {
        cout << "[FAILURE] Minus method doesn't work, Result : ";
        f3.display();
        cout << endl;
    }

    f3 = f1.multiply(f2);
    if (f3.getNumerateur() == 3 && f3.getDenominateur() == 8) {
        cout << "[OK] Multiply method works, Result : ";
        f3.display();
        cout << endl;
    } else {
        cout << "[FAILURE] Multiply method doesn't work, Result : ";
        f3.display();
        cout << endl;
    }

    f3 = f1.divide(f2);
    if (f3.getNumerateur() == 4 && f3.getDenominateur() == 6) {
        cout << "[OK] Divide method works, Result : ";
        f3.display();
        cout << endl;
    } else {
        cout << "[FAILURE] Divide method doesn't work, Result : ";
        f3.display();
        cout << endl;
    }

    

    return 0;
}
#endif

/* ==================== */
/* Creature and Heros  */
/* ==================== */
class Creature {
private:
    int pv;
    int pa;
    int niveau;

public:
    Creature() : pv(5), pa(1), niveau(1) {}
    Creature(int pv, int pa, int niveau) : pv(pv), pa(pa), niveau(niveau) {}

    void affiche() {
        cout << "CREATURE PV: " << pv << " PA: " << pa << " Niveau: " << niveau << endl;
    }

    int attaque() {
        int facteurAleatoire = rand() % 10 + 1;
        int degats = (pa * niveau * facteurAleatoire) / 10;
        cout << "CREATURE attaque et inflige " << degats << " degats" << endl;
        return degats;
    }

    void subitDegats(int degats) {
        pv -= degats;
        cout << "CREATURE subit " << degats << " degats" << endl;
    }

    bool estVivant() {
        return pv > 0;
    }
};

class Heros {
private:
    int pv;
    int pa;
    int niveau;
    string nom;

public:
    Heros() : pv(5), pa(1), niveau(1), nom("Hrun") {}
    Heros(int pv, int pa, int niveau, string nom) : pv(pv), pa(pa), niveau(niveau), nom(nom) {}

    void affiche() {
        cout << "HEROS " << nom << " PV: " << pv << " PA: " << pa << " Niveau: " << niveau << endl;
    }

    int attaque() {
        int facteurAleatoire = rand() % 10 + 1;
        int degats = (pa * niveau * facteurAleatoire) / 10;
        cout << "HEROS " << nom << " attaque et inflige " << degats << " degats" << endl;
        return degats;
    }

    void subitDegats(int degats) {
        pv -= degats;
        cout << "HEROS " << nom << " subit " << degats << " degats" << endl;
    }

    bool estVivant() {
        return pv > 0;
    }
};

/* ==================== */
/*  RPG Main Test      */
/* ==================== */
#ifdef PART_3
int main() {
    srand(static_cast<unsigned int>(time(0)));

    Heros heros(10, 10, 8, "Hrun");
    Creature creature(10, 10, 5);

    heros.affiche();
    creature.affiche();

    int degats = heros.attaque();
    creature.subitDegats(degats);

    degats = creature.attaque();
    heros.subitDegats(degats);

    heros.affiche();
    creature.affiche();

    return 0;
}
#endif
