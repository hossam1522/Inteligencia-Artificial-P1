#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st,
													vector< vector<unsigned char> > &matriz){
		matriz[st.fil][st.col] = terreno[0];
}

Action ComportamientoJugador::think(Sensores sensores){

	Action accion;

	if (sensores.nivel!=0 && !orientacion_correcta){
		current_state.brujula = norte;
		sensores.sentido = norte;
		orientacion_correcta = true;
	}

	if (sensores.reset){
		bien_situado = false;
		tiene_bikini = false;
		tiene_zapatillas = false;
	}

	actualizarVariablesEstado();

	if ((sensores.terreno[0] == 'G' && !bien_situado) || sensores.nivel == 0){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}

	if (sensores.terreno[0] == 'K' && !tiene_bikini){
		tiene_bikini = true;
	}

	if (sensores.terreno[0] == 'D' && !tiene_zapatillas){
		tiene_zapatillas = true;
	}

	if (sensores.terreno[0] == 'X' && !recargando){
		recargando = true;
	}

	if (bien_situado){
		sensores.posF = current_state.fil;
		sensores.posC = current_state.col;
		sensores.sentido = current_state.brujula;
		mapaVecesVisitado[sensores.posF][sensores.posC]++;
		rellenarMapa(sensores, mapaResultado);
	}

	if(!precipicios_rellenos){
		rellenarPrecipicios(mapaResultado);
		precipicios_rellenos=true;
	}

	//Decidir la nueva acción
	elegirMovimiento(accion, sensores);

	//Recordar la última acción
	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

void ComportamientoJugador::rellenarMapa(Sensores sensores, vector< vector<unsigned char> > &matriz){
	// Aquí hay que rellenar el mapa con el terreno que hay delante
	// de nuestro personaje.

	switch(sensores.sentido){
		case norte:
			matriz[sensores.posF][sensores.posC] = sensores.terreno[0];
			matriz[sensores.posF-1][sensores.posC-1] = sensores.terreno[1];
			matriz[sensores.posF-1][sensores.posC] = sensores.terreno[2];
			matriz[sensores.posF-1][sensores.posC+1] = sensores.terreno[3];
			matriz[sensores.posF-2][sensores.posC-2] = sensores.terreno[4];
			matriz[sensores.posF-2][sensores.posC-1] = sensores.terreno[5];
			matriz[sensores.posF-2][sensores.posC] = sensores.terreno[6];
			matriz[sensores.posF-2][sensores.posC+1] = sensores.terreno[7];
			matriz[sensores.posF-2][sensores.posC+2] = sensores.terreno[8];
			matriz[sensores.posF-3][sensores.posC-3] = sensores.terreno[9];
			matriz[sensores.posF-3][sensores.posC-2] = sensores.terreno[10];
			matriz[sensores.posF-3][sensores.posC-1] = sensores.terreno[11];
			matriz[sensores.posF-3][sensores.posC] = sensores.terreno[12];
			matriz[sensores.posF-3][sensores.posC+1] = sensores.terreno[13];
			matriz[sensores.posF-3][sensores.posC+2] = sensores.terreno[14];
			matriz[sensores.posF-3][sensores.posC+3] = sensores.terreno[15];
			break;

		case noreste:
			matriz[sensores.posF][sensores.posC] = sensores.terreno[0];
			matriz[sensores.posF-1][sensores.posC] = sensores.terreno[1];
			matriz[sensores.posF-1][sensores.posC+1] = sensores.terreno[2];
			matriz[sensores.posF][sensores.posC+1] = sensores.terreno[3];
			matriz[sensores.posF-2][sensores.posC] = sensores.terreno[4];
			matriz[sensores.posF-2][sensores.posC+1] = sensores.terreno[5];
			matriz[sensores.posF-2][sensores.posC+2] = sensores.terreno[6];
			matriz[sensores.posF-1][sensores.posC+2] = sensores.terreno[7];
			matriz[sensores.posF][sensores.posC+2] = sensores.terreno[8];
			matriz[sensores.posF-3][sensores.posC] = sensores.terreno[9];
			matriz[sensores.posF-3][sensores.posC+1] = sensores.terreno[10];
			matriz[sensores.posF-3][sensores.posC+2] = sensores.terreno[11];
			matriz[sensores.posF-3][sensores.posC+3] = sensores.terreno[12];
			matriz[sensores.posF-2][sensores.posC+3] = sensores.terreno[13];
			matriz[sensores.posF-1][sensores.posC+3] = sensores.terreno[14];
			matriz[sensores.posF][sensores.posC+3] = sensores.terreno[15];
			break;

		case este:
			matriz[sensores.posF][sensores.posC] = sensores.terreno[0];
			matriz[sensores.posF-1][sensores.posC+1] = sensores.terreno[1];
			matriz[sensores.posF][sensores.posC+1] = sensores.terreno[2];
			matriz[sensores.posF+1][sensores.posC+1] = sensores.terreno[3];
			matriz[sensores.posF-2][sensores.posC+2] = sensores.terreno[4];
			matriz[sensores.posF-1][sensores.posC+2] = sensores.terreno[5];
			matriz[sensores.posF][sensores.posC+2] = sensores.terreno[6];
			matriz[sensores.posF+1][sensores.posC+2] = sensores.terreno[7];
			matriz[sensores.posF+2][sensores.posC+2] = sensores.terreno[8];
			matriz[sensores.posF-3][sensores.posC+3] = sensores.terreno[9];
			matriz[sensores.posF-2][sensores.posC+3] = sensores.terreno[10];
			matriz[sensores.posF-1][sensores.posC+3] = sensores.terreno[11];
			matriz[sensores.posF][sensores.posC+3] = sensores.terreno[12];
			matriz[sensores.posF+1][sensores.posC+3] = sensores.terreno[13];
			matriz[sensores.posF+2][sensores.posC+3] = sensores.terreno[14];
			matriz[sensores.posF+3][sensores.posC+3] = sensores.terreno[15];
			break;

		case sureste:
			matriz[sensores.posF][sensores.posC] = sensores.terreno[0];
			matriz[sensores.posF][sensores.posC+1] = sensores.terreno[1];
			matriz[sensores.posF+1][sensores.posC+1] = sensores.terreno[2];
			matriz[sensores.posF+1][sensores.posC] = sensores.terreno[3];
			matriz[sensores.posF][sensores.posC+2] = sensores.terreno[4];
			matriz[sensores.posF+1][sensores.posC+2] = sensores.terreno[5];
			matriz[sensores.posF+2][sensores.posC+2] = sensores.terreno[6];
			matriz[sensores.posF+2][sensores.posC+1] = sensores.terreno[7];
			matriz[sensores.posF+2][sensores.posC] = sensores.terreno[8];
			matriz[sensores.posF][sensores.posC+3] = sensores.terreno[9];
			matriz[sensores.posF+1][sensores.posC+3] = sensores.terreno[10];
			matriz[sensores.posF+2][sensores.posC+3] = sensores.terreno[11];
			matriz[sensores.posF+3][sensores.posC+3] = sensores.terreno[12];
			matriz[sensores.posF+3][sensores.posC+2] = sensores.terreno[13];
			matriz[sensores.posF+3][sensores.posC+1] = sensores.terreno[14];
			matriz[sensores.posF+3][sensores.posC] = sensores.terreno[15];
			break;

		case sur:
			matriz[sensores.posF][sensores.posC] = sensores.terreno[0];
			matriz[sensores.posF+1][sensores.posC+1] = sensores.terreno[1];
			matriz[sensores.posF+1][sensores.posC] = sensores.terreno[2];
			matriz[sensores.posF+1][sensores.posC-1] = sensores.terreno[3];
			matriz[sensores.posF+2][sensores.posC+2] = sensores.terreno[4];
			matriz[sensores.posF+2][sensores.posC+1] = sensores.terreno[5];
			matriz[sensores.posF+2][sensores.posC] = sensores.terreno[6];
			matriz[sensores.posF+2][sensores.posC-1] = sensores.terreno[7];
			matriz[sensores.posF+2][sensores.posC-2] = sensores.terreno[8];
			matriz[sensores.posF+3][sensores.posC+3] = sensores.terreno[9];
			matriz[sensores.posF+3][sensores.posC+2] = sensores.terreno[10];
			matriz[sensores.posF+3][sensores.posC+1] = sensores.terreno[11];
			matriz[sensores.posF+3][sensores.posC] = sensores.terreno[12];
			matriz[sensores.posF+3][sensores.posC-1] = sensores.terreno[13];
			matriz[sensores.posF+3][sensores.posC-2] = sensores.terreno[14];
			matriz[sensores.posF+3][sensores.posC-3] = sensores.terreno[15];
			break;

		case suroeste:
			matriz[sensores.posF][sensores.posC] = sensores.terreno[0];
			matriz[sensores.posF+1][sensores.posC] = sensores.terreno[1];
			matriz[sensores.posF+1][sensores.posC-1] = sensores.terreno[2];
			matriz[sensores.posF][sensores.posC-1] = sensores.terreno[3];
			matriz[sensores.posF+2][sensores.posC] = sensores.terreno[4];
			matriz[sensores.posF+2][sensores.posC-1] = sensores.terreno[5];
			matriz[sensores.posF+2][sensores.posC-2] = sensores.terreno[6];
			matriz[sensores.posF+1][sensores.posC-2] = sensores.terreno[7];
			matriz[sensores.posF][sensores.posC-2] = sensores.terreno[8];
			matriz[sensores.posF+3][sensores.posC] = sensores.terreno[9];
			matriz[sensores.posF+3][sensores.posC-1] = sensores.terreno[10];
			matriz[sensores.posF+3][sensores.posC-2] = sensores.terreno[11];
			matriz[sensores.posF+3][sensores.posC-3] = sensores.terreno[12];
			matriz[sensores.posF+2][sensores.posC-3] = sensores.terreno[13];
			matriz[sensores.posF+1][sensores.posC-3] = sensores.terreno[14];
			matriz[sensores.posF][sensores.posC-3] = sensores.terreno[15];
			break;

		case oeste:
			matriz[sensores.posF][sensores.posC] = sensores.terreno[0];
			matriz[sensores.posF+1][sensores.posC-1] = sensores.terreno[1];
			matriz[sensores.posF][sensores.posC-1] = sensores.terreno[2];
			matriz[sensores.posF-1][sensores.posC-1] = sensores.terreno[3];
			matriz[sensores.posF+2][sensores.posC-2] = sensores.terreno[4];
			matriz[sensores.posF+1][sensores.posC-2] = sensores.terreno[5];
			matriz[sensores.posF][sensores.posC-2] = sensores.terreno[6];
			matriz[sensores.posF-1][sensores.posC-2] = sensores.terreno[7];
			matriz[sensores.posF-2][sensores.posC-2] = sensores.terreno[8];
			matriz[sensores.posF+3][sensores.posC-3] = sensores.terreno[9];
			matriz[sensores.posF+2][sensores.posC-3] = sensores.terreno[10];
			matriz[sensores.posF+1][sensores.posC-3] = sensores.terreno[11];
			matriz[sensores.posF][sensores.posC-3] = sensores.terreno[12];
			matriz[sensores.posF-1][sensores.posC-3] = sensores.terreno[13];
			matriz[sensores.posF-2][sensores.posC-3] = sensores.terreno[14];
			matriz[sensores.posF-3][sensores.posC-3] = sensores.terreno[15];
			break;

		case noroeste:
			matriz[sensores.posF][sensores.posC] = sensores.terreno[0];
			matriz[sensores.posF][sensores.posC-1] = sensores.terreno[1];
			matriz[sensores.posF-1][sensores.posC-1] = sensores.terreno[2];
			matriz[sensores.posF-1][sensores.posC] = sensores.terreno[3];
			matriz[sensores.posF][sensores.posC-2] = sensores.terreno[4];
			matriz[sensores.posF-1][sensores.posC-2] = sensores.terreno[5];
			matriz[sensores.posF-2][sensores.posC-2] = sensores.terreno[6];
			matriz[sensores.posF-2][sensores.posC-1] = sensores.terreno[7];
			matriz[sensores.posF-2][sensores.posC] = sensores.terreno[8];
			matriz[sensores.posF][sensores.posC-3] = sensores.terreno[9];
			matriz[sensores.posF-1][sensores.posC-3] = sensores.terreno[10];
			matriz[sensores.posF-2][sensores.posC-3] = sensores.terreno[11];
			matriz[sensores.posF-3][sensores.posC-3] = sensores.terreno[12];
			matriz[sensores.posF-3][sensores.posC-2] = sensores.terreno[13];
			matriz[sensores.posF-3][sensores.posC-1] = sensores.terreno[14];
			matriz[sensores.posF-3][sensores.posC] = sensores.terreno[15];
			break;
	}
}

void ComportamientoJugador::rellenarPrecipicios(vector< vector<unsigned char> > &matriz){
	for (int i=0; i<3; ++i)
		for(int j=0;j<matriz.size();++j){

			matriz[i][j]='P';
			matriz[matriz.size()-i-1][j]='P';
			matriz[j][i]='P';
			matriz[j][matriz.size()-i-1]='P';
		}

}

bool ComportamientoJugador::loboCerca(Sensores sensores){
	for (int i=1; i<sensores.superficie.size()-7; ++i)
		if (sensores.superficie[i]=='l')
			return true;

	return false;
}

bool ComportamientoJugador::bikiniCercaIZQ(Sensores sensores){
	return ( (sensores.terreno[9]=='K' && sensores.terreno[4]!='M' && sensores.terreno[1]!='M')||
				(sensores.terreno[4]=='K' && sensores.terreno[1]!='M') ||
				sensores.terreno[1]=='K');
}

bool ComportamientoJugador::bikiniCercaDCHA(Sensores sensores){
	return ( (sensores.terreno[15]=='K' && sensores.terreno[8]!='M' && sensores.terreno[3]!='M')||
				(sensores.terreno[8]=='K' && sensores.terreno[3]!='M') ||
				sensores.terreno[3]=='K');
}

bool ComportamientoJugador::zapatillasCercaIZQ(Sensores sensores){
	return ( (sensores.terreno[9]=='D' && sensores.terreno[4]!='M' && sensores.terreno[1]!='M')||
					(sensores.terreno[4]=='D' && sensores.terreno[1]!='M') ||
					sensores.terreno[1]=='D');
}

bool ComportamientoJugador::zapatillasCercaDCHA(Sensores sensores){
	return ( (sensores.terreno[15]=='D' && sensores.terreno[8]!='M' && sensores.terreno[3]!='M')||
					(sensores.terreno[8]=='D' && sensores.terreno[3]!='M') ||
					sensores.terreno[3]=='D');
}

bool ComportamientoJugador::posicionamientoCercaIZQ(Sensores sensores){
	return ( (sensores.terreno[9]=='G' && sensores.terreno[4]!='M' && sensores.terreno[1]!='M')||
			(sensores.terreno[4]=='G' && sensores.terreno[1]!='M') ||
			sensores.terreno[1]=='G') ;
}

bool ComportamientoJugador::posicionamientoCercaDCHA(Sensores sensores){
	return ( (sensores.terreno[15]=='G' && sensores.terreno[8]!='M' && sensores.terreno[3]!='M')||
				(sensores.terreno[8]=='G' && sensores.terreno[3]!='M') ||
				sensores.terreno[3]=='G');
}

bool ComportamientoJugador::posicionamientoCercaFrente(Sensores sensores){
	return (sensores.terreno[2]=='G' || sensores.terreno[6]=='G' || sensores.terreno[12]=='G');
}

bool ComportamientoJugador::hayPrecipicioDelante(Sensores sensores){
	bool precipicio = true;
	for (int i=1; i<sensores.terreno.size(); ++i)
		if (sensores.terreno[i]!='P')
			precipicio = false;

	return precipicio;
}

bool ComportamientoJugador::hayLimiteIzquierda(Sensores sensores){
	return ((sensores.terreno[1]=='P' || sensores.terreno[1]=='M')
					&& (sensores.terreno[2]=='P' || sensores.terreno[2]=='M'));
}

bool ComportamientoJugador::hayLimiteDerecha(Sensores sensores){
	return ((sensores.terreno[3]=='P' || sensores.terreno[3]=='M')
					&& (sensores.terreno[2]=='P' || sensores.terreno[2]=='M'));
}

bool ComportamientoJugador::hayHuecoIzquierda(Sensores sensores){
	return ((sensores.terreno[5]=='M' && sensores.terreno[11]=='M' && sensores.terreno[1]!='M'));
}

bool ComportamientoJugador::hayHuecoDerecha(Sensores sensores){
	return ((sensores.terreno[7]=='M' && sensores.terreno[13]=='M' && sensores.terreno[3]!='M'));
}

bool ComportamientoJugador::puedoAvanzar(Sensores sensores){
	return ((sensores.terreno[2]== 'T' || sensores.terreno[2]== 'S' || sensores.terreno[2]== 'G' ||
			sensores.terreno[2]== 'D' || sensores.terreno[2]== 'X' || sensores.terreno[2]== 'K'||
			(sensores.terreno[2]== 'A' && tiene_bikini) || (sensores.terreno[2]== 'B' && tiene_zapatillas) )
			&& sensores.superficie[2]== '_');
}

/* void ComportamientoJugador::elegirMovimiento(Action &accion, Sensores sensores){

	// Decidir la nueva acción
	if (loboCerca(sensores) && !girar_derecha)
		accion = actTURN_BL;

	else if (loboCerca(sensores) && girar_derecha)
		accion = actTURN_BR;

	else if (!bien_situado &&
					puedoCruzarDiagonalIZQSinZapatillas(sensores) && puedoCruzarDiagonalIZQSinBikini(sensores) &&
					posicionamientoCercaIZQ(sensores))
		accion = actTURN_SL;

	else if (!bien_situado &&
						puedoCruzarDiagonalDCHASinZapatillas(sensores) && puedoCruzarDiagonalDCHASinBikini(sensores) &&
						posicionamientoCercaDCHA(sensores))
		accion = actTURN_SR;

	else if (!tiene_zapatillas && !posicionamientoCercaIZQ(sensores) && !posicionamientoCercaDCHA(sensores) &&
						puedoCruzarDiagonalIZQSinZapatillas(sensores) && puedoCruzarDiagonalIZQSinBikini(sensores) &&
						zapatillasCercaIZQ(sensores))
		accion = actTURN_SL;

	else if (!tiene_zapatillas && !posicionamientoCercaIZQ(sensores) && !posicionamientoCercaDCHA(sensores) &&
						puedoCruzarDiagonalDCHASinZapatillas(sensores) && puedoCruzarDiagonalDCHASinBikini(sensores) &&
						zapatillasCercaDCHA(sensores))
		accion = actTURN_SR;

	else if (!tiene_bikini && !posicionamientoCercaIZQ(sensores) && !posicionamientoCercaDCHA(sensores) &&
						puedoCruzarDiagonalIZQSinZapatillas(sensores) && puedoCruzarDiagonalIZQSinBikini(sensores) &&
						bikiniCercaIZQ(sensores))
		accion = actTURN_SL;

	else if (!tiene_bikini && !posicionamientoCercaIZQ(sensores) && !posicionamientoCercaDCHA(sensores) &&
						puedoCruzarDiagonalDCHASinZapatillas(sensores) && puedoCruzarDiagonalDCHASinBikini(sensores) &&
						bikiniCercaDCHA(sensores))
		accion = actTURN_SR;

	else if (hayPrecipicioDelante(sensores) && !girar_derecha)
		accion = actTURN_BL;

	else if (hayPrecipicioDelante(sensores))
		accion = actTURN_SL;

	else if (hayHuecoIzquierda(sensores))
		accion = actTURN_SL;

	else if (hayHuecoDerecha(sensores))
		accion = actTURN_SR;

	else if (puedoAvanzar(sensores))
		accion = actFORWARD;

	else if (hayLimiteIzquierda(sensores))
		accion = actTURN_SR;

	else if (hayLimiteDerecha(sensores))
		accion = actTURN_SL;

	 else if (!girar_derecha)
		accion = actTURN_SL;

	else
		accion = actTURN_SR;



	if (sensores.bateria<2000 &&
			(sensores.terreno[9]=='X' ||  sensores.terreno[4]=='X' || sensores.terreno[1]=='X'))
		accion = actTURN_SL;

	else if (sensores.bateria<2000 &&
			(sensores.terreno[15]=='X' ||  sensores.terreno[8]=='X' || sensores.terreno[3]=='X'))
		accion = actTURN_SR;

	if((sensores.terreno[0] == 'B' and !tiene_zapatillas) || (sensores.terreno[0]=='A' and !tiene_bikini)
			&& sensores.superficie[2] == '_' )
		accion=actFORWARD;

	if ((sensores.terreno[2]=='G' || sensores.terreno[6]=='G' || sensores.terreno[12]=='G')
			&& !bien_situado)
		accion=actFORWARD;

	if (recargando && sensores.terreno[0] == 'X' && sensores.bateria < 5000)
		accion = actIDLE;
	else
		recargando = false;

	girar_derecha=(rand()%2==0);
}*/

void ComportamientoJugador::elegirMovimiento(Action &accion, Sensores sensores){
	if (!bien_situado){
		if (loboCerca(sensores) && !girar_derecha)
			accion = actTURN_BL;

		else if (loboCerca(sensores) && girar_derecha)
			accion = actTURN_BR;

		else if (posicionamientoCercaDCHA(sensores) && puedoCruzarDiagonalDCHASinZapatillas(sensores)
						 && puedoCruzarDiagonalDCHASinZapatillas(sensores))
			accion = actTURN_SR;

		else if (posicionamientoCercaIZQ(sensores) && puedoCruzarDiagonalIZQSinZapatillas(sensores)
						 && puedoCruzarDiagonalIZQSinZapatillas(sensores)){
			accion = actTURN_SL;
		}
	}

	girar_derecha=(rand()%2==0);
}

void ComportamientoJugador::irHaciaDesconocido(Action &accion, Sensores sensores){
	accion = actTURN_BL;
}

void ComportamientoJugador::actualizarVariablesEstado(){
	int a;
	// Actualizacion de las variables de estado
	switch (last_action){
		case actFORWARD:
			switch (current_state.brujula){
				case norte: current_state.fil--; break;
				case noreste: current_state.fil--; current_state.col++; break;
				case este: current_state.col++; break;
				case sureste: current_state.fil++; current_state.col++; break;
				case sur: current_state.fil++; break;
				case suroeste: current_state.fil++; current_state.col--; break;
				case oeste: current_state.col--; break;
				case noroeste: current_state.fil--; current_state.col--; break;
			}
			break;

		case actTURN_SL:
			a=current_state.brujula;
			a=(a+7)%8;
			current_state.brujula=static_cast<Orientacion>(a);
			break;

		case actTURN_SR:
			a=current_state.brujula;
			a=(a+1)%8;
			current_state.brujula=static_cast<Orientacion>(a);
			break;

		case actTURN_BL:
			a=current_state.brujula;
			a=(a+5)%8;
			current_state.brujula=static_cast<Orientacion>(a);
			break;

		case actTURN_BR:
			a=current_state.brujula;
			a=(a+3)%8;
			current_state.brujula=static_cast<Orientacion>(a);
			break;
	}
}

bool ComportamientoJugador::puedoCruzarDiagonalIZQSinZapatillas(Sensores sensores){
	if (tiene_zapatillas)
		return true;
	else{
		return (sensores.terreno[4]!='B' && sensores.terreno[1]!='B');
	}
}

bool ComportamientoJugador::puedoCruzarDiagonalDCHASinZapatillas(Sensores sensores){
	if (tiene_zapatillas)
		return true;
	else{
		return (sensores.terreno[8]!='B' && sensores.terreno[3]!='B');
	}
}

bool ComportamientoJugador::puedoCruzarDiagonalIZQSinBikini(Sensores sensores){
	if(tiene_bikini)
		return true;
	else{
		return (sensores.terreno[4]!='A' && sensores.terreno[1]!='A');
	}
}

bool ComportamientoJugador::puedoCruzarDiagonalDCHASinBikini(Sensores sensores){
	if(tiene_bikini)
		return true;
	else{
		return (sensores.terreno[8]!='A' && sensores.terreno[3]!='A');
	}
}
