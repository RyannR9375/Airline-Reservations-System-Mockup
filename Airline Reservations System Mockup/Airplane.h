#include <vector>
#include "Passenger.h"

class C_Airplane{
private:
  //PRIVATE MEMBER VARIABLES
    std::string m_flightNum; //UNIQUE FLIGHT ID
    int m_seatCapacity; //SEAT CAPACITY

    std::vector<bool> m_isAvailable; //PARALLEL VECTOR TO 'm_availableSeats' IF THE SEAT IS AVAILABLE
    std::vector<std::string> m_seatingGroups = {"Economy", "Business"}; //SEATING CLASS CHOICES
    std::vector<int> m_seatingChoices; //LIST OF ALL SEATING CHOICES
    std::vector<int> m_takenSeats; //LIST OF ALL TAKEN SEATING CHOICES
    std::vector<int> m_availableSeats; //LIST OF AVAILABLE SEATING CHOICES
    std::vector<int> m_economySeats; //LIST OF AVAILABLE ECONOMY SEATS
    std::vector<int> m_businessSeats; //LIST OF AVAILABLE ECONOMY SEATS
    std::vector<C_Passenger> m_passengerList; //LIST OF PASSENGERS

  private:
    //PRIVATE MEMBER FUNCTIONS
    void fillSeatingChoices(); //FILL SEATING CHOICE VECTORS
    void fillPassengerList(); //FILL 'm_passengerList' WITH RANDOM PASSENGERS
    void assignSeats(); //ASSIGN THE PASSENGERS IN 'm_passengerList' RANDOM SEATS

    int setUniqueValue(std::vector<int>); //RETURNS A VALUE THAT ISN'T PRESENT IN THE VECTOR
    bool binSrch(std::vector<int>, int, int&); //BINARY SEARCH

    //INLINE FUNCTIONS
    inline void errCheckCap(){ m_seatCapacity = m_seatCapacity >= 1 ? m_seatCapacity : defSeatCap; }

public:
    friend class C_Passenger;
    //CONSTRUCTORS
    C_Airplane(){
      m_flightNum    = defFlightNum;
      m_seatCapacity = defSeatCap;

      C_Airplane::fillSeatingChoices();
      C_Airplane::fillPassengerList();
      C_Airplane::assignSeats();
    }
    C_Airplane(int seatCapacity){
      m_flightNum    = defFlightNum;
      m_seatCapacity = seatCapacity;

      C_Airplane::fillSeatingChoices();
      C_Airplane::errCheckCap();
      C_Airplane::fillPassengerList();
      C_Airplane::assignSeats();
    }
    C_Airplane(int seatCapacity, std::string flightNum, std::string nameOfPlane){
      m_seatCapacity = seatCapacity;
      m_flightNum    = flightNum;
      planeName = nameOfPlane;

      C_Airplane::fillSeatingChoices();
      C_Airplane::errCheckCap();
      C_Airplane::fillPassengerList();
      C_Airplane::assignSeats();
    }
    C_Airplane(std::string flightNum){
      m_flightNum    = flightNum;
      m_seatCapacity = defSeatCap;

      C_Airplane::fillSeatingChoices();
      C_Airplane::fillPassengerList();
      C_Airplane::assignSeats();
    }
    C_Airplane(std::string flightNum, int seatCapacity){
      m_flightNum    = flightNum;
      m_seatCapacity = seatCapacity;

      C_Airplane::fillSeatingChoices();
      C_Airplane::errCheckCap();
      C_Airplane::fillPassengerList();
      C_Airplane::assignSeats();
    }
    C_Airplane(std::string flightNum, int seatCapacity, std::vector<C_Passenger> passengerList){
      m_flightNum     = flightNum;
      m_seatCapacity  = seatCapacity;
      m_passengerList = passengerList;
      
      C_Airplane::fillSeatingChoices();
      C_Airplane::errCheckCap();
      C_Airplane::assignSeats();
    }

  public:
    //PUBLIC MEMBER VARIABLES  
        //DEFAULT VALUES
    std::string defFlightNum = "A00";
    int defSeatCap = 10;
    std::string defPlaneName = "Plane Gordon";
    std::string planeName;

  public:
    //PUBLIC MEMBER FUNCTIONS
    void printManifest(); //PRINT PLANE MANIFEST (SEAT # - PASSENGER)
    bool hasOpenSeat(int); //CHECK IF THE PLANES SEATING GROUP HAS AN AVAILABLE SEAT
    std::vector<int> getAvailSeats(int); //GET THE SEAT VECTOR FOR THE SEAT GROUP OF YOUR CHOICE
    std::vector<int> checkAvail(); //CHECKS FLIGHT'S SEAT AVAILABILITY
    std::vector<int> checkAvail(int); //CHECKS FLIGHT'S SEAT AVAILABILITY FOR CERTAIN SEATING GROUP

    C_Passenger createPassenger(std::string first, std::string last, int seatNum);

    //INLINE FUNCTIONS
    inline int getSeatCap(){ return m_seatCapacity; }

    inline std::string getFlightNum() { return m_flightNum; }

    inline std::vector<int> getTakenSeats() { return m_takenSeats; }
    inline std::vector<int> getAvailSeats() { return m_availableSeats; }

    inline std::vector<std::string> getSeatGroupOptions() { return m_seatingGroups; }

    inline void reserveSeat(int seatNum){ m_takenSeats.push_back(seatNum); }
    inline void setSeatingGroups(std::vector<std::string> newGroup) { m_seatingGroups = newGroup; }
};