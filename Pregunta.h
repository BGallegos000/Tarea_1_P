// Pregunta.h
#ifndef PREGUNTA_H
#define PREGUNTA_H

#include <iostream>
#include <string>
using namespace std;

// Definición de constantes
#define MAX_PREGUNTAS 100
#define MAX_OPCIONES 10

// Clase base para todas las preguntas
class Pregunta {
protected:
    string enunciado;       // Texto de la pregunta
    string solucion;        // Solución interna (no visible para estudiantes)
    string nivelBloom;      // Nivel de la taxonomía de Bloom
    string asignatura;      // Asignatura a la que pertenece la pregunta
    int tiempoEstimado;     // Tiempo estimado para responder

public:
    Pregunta() {}
    virtual ~Pregunta() {} // Destructor virtual necesario



    // Constructor con parámetros
    Pregunta(string e, string s, string n, int t, string a);

    // Asigna los datos comunes a toda pregunta
    void setBase(string e, string s, string n, int t, string a);

    // Getters
    string getNivel();
    int getTiempo();
    string getAsignatura();
    string getTipo(); // Virtual no se puede usar, pero simulado manualmente

    // Mostrar información base de la pregunta
    void mostrarBase();

    // Guardar pregunta en archivo (manual según tipo)
    virtual void guardar(ofstream &out) = 0;
};

// Clase para preguntas de elección múltiple
class PreguntaEleccionMultiple : public Pregunta {
private:
    string opciones[MAX_OPCIONES];  // Opciones disponibles
    int cantidadOpciones;
    int respuestaCorrecta;

public:
    PreguntaEleccionMultiple();
    void setDatos(string e, string s, string n, int t, string a, string ops[], int cant, int correcta);
    void mostrar();
    void guardar(ofstream &out);
};

// Clase para preguntas de Verdadero/Falso
class PreguntaVerdaderoyFalso : public Pregunta {
private:
    bool respuestaEsperada;

public:
    PreguntaVerdaderoyFalso();
    void setDatos(string e, string s, string n, int t, string a, bool r);
    void mostrar();
    void guardar(ofstream &out);
};

// Clase para preguntas de desarrollo
class PreguntaDesarrollo : public Pregunta {
private:
    string respuestaEsperada;

public:
    PreguntaDesarrollo();
    void setDatos(string e, string s, string n, int t, string a, string r);
    void mostrar();
    void guardar(ofstream &out);
};

// Estructura para almacenar puntero genérico a pregunta y su tipo
struct RegistroPregunta {
    Pregunta* ptr;
    int tipo; // 1 = Elección múltiple, 2 = Verdadero/Falso, 3 = Desarrollo
};

// Clase para gestionar una evaluación
class Evaluacion {
private:
    string asignatura;                          // Nombre de la asignatura
    RegistroPregunta preguntas[MAX_PREGUNTAS];  // Preguntas incluidas en evaluación
    int totalPreguntas;                         // Contador de preguntas

public:
    Evaluacion();
    void setAsignatura(string a);
    void agregarPregunta(RegistroPregunta reg);
    void mostrar();
};

#endif // PREGUNTA_H
