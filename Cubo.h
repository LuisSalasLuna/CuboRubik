#include <vector>
#include <iostream>
#include "Shaders/shader_s.h"
#include "Cara.h"

using namespace std;

class cubo {
public:
	vector<cara*> Caras;
	vector<float> vertices;
    int index;
    int idCenter;
    
    cubo(float x, float y, float z, float tam, vector<int> texIndex, vector<int> flipIndex, int _index);
    void init(Shader OurShader);
    void draw();
    void printVertices(int i);
    void deleteCaras();

    void rotar(float* matrix);
};

cubo::cubo(float x, float y, float z, float tam, vector<int> texIndex, vector<int> flipIndex, int _index) {
    index = _index;
    idCenter = _index;
	
    tam = tam / 2;
    
    vector<float> UL = { 0.0f, 1.0f };
    vector<float> UR = { 1.0f, 1.0f };
    vector<float> BL = { 0.0f, 0.0f };
    vector<float> BR = { 1.0f, 0.0f };

    vector<vector<float>> texCoords = { UL, UR, BL, BR };

    vector<vector<float>> coord{
        {x - tam,  y + tam, z + tam}, //0
        {x + tam,  y + tam, z + tam}, //1
        {x - tam,  y - tam, z + tam}, //2
        {x + tam,  y - tam, z + tam}, //3
        {x - tam,  y + tam, z - tam}, //4
        {x + tam,  y + tam, z - tam}, //5
        {x - tam,  y - tam, z - tam}, //6
        {x + tam,  y - tam, z - tam}, //7
    };
    vector<int> point{
        0,1,2,3, //R F
        4,5,6,7, //O B
        4,5,0,1, //B U
        6,7,2,3, //G D
        1,5,3,7, //Y R
        4,0,6,2, //W L
    };

    //vector<float> Cube;
    for (int i = 0; i < 6;) {
        for (int j = 0; j < 4; j++) {
            vector<float>::iterator it = vertices.end();
            vertices.insert(it, coord[point[(i * 4) + j]].begin(), coord[point[(i * 4) + j]].end());
            it = vertices.end();

            vertices.insert(it, texCoords[j].begin(), texCoords[j].end());
        }
        i++;
    }

    //Pasar vertices a las caras
    vector<float> aux;
    for (int i = 0, j = 0; i < vertices.size(); i++) {
        aux.push_back(vertices[i]);
        if ((i + 1) % (20) == 0) {
            Caras.push_back(new cara(aux, texIndex[j], flipIndex[j]));
            aux.clear();
            j++;
        }
    }

}

void cubo::init(Shader OurShader) {
    for (auto i : Caras) {
        i->init(OurShader);
    }
}

void cubo::draw() {
    for (auto i : Caras) {
        i->draw();
    }
}

void cubo::printVertices(int i) {
    Caras[i]->printVertices();
}

void cubo::deleteCaras() {
    for (int i = 0; i < Caras.size(); i++) {
        glDeleteVertexArrays(1, &Caras[i]->VAO);
        glDeleteBuffers(1, &Caras[i]->VBO);
    }
}

void cubo::rotar(float* matrix) {
    for (auto i : Caras) {
        i->rotar(matrix);
    }
}