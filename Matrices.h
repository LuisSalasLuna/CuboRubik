//#include "../../build/mak.vc16/x64/src/Matrices/Matrices.h"
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;
#define PI 3.14159265359

    
float movArriba[] = { 1.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.01f,
                      0.0f, 0.0f, 1.0f };

float movAbajo[] = { 1.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, -0.01f,
                      0.0f, 0.0f, 1.0f };

float movDerecha[] = { 1.0f, 0.0f, 0.01f,
                      0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 1.0f };

float movIzquierda[] = { 1.0f, 0.0f, -0.01f,
                      0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 1.0f };
//,
float escalaMenor[] = { 0.99f, 0.0f, 0.0f,
                        0.0f, 0.99f, 0.0f,
                        0.0f, 0.0f, 1.0f };

//.
float escalaMayor[] = { 1.01f, 0.0f, 0.0f,
                        0.0f, 1.01f, 0.0f,
                        0.0f, 0.0f, 1.0f };

//k
float theta = 5*PI/180;
//float theta = -1.5708;
//float theta = -0.0174533;

float Ry[] = { cosf(theta), 0.0f, sinf(theta),
                0.0f, 1.0f, 0.0f,
                -sinf(theta), 0.0f, cosf(theta) };

float Ry2[] = { cosf(theta), 0.0f, -sinf(theta),
                0.0f, 1.0f, 0.0f,
                sinf(theta), 0.0f, cosf(theta) };

float Rx[] = { 1.0f, 0.0f, 0.0f ,
                0.0f, cosf(theta), -sinf(theta),
                0.0f, sinf(theta), cosf(theta) };
float Rx2[] = { 1.0f, 0.0f, 0.0f ,
                0.0f, cosf(theta), sinf(theta),
                0.0f, -sinf(theta), cosf(theta) };

float Rz[] = { cosf(theta), -sinf(theta), 0.0f ,
                sinf(theta), cosf(theta), 0.0f,
                0.0f, 0.0f , 1.0f };
float Rz2[] = { cosf(theta), sinf(theta), 0.0f ,
                -sinf(theta), cosf(theta), 0.0f,
                0.0f, 0.0f , 1.0f };

float rotarHorario[] = { cos(theta), sin(theta), 0.0f,
                -sin(theta), cos(theta), 0.0f,
                0.0f,0.0f,1.0f };

//l

float rotarAntiHorario[] = { cos(theta), -sin(theta), 0.0f,
                            sin(theta), cos(theta), 0.0f,
                            0.0f,0.0f,1.0f };

//w
float cutRight[] = { 1.0f, tan(theta), 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 1.0f };

//q
float cutLeft[] = { 1.0f, 0.0f, 0.0f,
                        tan(theta), 1.0f, 0.0f,
                        0.0f, 0.0f, 1.0f };


float round_up(float value, int decimal_places) {
    const float multiplier = std::pow(10.0, decimal_places);
    return std::ceil(value * multiplier) / multiplier;
}

//MATRICES
void MultMatrices(float* mMatrix, float* vertices, int numVertices) {

    for (int i = 0, k = 0; i < numVertices; i++, k += 3) {
        float vector[3];
        for (int j = 0; j < 3; j++) {
            vector[j] = vertices[j + k];
        }

        for (int l = 0, aux = 0; l < 3; l++, aux += 3) {
            float auxVertices = 0;
            for (int m = 0; m < 3; m++) {
                auxVertices += mMatrix[aux + m] * vector[m];
            }
            vertices[l + k] = (auxVertices);
        }

    }

    //for (int i = 0; i < numVertices * 3; i++) {
    //    if (i % 3 == 0) {
    //        std::cout << std::endl;
    //    }
    //    std::cout << vertices[i] << " ";
    //}

}

void MultMatrices6(float* mMatrix, float* vertices, int numVertices) {

    for (int i = 0, k = 0; i < numVertices; i++, k += 6) {
        float vector[3];
        for (int j = 0; j < 3; j++) {
            vector[j] = vertices[j + k];
        }

        for (int l = 0, aux = 0; l < 3; l++, aux += 3) {
            float auxVertices = 0;
            for (int m = 0; m < 3; m++) {
                auxVertices += mMatrix[aux + m] * vector[m];
            }
            vertices[l + k] = auxVertices;
        }

    }

    //for (int i = 0; i < numVertices * 6; i++) {
    //    if (i % 6 == 0) {
    //        std::cout << std::endl;
    //    }
    //    std::cout << vertices[i] << " ";
    //}

}

void MultMatrices8(float* mMatrix, vector<float>& vertices, int numVertices) {
    for (int i = 0, k = 0; i < numVertices; i++, k += 5) {
        float vector[3];
        for (int j = 0; j < 3; j++) {
            vector[j] = vertices[j + k];
        }

        for (int l = 0, aux = 0; l < 3; l++, aux += 3) {
            float auxVertices = 0;
            for (int m = 0; m < 3; m++) {
                auxVertices += mMatrix[aux + m] * vector[m];
            }
            vertices[l + k] = round_up(auxVertices, 5);
        }
    }
}

void MultMatrices9(float* mMatrix, vector<float>& vertices, int numVertices) {
    for (int i = 0, k = 0; i < numVertices; i++, k += 6) {
        float vector[3];
        for (int j = 0; j < 3; j++) {
            vector[j] = vertices[j + k];
        }

        for (int l = 0, aux = 0; l < 3; l++, aux += 3) {
            float auxVertices = 0;
            for (int m = 0; m < 3; m++) {
                auxVertices += mMatrix[aux + m] * vector[m];
            }
            vertices[l + k] = round_up(auxVertices, 3);
        }
    }
}

//VECTORES

float norma(float* vector, int dim) {
    float aux = 0.0f;
    for (int i = 0; i < dim; i++) {
        aux += vector[i] * vector[i];
    }
    return sqrt(aux);
}

void mover(float* vertices, float* dir, int v) {
    // normalizar
    float normaV = norma(dir, 3);
    for (int i = 0; i < 3; i++) {
        dir[i] = dir[i] / normaV;
    }

    //Multiplicar por K
    float k = 0.1f;
    for (int i = 0; i < 3; i++) {
        dir[i] = dir[i] * k;
    }

    for (int i = 0; i < v * 3; i++) {
        vertices[i] += dir[i % 3];
    }

}

//void moverRandom(float* vertices, int v) {
//    float RandomVector[3];
//    for (int i = 0; i < 3; i++) {
//        RandomVector[i] = (rand() % 10) - (rand() % 8);
//    }
//
//    // normalizar
//    float normaV = norma(RandomVector, 3);
//    for (int i = 0; i < 3; i++) {
//        RandomVector[i] = RandomVector[i] / normaV;
//    }
//
//    //Multiplicar por K
//    float k = 0.1f;
//    for (int i = 0; i < 3; i++) {
//        RandomVector[i] = RandomVector[i] * k;
//    }
//
//    for (int i = 0; i < v * 3; i++) {
//        vertices[i] += RandomVector[i % 3];
//    }
//
//}