#include <iostream>
#include <string>
using namespace std;


class Rocket;
class Astronaut;




class SpaceObject {                    //  CLASS 1 :  Abstract  Class                        
protected:
    string name;
    int    id;
    double weight;                    // tons

public:
    SpaceObject() : name("Unknown"), id(0), weight(0.0) {}
    SpaceObject(string n, int i, double w) : name(n), id(i), weight(w) {}

    
    virtual void input() {
        cout << "  Enter name   : ";                cin >> name;
        cout << "  Enter ID     : ";                cin >> id;
        cout << "  Enter weight (tons): ";          cin >> weight;
    }
    virtual void display() const {
        cout << "  Name   : " << name   << "\n"
             << "  ID     : " << id     << "\n"
             << "  Weight : " << weight << " \n";
    }
    
    virtual double calculateFuel()  const = 0;                  // pure virtual


    string getName() const { return name; }
    int    getId()   const { return id;   }
    double getWeight() const { return weight; }

    virtual ~SpaceObject() {}
};



class Rocket : public SpaceObject {                    //  CLASS 2 : (inherits SpaceObject)
private:
    int    thrustLevel;   
    double fuelCapacity;  
    string status;       

public:
    Rocket() : SpaceObject(), thrustLevel(1), fuelCapacity(0.0), status("Ready") {}
    Rocket(string n, int i, double w, int t, double fc, string s)
        : SpaceObject(n, i, w), thrustLevel(t), fuelCapacity(fc), status(s) {}

    
    void input() override {
        SpaceObject::input();
        cout << "  Enter thrust level (1-10): ";                                cin >> thrustLevel;
        cout << "  Enter fuel capacity (tons): ";                               cin >> fuelCapacity;
        cout << "  Enter status (Ready/InFlight/Maintenance): ";                cin >> status;
    }

    void display() const override {
        SpaceObject::display();
      
        cout << "  Thrust Level  : " << thrustLevel  << "\n"
             << "  Fuel Capacity : " << fuelCapacity << "\n"
             << "  Status        : " << status       << "\n";
    }

    // Fuel needed = weight * thrustLevel * 0.5
    double calculateFuel() const override {
        return weight * thrustLevel * 0.5;
    }

    // --- Overloading : compare two rockets by fuel needed ---
    bool operator>(const Rocket& other) const {
        return calculateFuel() > other.calculateFuel();
    }

    // --- Overloading : add fuel capacities ---
    double operator+(const Rocket& other) const {
        return fuelCapacity + other.fuelCapacity;
    }

    // --- Friend Function (declared here, defined below) ---
    friend void showMissionSummary(const Rocket& r, const Astronaut& a);

    int    getThrustLevel()  const { return thrustLevel;  }
    double getFuelCapacity() const { return fuelCapacity; }
    string getStatus()       const { return status;       }
};




class Astronaut : public SpaceObject {                              //  CLASS 3 :  (inherits SpaceObject)
protected:
    string rank;
    int    missionsCompleted;
    double healthScore; 

public:
    Astronaut() : SpaceObject(), rank("Trainee"), missionsCompleted(0), healthScore(100.0) {}
    Astronaut(string n, int i, double w, string r, int m, double h)
        : SpaceObject(n, i, w), rank(r), missionsCompleted(m), healthScore(h) {}

    
    void input() override {
        SpaceObject::input();
        cout << "  Enter rank    : ";                                          cin >> rank;
        cout << "  Enter missions completed: ";                                cin >> missionsCompleted;
        cout << "  Enter health score (0-100): ";                              cin >> healthScore;
    }

    void display() const override {
         SpaceObject::display();
        
         cout << "  Rank               : " << rank               << "\n"
             << "  Missions Completed : " << missionsCompleted  << "\n"
             << "  Health Score       : " << healthScore        << "\n";
    }

    // Fuel per astronaut = 0.3 tons per mission
    double calculateFuel() const override {
        return missionsCompleted * 0.3;
    }

    // Check if eligible for mission
    bool isEligible() const {
        return healthScore >= 75.0 && missionsCompleted >= 1;
    }

    string getRank()             const { return rank;             }
    int    getMissions()         const { return missionsCompleted;}
    double getHealthScore()      const { return healthScore;      }

    friend void showMissionSummary(const Rocket& r, const Astronaut& a);
};




class Commander : public Astronaut {                             //  CLASS 4 :  (inherits Astronaut)
private:
    string missionCode;
    int    crewSize;

public:
    Commander() : Astronaut(), missionCode("NONE"), crewSize(0) {}
    Commander(string n, int i, double w, string r, int m, double h,
              string mc, int cs)
        : Astronaut(n, i, w, r, m, h), missionCode(mc), crewSize(cs) {}

    
    void input() override {
        Astronaut::input();
        cout << "  Enter mission code  : "; cin >> missionCode;
        cout << "  Enter crew size     : "; cin >> crewSize;
    }

    void display() const override {
        Astronaut::display();
        cout << "  [Commander]\n"
             << "  Mission Code : " << missionCode << "\n"
             << "  Crew Size    : " << crewSize    << "\n";
    }

    // Commander fuel = base + extra per crew member
    double calculateFuel() const override {
        return Astronaut::calculateFuel() + crewSize * 0.15;
    }

    // --- Overloading : add two commanders' crew sizes ---
    int operator+(const Commander& other) const {
        return crewSize + other.crewSize;
    }

    string getMissionCode() const { return missionCode; }
    int    getCrewSize()    const { return crewSize;    }
};


//  FRIEND FUNCTION  (accesses private/protected of both)

void showMissionSummary(const Rocket& r, const Astronaut& a) {
    
   
    cout << "  Rocket  : " << r.name   << "  (ID: " << r.id   << ")\n";
    cout << "  Pilot   : " << a.name   << "  (ID: " << a.id   << ")\n";
    cout << "  Pilot Rank     : " << a.rank           << "\n";
    cout << "  Health Score   : " << a.healthScore     << "\n";
    cout << "  Rocket Status  : " << r.status          << "\n";
    cout << "  Fuel Needed    : " << r.calculateFuel() << " tons\n";
    cout << "  Eligible?      : " << (a.isEligible() ? "YES" : "NO") << "\n";
 
}


//  GLOBAL ARRAYS OF OBJECTS

const int MAX_ROCKETS    = 5;
const int MAX_ASTRONAUTS = 5;
const int MAX_COMMANDERS = 5;

Rocket    rockets[MAX_ROCKETS];
Astronaut astronauts[MAX_ASTRONAUTS];
Commander commanders[MAX_COMMANDERS];

int rocketCount    = 0;
int astronautCount = 0;
int commanderCount = 0;

//  HELPER : print header

void printHeader(const string& title) {
    cout << "\n  ==========================================\n";
    cout << "     " << title << "\n";
    cout << "  ==========================================\n";
}

// ============================================================
//  MENU FUNCTIONS
// ============================================================

// --- MENU 1 : Rockets ---
void rocketMenu() {
    int choice;
    do {
        printHeader("ROCKET MANAGEMENT");
        cout << "  [1] Add Rocket\n"
             << "  [2] Display All Rockets\n"
             << "  [3] Compare Two Rockets (Fuel Needed)\n"
             << "  [4] Total Fuel Capacity of Two Rockets\n"
             << "  [0] Back\n"
             << "  Choice: ";
        cin >> choice;

        if (choice == 1) {
            if (rocketCount >= MAX_ROCKETS) {
                cout << "  Rocket list is full!\n";
            } else {
                cout << "\n  --- Enter Rocket Data ---\n";
                rockets[rocketCount].input();
                rocketCount++;
                cout << "  Rocket added successfully!\n";
            }
        }
        else if (choice == 2) {
            if (rocketCount == 0) { cout << "  No rockets added yet.\n"; }
            else {
                for (int i = 0; i < rocketCount; i++) {
                    cout << "\n  Rocket #" << (i+1);
                    rockets[i].display();
                }
            }
        }
        else if (choice == 3) {
            if (rocketCount < 2) { cout << "  Need at least 2 rockets.\n"; }
            else {
                cout << "  Compare rocket index 1 vs 2 (first two added):\n";
                if (rockets[0] > rockets[1])
                    cout << "  " << rockets[0].getName() << " needs MORE fuel.\n";
                else
                    cout << "  " << rockets[1].getName() << " needs MORE fuel.\n";
            }
        }
        else if (choice == 4) {
            if (rocketCount < 2) { cout << "  Need at least 2 rockets.\n"; }
            else {
                double total = rockets[0] + rockets[1];
                cout << "  Combined fuel capacity of first two rockets: "
                     << total << " tons\n";
            }
        }
    } while (choice != 0);
}

// --- MENU 2 : Astronauts ---
void astronautMenu() {
    int choice;
    do {
        printHeader("ASTRONAUT MANAGEMENT");
        cout << "  [1] Add Astronaut\n"
             << "  [2] Display All Astronauts\n"
             << "  [3] Check Astronaut Eligibility\n"
             << "  [0] Back\n"
             << "  Choice: ";
        cin >> choice;

        if (choice == 1) {
            if (astronautCount >= MAX_ASTRONAUTS) {
                cout << "  Astronaut list is full!\n";
            } else {
                cout << "\n  --- Enter Astronaut Data ---\n";
                astronauts[astronautCount].input();
                astronautCount++;
                cout << "  Astronaut added successfully!\n";
            }
        }
        else if (choice == 2) {
            if (astronautCount == 0) { cout << "  No astronauts added yet.\n"; }
            else {
                for (int i = 0; i < astronautCount; i++) {
                    cout << "\n  Astronaut #" << (i+1);
                    astronauts[i].display();
                    cout << "  Fuel contribution: "
                         << astronauts[i].calculateFuel() << " tons\n";
                }
            }
        }
        else if (choice == 3) {
            if (astronautCount == 0) { cout << "  No astronauts added yet.\n"; }
            else {
                for (int i = 0; i < astronautCount; i++) {
                    cout << "  " << astronauts[i].getName()
                         << " -> " << (astronauts[i].isEligible() ? "ELIGIBLE" : "NOT ELIGIBLE") << "\n";
                }
            }
        }
    } while (choice != 0);
}

// --- MENU 3 : Commanders ---
void commanderMenu() {
    int choice;
    do {
        printHeader("COMMANDER MANAGEMENT");
        cout << "  [1] Add Commander\n"
             << "  [2] Display All Commanders\n"
             << "  [3] Combine Crew of First Two Commanders\n"
             << "  [0] Back\n"
             << "  Choice: ";
        cin >> choice;

        if (choice == 1) {
            if (commanderCount >= MAX_COMMANDERS) {
                cout << "  Commander list is full!\n";
            } else {
                cout << "\n  --- Enter Commander Data ---\n";
                commanders[commanderCount].input();
                commanderCount++;
                cout << "  Commander added successfully!\n";
            }
        }
        else if (choice == 2) {
            if (commanderCount == 0) { cout << "  No commanders added yet.\n"; }
            else {
                for (int i = 0; i < commanderCount; i++) {
                    cout << "\n  Commander #" << (i+1);
                    commanders[i].display();
                }
            }
        }
        else if (choice == 3) {
            if (commanderCount < 2) { cout << "  Need at least 2 commanders.\n"; }
            else {
                int total = commanders[0] + commanders[1];
                cout << "  Combined crew of first two commanders: "
                     << total << " members\n";
            }
        }
    } while (choice != 0);
}

// --- MENU 4 : Mission Summary (Friend Function demo) ---
void missionSummaryMenu() {
    if (rocketCount == 0 || astronautCount == 0) {
        cout << "  Please add at least one Rocket and one Astronaut first.\n";
        return;
    }
    cout << "\n  Using first rocket and first astronaut:\n";
    showMissionSummary(rockets[0], astronauts[0]);
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    // Pre-load sample data so demo runs quickly
    rockets[0]    = Rocket("Apollo-X",  101, 50.0, 8, 200.0, "Ready");
    rockets[1]    = Rocket("StarBird",  102, 30.0, 5, 120.0, "Ready");
    rocketCount   = 2;

    astronauts[0] = Astronaut("Yara Nile",   201, 70.0, "Lieutenant", 5, 95.0);
    astronauts[1] = Astronaut("Karim Orbit", 202, 80.0, "Sergeant",   2, 60.0);
    astronautCount = 2;

    commanders[0] = Commander("Laila Stars", 301, 68.0, "Colonel", 10, 99.0, "MISSION-ALPHA", 4);
    commanders[1] = Commander("Tarek Void",  302, 75.0, "Major",    7, 88.0, "MISSION-BETA",  3);
    commanderCount = 2;

    int choice;
    do {
        printHeader("SPACE MISSION CONTROL SYSTEM");
        cout << "  [1] Rocket Management\n"
             << "  [2] Astronaut Management\n"
             << "  [3] Commander Management\n"
             << "  [4] Mission Summary (Friend Function)\n"
             << "  [0] Exit\n"
             << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: rocketMenu();         break;
            case 2: astronautMenu();      break;
            case 3: commanderMenu();      break;
            case 4: missionSummaryMenu(); break;
            case 0: cout << "  Goodbye! Stay in orbit.\n"; break;
            default: cout << "  Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
