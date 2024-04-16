#include <vector>
#include "Passenger.h"

void C_Passenger::getRandomName(){
  //GET RANDOM NAME IN NAME VECTOR 'randomNames'
  for(int i = 0; i < int(m_randomNames.size()); i++){
    int randomFirst = rand() % int(m_randomNames[0].size()) + 1;
    int randomLast  = rand() % int(m_randomNames[1].size()) + 1;
    
    for(int j = 0; j < int(m_randomNames[i].size()); j++){ 
      firstName = m_randomNames[0].at(randomFirst - 1);
      lastName  = m_randomNames[1].at(randomLast  - 1);
    }
  }
  C_Passenger::setNames();
} 
std::vector<std::string> C_Passenger::getInfo(){
  std::vector<std::string> info = {C_Passenger::getName(), C_Passenger::getFlightNum()};
  return info;
}
