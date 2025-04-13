// main.cpp
#include <iostream> // Para cout y cin
#include <fstream> // Para ifstream y ofstream
#include <string> // Para getline
#include <cstdlib> // Para atoi
#include "Pregunta.h" // Para las clases de preguntas y evaluación
using namespace std;

// Declaración del banco y contador global
RegistroPregunta banco[MAX_PREGUNTAS];
int total = 0;

// Carga todas las preguntas desde archivo
void cargarPreguntasDesdeArchivo() {
    ifstream in("banco_preguntas.txt");
    if (!in.is_open()) return;

    string linea;
    while (getline(in, linea)) {
        int tipo = linea[0] - '0';
        string datos[30];
        int idx = 2, d = 0;
        string actual = "";
        while (idx < linea.size()) {
            if (linea[idx] == '|') {
                datos[d++] = actual;
                actual = "";
            } else {
                actual += linea[idx];
            }
            idx++;
        }
        datos[d++] = actual;

        if (tipo == 1) {
            PreguntaEleccionMultiple* p = new PreguntaEleccionMultiple();
            int cantidad = stoi(datos[5]);
            int correcta = stoi(datos[6]);
            string opciones[MAX_OPCIONES];
            for (int i = 0; i < cantidad; ++i) {
                opciones[i] = datos[7 + i];
            }
            p->setDatos(datos[0], datos[1], datos[2], stoi(datos[3]), datos[4], opciones, cantidad, correcta);
            banco[total].ptr = p;
            banco[total].tipo = 1;
            total++;
        } else if (tipo == 2) {
            PreguntaVerdaderoyFalso* p = new PreguntaVerdaderoyFalso();
            p->setDatos(datos[0], datos[1], datos[2], stoi(datos[3]), datos[4], datos[5] == "1");
            banco[total].ptr = p;
            banco[total].tipo = 2;
            total++;
        } else if (tipo == 3) {
            PreguntaDesarrollo* p = new PreguntaDesarrollo();
            p->setDatos(datos[0], datos[1], datos[2], stoi(datos[3]), datos[4], datos[5]);
            banco[total].ptr = p;
            banco[total].tipo = 3;
            total++;
        }
    }

    in.close();
}

// Guarda todas las preguntas en archivo
void guardarPreguntaEnArchivo(Pregunta* ptr) {
    ofstream out("banco_preguntas.txt", ios::app);
    if (out.is_open()) {
        ptr->guardar(out);
        out.close();
    }
}

int main() {
    cargarPreguntasDesdeArchivo();
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n--- MENÚ PRINCIPAL ---\n";
        cout << "1. Crear pregunta Elección Múltiple\n";
        cout << "2. Crear pregunta Verdadero/Falso\n";
        cout << "3. Crear pregunta Respuesta Corta\n";
        cout << "4. Listar preguntas\n";
        cout << "5. Eliminar una pregunta\n";
        cout << "6. Crear evaluación por asignatura\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1 && total < MAX_PREGUNTAS) {
            string enunciado, solucion, nivel, asignatura;
            int tiempo, cantidadOpciones, correcta;
            string opciones[MAX_OPCIONES];

            cout << "Asignatura: ";
            getline(cin, asignatura);
            cout << "Enunciado: ";
            getline(cin, enunciado);
            cout << "Solución: ";
            getline(cin, solucion);
            cout << "Nivel de Bloom: ";
            getline(cin, nivel);
            cout << "Tiempo estimado (min): ";
            cin >> tiempo;
            cin.ignore();

            cout << "Cantidad de opciones: ";
            cin >> cantidadOpciones;
            cin.ignore();

            for (int i = 0; i < cantidadOpciones; ++i) {
                cout << "Opción " << i + 1 << ": ";
                getline(cin, opciones[i]);
            }

            cout << "Respuesta correcta (1 a " << cantidadOpciones << "): ";
            cin >> correcta;
            cin.ignore();

            PreguntaEleccionMultiple* p = new PreguntaEleccionMultiple();
            p->setDatos(enunciado, solucion, nivel, tiempo, asignatura, opciones, cantidadOpciones, correcta - 1);
            banco[total].ptr = p;
            banco[total].tipo = 1;
            guardarPreguntaEnArchivo(p);
            total++;
        }

        else if (opcion == 2 && total < MAX_PREGUNTAS) {
            string enunciado, solucion, nivel, asignatura;
            int tiempo;
            char resp;
            bool respuesta;

            cout << "Asignatura: ";
            getline(cin, asignatura);
            cout << "Enunciado: ";
            getline(cin, enunciado);
            cout << "Solución: ";
            getline(cin, solucion);
            cout << "Nivel de Bloom: ";
            getline(cin, nivel);
            cout << "Tiempo estimado (min): ";
            cin >> tiempo;
            cin.ignore();

            cout << "Respuesta esperada (V/F): ";
            cin >> resp;
            cin.ignore();
            respuesta = (resp == 'V' || resp == 'v');

            PreguntaVerdaderoyFalso* p = new PreguntaVerdaderoyFalso();
            p->setDatos(enunciado, solucion, nivel, tiempo, asignatura, respuesta);
            banco[total].ptr = p;
            banco[total].tipo = 2;
            guardarPreguntaEnArchivo(p);
            total++;
        }

        else if (opcion == 3 && total < MAX_PREGUNTAS) {
            string enunciado, solucion, nivel, asignatura, respuestaEsperada;
            int tiempo;

            cout << "Asignatura: ";
            getline(cin, asignatura);
            cout << "Enunciado: ";
            getline(cin, enunciado);
            cout << "Solución: ";
            getline(cin, solucion);
            cout << "Nivel de Bloom: ";
            getline(cin, nivel);
            cout << "Tiempo estimado (min): ";
            cin >> tiempo;
            cin.ignore();

            cout << "Respuesta esperada: ";
            getline(cin, respuestaEsperada);

            PreguntaDesarrollo* p = new PreguntaDesarrollo();
            p->setDatos(enunciado, solucion, nivel, tiempo, asignatura, respuestaEsperada);
            banco[total].ptr = p;
            banco[total].tipo = 3;
            guardarPreguntaEnArchivo(p);
            total++;
        }

        else if (opcion == 4) {
            for (int i = 0; i < total; ++i) {
                cout << "[" << i + 1 << "] ";
                if (banco[i].tipo == 1) {
                    ((PreguntaEleccionMultiple*)banco[i].ptr)->mostrar();
                } else if (banco[i].tipo == 2) {
                    ((PreguntaVerdaderoyFalso*)banco[i].ptr)->mostrar();
                } else if (banco[i].tipo == 3) {
                    ((PreguntaDesarrollo*)banco[i].ptr)->mostrar();
                }
            }
        }

        else if (opcion == 5) {
            int idx;
            cout << "Índice de la pregunta a eliminar: ";
            cin >> idx;
            cin.ignore();

            if (idx >= 1 && idx <= total) {
                delete banco[idx - 1].ptr;
                for (int i = idx; i < total; ++i) {
                    banco[i - 1] = banco[i];
                }
                total--;
                cout << "Pregunta eliminada (pero NO se elimina del archivo).\n";
            } else {
                cout << "Índice inválido.\n";
            }
        }

        else if (opcion == 6) {
            string asignatura;
            int cantidad;
            Evaluacion eval;

            cout << "Nombre de la asignatura: ";
            getline(cin, asignatura);
            eval.setAsignatura(asignatura);

            cout << "Cantidad de preguntas para la evaluación: ";
            cin >> cantidad;
            cin.ignore();

            for (int i = 0; i < cantidad; ++i) {
                for (int j = 0; j < total; ++j) {
                    if (banco[j].ptr->getAsignatura() == asignatura) {
                        cout << "[" << j + 1 << "] ";
                        if (banco[j].tipo == 1)
                            ((PreguntaEleccionMultiple*)banco[j].ptr)->mostrar();
                        else if (banco[j].tipo == 2)
                            ((PreguntaVerdaderoyFalso*)banco[j].ptr)->mostrar();
                        else if (banco[j].tipo == 3)
                            ((PreguntaDesarrollo*)banco[j].ptr)->mostrar();
                    }
                }

                int idx;
                cout << "Seleccione el índice de la pregunta " << i + 1 << ": ";
                cin >> idx;
                cin.ignore();

                if (idx >= 1 && idx <= total && banco[idx - 1].ptr->getAsignatura() == asignatura) {
                    eval.agregarPregunta(banco[idx - 1]);
                } else {
                    cout << "Índice inválido o pregunta no pertenece a la asignatura. Se omite.\n";
                }
            }

            eval.mostrar();
        }
    }

    for (int i = 0; i < total; ++i) {
        delete banco[i].ptr;
    }

    cout << "Programa finalizado.\n";
    return 0;
}
