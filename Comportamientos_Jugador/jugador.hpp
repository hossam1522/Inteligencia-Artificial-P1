#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state{
  int fil;
  int col;
  Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      current_state.fil = current_state.col = 99;
      current_state.brujula = norte;
      last_action = actIDLE;
      girar_derecha = bien_situado = false;
      tiene_bikini = tiene_zapatillas = recargando = false;
      precipicios_rellenos = false;
      orientacion_correcta = false;
      mapaVecesVisitado.resize(mapaResultado.size());
      for (int i=0; i<mapaResultado.size(); i++)
        mapaVecesVisitado[i].resize(mapaResultado[i].size(), 0);
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void rellenarMapa(Sensores sensores, vector< vector<unsigned char> > &matriz);
    void rellenarPrecipicios(vector< vector<unsigned char> > &matriz);
    int vecesVisitado (int num, Sensores sensores);
    void elegirMovimiento(Action &accion, Sensores sensores);
    void irHaciaDesconocido (Action &accion, Sensores sensores);
    void actualizarVariablesEstado();
    bool loboCerca(Sensores sensores);
    bool bikiniCercaIZQ(Sensores sensores);
    bool bikiniCercaDCHA(Sensores sensores);
    bool bikiniCercaFrente(Sensores sensores);
    bool zapatillasCercaIZQ(Sensores sensores);
    bool zapatillasCercaDCHA(Sensores sensores);
    bool zapatillasCercaFrente(Sensores sensores);
    bool posicionamientoCercaIZQ(Sensores sensores);
    bool posicionamientoCercaDCHA(Sensores sensores);
    bool posicionamientoCercaFrente(Sensores sensores);
    bool hayPrecipicioDelante(Sensores sensores);
    bool hayLimiteIzquierda(Sensores sensores);
    bool hayLimiteDerecha(Sensores sensores);
    bool puedoAvanzar(Sensores sensores);
    bool puedoAvanzarDCHA(Sensores sensores);
    bool puedoAvanzarIZQ(Sensores sensores);
    bool hayHuecoIzquierda (Sensores sensores);
    bool hayHuecoDerecha (Sensores sensores);
    bool puedoCruzarDiagonalIZQSinZapatillas(Sensores sensores);
    bool puedoCruzarDiagonalDCHASinZapatillas(Sensores sensores);
    bool puedoCruzarFrenteSinZapatillas(Sensores sensores);
    bool puedoCruzarDiagonalIZQSinBikini(Sensores sensores);
    bool puedoCruzarDiagonalDCHASinBikini(Sensores sensores);
    bool puedoCruzarFrenteSinBikini(Sensores sensores);

  private:

  // Declarar aquí las variables de estado
  vector< vector<int> > mapaVecesVisitado;
  state current_state;
  Action last_action;
  bool girar_derecha, bien_situado, orientacion_correcta;
  bool tiene_bikini, tiene_zapatillas, recargando;
  bool precipicios_rellenos;
};

#endif
