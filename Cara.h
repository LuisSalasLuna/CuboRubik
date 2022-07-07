#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Shaders/shader_s.h"

#include <iostream>

#include "Matrices.h"
#include "Shaders/shader_s.h"

using namespace std;

class cara {
public:
	unsigned int VBO, VAO, EBO;
	vector<float> vertices;
	string texPath = "D:/Usuarios/Luis/Documents/UCSP/7mo Sem/Computacion Grafica/CGtrab/Laboratorio_CG/GLFW_GLAD_GLUT_GLEW_cmake_project/src/12_Rubik/img/";
	unsigned int texture1;
    int flipTexture = 0;

	cara(vector<float> _vertices, int nImagen, int _flipTexture);
	void init(Shader OurShader);
    void draw();
    void printVertices();
    void rotar(float* matrix);
};

cara::cara(vector<float> _vertices, int nImagen, int _flipTexture) {
    flipTexture = _flipTexture;
    vertices = _vertices;
	texPath += to_string(nImagen) + ".jpg";
}

void cara::init(Shader Ourshader) {
    unsigned int indices[] = {
        0,1,2,
        1,2,3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texturas---------------------------------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
	if(flipTexture == 0)
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	if(flipTexture == 1)
        stbi_set_flip_vertically_on_load(false); // tell stb_image.h to flip loaded texture's on the y-axis.

    unsigned char* data = stbi_load(texPath.c_str(), &width, &height, &nrChannels, 4);
    if (data)
    {
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    Ourshader.use();
    Ourshader.setInt("texture1", 0);

}

void cara::draw() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void cara::printVertices() {
    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i] << ",";
        if ((i + 1) % 5 == 0)
            cout << endl;
    }
} 

void cara::rotar(float* matrix) {
    MultMatrices8(matrix, this->vertices, vertices.size() / 5);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
}