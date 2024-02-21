#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

#define NUM_CANDIDATOS 5
#define NUMERO_VOTANTES 50
#define RONDAS 5
#define MAX_votos 50
#define MIN_VOTO 0
#define MAXIMA_LONGITUD_CADENA 100

void llamaCiclo();
int busquedaAleatorios(int minimo, int maximo);
void llenarMatriz(float matriz[NUM_CANDIDATOS][RONDAS + 1]);
void imprimirMatrizLinea();
void imprimirMatriz(float matriz[NUM_CANDIDATOS][RONDAS + 1], char candidatos[NUM_CANDIDATOS][MAXIMA_LONGITUD_CADENA]);
int main()
{
    srand(getpid());
    llamaCiclo();
    return 0;
}
void llamaCiclo()
{
    float matriz_votos[NUM_CANDIDATOS][RONDAS + 1];
    char opcion;
    bool repetir = true;



    char candidatos[NUM_CANDIDATOS][MAXIMA_LONGITUD_CADENA] = {"","","","",""};
    do
    {
        system("cls");




        for (int i=0; i < NUM_CANDIDATOS; i ++ )
        {
            cout << "* Elecciones Generales 2024 *" << endl << endl;
            cout << "Ingrese el nombre del candidato " << i + 1 << endl;;
            cin >> candidatos[i] ;
            system("cls");
        }
        cout << "* Elecciones Generales 2024 *" << endl << endl;
        llenarMatriz(matriz_votos);
        imprimirMatriz(matriz_votos, candidatos);
        cout << endl << endl << "Desea realizar una nueva votaci�n (s/n)? ";
        cin >> opcion;
        if (opcion == 'n')
        {
            repetir=false;
        }
    } while (repetir);
}
int busquedaAleatorios(int minimo, int maximo)
{
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void llenarMatriz(float matriz[NUM_CANDIDATOS][RONDAS + 1])
{
    int y, x, z;
    for (y = 0; y < NUM_CANDIDATOS; y++)
    {
        float suma = 0;
        int voto = 0;
        int totalvoto = 0;
        for (x = 0; x < RONDAS; x++)
        {
            for (z = 0; z < NUMERO_VOTANTES; z++)
            {
                voto = busquedaAleatorios(MIN_VOTO, 1);
                suma += (float)voto;
                voto=0;
            }
         matriz[y][x] = suma;
         totalvoto += suma;
         suma = 0 ;
        }
        // Agregar total votos por candidato
        matriz[y][RONDAS] = totalvoto;

    }
}

void imprimirMatrizLinea()
{
    int x;

    cout << "+--------";
    for (x = 0; x < RONDAS + 1; x++)
    {
        cout << "+---------";
    }
    cout << "+\n";
}
void imprimirMatriz(float matriz[NUM_CANDIDATOS][RONDAS + 1], char candidatos[NUM_CANDIDATOS][MAXIMA_LONGITUD_CADENA] )
{
    //Funci�n que imprime la matriz en pantalla y realizando los calculos necesarios del promedio
    int y, x;

    float votosMayor = matriz[0][RONDAS];
    float votosMenor = matriz[0][RONDAS];
    float totalGeneral = 0;
    float promedioGeneral = 0;
    char candidatoGanador[MAXIMA_LONGITUD_CADENA];
    char candidatoMenor[MAXIMA_LONGITUD_CADENA];
    memcpy(candidatoGanador, candidatos[0], MAXIMA_LONGITUD_CADENA);
    memcpy(candidatoMenor, candidatos[0], MAXIMA_LONGITUD_CADENA);
    cout << "A continuacion se muestran los resultados de las Votaciones Generales" << endl << endl;

    imprimirMatrizLinea();
    cout << setw(9) << "Candidato";
    for (x = 0; x < RONDAS; x++)
    {
        cout << setw(9) << "Ronda " << x + 1;
    }
    cout << setw(8) << "Total" << endl;
    imprimirMatrizLinea();
    for (y = 0; y < NUM_CANDIDATOS; y++)
    {
        cout << "!" << setw(8) << candidatos[y] << "!";
        float suma = 0;
        for (x = 0; x < RONDAS; x++)
        {
            int votos = matriz[y][x];
            cout << setw(9) << votos << "!";
        }
        float promedio = matriz[y][RONDAS];
        totalGeneral += matriz[y][RONDAS];
        if (promedio > votosMayor)
        {
            votosMayor = promedio;
            memcpy(candidatoGanador, candidatos[y], MAXIMA_LONGITUD_CADENA);
        }
        if (promedio < votosMenor)
        {
            votosMenor = promedio;
            memcpy(candidatoMenor, candidatos[y], MAXIMA_LONGITUD_CADENA);
        }
        cout << setw(9) << fixed << setprecision(2) << promedio << "!" << endl;
        imprimirMatrizLinea();
    }
    promedioGeneral = totalGeneral / NUM_CANDIDATOS;
    cout << "Candidatos Ganador         : " << setw(10) << candidatoGanador <<  setw(10) << votosMayor << endl;
    cout << "Candidatos con menor votos : " << setw(10) << candidatoMenor <<  setw(10) << votosMenor << endl;


}
