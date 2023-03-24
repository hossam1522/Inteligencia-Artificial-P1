#include "../Comportamientos_Jugador/perro.hpp"
#include "motorlib/util.h"


#include <iostream>
#include <stdlib.h>



Action ComportamientoPerro::think(Sensores sensores){

  Action accion = actIDLE;

  // Lobo comun
  if ( (sensores.superficie[11] == 'j' or sensores.superficie[12]== 'j' or sensores.superficie[13]== 'j' or sensores.superficie[6]== 'j') and
       (sensores.terreno[6] != 'P' and sensores.terreno[6] != 'M') and
       (sensores.terreno[2] != 'P' and sensores.terreno[2] != 'M')
     ){
      accion = actFORWARD;
      return accion;
     }

  int cual = aleatorio(10);
  switch (cual) {
	case 0: accion = actIDLE; break;
	case 1: accion = actTURN_SL; break;
	case 2: accion = actTURN_BR; break;
	case 3: case 4: case 5: case 6: case 7: 
		if (sensores.superficie[2] == 'j') accion = actFORWARD;
		break;
	case 8: accion = actTURN_SR; break;
	case 9: accion = actTURN_BL; break;
  }

  return accion;


}

int ComportamientoPerro::interact(Action accion, int valor){
  return 0;
}
