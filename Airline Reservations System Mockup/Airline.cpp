#include "Airline.h"

void C_Airline::fillList(){
  //FILL MEMBER VARIABLE 'm_numAirPlanes' WITH NEW INSTANCES OF CLASS 'C_Airplane', 'm_numAirPlanes' times 
  for(int i = 0; i < m_numAirPlanes; i++){
    C_Airplane newPlane;
    m_airPlanes.push_back(newPlane);
  }
}