#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Solver.h"
#include <cstdlib>
#include "CuboRubik.h"
#include "Shaders/shader_s.h"
#include <Windows.h>
#include <iostream>
#include <vector>

//// enable optimus!
//extern "C" {
//    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
//}

using namespace std;
bool modoAnimacion = 0;
int ciclo = 1;
int modoCamara = 0;
char modoRotacion = 'n';
bool solver = false;
int rotloop = 90;
string pasos;
vector<char> pasos2;
int aux = 0;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// settings

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


vector<glm::vec3> getCentros(float c) {
    vector<glm::vec3> centros{
        //Front
         {-c, c, c}, //0  ufl  
        { 0.0f, c, c}, //1  uf
        { c, c, c}, //2  urf
        {-c, 0.0f, c}, //3  fl  
        { 0.0f, 0.0f, c}, //4  RED
        { c, 0.0f, c}, //5  fr
        {-c, -c, c}, //6 dlf
        { 0.0f, -c, c}, //7 df
        { c, -c, c}, //8 dfr
        //Mid
        {-c, c, 0.0f}, //9  ul
        { 0.0f, c, 0.0f}, //10 BLUE
        { c, c, 0.0f}, //11 ur
        {-c, 0.0f, 0.0f}, //12  WHITE
        //{ 0.0f, 0.0f, 0.0f}, //13
        { c, 0.0f, 0.0f}, //13 YELLOW
        {-c, -c, 0.0f}, //14  dl
        { 0.0f, -c, 0.0f}, //15 GREEN
        { c, -c, 0.0f}, //16  dr
         //Back
        {-c, c, -c}, //17  ulb
        { 0.0f, c, -c}, //18  ub
        { c, c, -c}, //19 ubr
        {-c, 0.0f, -c}, //20  bl
        { 0.0f, 0.0f, -c}, //21 ORANGE
        { c, 0.0f, -c}, //22  br
        {-c, -c, -c}, //23  dbl
        { 0.0f, -c, -c}, //24  db
        { c, -c, -c} //25  drb
    };
    return centros;
}

void Respirar(cuboRubik& cubo1, Shader& Shader) {
    float Eval2 = (sin(glfwGetTime()) * 0.2);
    vector<glm::vec3> vec = getCentros((Eval2)*0.2);
    cubo1.drawA(Shader, vec, glm::vec3(1 - Eval2, 1 - Eval2, 1 - Eval2));
  }

vector<glm::vec3> initPos;
void createInitPos(vector<glm::vec3>& initPos) {
	
    int min_x = -10, max_x = 10;
    int min_z = 2, max_z = 5;
	
    for (int i = 0; i < 26; i++) {
	    float x = min_x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_x - min_x)));
		float y = -3.0f;
		float z = min_z + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_z - min_z)));
		initPos.push_back(glm::vec3(x, y, -z));
    }

	for (int i = 0; i < 26; i++) {
		cout << initPos[i].x << " " << initPos[i].y << " " << initPos[i].z << endl;
	}
}

void aprox_vector(vector<glm::vec3>& v_origen, float velocidad) {
    
    for (int i = 0; i < v_origen.size(); i++) {
        for (int j = 0; j < v_origen[i].length(); j++) {
            if (v_origen[i][j] < 0) {
                v_origen[i][j] += velocidad;
            }
            else if (v_origen[i][j] > 0) {
                v_origen[i][j] -= velocidad;
            }
            else if(v_origen[i][j] > -1 && v_origen[i][j] < 1) {
                v_origen[i][j] = 0;
            }
        }
    }
}

void rotarUp(Shader& Shader, cuboRubik& Cubo) {
    rotloop -= 5;
    //test = true;
    Cubo.Up(Shader, 0);
    if (rotloop == 0) {
        Cubo.Up(Shader, 1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarDown(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Down(0);
    if (rotloop == 0) {
        Cubo.Down(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarRigth(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Rigth(0);
    if (rotloop == 0) {
        Cubo.Rigth(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarLeft(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Left(0);
    if (rotloop == 0) {
        Cubo.Left(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarFront(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Front(0);
    if (rotloop == 0) {
        Cubo.Front(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarBack(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Back(0);
    if (rotloop == 0) {
        Cubo.Back(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}

// Giros Antihorarios

void rotarUp2(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Up2(0);
    if (rotloop == 0) {
        Cubo.Up2(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarDown2(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Down2(0);
    if (rotloop == 0) {
        Cubo.Down2(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarRigth2(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Rigth2(0);
    if (rotloop == 0) {
        Cubo.Rigth2(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarLeft2(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Left2(0);
    if (rotloop == 0) {
        Cubo.Left2(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarFront2(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Front2(0);
    if (rotloop == 0) {
        Cubo.Front2(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}
void rotarBack2(cuboRubik& Cubo) {
    rotloop -= 5;
    Cubo.Back2(0);
    if (rotloop == 0) {
        Cubo.Back2(1);
        rotloop = 90;
        modoRotacion = 'n';
    }
}

cuboRubik cubo1;

int main()
{ 
    createInitPos(initPos);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("../../../../../src/12_Rubik/Shaders/shader.vs", "../../../../../src/12_Rubik/Shaders/shader.fs");

    ourShader.use();
    glm::mat4 model = glm::mat4(1.0f);
    ourShader.setMat4("model", model);
	
    glm::mat4 projection = glm::perspective(glm::radians(50.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 50.0f);
    //glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 100.0f);
    ourShader.setMat4("projection", projection);

    cubo1.init(ourShader);
    int it_animacion = 1025;
    //glPointSize(10);
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (modoCamara == 0) {

            ourShader.use();
      
            glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            ourShader.setMat4("view", view);

        }if (modoCamara == 1) {

            ourShader.use();
            const float radius = 4.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
			
            glm::mat4 view;
            view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            ourShader.setMat4("view", view);

        }if (modoCamara == 2) {
            
			float YU = 1.0f;
			
            ourShader.use();
            const float radius = 4.0f;
            float camY = sin(glfwGetTime()) * radius;
       
            float camZ = cos(glfwGetTime()) * radius;
            
            if (camZ < 0) {
                if (YU == 1.0f) {
                    YU = -1.0f;
                }
                else {
                    YU == 1.0f;
                }
            }
            
            glm::mat4 view;
            view = glm::lookAt(glm::vec3(0.0, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0f, YU, 0.0f));
            ourShader.setMat4("view", view);
            
			
        }if (modoCamara == 3) {
            ourShader.use();
            const float radius = 4.0f;
			const float yradius = 6.0;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            float camY = sin(glfwGetTime()) * radius;
            glm::mat4 view;
            view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            ourShader.setMat4("view", view);
			
        }if (modoCamara == 4) {
            ourShader.use();
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            ourShader.setMat4("view", view);
            ourShader.setMat4("model", model);
        }
		
        if (solver && modoRotacion == 'n') {
            std::cout << "Solver & n" << endl;
            if (pasos2.size()) {
                cout << "Pasos" << endl;
                modoRotacion = pasos2[0];
                pasos2.erase(pasos2.begin());
            }
            else {
                solver = false;
                pasos2.clear();
                pasos.clear();
            }
        }

        if (modoRotacion == 'U') {
            rotarUp(ourShader ,cubo1);
        }
        else if (modoRotacion == 'I') {
            rotarUp2(cubo1);
        }
        else if (modoRotacion == 'D') {
            rotarDown(cubo1);
        }
        else if (modoRotacion == 'S') {
            rotarDown2(cubo1);
        }
        else if (modoRotacion == 'R') {
            rotarRigth(cubo1);
        }
        else if (modoRotacion == 'T') {
            rotarRigth2(cubo1);
        }
        else if (modoRotacion == 'L') {
            rotarLeft(cubo1);
        }
        else if (modoRotacion == 'K') {
            rotarLeft2(cubo1);
        }
        else if (modoRotacion == 'F') {
            rotarFront(cubo1);
        }
        else if (modoRotacion == 'G') {
            rotarFront2(cubo1);
        }
        else if (modoRotacion == 'B') {
            rotarBack(cubo1);
        }
        else if (modoRotacion == 'N') {
            rotarBack2(cubo1);
        }

        if (modoAnimacion == 0) {
            cubo1.draw(ourShader, initPos);
        }else{
            if (it_animacion > 0) {
                cubo1.draw(ourShader, initPos);
                aprox_vector(initPos, 0.01);
                it_animacion--;
            }
            else {
                Respirar(cubo1, ourShader);
            }
        }

        //Respirar(cubo1, ourShader);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    cubo1.deleteCubo();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        cameraPos -= cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        modoCamara = 0;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        modoCamara = 1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        modoCamara = 2;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        modoCamara = 3;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        modoCamara = 4;
    if (modoRotacion == 'n') {
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) { //
            modoRotacion = 'U';
            pasos += "U ";
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) { //
            modoRotacion = 'I';
            pasos += "U\' ";
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            modoRotacion = 'D';
            pasos += "D ";
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            modoRotacion = 'S';
            pasos += "D\' ";
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            modoRotacion = 'R';
            pasos += "R ";
        }
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            modoRotacion = 'T';
            pasos += "R\' ";
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            modoRotacion = 'L';
            pasos += "L ";
        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            modoRotacion = 'K';
            pasos += "L\' ";
        }
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            modoRotacion = 'F';
            pasos += "F ";
        }
        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
            modoRotacion = 'G';
            pasos += "F\' ";
        }
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            modoRotacion = 'B';
            pasos += "B ";
        }
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
            modoRotacion = 'N';
            pasos += "B\' ";
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        string aux;
        aux = pasos.substr(0, pasos.size() - 1);

        cout << "Pasos shuffle: " << aux << endl;;
        aux = CubeSolver(aux);


        for (int i = 0; i < aux.size(); i++) {
            if (aux[i] != ' ')
                pasos2.push_back(aux[i]);
        }
        cout << "Pasos solucion: " << aux << endl;
        vector<char> Vaux;
        for (int i = 0; i < pasos2.size(); i++) {
            if (pasos2[i] == 'U') {
                if (i + 1 < pasos2.size()) {
                    if (pasos2[i + 1] == '\'') {
                        Vaux.push_back('I');
                        i++;
                    }
                    else if (pasos2[i + 1] == '2') {
                        Vaux.push_back('U');
                        Vaux.push_back('U');
                        i++;
                    }
                    else {
                        Vaux.push_back('U');
                    }
                }
            }
            else if (pasos2[i] == 'D') {
                if (i + 1 < pasos2.size()) {
                    if (pasos2[i + 1] == '\'') {
                        Vaux.push_back('S');
                        i++;
                    }
                    else if (pasos2[i + 1] == '2') {
                        Vaux.push_back('D');
                        Vaux.push_back('D');
                        i++;
                    }
                    else {
                        Vaux.push_back('D');
                    }
                }
            }
            else if (pasos2[i] == 'L') {
                if (i + 1 < pasos2.size()) {
                    if (pasos2[i + 1] == '\'') {
                        Vaux.push_back('K');
                        i++;
                    }
                    else if (pasos2[i + 1] == '2') {
                        Vaux.push_back('L');
                        Vaux.push_back('L');
                        i++;
                    }
                    else {
                        Vaux.push_back('L');
                    }
                }
            }
            else if (pasos2[i] == 'R') {
                if (i + 1 < pasos2.size()) {
                    if (pasos2[i + 1] == '\'') {
                        Vaux.push_back('T');
                        i++;
                    }
                    else if (pasos2[i + 1] == '2') {
                        Vaux.push_back('R');
                        Vaux.push_back('R');
                        i++;
                    }
                    else {
                        Vaux.push_back('R');
                    }
                }
            }
            else if (pasos2[i] == 'F') {
                if (i + 1 < pasos2.size()) {
                    if (pasos2[i + 1] == '\'') {
                        Vaux.push_back('G');
                        i++;
                    }
                    else if (pasos2[i + 1] == '2') {
                        Vaux.push_back('F');
                        Vaux.push_back('F');
                        i++;
                    }
                    else {
                        Vaux.push_back('F');
                    }
                }
            }
            else if (pasos2[i] == 'B') {
                if (i + 1 < pasos2.size()) {
                    if (pasos2[i + 1] == '\'') {
                        Vaux.push_back('N');
                        i++;
                    }
                    else if (pasos2[i + 1] == '2') {
                        Vaux.push_back('B');
                        Vaux.push_back('B');;
                        i++;
                    }
                    else {
                        Vaux.push_back('B');
                    }
                }
            }
        }

        pasos2 = Vaux;
        for (int i = 0; i < pasos2.size(); i++) {
            cout << pasos2[i] << " ";
        }
        solver = true;
        cout << "Solver access ENTER" << endl;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        modoAnimacion = 1;
    }
};

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}