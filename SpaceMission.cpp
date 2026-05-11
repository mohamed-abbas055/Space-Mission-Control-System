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

    virtual ~SpaceObject() {}                                 // virtual destructor
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

   
    double calculateFuel() const override {                  //  weight * thrustLevel * 0.5      
        return weight * thrustLevel * 0.5;
    }

    
    bool operator>(const Rocket& other) const {
        return calculateFuel() > other.calculateFuel();
    }

    
    double operator+(const Rocket& other) const {
        return fuelCapacity + other.fuelCapacity;
    }

    
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

    
    double calculateFuel() const override {
        return missionsCompleted * 0.3;
    }

    
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
        cout << "  Enter mission code  : ";               cin >> missionCode;
        cout << "  Enter crew size     : ";               cin >> crewSize;
    }

    void display() const override {
        Astronaut::display();
        cout << "  [Commander]\n"
             << "  Mission Code : " << missionCode << "\n"
             << "  Crew Size    : " << crewSize    << "\n";
    }

    
    double calculateFuel() const override {
        return Astronaut::calculateFuel() + crewSize * 0.15;
    }

    

    string getMissionCode() const { return missionCode; }
    int    getCrewSize()    const { return crewSize;    }
};




void showMissionSummary(const Rocket& r, const Astronaut& a) {
    
   
    cout << "  Rocket  : " << r.name   << "  ID: " << r.id   << "\n";
    cout << "  Pilot   : " << a.name   << "  ID: " << a.id   << "\n";
    cout << "  Pilot Rank     : " << a.rank           << "\n";
    cout << "  Health Score   : " << a.healthScore     << "\n";
    cout << "  Rocket Status  : " << r.status          << "\n";
    cout << "  Fuel Needed    : " << r.calculateFuel() << " \n";
    cout << "  Eligible       : ";
        if (a.isEligible()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    } 
 
}



Rocket* rockets = nullptr;
int rocketCount = 0;
int rocketCapacity = 0;

Astronaut* astronauts = nullptr;
int astronautCount = 0;
int astronautCapacity = 0;

Commander* commanders = nullptr;
int commanderCount = 0;
int commanderCapacity = 0;




void rocketMenu() {                                                      //  MENU 1         
    int choice;
    do {
        
        cout << "  [1] Add Rocket\n"
             << "  [2] Display All Rockets\n"
             << "  [3] Compare Two Rockets (Fuel Needed)\n"
             << "  [4] Total Fuel Capacity of Two Rockets\n"
             << "  [0] Back\n"
             << "  Choice: ";
        cin >> choice;

        if (choice == 1) {
            if (rockets == nullptr) {
                cout << " Enter how many rockets you want to store: \n";
                cin >> rocketCapacity;
                rockets = new Rocket[rocketCapacity];

            } if (rocketCount >= rocketCapacity) {
                cout << "  Full\n";
            }
            else {
                cout << "Enter Rocket Data \n";
                rockets[rocketCount].input();
                rocketCount++;
               
            }
            
        }
        else if (choice == 2) {
            if (rocketCount == 0) { cout << "  No rockets \n"; }
            else {
                for (int i = 0; i < rocketCount; i++) {
                    cout << "  Rocket " << (i+1);
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
                    cout <<  rockets[1].getName() << " needs MORE fuel.\n";
            }
        }
        else if (choice == 4) {
            if (rocketCount < 2) { cout << "  Need at least 2 rockets.\n"; }
            else {
                double total = rockets[0] + rockets[1];
                cout << "  Combined fuel capacity of first two rockets: "
                     << total << " \n";
            }
        }
    } while (choice != 0);
}

void astronautMenu() {                                                            //  MENU 2                
    int choice;
    do {
        

        cout << "  [1] Add Astronaut\n"
            << "  [2] Display All Astronauts\n"
            << "  [3] Check Astronaut Eligibility\n"
            << "  [0] Back\n"
            << "  Choice: ";
        cin >> choice;

        if (choice == 1) {
         
            if (astronauts == nullptr) {
                cout << "  Enter maximum number of astronauts: ";
                cin >> astronautCapacity;
                astronauts = new Astronaut[astronautCapacity];
            }

            if (astronautCount >= astronautCapacity) {
                cout << "  Astronaut list is full \n";
            }
            else {
                astronauts[astronautCount].input();
                astronautCount++;
              
            }
        }
        else if (choice == 2) {
            if (astronautCount == 0) {
                cout << "  No astronauts added yet.\n";
            }
            else {
                for (int i = 0; i < astronautCount; i++) {
                    cout << " Astronaut " << (i + 1);
                    astronauts[i].display();
                  
                    cout << "  Fuel contribution: "
                        << astronauts[i].calculateFuel() << " \n";
                }
            }
        }
        else if (choice == 3) {
            if (astronautCount == 0) {
                cout << "  No astronauts added yet.\n";
            }
            else {
                
                for (int i = 0; i < astronautCount; i++) {
                    cout << "  " << astronauts[i].getName() ;

                    if (astronauts[i].isEligible()) {
                        cout << "ELIGIBLE\n";
                    }
                    else {
                        cout << "NOT ELIGIBLE\n";
                    }
                }
            }
        }
    } while (choice != 0);
}

 
void commanderMenu() {                                      //  MENU 3
    int choice;
    do {

        cout << "  [1] Add Commander\n"
            << "  [2] Display All Commanders\n"
            << "  [0] Back\n"
            << "  Choice: ";
        cin >> choice;

        if (choice == 1) {
           
            if (commanders == nullptr) {
                cout << "  Enter maximum number of commanders: ";
                cin >> commanderCapacity;
                commanders = new Commander[commanderCapacity];
            }

            if (commanderCount >= commanderCapacity) {
                cout << "  Commander list is full!\n";
            }
            else {
              
                commanders[commanderCount].input();
                commanderCount++;
              
            }
        }
        else if (choice == 2) {
            if (commanderCount == 0) {
                cout << "  No commanders added yet.\n";
            }
            else {
                for (int i = 0; i < commanderCount; i++) {
                    cout << " Commander " << (i + 1);
                    commanders[i].display();
                }
            }
        }
       
    } while (choice != 0);
}


void missionSummaryMenu() {
    if (rockets == nullptr || astronauts == nullptr || rocketCount == 0 || astronautCount == 0) {
        cout << "  Please add at least one Rocket and one Astronaut first\n";
        return;
    }
    cout << "  Using first rocket and first astronaut:\n";
    showMissionSummary(rockets[0], astronauts[0]);
}


int main() {
   
    

    int choice;
    do {
        
        cout << "  [1] Rocket Management\n"
             << "  [2] Astronaut Management\n"
             << "  [3] Commander Management\n"
             << "  [4] Mission Summary (Friend Function)\n"
             << "  [0] Exit\n"
             << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: rocketMenu();                         break;
            case 2: astronautMenu();                      break;
            case 3: commanderMenu();                      break;
            case 4: missionSummaryMenu();                 break;
            case 0: cout << "  Goodbye\n";                break;
            default: cout << "  Invalid choice.\n";
        }
    } while (choice != 0);

    if (rockets != nullptr)     delete[] rockets;
    if (astronauts != nullptr)  delete[] astronauts;
    if (commanders != nullptr)  delete[] commanders;

    return 0;
}
