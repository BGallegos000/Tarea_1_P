// Pregunta.cpp
#include "Pregunta.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// Constructor con parámetros para clase base
Pregunta::Pregunta(string e, string s, string n, int t, string a) {
    enunciado = e;
    solucion = s;
    nivelBloom = n;
    tiempoEstimado = t;
    asignatura = a;
}

// Asignar datos comunes
void Pregunta::setBase(string e, string s, string n, int t, string a) {
    enunciado = e;
    solucion = s;
    nivelBloom = n;
    tiempoEstimado = t;
    asignatura = a;
}

// Getters
string Pregunta::getNivel() { return nivelBloom; }
int Pregunta::getTiempo() { return tiempoEstimado; }
string Pregunta::getAsignatura() { return asignatura; }

// Mostrar datos comunes
void Pregunta::mostrarBase() {
    cout << "Asignatura: " << asignatura << "\n";
    cout << "Nivel Bloom: " << nivelBloom << "\n";
    cout << "Tiempo estimado: " << tiempoEstimado << " min\n";
    cout << "Pregunta: " << enunciado << "\n";
}

// ==============================
// PreguntaEleccionMultiple
// ==============================
PreguntaEleccionMultiple::PreguntaEleccionMultiple() {}

void PreguntaEleccionMultiple::setDatos(string e, string s, string n, int t, string a, string ops[], int cant, int correcta) {
    setBase(e, s, n, t, a);
    cantidadOpciones = cant;
    respuestaCorrecta = correcta;
    for (int i = 0; i < cant; ++i) {
        opciones[i] = ops[i];
    }
}

void PreguntaEleccionMultiple::mostrar() {
    cout << "Tipo: Elección Múltiple\n";
    mostrarBase();
    for (int i = 0; i < cantidadOpciones; ++i) {
        cout << i + 1 << ". " << opciones[i] << "\n";
    }
    cout << "Respuesta correcta: " << opciones[respuestaCorrecta] << "\n\n";
}

// Guardar pregunta en archivo
void PreguntaEleccionMultiple::guardar(ofstream &out) {
    out << "1|" << enunciado << "|" << solucion << "|" << nivelBloom << "|" << tiempoEstimado << "|" << asignatura << "|"
        << cantidadOpciones << "|" << respuestaCorrecta;
    for (int i = 0; i < cantidadOpciones; ++i) {
        out << "|" << opciones[i];
    }
    out << "\n";
}

// ==============================
// PreguntaVerdaderoyFalso
// ==============================
PreguntaVerdaderoyFalso::PreguntaVerdaderoyFalso() {}

void PreguntaVerdaderoyFalso::setDatos(string e, string s, string n, int t, string a, bool r) {
    setBase(e, s, n, t, a);
    respuestaEsperada = r;
}

void PreguntaVerdaderoyFalso::mostrar() {
    cout << "Tipo: Verdadero/Falso\n";
    mostrarBase();
    cout << "Respuesta esperada: " << (respuestaEsperada ? "V" : "F") << "\n\n";
}

void PreguntaVerdaderoyFalso::guardar(ofstream &out) {
    out << "2|" << enunciado << "|" << solucion << "|" << nivelBloom << "|" << tiempoEstimado << "|" << asignatura << "|"
        << (respuestaEsperada ? "1" : "0") << "\n";
}

// ==============================
// PreguntaDesarrollo
// ==============================
PreguntaDesarrollo::PreguntaDesarrollo() {}

void PreguntaDesarrollo::setDatos(string e, string s, string n, int t, string a, string r) {
    setBase(e, s, n, t, a);
    respuestaEsperada = r;
}

void PreguntaDesarrollo::mostrar() {
    cout << "Tipo: Respuesta Corta\n";
    mostrarBase();
    cout << "Respuesta esperada: " << respuestaEsperada << "\n\n";
}

void PreguntaDesarrollo::guardar(ofstream &out) {
    out << "3|" << enunciado << "|" << solucion << "|" << nivelBloom << "|" << tiempoEstimado << "|" << asignatura
        << "|" << respuestaEsperada << "\n";
}

// ==============================
// Evaluacion
// ==============================
Evaluacion::Evaluacion() {
    totalPreguntas = 0;
}

void Evaluacion::setAsignatura(string a) {
    asignatura = a;
}

void Evaluacion::agregarPregunta(RegistroPregunta reg) {
    if (totalPreguntas < MAX_PREGUNTAS) {
        preguntas[totalPreguntas++] = reg;
    }
}

void Evaluacion::mostrar() {
    cout << "\n--- Evaluación de: " << asignatura << " ---\n";
    int tiempoTotal = 0;
    for (int i = 0; i < totalPreguntas; ++i) {
        if (preguntas[i].tipo == 1) {
            ((PreguntaEleccionMultiple*)preguntas[i].ptr)->mostrar();
        } else if (preguntas[i].tipo == 2) {
            ((PreguntaVerdaderoyFalso*)preguntas[i].ptr)->mostrar();
        } else if (preguntas[i].tipo == 3) {
            ((PreguntaDesarrollo*)preguntas[i].ptr)->mostrar();
        }
        tiempoTotal += preguntas[i].ptr->getTiempo();
    }
    cout << "Tiempo total estimado: " << tiempoTotal << " minutos\n";
}
