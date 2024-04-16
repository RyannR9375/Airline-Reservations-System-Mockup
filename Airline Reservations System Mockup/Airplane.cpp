#include <iomanip>
#include <algorithm>
#include "Airplane.h"

void C_Airplane::fillSeatingChoices(){
  C_Airplane::errCheckCap();

  //FILLS THE 'm_seatingChoices' VECTOR WITH VALUES 1 THROUGH m_seatCapacity
  for(int i = 1; i <= m_seatCapacity; i++){
    m_seatingChoices.push_back(i);
  }

  //FILLS THE 'm_isAvailable' VECTOR WITH ALL 'true' VALUES
  for(int i = 1; i <= int(m_seatingChoices.size()); i++){
    m_isAvailable.push_back(true);
  }
}

void C_Airplane::fillPassengerList(){
  C_Airplane::errCheckCap();
  
  for(int i = 0; i < m_seatCapacity; i++){
    int passengersPresent = rand() % m_seatCapacity + 1;
    int randomNum = rand() % 7 + 1;

    //AMOUNT PASSENGERS WILL RANDOMLY BE ADDED
    if(passengersPresent > randomNum){
      C_Passenger randomPassenger;

      //PASSENGERS 'm_flightNum' WILL BE ASSIGNED THE 'Airplane' MEMBER VARIABLE 'm_flightNum';
      randomPassenger.setFlightNum(m_flightNum);

      //ADD THIS RANDOM PASSENGER TO THE AIRPLANES 'm_passengerList'
      m_passengerList.push_back(randomPassenger);
    }
  }
}

void C_Airplane::assignSeats(){
  std::vector<C_Passenger>& passengers = m_passengerList;
  std::vector<int> usedValues;
  m_availableSeats = m_seatingChoices;
  
  for(int i = 0; i < int(passengers.size()); i++){
    int seatNum = passengers.at(i).getSeatNum();
    usedValues.push_back(seatNum);
    
    int ind;
    //IF THE SEAT IS AVAILABLE, ASSIGN 'passenger.at(i)' THE SEAT
    if(m_isAvailable.at(i)){
      m_isAvailable[i] = false;
      passengers.at(i).setSeatNum(setUniqueValue(m_takenSeats));
      seatNum = passengers.at(i).getSeatNum();
      
      m_takenSeats.push_back(seatNum);
    }
    
    //IF A PASSENGER HAS AN AVAILABLE SEAT, REMOVE THAT AVAILABLE SEAT FROM THE LIST
    int indx;
    if(binSrch(m_availableSeats, seatNum, indx)){
      m_availableSeats.erase(std::remove(m_availableSeats.begin(), m_availableSeats.end(), seatNum),
      m_availableSeats.end());
    }
  }
  
  for(int& seats : m_availableSeats){
    //FILLING UP THE GROUP SEATING CLASS VECTORS
    std::vector<int>& whichSeatGroup = 
      seats <= int(m_seatingChoices.size()) / 2 ? 
    m_economySeats : m_businessSeats;

    whichSeatGroup.push_back(seats);

    //DEBUG STUFF
    /*std::string group =
    seats <= int(m_seatingChoices.size()) / 2 ?
    "eco" : "bus";
    std::cout << group << "(" << int(whichSeatGroup.size()) << ") : " << seats  << "\n";*/
  }

  //SORT SEAT VECTORS SO WE CAN SEARCH THROUGH IT LATER
  std::sort(m_economySeats.begin(), m_economySeats.end());
  std::sort(m_businessSeats.begin(), m_businessSeats.end());
  std::sort(m_takenSeats.begin(), m_takenSeats.end());
}

int C_Airplane::setUniqueValue(std::vector<int> vec){
  int x = 1;
  
      //EITHER HAS THE FUNCTION ASSIGN A RANDOM NUMBER WHICH INCREMENTS FROM X, OR DECREMENTS FROM THE SIZE OF 'm_seatingChoices'
  while( std::find(vec.begin(), vec.end(), x) != vec.end() && x < int(m_seatingChoices.size()) ){
    int whichDir  = rand() % 10 + 1;
    int randomNum = rand() % 10 + 1;

    if(whichDir > randomNum)
      x++;
    else if(int(m_seatingChoices.size()) - randomNum != 0){
      x = int(m_seatingChoices.size()) - randomNum;
    }
  }
  return x;
}

bool C_Airplane::hasOpenSeat(int seatGroup){
  //ERROR CHECK THE VALUE SO THE LOOP DOESN'T GO OUT OF RANGE
  //INCLUDE THE +1 AFTER THE SIZE CHECK INCASE USER WANTS TO CHECK ALL AVAILABLE SEATS
  seatGroup = 
    seatGroup > int(m_seatingGroups.size()) + 1 ?
  int(m_seatingGroups.size()) + 1 : seatGroup;

  std::vector<int>& whichSeatGroup = 
    seatGroup == 1 ?
  m_economySeats : m_businessSeats;

  //FIRST CHECK IF THE USER WANTED TO CHECK IF THERE WERE ANY SEATS AT ALL
  if(seatGroup == int(m_seatingGroups.size()) + 1){
    if(m_availableSeats.empty())
      return false;
    else
      return true;
  }
  
  //DOES THE CHOSEN SEAT GROUP HAVE AN AVAILABLE SEAT?
  if(whichSeatGroup.empty())
    return false;
  else
    return true;
}

std::vector<int> C_Airplane::checkAvail(){
  std::string message = "\n\nFLIGHT " + m_flightNum + " SEAT AVAILABILITY\n";
  std::cout << message << std::setw(message.length()) << std::setfill('-') << "\n";

  //LOOP THROUGH 'm_availableSeats' VECTOR AND PRINT IT'S VALUES
  int i = 0;
  for(int s : m_availableSeats){
    std::string seatGroup = 
      int(m_seatingChoices.size()) - m_availableSeats.at(i) >= int(m_seatingChoices.size()) / 2 ?
        m_seatingGroups[0] : m_seatingGroups[1];
    
    std::cout << "Seat " << s << " (" << seatGroup << ")\n";
    i++;
  }

  return m_availableSeats;
}

std::vector<int> C_Airplane::checkAvail(int formatNum){
  int amtOfFormats = 3;
  
  //IF THE USER INPUTTED A VALUE ABOVE THE AMOUNT OF FORMATS, SET IT TO THE MAXIMUM VALUE
  formatNum = 
    formatNum <= amtOfFormats && formatNum != 4 ?
    formatNum : amtOfFormats;
  
  std::string txtSeatGroup = 
    formatNum == 1 ? 
  m_seatingGroups[0] : m_seatingGroups[1];

  if(formatNum != 3){
  //OUTPUT MESSAGE
  std::string message = "\n\nFLIGHT " + m_flightNum + " " + txtSeatGroup + " SEAT AVAILABILITY\n";
  std::cout << message << std::setw(message.length()) << std::setfill('-') << "\n";
  }

  int ecoCount = 0;
  int busCount = 0;

  int& usedCounter = 
    formatNum == 1 ?
  ecoCount : busCount;

  std::vector<int> whichSeatGroup = 
    formatNum == 1?
  m_economySeats : m_businessSeats;
  
  //OUTPUT THE POSSIBLE OPTIONS
  if(formatNum != 3){
    for(int i = 0; i < int(whichSeatGroup.size()); i++){
      std::cout << "Seat " << whichSeatGroup.at(i) << " (" << txtSeatGroup << ")\n";
      usedCounter++;
    }
  }
  
  //IF THE USER PICKED OPTION 3, PRINT THE MANIFEST
  if(formatNum == 3){
    C_Airplane::printManifest();
    C_Airplane::checkAvail();
  }

  if(usedCounter <= 0 && formatNum != 3)
    std::cout << "There are no available seats in " << txtSeatGroup << ".\n" << 
      "Next flight leaves in 3 hours.\n";
  
  return m_availableSeats;
}

std::vector<int> C_Airplane::getAvailSeats(int seatGroup){ 
  if(seatGroup == 1)
    return m_economySeats;
  else if(seatGroup == 2)
    return m_businessSeats; 
  else
    return m_availableSeats;
}

void C_Airplane::printManifest(){
  //NOT SORTED ALPHABETICALLY, OR NUMERICALLY
  std::string message = "\n\nFLIGHT " + m_flightNum + " PASSENGER MANIFEST\n";
  std::cout << message << std::setw(message.length()) << std::setfill('-') << "\n";
  
  for(int i = 0; i < int(m_passengerList.size()); i++){
    //DETERMINE SEATING GROUP (ECONOMY = 0, BUSINESS = 1)
    std::string seatGroup = 
      int(m_seatingChoices.size()) - m_passengerList.at(i).getSeatNum() >= int(m_seatingChoices.size()) / 2 ?
        m_seatingGroups[0] : m_seatingGroups[1];
    
    //OUTPUT MESSAGE
    std::cout << "Seat " << m_passengerList.at(i).getSeatNum() << " (" << seatGroup << ") - " << m_passengerList.at(i).rFullName << "\n";
  }
}

bool C_Airplane::binSrch(std::vector<int> vec, int val,int& index){
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

C_Passenger C_Airplane::createPassenger(std::string first, std::string last, int seatNum){
  C_Passenger user(first, last, seatNum);
  user.setFlightNum(m_flightNum);
  m_passengerList.push_back(user); //ADD THE USER TO THE LIST OF PASSENGERS

  //REMOVE THE USER'S RESERVED SEAT FROM THE LIST OF AVAILABLE SEATS
  std::vector<int>& whichSeatGroup = 
    seatNum <= int(m_seatingChoices.size()) / 2 ? 
  m_economySeats : m_businessSeats;
  
  int indx;
  if(binSrch(m_availableSeats, seatNum, indx)){
      m_availableSeats.erase(std::remove(m_availableSeats.begin(), m_availableSeats.end(), seatNum),
      m_availableSeats.end());
  }
  
  if(binSrch(whichSeatGroup, seatNum, indx)){
      whichSeatGroup.erase(std::remove(whichSeatGroup.begin(), whichSeatGroup.end(), seatNum),
      whichSeatGroup.end());
  }
  //ADD THEIR SEAT TO THE LIST OF TAKEN SEATS
  m_takenSeats.push_back(seatNum);
  return user;
}