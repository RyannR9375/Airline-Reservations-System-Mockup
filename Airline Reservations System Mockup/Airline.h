#include "Airplane.h"

class C_Airline{
private:
  //PRIVATE MEMBER VARIABLES
    std::vector<C_Airplane> m_airPlanes; //VECTOR OF AIRPLANES
    int m_numAirPlanes; //NUMBER OF AIRPLANES IN THE AIRLINE

    //DEFAULT VALUES
    int m_defNumAirPlanes = 1;
    std::string m_defAirLineName = "Lune Airways";
  private:
    //PRIVATE MEMBER FUNCTIONS
    void fillList();

public:
  //CONSTRUCTORS
    C_Airline(){
      airLineName  = m_defAirLineName;
      m_numAirPlanes = m_defNumAirPlanes;
      fillList();
    }
    C_Airline(std::vector<C_Airplane> airPlanes){
      airLineName    = m_defAirLineName;
      m_airPlanes    = airPlanes;
      m_numAirPlanes = int(airPlanes.size());
    }
    C_Airline(std::string nameOfAirLine){
      airLineName    = nameOfAirLine;
      m_numAirPlanes = m_defNumAirPlanes;
      fillList();
    }
    C_Airline(int numAirPlanes){
      airLineName    = m_defAirLineName;
      m_numAirPlanes = numAirPlanes;
      fillList();
    }
    C_Airline(std::string nameOfAirLine, int numAirPlanes){
      airLineName    = nameOfAirLine;
      m_numAirPlanes = numAirPlanes;
      fillList();
    }
    C_Airline(std::string nameOfAirLine, std::vector<C_Airplane> airPlanes){
      airLineName    = nameOfAirLine;
      m_airPlanes    = airPlanes;
      m_numAirPlanes = int(airPlanes.size());
    }    
    C_Airline(std::string nameOfAirLine, std::vector<C_Airplane> airPlanes, int numAirPlanes){
      airLineName    = nameOfAirLine;
      m_airPlanes    = airPlanes;
      m_numAirPlanes = numAirPlanes;
    }

  public:
    //PUBLIC MEMBER VARIABLES
    std::string airLineName; //AIRLINE'S PUBLIC NAME

  public:
    //PUBLIC MEMBER FUNCTIONS
    inline std::vector<C_Airplane> getAirplaneList() { return m_airPlanes; }
};
