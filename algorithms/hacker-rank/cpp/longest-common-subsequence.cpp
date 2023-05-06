// https://www.hackerrank.com/challenges/magic-spells/problem?isFullScreen=true
// https://www.programiz.com/dsa/longest-common-subsequence

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
    if (auto p = dynamic_cast<Fireball*>(spell)) {
        p->revealFirepower();
    } else if (auto p = dynamic_cast<Frostbite*>(spell)) {
        p->revealFrostpower();
    } else if (auto p = dynamic_cast<Waterbolt*>(spell)) {
        p->revealWaterpower();
    } else if (auto p = dynamic_cast<Thunderstorm*>(spell)) {
        p->revealThunderpower();
    } else {
        string name = spell->revealScrollName();
        string journal = SpellJournal::journal;
        auto sz1 = name.length();
        auto sz2 = journal.length();
        int lcs[sz1 + 1][sz2 + 1];
        // initialize 1st column
        for (int i = 0; i <= sz1; i++) {
            lcs[i][0] = 0;
        }
        // initialize 1st row
        for (int j = 0; j <= sz2; j++) {
            lcs[0][j] = 0;
        }
        for (int i = 1; i <= sz1; i++) {
            for (int j = 1; j <= sz2; j++) {
                if (name[i - 1] == journal[j - 1]) {
                    lcs[i][j] = lcs[i-1][j-1] + 1;
                } else {
                    // take the maximum value from the previous column and previous row
                    int value_from_previous_row = lcs[i-1][j];
                    int value_from_previous_column = lcs[i][j-1];
                    lcs[i][j] = max(value_from_previous_row, value_from_previous_column);
                }
            }
        }
        cout << lcs[sz1][sz2] << endl;
    }
    delete spell;
}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
