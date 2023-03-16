#include "../Comportamientos_Jugador/aldeano.hpp"
#include "motorlib/util.h"

Action ComportamientoAldeano::think(Sensores sensores) {
  Action accion = actIDLE;

  // Aldeano comun
  int cual = aleatorio(8);
  switch (cual) {
	case 0: accion = actIDLE; break;
	case 1: accion = actTURN_SL; break;
	case 2: accion = actTURN_BR; break;
	case 3: case 4: case 5: case 6: case 7: 
		if (sensores.superficie[2] != 'j') accion = actFORWARD;
		break;
  }

  return accion;
}

int ComportamientoAldeano::interact(Action accion, int valor) {
    return 0;
}
