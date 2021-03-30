#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

//16:9
#define WINDOW_WIDTH 2048
#define WINDOW_HEIGHT 1152

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myTeapot.h"
#include "Grass.h"
#include "Wall.h"
#include <vector>
#include "parser.cpp"
#include "Collision.cpp"



float speed_x = 0;
float speed_y = 0;
float aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
float speedCamX_WS = 0;
float speedCamZ_WS = 0;
float speedCamY_WS = 0;
float speedCamX_AD = 0;
float speedCamZ_AD = 0;


ShaderProgram* spPhong;

GLuint texGrass;
GLuint texSky;
GLuint texWall;
GLuint texBark;
GLuint texLeaves;
GLuint texDuck;
GLuint texGoal;
GLuint texLadder;
GLuint texHorse;
GLuint texWinner;

Parser parser;

Collision collision;

bool runWinner = false;


//Początkowe ustawienia kamery
float camX = 2.0f;
float camY = 0.5f;
float camZ = 4.0f;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 front;



// FPS camera variables
GLfloat yaw = -90.0f; // init pointing to inside
GLfloat pitch = 0.0f; // start centered
GLfloat lastX = WINDOW_WIDTH / 2.0f; // start middle screen
GLfloat lastY = WINDOW_HEIGHT / 2.0f; // start middle screen
bool firstMouse = true;
bool runSpeedCam_W = false;
bool runSpeedCam_S = false;
int direct;



vector<float> verticesGround;
vector<float> normalsGround;
vector<float> texturesGround;

vector<float> verticesBark;
vector<float> normalsBark;
vector<float> texturesBark;

vector<float> verticesLeaves;
vector<float> normalsLeaves;
vector<float> texturesLeaves;

vector<float> verticesDuck;
vector<float> normalsDuck;
vector<float> texturesDuck;

vector<float> verticesGoal;
vector<float> normalsGoal;
vector<float> texturesGoal;

vector<float> verticesLadder;
vector<float> normalsLadder;
vector<float> texturesLadder;

vector<float> verticesHorse;
vector<float> normalsHorse;
vector<float> texturesHorse;

vector<float> verticesBalloon;
vector<float> normalsBalloon;
vector<float> texturesBalloon;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazkBa
	unsigned width, height; //Zmienne do których wczytamy wymiary obrazka

	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt

	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,

		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {


		if (key == GLFW_KEY_W) 
		{ 
			runSpeedCam_W = true;
			direct = 1;
			speed_y = PI / 2;
			
		}
		if (key == GLFW_KEY_S) 
		{
			runSpeedCam_S = true;
			direct = -1;
			speed_y = -PI / 2;
		}
	}
	if (action == GLFW_RELEASE) {


		if (key == GLFW_KEY_W)
		{
			speedCamZ_WS = 0;
			speedCamX_WS = 0;
			runSpeedCam_W = false;
			speed_y = 0;
			
		}
		if (key == GLFW_KEY_S) {
			speedCamZ_WS = 0;
			speedCamX_WS = 0;
			runSpeedCam_S = false;
			speed_y = 0;
			
		}
	}
}



void onMouseMoveCallback(GLFWwindow* window, double x, double y)
{
	int mouseX = static_cast<int>(x);
	int mouseY = static_cast<int>(y);

	if (firstMouse) {
		lastX = (float)mouseX;
		lastY = (float)mouseY;
		firstMouse = false;
	}

	GLfloat xoffset = mouseX - lastX;
	GLfloat yoffset = lastY - mouseY; // Reversed
	lastX = (float)mouseX;
	lastY = (float)mouseY;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// check for pitch out of bounds otherwise screen gets flipped
	if (pitch > 40.0f)
		pitch = 40.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(front);
}



void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

void camera(float time, float &tmpCamX, float &tmpCamZ){
		// chcemy wejsc po drabinie
		if (collision.check_ladder(camX, camZ, pos_ladder) && runSpeedCam_W && (camY < 2.5f)) {
			speedCamY_WS = 2.0f;
			speedCamZ_WS = 0.0f;
			speedCamX_WS = 0.0f;

		}
		//ccemy zejsc z drabiny
		else if (collision.check_ladder(camX, camZ, pos_ladder) && runSpeedCam_S && (camY >= 0.49f)) {
			speedCamY_WS = -2.0f;
			speedCamZ_WS = 0.0f;
			speedCamX_WS = 0.0f;
		}
		//chcemy poruszyc się po mapie
		else if (runSpeedCam_W || runSpeedCam_S)
		{
			speedCamY_WS = 0.0f;
			speedCamZ_WS = 5.0f * normalize(cameraFront).z * direct;
			speedCamX_WS = 5.0f * normalize(cameraFront).x * direct;
		}
		//stoimy w miejscu
		else
		{
			speedCamY_WS = 0.0f;
		}


		time = glfwGetTime();

		tmpCamX += speedCamX_WS * time;
		tmpCamZ += speedCamZ_WS * time;
		camY += speedCamY_WS * time;

		cout << "CamX " << camX << " CamY " << camY << " CamZ " << camZ << endl;
		//kamera jest ponizej 2.5 czyli poruszamy sie po ziemi
		if (camY < 2.5f) {
			//wystepuje kolizja, zostajemy w tym samym miejscu co w ostatniej klatce
			if (!(collision.check_collision(tmpCamX, tmpCamZ, wallinmap))) {
				camX = tmpCamX;
				camZ = tmpCamZ;
			}
			//brak kolizji
			else
			{
				tmpCamX = camX;
				tmpCamZ = camZ;

			}
		}
		//poruszamy sie u góry po murze
		else {
			//jestemy na murze - mozemy sie po nim poruszac
			if (!(collision.check_collision_up(tmpCamX, tmpCamZ, wall_ladderinmap)))
			{
				camX = tmpCamX;
				camZ = tmpCamZ;

			}
			//kamera chce wyjsc poza mur - zostajemy w tym samym miejscu, co w poprzedniej klatce
			else
			{
				tmpCamX = camX;
				tmpCamZ = camZ;

			}
		}

};




//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	
	//glfwSetKeyCallback(window, onKeyCallback); // Set Callback for keys
	glfwSetCursorPosCallback(window, onMouseMoveCallback); // Set callback for mouse move
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Set mouse cursor FPS.

	//czytanie tekstur
	texGrass = readTexture("grass.png");
	texSky = readTexture("sky.png");
	texWall = readTexture("bricks.png");
	texBark = readTexture("bark.png");
	texLeaves = readTexture("leaves.png");
	texDuck = readTexture("ball.png");
	texGoal = readTexture("goal.png");
	texLadder = readTexture("ladder.png");
	texHorse = readTexture("horse.png");
	texWinner = readTexture("win.png");

	//zaladowanie programu cieniujacego
	spPhong = new ShaderProgram("v_phong.glsl", NULL, "f_phong.glsl");

	//parsowanie plikow .obj do formatu cpp
	parser.readfile("bark.obj", verticesBark, normalsBark, texturesBark);

	parser.readfile("ground.obj", verticesGround, normalsGround, texturesGround);

	parser.readfile("leaves.obj", verticesLeaves, normalsLeaves, texturesLeaves);

	parser.readfile("ball.obj", verticesDuck, normalsDuck, texturesDuck);

	parser.readfile("goal.obj", verticesGoal, normalsGoal, texturesGoal);

	parser.readfile("ladder.obj", verticesLadder, normalsLadder, texturesLadder);

	parser.readfile("horse.obj", verticesHorse, normalsHorse, texturesHorse);

	parser.readfile("balloon.obj", verticesBalloon, normalsBalloon, texturesBalloon);

	//włączenie współczynika alfa (przezroczystosci)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej***********

	delete spPhong;
}


void drawGrass(glm::mat4 M) {

	glm::mat4 MG = M;
	float wymiary = 100.0f;
	float X = (wymiary / 2) - 1;
	float Z = (wymiary / 2) - 1;
	
	glm::mat4 MGi = glm::translate(MG, glm::vec3(-X, 0.0f, -Z));


	glEnableVertexAttribArray(spPhong->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, grassVerts); //Wskaż tablicę z danymi dla atrybutu vertex


	glEnableVertexAttribArray(spPhong->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, grassNormals); //Wskaż tablicę z danymi dla atnormalrybutu 

	glEnableVertexAttribArray(spPhong->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, grassTexCoords); //Wskaż tablicę z danymi dla atnormalrybutu 

	glUniform1i(spPhong->u("textureMap0"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texGrass);

	
	//rysujemy male kwadraciki
	for (float posZ = -Z; posZ <= Z; posZ += 2.0f) {
		for (float posX = -X; posX <= X; posX += 2.0f) {

			glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MGi));

			glDrawArrays(GL_TRIANGLES, 0, grassVertexCount); //Narysuj obiekt

			//MG = glm::rotate(MG, PI/2, glm::vec3(0.0f, 1.0f, 0.0f));
			MGi = glm::translate(MG, glm::vec3(posX, 0.0f, posZ));
		}
	}
	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal

}

void drawSky(glm::mat4 M) {


	M = glm::scale(M, glm::vec3(50.0f, 200.0f, 50.0f));

	glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(spPhong->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, verticesSky); //Wskaż tablicę z danymi dla atrybutu vertex


	glEnableVertexAttribArray(spPhong->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, normalsSky); //Wskaż tablicę z danymi dla atnormalrybutu 


	glEnableVertexAttribArray(spPhong->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, texturesSky); //Wskaż tablicę z danymi dla atnormalrybutu 

	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texSky);

	glDrawArrays(GL_TRIANGLES, 0, countSky); //Narysuj obiekt

	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal



}

void drawTree(glm::mat4 M) {

	//Osobno rysowane są liście i pień drzewa
	
	//Pień
	glEnableVertexAttribArray(spPhong->a("vertex"));  
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, verticesBark.data()); 


	glEnableVertexAttribArray(spPhong->a("normal"));  
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, normalsBark.data()); 


	glEnableVertexAttribArray(spPhong->a("texCoord0"));  
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, texturesBark.data()); 

	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texBark);

	//drzewa rysowane są wokół labiryntu, więc każdy drawArrays odpowiada za inną ścianę labiryntu
	glm::mat4 MT = M;
	for (int x = 0; x < 5; x++) {
		
		MT = glm::translate(M, glm::vec3(x*6.5f+2.0f, 0.0f, -1.0f));
		MT = glm::scale(MT, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MT));
		glDrawArrays(GL_QUADS, 0, verticesBark.size()/4); 
		
		MT = glm::translate(M, glm::vec3(x* 6.5f + 4.5f, 0.0f, 34.0f));
		MT = glm::scale(MT, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MT));
		glDrawArrays(GL_QUADS, 0, verticesBark.size()/4); 

		MT = glm::translate(M, glm::vec3(-1.0f, 0.0f, x*6.5f+2.0f));
		MT = glm::scale(MT, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MT));
		glDrawArrays(GL_QUADS, 0, verticesBark.size()/4); 

		MT = glm::translate(M, glm::vec3(33.0f, 0.0f, x*6.5f+2.0f));
		MT = glm::scale(MT, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MT));
		glDrawArrays(GL_QUADS, 0, verticesBark.size()/4); 
	}


	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal

	//Liście
	
	glEnableVertexAttribArray(spPhong->a("vertex"));
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, verticesLeaves.data());


	glEnableVertexAttribArray(spPhong->a("normal"));
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, normalsLeaves.data());


	glEnableVertexAttribArray(spPhong->a("texCoord0"));
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, texturesLeaves.data());

	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texLeaves);



	//translate i scale musi być taki sam jak dla pnia
	for (int x = 0; x < 5; x++) {

		MT = glm::translate(M, glm::vec3(x * 6.5f + 2.0f, 0.0f, -1.0f));
		MT = glm::scale(MT, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MT));
		glDrawArrays(GL_QUADS, 0, verticesLeaves.size()/4);

		MT = glm::translate(M, glm::vec3(x * 6.5f + 4.5f, 0.0f, 34.0f));
		MT = glm::scale(MT, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MT));
		glDrawArrays(GL_QUADS, 0, verticesLeaves.size()/4);

		MT = glm::translate(M, glm::vec3(-1.0f, 0.0f, x * 6.5f + 2.0f));
		MT = glm::scale(MT, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MT));
		glDrawArrays(GL_QUADS, 0, verticesLeaves.size()/4);

		MT = glm::translate(M, glm::vec3(33.0f, 0.0f, x * 6.5f + 2.0f));
		MT = glm::scale(MT, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MT));
		glDrawArrays(GL_QUADS, 0, verticesLeaves.size()/4);
	}


	

	glDisableVertexAttribArray(spPhong->a("vertex"));
	glDisableVertexAttribArray(spPhong->a("normal"));
	glDisableVertexAttribArray(spPhong->a("texCoord0"));

}

void drawWall(glm::mat4 M) {



	glEnableVertexAttribArray(spPhong->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, wallVertices); //Wskaż tablicę z danymi dla atrybutu vertex


	glEnableVertexAttribArray(spPhong->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, wallNormals); //Wskaż tablicę z danymi dla atnormalrybutu 

	glEnableVertexAttribArray(spPhong->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, wallTexCoords); //Wskaż tablicę z danymi dla atnormalrybutu 

	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texWall);


	//w pliku Wall.h mamy w wektorach umieszczone jak bloki labiryntu mają być rozmieszczone
	glm::mat4 MW = M;
	for (float y = 0; y < placeWallXY.size(); y++) {
		for (float x = 0; x < placeWallXX[y].size(); x++) {

			MW = glm::translate(M, glm::vec3(placeWallXX[y][x], 0, placeWallXY[y]));
			glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MW));
			glDrawArrays(GL_TRIANGLES, 0, WallCount); //Narysuj obiekt

		}
	}


	glm::mat4 MWY = M;
	for (float y = 0; y < placeWallYX.size(); y++) {
		for (float x = 0; x < placeWallYY[y].size(); x++) {

			MWY = glm::translate(M, glm::vec3(placeWallYX[y], 0, placeWallYY[y][x]));
			MWY = glm::rotate(MWY, -PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));
			MWY = glm::translate(MWY, glm::vec3(0.0f, 0.0f, -1.0f));
			glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(MWY));
			glDrawArrays(GL_TRIANGLES, 0, WallCount); //Narysuj obiekt

	
		}
	}



	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal

}

void drawWinner(glm::mat4 M) {

	//rysujemy gdy piłka trafi do bramki
	glEnableVertexAttribArray(spPhong->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, wallVertices); //Wskaż tablicę z danymi dla atrybutu vertex


	glEnableVertexAttribArray(spPhong->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, wallNormals); //Wskaż tablicę z danymi dla atnormalrybutu 

	glEnableVertexAttribArray(spPhong->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, wallTexCoords); //Wskaż tablicę z danymi dla atnormalrybutu 

	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texWinner);


	M = glm::translate(M, glm::vec3(19.0f, 0, 33.0f));
	glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(M));
	glDrawArrays(GL_TRIANGLES, 0, WallCount); //Narysuj obiekt


	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal

}

void drawBall(glm::mat4 M) {
	
	M = glm::translate(M, glm::vec3(camX, camY - 0.3f, camZ));
	M = glm::scale(M, glm::vec3(0.3f, 0.3f, 0.3f));
	
	M = glm::rotate(M, -PI, glm::vec3(1.0f, 0.0f, 0.0f));

	glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(M));
	glEnableVertexAttribArray(spPhong->a("vertex"));
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, verticesDuck.data());


	glEnableVertexAttribArray(spPhong->a("normal"));
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, normalsDuck.data());


	glEnableVertexAttribArray(spPhong->a("texCoord0"));
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, texturesDuck.data());
	
	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texDuck);

	
	glDrawArrays(GL_QUADS , 0, verticesDuck.size() / 4); //dzielimy przez 4, gdyż wierzchołki są reprezentowane przez 4 zmienne


	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal

	

}

void drawLadder(glm::mat4 M) {

	glEnableVertexAttribArray(spPhong->a("vertex"));
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, verticesLadder.data());


	glEnableVertexAttribArray(spPhong->a("normal"));
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, normalsLadder.data());


	glEnableVertexAttribArray(spPhong->a("texCoord0"));
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, texturesLadder.data());

	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texLadder);

	glm::mat4 M1 = M;

	//pos_ladder to wektorach, kotry ma w sobie pozycje x i z, gdzie drabina ma być umeszczona na mapie 
	for (int count = 0; count < pos_ladder.size(); count++) {
		M1 = glm::translate(M, glm::vec3(pos_ladder[count][0], 0.0f, pos_ladder[count][1]));
		M1 = glm::scale(M1, glm::vec3(0.32f, 0.32f, 0.32f));
		glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(M1));
		glDrawArrays(GL_QUADS, 0, verticesLadder.size() / 4);
	}




	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal



}

void drawHorse(glm::mat4 M) {
	
	
	glEnableVertexAttribArray(spPhong->a("vertex"));
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, verticesHorse.data());




	glEnableVertexAttribArray(spPhong->a("normal"));
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, normalsHorse.data());


	glEnableVertexAttribArray(spPhong->a("texCoord0"));
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, texturesHorse.data());

	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texHorse);


	//rysujemy 2 konie
	glm::mat4 M1;

	M1 = glm::translate(M, glm::vec3(15.0f, 0.0f, 36.0f));
	M1 = glm::rotate(M1, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M1 = glm::rotate(M1, PI / 4, glm::vec3(0.0f, 0.0f, 1.0f));
	M1 = glm::scale(M1, glm::vec3(0.0009f, 0.0009f, 0.0009f));

	glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(M1));
	glDrawArrays(GL_QUADS, 0, verticesHorse.size() / 4);

	M1 = M;

	M1 = glm::translate(M1, glm::vec3(26.0f, 0.0f, 34.0f));
	M1 = glm::rotate(M1, -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	M1 = glm::scale(M1, glm::vec3(0.0009f, 0.0009f, 0.0009f));

	glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(M1));
	glDrawArrays(GL_QUADS, 0, verticesHorse.size() / 4);

	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal



}

void drawGoal(glm::mat4 M) {


	glEnableVertexAttribArray(spPhong->a("vertex"));
	glVertexAttribPointer(spPhong->a("vertex"), 4, GL_FLOAT, false, 0, verticesGoal.data());


	glEnableVertexAttribArray(spPhong->a("normal"));
	glVertexAttribPointer(spPhong->a("normal"), 4, GL_FLOAT, false, 0, normalsGoal.data());


	glEnableVertexAttribArray(spPhong->a("texCoord0"));
	glVertexAttribPointer(spPhong->a("texCoord0"), 2, GL_FLOAT, false, 0, texturesGoal.data());

	glUniform1i(spPhong->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texGoal);



	M = glm::translate(M, glm::vec3(20.5f, 0.0f, 38.0f));
	M = glm::rotate(M, PI, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.0009f, 0.0009f, 0.0009f));

	glUniformMatrix4fv(spPhong->u("M"), 1, false, glm::value_ptr(M));
	glDrawArrays(GL_QUADS, 0, verticesGoal.size() / 4);


	glDisableVertexAttribArray(spPhong->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(spPhong->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(spPhong->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu normal
}




//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3 cameraPosition = glm::vec3(camX, camY, camZ);

	//ustawienia kamery
	glm::mat4 V = glm::lookAt(cameraPosition, // eye
		cameraPosition + cameraFront, // centre
		cameraUp); // up//Wylicz macierz widoku

	glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, aspectRatio, 0.01f, 150.0f); //Wylicz macierz rzutowania

	glm::mat4 M = glm::mat4(1.0f);


	spPhong->use(); //aktywacja progrsamu cieniujacego
	glUniformMatrix4fv(spPhong->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spPhong->u("V"), 1, false, glm::value_ptr(V));

	//rysowanie poszczegolnych elementow
	drawWall(M);
	drawSky(M);
	drawLadder(M);
	drawBall(M);
	drawHorse(M);
	drawGoal(M);

	if (collision.check_ballingoal(camX,camZ)) runWinner = true; //sprawdzamy czy piłka jest w bramce

	if (runWinner) {
		//jesli piłka trafi do bramki, to wtedy wstawiamy napis winner, zamykamy labirynt
		wallinmap[33][19] = 1; //w tych miejscch wpisujemy 1, żeby zablokowac wejscie do labiryntu
		wallinmap[33][20] = 1;
		wallinmap[33][21] = 1;
		drawWinner(M);
	}

	drawTree(M);
	drawGrass(M);

	glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)
{

	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Labirynt", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące


	/*tmpCam to pozycja kamery w nastepnej klatce
	  Jest to nam potrzebne do tego, aby sprawdzić czy wspolrzedne nachodzą na jakis obiekt
	  Jeżeli nachodzą to następna klatka będzie nadal Cam*/
	glfwSetTime(0); //Zeruj timer
	float time = glfwGetTime();
	float tmpCamX = camX;
	float tmpCamZ = camZ;
	float tmpCamY = camY;
	printf("CHUJ");

	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		camera(time, tmpCamX, tmpCamZ);
		printf_s("Jestem");
		glfwSetTime(0); //Zeruj timer
		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}