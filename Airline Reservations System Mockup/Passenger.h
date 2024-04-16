#include <iostream>
#include <stdlib.h>

class C_Passenger{
private:
  //PRIVATE MEMBER VARIABLES
    std::string m_flightNum;
    int m_seatNum;

    std::vector<std::vector<std::string>> m_randomNames = 
    {
      {"Kendra", "Ryan", "Uriel", "Sunay", "Peter", "Norma", "Connor", "Gordon", "Lune", "Iver"}, 
      {"Devlahovicht", "Ramos", "Rodriguez", "Dabney", "Marduk", "Fuentes", "Garcia", "Vu", "Lorono", "Neeona"}
    };
  private:
  //PRIVATE MEMBER FUNCTIONS
    void getRandomName();
    inline void setNames() { fullName = firstName + " " + lastName; 
                            rFullName = lastName + ", " + firstName; }
public:
    friend class C_AirPlane;
    //CONSTRUCTORS
    C_Passenger(){
      C_Passenger::getRandomName();
    }
    C_Passenger(std::string first, std::string last){
      firstName = first;
      lastName  = last;

      C_Passenger::setNames();
    }
    C_Passenger(std::string first, std::string last, int seat){
      firstName = first;
      lastName  = last;
      m_seatNum = seat;

      C_Passenger::setNames();
    }
    C_Passenger(std::string first, std::string last, std::string flightNum){
      firstName = first;
      lastName  = last;
      m_flightNum = flightNum;

      C_Passenger::setNames();
    }
    C_Passenger(std::string first, std::string last, std::string flightNum, int seat){
      firstName = first;
      lastName  = last;
      m_flightNum = flightNum;
      m_seatNum = seat;

      C_Passenger::setNames();
    }

  public:
    //PUBLIC MEMBER VARIABLES
    std::string firstName;
    std::string lastName;

    std::string fullName;
    std::string rFullName;

  public:
    //PUBLIC MEMBER FUNCTIONS
    std::vector<std::string> getInfo();

    inline void setRandomSeatNum(int max) { m_seatNum = rand() % max + 1; }
    inline void setFlightNum(std::string flightNum) { m_flightNum = flightNum; }
    inline void setSeatNum(int seatNum){ m_seatNum = seatNum; }

    inline int getSeatNum() { return m_seatNum; }

    inline std::string getName() { return firstName + " " + lastName; }
    inline std::string getFlightNum() { return m_flightNum; }
};