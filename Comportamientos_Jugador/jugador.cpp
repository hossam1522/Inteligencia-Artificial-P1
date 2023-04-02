#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <bits/stdc++.h>
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

int ComportamientoJugador::vecesVisitado (int num, Sensores sensores){
	// Esta funcion devuelve el numero de veces que se ha visitado una casilla dentro del rango de visión

	if (sensores.terreno[num]!='M' && sensores.terreno[num]!='P'){

			if (sensores.terreno[num]=='B' && !tiene_zapatillas)
				return INT_MAX;
			else if (sensores.terreno[num]=='A' && !tiene_bikini)
				return INT_MAX;

	switch(sensores.sentido){
		case norte:
			switch(num){
				case 0:
					return mapaVecesVisitado[current_state.fil][current_state.col];
					break;
				case 1:
					return mapaVecesVisitado[current_state.fil-1][current_state.col-1];
					break;
				case 2:
					return mapaVecesVisitado[current_state.fil-1][current_state.col];
					break;
				case 3:
					return mapaVecesVisitado[current_state.fil-1][current_state.col+1];
					break;
				case 4:
					return mapaVecesVisitado[current_state.fil-2][current_state.col-2];
					break;
				case 5:
					return mapaVecesVisitado[current_state.fil-2][current_state.col-1];
					break;
				case 6:
					return mapaVecesVisitado[current_state.fil-2][current_state.col];
					break;
				case 7:
					return mapaVecesVisitado[current_state.fil-2][current_state.col+1];
					break;
				case 8:
					return mapaVecesVisitado[current_state.fil-2][current_state.col+2];
					break;
				case 9:
					return mapaVecesVisitado[current_state.fil-3][current_state.col-3];
					break;
				case 10:
					return mapaVecesVisitado[current_state.fil-3][current_state.col-2];
					break;
				case 11:
					return mapaVecesVisitado[current_state.fil-3][current_state.col-1];
					break;
				case 12:
					return mapaVecesVisitado[current_state.fil-3][current_state.col];
					break;
				case 13:
					return mapaVecesVisitado[current_state.fil-3][current_state.col+1];
					break;
				case 14:
					return mapaVecesVisitado[current_state.fil-3][current_state.col+2];
					break;
				case 15:
					return mapaVecesVisitado[current_state.fil-3][current_state.col+3];
					break;
			}
			break;

		case noreste:
			switch(num){
				case 0:
					return mapaVecesVisitado[current_state.fil][current_state.col];
					break;
				case 1:
					return mapaVecesVisitado[current_state.fil-1][current_state.col];
					break;
				case 2:
					return mapaVecesVisitado[current_state.fil-1][current_state.col+1];
					break;
				case 3:
					return mapaVecesVisitado[current_state.fil][current_state.col+1];
					break;
				case 4:
					return mapaVecesVisitado[current_state.fil-2][current_state.col];
					break;
				case 5:
					return mapaVecesVisitado[current_state.fil-2][current_state.col+1];
					break;
				case 6:
					return mapaVecesVisitado[current_state.fil-2][current_state.col+2];
					break;
				case 7:
					return mapaVecesVisitado[current_state.fil-1][current_state.col+2];
					break;
				case 8:
					return mapaVecesVisitado[current_state.fil][current_state.col+2];
					break;
				case 9:
					return mapaVecesVisitado[current_state.fil-3][current_state.col];
					break;
				case 10:
					return mapaVecesVisitado[current_state.fil-3][current_state.col+1];
					break;
				case 11:
					return mapaVecesVisitado[current_state.fil-3][current_state.col+2];
					break;
				case 12:
					return mapaVecesVisitado[current_state.fil-3][current_state.col+3];
					break;
				case 13:
					return mapaVecesVisitado[current_state.fil-2][current_state.col+3];
					break;
				case 14:
					return mapaVecesVisitado[current_state.fil-1][current_state.col+3];
					break;
				case 15:
					return mapaVecesVisitado[current_state.fil][current_state.col+3];
					break;
			}
			break;

		case este:
			switch(num){
				case 0:
					return mapaVecesVisitado[current_state.fil][current_state.col];
					break;
				case 1:
					return mapaVecesVisitado[current_state.fil-1][current_state.col+1];
					break;
				case 2:
					return mapaVecesVisitado[current_state.fil][current_state.col+1];
					break;
				case 3:
					return mapaVecesVisitado[current_state.fil+1][current_state.col+1];
					break;
				case 4:
					return mapaVecesVisitado[current_state.fil-2][current_state.col+2];
					break;
				case 5:
					return mapaVecesVisitado[current_state.fil-1][current_state.col+2];
					break;
				case 6:
					return mapaVecesVisitado[current_state.fil][current_state.col+2];
					break;
				case 7:
					return mapaVecesVisitado[current_state.fil+1][current_state.col+2];
					break;
				case 8:
					return mapaVecesVisitado[current_state.fil+2][current_state.col+2];
					break;
				case 9:
					return mapaVecesVisitado[current_state.fil-3][current_state.col+3];
					break;
				case 10:
					return mapaVecesVisitado[current_state.fil-2][current_state.col+3];
					break;
				case 11:
					return mapaVecesVisitado[current_state.fil-1][current_state.col+3];
					break;
				case 12:
					return mapaVecesVisitado[current_state.fil][current_state.col+3];
					break;
				case 13:
					return mapaVecesVisitado[current_state.fil+1][current_state.col+3];
					break;
				case 14:
					return mapaVecesVisitado[current_state.fil+2][current_state.col+3];
					break;
				case 15:
					return mapaVecesVisitado[current_state.fil+3][current_state.col+3];
					break;
			}
			break;

		case sureste:
			switch (num){
				case 0:
					return mapaVecesVisitado[current_state.fil][current_state.col];
					break;
				case 1:
					return mapaVecesVisitado[current_state.fil][current_state.col+1];
					break;
				case 2:
					return mapaVecesVisitado[current_state.fil+1][current_state.col+1];
					break;
				case 3:
					return mapaVecesVisitado[current_state.fil+1][current_state.col];
					break;
				case 4:
					return mapaVecesVisitado[current_state.fil][current_state.col+2];
					break;
				case 5:
					return mapaVecesVisitado[current_state.fil+1][current_state.col+2];
					break;
				case 6:
					return mapaVecesVisitado[current_state.fil+2][current_state.col+2];
					break;
				case 7:
					return mapaVecesVisitado[current_state.fil+2][current_state.col+1];
					break;
				case 8:
					return mapaVecesVisitado[current_state.fil+2][current_state.col];
					break;
				case 9:
					return mapaVecesVisitado[current_state.fil][current_state.col+3];
					break;
				case 10:
					return mapaVecesVisitado[current_state.fil+1][current_state.col+3];
					break;
				case 11:
					return mapaVecesVisitado[current_state.fil+2][current_state.col+3];
					break;
				case 12:
					return mapaVecesVisitado[current_state.fil+3][current_state.col+3];
					break;
				case 13:
					return mapaVecesVisitado[current_state.fil+3][current_state.col+2];
					break;
				case 14:
					return mapaVecesVisitado[current_state.fil+3][current_state.col+1];
					break;
				case 15:
					return mapaVecesVisitado[current_state.fil+3][current_state.col];
					break;
			}
			break;

		case sur:
			switch (num){
				case 0:
					return mapaVecesVisitado[current_state.fil][current_state.col];
					break;
				case 1:
					return mapaVecesVisitado[current_state.fil+1][current_state.col+1];
					break;
				case 2:
					return mapaVecesVisitado[current_state.fil+1][current_state.col];
					break;
				case 3:
					return mapaVecesVisitado[current_state.fil+1][current_state.col-1];
					break;
				case 4:
					return mapaVecesVisitado[current_state.fil+2][current_state.col+2];
					break;
				case 5:
					return mapaVecesVisitado[current_state.fil+2][current_state.col+1];
					break;
				case 6:
					return mapaVecesVisitado[current_state.fil+2][current_state.col];
					break;
				case 7:
					return mapaVecesVisitado[current_state.fil+2][current_state.col-1];
					break;
				case 8:
					return mapaVecesVisitado[current_state.fil+2][current_state.col-2];
					break;
				case 9:
					return mapaVecesVisitado[current_state.fil+3][current_state.col+3];
					break;
				case 10:
					return mapaVecesVisitado[current_state.fil+3][current_state.col+2];
					break;
				case 11:
					return mapaVecesVisitado[current_state.fil+3][current_state.col+1];
					break;
				case 12:
					return mapaVecesVisitado[current_state.fil+3][current_state.col];
					break;
				case 13:
					return mapaVecesVisitado[current_state.fil+3][current_state.col-1];
					break;
				case 14:
					return mapaVecesVisitado[current_state.fil+3][current_state.col-2];
					break;
				case 15:
					return mapaVecesVisitado[current_state.fil+3][current_state.col-3];
					break;
			}
			break;

		case suroeste:
			switch(num){
				case 0:
					return mapaVecesVisitado[current_state.fil][current_state.col];
					break;
				case 1:
					return mapaVecesVisitado[current_state.fil+1][current_state.col];
					break;
				case 2:
					return mapaVecesVisitado[current_state.fil+1][current_state.col-1];
					break;
				case 3:
					return mapaVecesVisitado[current_state.fil][current_state.col-1];
					break;
				case 4:
					return mapaVecesVisitado[current_state.fil+2][current_state.col];
					break;
				case 5:
					return mapaVecesVisitado[current_state.fil+2][current_state.col-1];
					break;
				case 6:
					return mapaVecesVisitado[current_state.fil+2][current_state.col-2];
					break;
				case 7:
					return mapaVecesVisitado[current_state.fil+1][current_state.col-2];
					break;
				case 8:
					return mapaVecesVisitado[current_state.fil][current_state.col-2];
					break;
				case 9:
					return mapaVecesVisitado[current_state.fil+3][current_state.col];
					break;
				case 10:
					return mapaVecesVisitado[current_state.fil+3][current_state.col-1];
					break;
				case 11:
					return mapaVecesVisitado[current_state.fil+3][current_state.col-2];
					break;
				case 12:
					return mapaVecesVisitado[current_state.fil+3][current_state.col-3];
					break;
				case 13:
					return mapaVecesVisitado[current_state.fil+2][current_state.col-3];
					break;
				case 14:
					return mapaVecesVisitado[current_state.fil+1][current_state.col-3];
					break;
				case 15:
					return mapaVecesVisitado[current_state.fil][current_state.col-3];
					break;
			}
			break;

		case oeste:
			switch(num){
				case 0:
					return mapaVecesVisitado[current_state.fil][current_state.col];
					break;
				case 1:
					return mapaVecesVisitado[current_state.fil+1][current_state.col-1];
					break;
				case 2:
					return mapaVecesVisitado[current_state.fil][current_state.col-1];
					break;
				case 3:
					return mapaVecesVisitado[current_state.fil-1][current_state.col-1];
					break;
				case 4:
					return mapaVecesVisitado[current_state.fil+2][current_state.col-2];
					break;
				case 5:
					return mapaVecesVisitado[current_state.fil+1][current_state.col-2];
					break;
				case 6:
					return mapaVecesVisitado[current_state.fil][current_state.col-2];
					break;
				case 7:
					return mapaVecesVisitado[current_state.fil-1][current_state.col-2];
					break;
				case 8:
					return mapaVecesVisitado[current_state.fil-2][current_state.col-2];
					break;
				case 9:
					return mapaVecesVisitado[current_state.fil+3][current_state.col-3];
					break;
				case 10:
					return mapaVecesVisitado[current_state.fil+2][current_state.col-3];
					break;
				case 11:
					return mapaVecesVisitado[current_state.fil+1][current_state.col-3];
					break;
				case 12:
					return mapaVecesVisitado[current_state.fil][current_state.col-3];
					break;
				case 13:
					return mapaVecesVisitado[current_state.fil-1][current_state.col-3];
					break;
				case 14:
					return mapaVecesVisitado[current_state.fil-2][current_state.col-3];
					break;
				case 15:
					return mapaVecesVisitado[current_state.fil-3][current_state.col-3];
					break;
			}
			break;

		case noroeste:
			switch(num){
				case 0:
					return mapaVecesVisitado[current_state.fil][current_state.col];
					break;
				case 1:
					return mapaVecesVisitado[current_state.fil][current_state.col-1];
					break;
				case 2:
					return mapaVecesVisitado[current_state.fil-1][current_state.col-1];
					break;
				case 3:
					return mapaVecesVisitado[current_state.fil-1][current_state.col];
					break;
				case 4:
					return mapaVecesVisitado[current_state.fil][current_state.col-2];
					break;
				case 5:
					return mapaVecesVisitado[current_state.fil-1][current_state.col-2];
					break;
				case 6:
					return mapaVecesVisitado[current_state.fil-2][current_state.col-2];
					break;
				case 7:
					return mapaVecesVisitado[current_state.fil-2][current_state.col-1];
					break;
				case 8:
					return mapaVecesVisitado[current_state.fil-2][current_state.col];
					break;
				case 9:
					return mapaVecesVisitado[current_state.fil][current_state.col-3];
					break;
				case 10:
					return mapaVecesVisitado[current_state.fil-1][current_state.col-3];
					break;
				case 11:
					return mapaVecesVisitado[current_state.fil-2][current_state.col-3];
					break;
				case 12:
					return mapaVecesVisitado[current_state.fil-3][current_state.col-3];
					break;
				case 13:
					return mapaVecesVisitado[current_state.fil-3][current_state.col-2];
					break;
				case 14:
					return mapaVecesVisitado[current_state.fil-3][current_state.col-1];
					break;
				case 15:
					return mapaVecesVisitado[current_state.fil-3][current_state.col];
					break;
			}
			break;
	}
	}
	return INT_MAX;
}

bool ComportamientoJugador::loboCerca(Sensores sensores){
	for (int i=1; i<sensores.superficie.size(); ++i)
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

bool ComportamientoJugador::bikiniCercaFrente(Sensores sensores){
	return ( (sensores.terreno[12]=='K' && sensores.terreno[6]!='M' && sensores.terreno[2]!='M')||
				(sensores.terreno[6]=='K' && sensores.terreno[2]!='M') ||
				sensores.terreno[2]=='K');
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

bool ComportamientoJugador::zapatillasCercaFrente(Sensores sensores){
	return ( (sensores.terreno[12]=='D' && sensores.terreno[6]!='M' && sensores.terreno[2]!='M')||
					(sensores.terreno[6]=='D' && sensores.terreno[2]!='M') ||
					sensores.terreno[2]=='D');
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
	return ( (sensores.terreno[12]=='G' && sensores.terreno[6]!='G' && sensores.terreno[2]!='G')||
					(sensores.terreno[6]=='G' && sensores.terreno[2]!='G') ||
					sensores.terreno[2]=='G');
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
	return ((sensores.terreno[5]=='M' && sensores.terreno[11]=='M' &&
					sensores.terreno[1]!='M' && sensores.terreno[4]!='M' && sensores.terreno[9]!='M' &&
					sensores.terreno[1]!='P' && sensores.terreno[4]!='P' && sensores.terreno[9]!='P') ||
					(sensores.terreno[5]=='P' && sensores.terreno[11]=='P' &&
					sensores.terreno[1]!='P' && sensores.terreno[4]!='P' && sensores.terreno[9]!='P' &&
					sensores.terreno[1]!='M' && sensores.terreno[4]!='M' && sensores.terreno[9]!='M'));
}

bool ComportamientoJugador::hayHuecoDerecha(Sensores sensores){
	return ((sensores.terreno[7]=='M' && sensores.terreno[13]=='M' &&
					sensores.terreno[3]!='M' && sensores.terreno[8]!='M' && sensores.terreno[15]!='M' &&
					sensores.terreno[3]!='P' && sensores.terreno[8]!='P' && sensores.terreno[15]!='P') ||
					(sensores.terreno[7]=='P' && sensores.terreno[13]=='P' &&
					sensores.terreno[3]!='P' && sensores.terreno[8]!='P' && sensores.terreno[15]!='P') &&
					sensores.terreno[3]!='M' && sensores.terreno[8]!='M' && sensores.terreno[15]!='M');
}

bool ComportamientoJugador::puedoAvanzar(int num, Sensores sensores){
	return ((sensores.terreno[num]== 'T' || sensores.terreno[num]== 'S' || sensores.terreno[num]== 'G' ||
			sensores.terreno[num]== 'D' || sensores.terreno[num]== 'X' || sensores.terreno[num]== 'K'||
			(sensores.terreno[num]== 'A' && tiene_bikini) || (sensores.terreno[num]== 'B' && tiene_zapatillas) )
			&& sensores.superficie[num]== '_');
}

void ComportamientoJugador::elegirMovimiento(Action &accion, Sensores sensores){

	if (!bien_situado){

		if (loboCerca(sensores) && !girar_derecha)
			accion = actTURN_BL;

		else if (loboCerca(sensores))
			accion = actTURN_BR;

		/* else if (hayPrecipicioDelante(sensores) ||
						(sensores.terreno[1]=='M' && sensores.terreno[2]=='M' && sensores.terreno[3]=='M'))
			accion = actTURN_BR; */

		else if (posicionamientoCercaFrente(sensores) /* && puedoCruzarFrenteSinZapatillas(sensores)
						 && puedoCruzarFrenteSinBikini(sensores) */)
			accion = actFORWARD;

		else if (posicionamientoCercaDCHA(sensores) && puedoCruzarDiagonalDCHASinZapatillas(sensores)
						 && puedoCruzarDiagonalDCHASinBikini(sensores))
			accion = actTURN_SR;

		else if (posicionamientoCercaIZQ(sensores) && puedoCruzarDiagonalIZQSinZapatillas(sensores)
						 && puedoCruzarDiagonalIZQSinBikini(sensores))
			accion = actTURN_SL;

		else if ((hayPrecipicioDelante(sensores) ||
						(sensores.terreno[1]=='M' && sensores.terreno[2]=='M' && sensores.terreno[3]=='M')) /* && !girar_derecha */)
			if (!girar_derecha)
				accion = actTURN_BL;
			else
				accion = actTURN_BR;

		else if ((last_action==actTURN_SR || last_action==actTURN_SL) && puedoAvanzar(2, sensores))
				accion = actFORWARD;

		else if (hayHuecoIzquierda(sensores))
			accion = actTURN_SL;

		else if (hayHuecoDerecha(sensores))
			accion = actTURN_SR;

		else if (hayLimiteIzquierda(sensores))
			accion = actTURN_SR;

		else if (hayLimiteDerecha(sensores))
			accion = actTURN_SL;

		else if (puedoAvanzar(2, sensores))
			accion = actFORWARD;



		else if (!girar_derecha)
		accion = actTURN_SL;

		else
		accion = actTURN_SR;


		if((sensores.terreno[0] == 'B' and !tiene_zapatillas) || (sensores.terreno[0]=='A' and !tiene_bikini)
			&& sensores.superficie[2] == '_' )
		accion=actFORWARD;
	}
	else{

		if (loboCerca(sensores) && !girar_derecha)
			accion = actTURN_BL;

		else if (loboCerca(sensores))
			accion = actTURN_BR;

		if (sensores.bateria<2000 &&
				(sensores.terreno[9]=='X' ||  sensores.terreno[4]=='X' || sensores.terreno[1]=='X'))
			accion = actTURN_SL;

		else if (sensores.bateria<2000 &&
				(sensores.terreno[15]=='X' ||  sensores.terreno[8]=='X' || sensores.terreno[3]=='X'))
			accion = actTURN_SR;

		else if (sensores.bateria<2000 &&
				(sensores.terreno[12]=='X' ||  sensores.terreno[6]=='X' || sensores.terreno[2]=='X'))
			accion = actFORWARD;

		else if ((!tiene_zapatillas && zapatillasCercaFrente(sensores) && puedoCruzarFrenteSinZapatillas(sensores) &&
							puedoCruzarFrenteSinBikini(sensores) ) ||
							(!tiene_bikini && bikiniCercaFrente(sensores) && puedoCruzarFrenteSinBikini(sensores) &&
							puedoCruzarFrenteSinZapatillas(sensores) ))
			accion = actFORWARD;

		else if (!tiene_zapatillas &&
							puedoCruzarDiagonalIZQSinZapatillas(sensores) && puedoCruzarDiagonalIZQSinBikini(sensores) &&
							zapatillasCercaIZQ(sensores))
			accion = actTURN_SL;

		else if (!tiene_zapatillas &&
							puedoCruzarDiagonalDCHASinZapatillas(sensores) && puedoCruzarDiagonalDCHASinBikini(sensores) &&
							zapatillasCercaDCHA(sensores))
			accion = actTURN_SR;

		else if (!tiene_bikini &&
							puedoCruzarDiagonalIZQSinZapatillas(sensores) && puedoCruzarDiagonalIZQSinBikini(sensores) &&
							bikiniCercaIZQ(sensores))
			accion = actTURN_SL;

		else if (!tiene_bikini &&
							puedoCruzarDiagonalDCHASinZapatillas(sensores) && puedoCruzarDiagonalDCHASinBikini(sensores) &&
							bikiniCercaDCHA(sensores))
			accion = actTURN_SR;

		else if (vecesVisitado(2, sensores) <= vecesVisitado(1,sensores) &&
							vecesVisitado(2, sensores) <= vecesVisitado(3,sensores) && puedoAvanzar(2, sensores)) {

			if ((sensores.terreno[3]=='M' && sensores.terreno[5]=='M') ||
					(sensores.terreno[3]=='M' && sensores.terreno[1]=='M'))
				accion = actFORWARD;

			else if (hayHuecoIzquierda(sensores))
				accion = actTURN_SL;

			else if (hayHuecoDerecha(sensores))
				accion = actTURN_SR;

			else if ((last_action==actTURN_SR || last_action==actTURN_SL) && puedoAvanzar(2, sensores))
				accion = actFORWARD;

			else if (vecesVisitado(1, sensores) <= vecesVisitado(2, sensores) &&
								vecesVisitado(4, sensores) < vecesVisitado(6,sensores) &&
								vecesVisitado(9, sensores) < vecesVisitado(12,sensores) && puedoAvanzar(1,sensores) &&
								puedoAvanzar(4, sensores) && puedoAvanzar(9, sensores))
				accion = actTURN_SL;

			else if (vecesVisitado(3, sensores) <= vecesVisitado(2, sensores) &&
								vecesVisitado(8, sensores) < vecesVisitado(6,sensores) &&
								vecesVisitado(15, sensores) < vecesVisitado(12,sensores) && puedoAvanzar(3, sensores) &&
								puedoAvanzar(8, sensores) && puedoAvanzar(15, sensores))
				accion = actTURN_SR;

			else
				accion = actFORWARD;

		}

		else if ((hayPrecipicioDelante(sensores) ||
						(sensores.terreno[1]=='M' && sensores.terreno[2]=='M' && sensores.terreno[3]=='M')) /* && !girar_derecha */)
			if (!girar_derecha)
				accion = actTURN_BL;
			else
				accion = actTURN_BR;

		else if (hayHuecoIzquierda(sensores))
			accion = actTURN_SL;

		else if (hayHuecoDerecha(sensores))
			accion = actTURN_SR;

		else if ((last_action==actTURN_SR || last_action==actTURN_SL) && puedoAvanzar(2, sensores))
				accion = actFORWARD;

		else if (vecesVisitado(1, sensores) <= vecesVisitado(2, sensores) &&
							vecesVisitado(4, sensores) < vecesVisitado(6,sensores) &&
							vecesVisitado(9, sensores) < vecesVisitado(12,sensores) && puedoAvanzar(1,sensores) &&
							puedoAvanzar(4, sensores) && puedoAvanzar(9, sensores))
			accion = actTURN_SL;

		else if (vecesVisitado(3, sensores) <= vecesVisitado(2, sensores) &&
							vecesVisitado(8, sensores) < vecesVisitado(6,sensores) &&
							vecesVisitado(15, sensores) < vecesVisitado(12,sensores) && puedoAvanzar(3, sensores) &&
							puedoAvanzar(8, sensores) && puedoAvanzar(15, sensores))
			accion = actTURN_SR;


		else if (puedoAvanzar(2,sensores))
			accion = actFORWARD;

		/*else if (hayLimiteIzquierda(sensores))
			accion = actTURN_SR;

		else if (hayLimiteDerecha(sensores))
			accion = actTURN_SL; */

		else if (!girar_derecha)
		accion = actTURN_SL;

		else
		accion = actTURN_SR;


		if (recargando && sensores.terreno[0] == 'X' && sensores.bateria < 4000)
			accion = actIDLE;
		else
			recargando = false;

		if((sensores.terreno[0] == 'B' and !tiene_zapatillas) || (sensores.terreno[0]=='A' and !tiene_bikini)
			&& sensores.superficie[2] == '_' )
		accion=actFORWARD;
	}

	girar_derecha=(rand()%2==0);
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
		return (sensores.terreno[4]!='B' && sensores.terreno[1]!='B' &&
						sensores.terreno[4]!='M' && sensores.terreno[1]!='M');
	}
}

bool ComportamientoJugador::puedoCruzarDiagonalDCHASinZapatillas(Sensores sensores){
	if (tiene_zapatillas)
		return true;
	else{
		return (sensores.terreno[8]!='B' && sensores.terreno[3]!='B' &&
						sensores.terreno[8]!='M' && sensores.terreno[3]!='M');
	}
}

bool ComportamientoJugador::puedoCruzarFrenteSinZapatillas(Sensores sensores){
	if (tiene_zapatillas)
		return true;
	else{
		return (sensores.terreno[6]!='B' && sensores.terreno[2]!='B' &&
						sensores.terreno[6]!='M' && sensores.terreno[2]!='M');
	}
}

bool ComportamientoJugador::puedoCruzarDiagonalIZQSinBikini(Sensores sensores){
	if(tiene_bikini)
		return true;
	else{
		return (sensores.terreno[4]!='A' && sensores.terreno[1]!='A' &&
						sensores.terreno[4]!='M' && sensores.terreno[1]!='M');
	}
}

bool ComportamientoJugador::puedoCruzarDiagonalDCHASinBikini(Sensores sensores){
	if(tiene_bikini)
		return true;
	else{
		return (sensores.terreno[8]!='A' && sensores.terreno[3]!='A' &&
						sensores.terreno[8]!='M' && sensores.terreno[3]!='M');
	}
}

bool ComportamientoJugador::puedoCruzarFrenteSinBikini(Sensores sensores){
	if(tiene_bikini)
		return true;
	else{
		return (sensores.terreno[6]!='A' && sensores.terreno[2]!='A' &&
						sensores.terreno[6]!='M' && sensores.terreno[2]!='M');
	}
}
