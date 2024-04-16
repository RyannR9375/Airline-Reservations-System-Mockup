#include <iomanip>
#include "Airline.h"

bool binSrch(std::vector<int>, int, int&);

int menuOptions(C_Airplane);

void userInputOpt(C_Airplane, int, int&);
void interface(C_Airline);
void printEnjoy(C_Passenger);

int main() {
  srand(time(0));
  const int AIRPLANE_SEAT_CAPACITY = 10;
  
  C_Airplane PlaneGordon(AIRPLANE_SEAT_CAPACITY, "B27", "Plane, Gordon");
  std::vector<C_Airplane> Planes = {PlaneGordon};
  
  C_Airline LuneAirways("Lune AirWays", Planes);

  interface(LuneAirways);

  return 0;
}

int menuOptions(C_Airplane airplane){
  std::vector<std::string> extraOpts = {"Passenger Manifest", "Exit"};
  
  std::vector<std::string> options = airplane.getSeatGroupOptions();
  int totalSz = int(options.size()) + int(extraOpts.size());

  //ADD THE EXTRA OPTIONS TO THE OPTIONS LIST
  for(int i = 0; i < int(extraOpts.size()); i++){
    options.push_back(extraOpts.at(i));
  }
  
  for(int i = 0; i < totalSz; i++){
    std::cout << "Enter " << (i + 1) << " for '" << options.at(i) << "'" << "\n";
  }

  return int(options.size());
}

void userInputOpt(C_Airplane airplane, int menuOptAmt, int& input){
  bool hasReserved = false;
  //IF THE USER INPUTTED AN OPTION THAT ISN'T THE LAST OPTION (LAST OPTION IS USUALLY EXIT)
  while(input != menuOptAmt && hasReserved == false){
    airplane.checkAvail(input);
    std::cout << "\n\n";

    bool isAvail = airplane.hasOpenSeat(input);

    if(!isAvail){
      menuOptions(airplane);
      std::cin >> input;

      if(input != menuOptAmt){
        airplane.checkAvail(input);
        isAvail = airplane.hasOpenSeat(input);
      }
    }
    
    //IF THERE IS AN OPEN SPOT, PROMPT THE USER TO SELECT A SEAT CHOICE
    if(isAvail){
      int seatNum;
      std::cout << "\nEnter the seat number you would like to reserve: ";

      std::cin >> seatNum;

      //MAKE SURE THE USER IS NOT RESERVING A SEAT THAT'S ALREADY TAKEN
      int indx;
      while(!binSrch(airplane.getAvailSeats(input), seatNum, indx)){
        std::cout << "\nThat seating option is not currently available. Please enter a valid seat number and try again.\n";
        std::cin >> seatNum;
      }

      //RESERVE THE USER'S SEAT CHOICE
      airplane.reserveSeat(seatNum);

      //ASK THE USER TO INPUT THEIR NAME
      std::string firstName;
      std::string lastName;

      std::cout << "Please enter your first name: ";
      std::cin >> firstName;
      std::cout << "Please enter your last name: ";
      std::cin >> lastName;

      //CREATE 'C_Passenger' INSTANCE CALLED 'user' TO STORE USER INFORMATION
      C_Passenger user = airplane.createPassenger(firstName, lastName, seatNum);
      hasReserved = true;

      //CURRENTLY USING AN EARLY RETURN BECAUSE THE SYSTEM WILL BUG OUT AFTER RESERVING A FLIGHT
      printEnjoy(user);
      //return;
    }

    //IF THE USER HAS RESERVED, TAKE AWAY THE OPTION TO RESERVE A FLIGHT.
    while(input != menuOptAmt){
      menuOptions(airplane);
      std::cin >> input;

      if(input != menuOptAmt){
        airplane.checkAvail(input);
        std::cout << "\n\n";
      }
    }
  }

  //IF THE USER CHOSE THE LAST OPTION (LAST OPTION IS USUALLY EXIT)
  if(input == menuOptAmt){
    std::cout << "\n\nExiting system...\n";
    exit(0);
  }
}

void interface(C_Airline airLine){
  //OUTPUT WELCOME MESSAGES
  std::string txtWelcomeMsg = "Welcome to " + airLine.airLineName + "!\n";
  std::cout << txtWelcomeMsg << std::setw(txtWelcomeMsg.length()) << std::setfill('-') << "\n";

  //GRAB THE SEATING GROUP FROM THE FIRST AIRPLANE IN THE AIRLINE
  C_Airplane airPlanesOpt = airLine.getAirplaneList().at(0);

  //OUTPUT MENU OPTIONS
  int numOpts = menuOptions(airPlanesOpt);
  int inputNum;

  //GET USER INPUT
  std::cin >> inputNum;

  //DISPLAY USER INPUT MENU
  userInputOpt(airPlanesOpt, numOpts, inputNum);
}

void printEnjoy(C_Passenger user){
  std::cout << "\n\nThank you, " << user.getName() << ". You have successfully reserved seat " << user.getSeatNum() << ".\n" <<
    "\nEnjoy your flight!\n";
}

bool binSrch(std::vector<int> vec, int val, int& index){
    int first = 0,
        middle,
        last = int(vec.size()) - 1;
    
    bool found = false;
    
    while(!found && first <= last){
        middle = (first + last) / 2;
        
        if(vec.at(middle) == val){
            index = middle;
            found = true;
        }else if(vec.at(middle) > val)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return found;
}