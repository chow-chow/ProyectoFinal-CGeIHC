/*---------------------------------------------------------*/
/* ---------------- Proyecto Final ----------------------- */
/*-----------------    2023-1   ---------------------------*/
/*---------- Alumno:Cruz Rangel Leonardo Said -------------*/
/*--------------- No. Cuenta 316031062 --------------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>
#include <fstream>
#include <string>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 200.0f, 700.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = 0.0f, //cambiar
		movAuto_z = 0.0f,
		orienta = 0.0f,
		girollantas = 0.0f,
		movAuto_y = 0.0f,
		escala = 30.0f;

float	movSport_x = 0.0f,
		movSport_z = 0.0f,
		orientation = 0.0f;

float	movHeli_x = 0.0f,
		movHeli_y = 0.0f,
		movHeli_z = 0.0f,
		orient = 0.0f,
		giroProp = 0.0f;

int		car = 1,
		sport = 1;

bool	animacion = false,
		animacion2 = false,
		recorrido1 = true,
		recorrido2 = false,
		recorrido3 = false,
		recorrido4 = false,
		recorrido5 = false,
		recorrido6 = false;


//Keyframes (Manipulación y dibujo)  //cambiar
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		rotAla = 0.0f,
		giro = 0.0f;
float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f,
		rotInc = 0.0f,
		giroInc = 0.0f;

//Animacion por archivo
int contador = 0;
string line;

#define MAX_FRAMES 18
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotAla;
	float giro;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 17;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	//std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotAla = rotAla;
	KeyFrame[FrameIndex].giro = giro;

	cout << posX << endl;
	cout << posY << endl;
	cout << posZ << endl;
	cout << rotAla << endl;
	cout << giro << endl;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotAla = KeyFrame[0].rotAla;
	giro = KeyFrame[0].giro;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotAla - KeyFrame[playIndex].rotAla) / i_max_steps;
	giroInc = (KeyFrame[playIndex + 1].giro - KeyFrame[playIndex].giro) / i_max_steps;

}

void animate(void)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				//std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotAla += rotInc;
			giro += giroInc;

			i_curr_steps++;
		}
	}

	//Vehículo
	if (animacion)
	{
		switch (car)
		{
		case 1:
			movAuto_z += 3.0f;
			girollantas += 3.0f;
			if (movAuto_z >= 240.0f) {
				orienta = -90.0f;
				movAuto_y = -9.5595;
				car = 2;
			}
			break;
		case 2:
			movAuto_x -= 3.0f;
			girollantas += 3.0f;
			if (movAuto_x <= -240.0f)
			{
				orienta = -180.0f;
				car = 3;
			}
			break;
		case 3:
			movAuto_z -= 3.0f;
			girollantas += 3.0f;
			if (movAuto_z <= 0.0f) {
				car = 4;
			}
			break;
		case 4:
			movAuto_z += 5.0f;
			girollantas -= 5.0f;
			if (movAuto_z >= 320.0f) {
				orienta = -90.0f;
				car = 5;
			}
			break;
		case 5:
			movAuto_x += 5.0f;
			girollantas -= 5.0f;
			if (movAuto_x >= 500.0f) {
				orienta = 0.0f;
				car = 6;
			}
			break;
		case 6:
			movAuto_z -= 5.0f;
			girollantas -= 5.0f;
			if (movAuto_z <= -600.0f) {
				escala = 0.0f;
				animacion = false;
			}
			break;
		}
	}

	//Helicoptero
	if (animacion2) {
		if (recorrido1) {
			movHeli_x = 0.0f;
			movHeli_z += 3.0f;
			orient = 0.0f;
			if (movHeli_z >= 200.0f) {
				recorrido1 = false;
				recorrido5 = true;
			}
		}
		else if (recorrido2) {
			movHeli_x -= 4.0f;
			movHeli_z = 200.0f;
			orient = 270.0f;
			if (movHeli_x <= -250.0f) {
				recorrido2 = false;
				recorrido3 = true;
			}
		}
		else if (recorrido3) {
			movHeli_x = -250.0f;
			movHeli_z -= 3.0f;
			orient = 180.0f;
			if (movHeli_z <= -200.0f) {
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		else if (recorrido4) {
			movHeli_x += 4.0f;
			movHeli_z = -200.0f;
			orient = 90.0f;
			if (movHeli_x >= 0.0f) {
				recorrido4 = false;
				recorrido1 = true;
			}
		}
		else if (recorrido5) {
			movHeli_x -= 3.0f;
			movHeli_z -= 3.0f * (400.0f / 250.0f);
			orient = 212.0f;
			if (movHeli_x <= -250.0f && movHeli_z <= -200.0f) {
				recorrido5 = false;
				recorrido6 = true;
			}
		}
		else if (recorrido6) {
			movHeli_x += 3.0f;
			movHeli_z += 3.0f * (200.0f / 250.0f);
			orient = 90.0f - 38.65f;
			if (movHeli_x >= 0.0f && movHeli_z >= 0.0f) {
				recorrido6 = false;
				recorrido1 = true;
			}
		}
	}

	switch (sport)
	{
	case 1:
		movSport_z += 5.0f;
		if (movSport_z >= 700.0f) {
			orientation = 90.0f;
			sport = 2;
		}
		break;
	case 2:
		movSport_x += 5.0f;
		if (movSport_x >= 500.0f) {
			orientation = 180.0f;
			sport = 3;
		}
		break;
	case 3:
		movSport_z -= 5.0f;
		if (movSport_z <= 0.0f)
		{
			orientation = 0.0f;
			movSport_z = 0;
			movSport_x = 0;
			sport = 1;
		}
		break;
	default:
		break;
	}
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// CARGA DE MODELOS
	// -----------

	// MODELOS ESTÁTICOS
	// ----------
	//ARBUSTOS
	Model arbustos("resources/objects/arbustos/bush.obj");

	//CASA
	Model casa("resources/objects/casa/casa.obj");

	//COCINA
	Model licuadora("resources/objects/cocina/blender.obj");
	Model comedor("resources/objects/cocina/comedor.obj");
	Model estufa("resources/objects/cocina/estufa.obj");
	Model mantel("resources/objects/cocina/mantel.obj");
	Model microwave("resources/objects/cocina/microwave.obj");
	Model mueble("resources/objects/cocina/mueble.obj");
	Model platos("resources/objects/cocina/platos.obj");
	Model refrigerador("resources/objects/cocina/refrigerador.obj");
	Model rollo("resources/objects/cocina/rollo.obj");

	//CUARTO1
	//cama1
	Model almohadas1("resources/objects/cuarto1/cama/almohadas.obj");
	Model base1("resources/objects/cuarto1/cama/base.obj");
	Model cabecera1("resources/objects/cuarto1/cama/cabecera.obj");
	Model colchon1("resources/objects/cuarto1/cama/colchon.obj");
	Model sabana1("resources/objects/cuarto1/cama/sabana.obj");
	//
	Model armario1("resources/objects/cuarto1/armario.obj");
	Model conejos("resources/objects/cuarto1/conejos.obj");
	Model mueble1("resources/objects/cuarto1/mueble.obj");
	Model planta("resources/objects/cuarto1/planta.obj");
	Model ropa("resources/objects/cuarto1/ropa.obj");
	Model tv1("resources/objects/cuarto1/tv.obj");

	//CUARTO2
	//cama2
	Model almohadas2("resources/objects/cuarto2/cama/almohadas.obj");
	Model base2("resources/objects/cuarto2/cama/base.obj");
	Model cabecera2("resources/objects/cuarto2/cama/cabecera.obj");
	Model colchon2("resources/objects/cuarto2/cama/colchon.obj");
	Model sabana2("resources/objects/cuarto2/cama/sabana.obj");
	//
	Model armario2("resources/objects/cuarto2/armario.obj");
	Model calcetines("resources/objects/cuarto2/calcetines.obj");
	Model camisas("resources/objects/cuarto2/camisas.obj");
	Model escritorio("resources/objects/cuarto2/escritorio.obj");
	Model lamp("resources/objects/cuarto2/lamp.obj");
	Model laptop("resources/objects/cuarto2/laptop.obj");
	Model libros2("resources/objects/cuarto2/libros.obj");
	Model mueble2("resources/objects/cuarto2/mueble.obj");
	Model patos("resources/objects/cuarto2/patos.obj");
	Model ps4("resources/objects/cuarto2/ps4.obj");
	Model sacos("resources/objects/cuarto2/sacos.obj");
	Model toallas2("resources/objects/cuarto2/toallas.obj");
	Model toy("resources/objects/cuarto2/toy.obj");
	Model zapatos("resources/objects/cuarto2/zapatos.obj"); //hasta aqui dibuje bien

	//CUARTO3
	//cama
	Model almohadas3("resources/objects/cuarto3/cama/almohadas.obj");
	Model base3("resources/objects/cuarto3/cama/base.obj");
	Model cabecera3("resources/objects/cuarto3/cama/cabecera.obj");
	Model colchon3("resources/objects/cuarto3/cama/colchon.obj");
	Model sabana3("resources/objects/cuarto3/cama/sabana.obj");
	//
	Model plantas("resources/objects/cuarto3/plantas.obj");
	Model retrato("resources/objects/cuarto3/retrato.obj");
	Model vestidor("resources/objects/cuarto3/vestidor.obj");

	//PISO
	Model piso("resources/objects/piso/piso.obj"); //ya está dibujado

	//PUERTAS
	Model puertas("resources/objects/puertas/puertas.obj");

	//SALA
	Model alfombra("resources/objects/sala/alfombra.obj");
	Model decoracion("resources/objects/sala/decoracion.obj");
	Model mesa("resources/objects/sala/mesa.obj");
	Model repisa("resources/objects/sala/repisa.obj");
	Model sofa("resources/objects/sala/sofa.obj");

	//VENTANAS
	Model ventanas("resources/objects/ventanas/ventanas.obj");

	//BAÑO SUITE (1)
	Model cortina1("resources/objects/wc1/cortina2.obj");
	Model jabon1("resources/objects/wc1/jabon.obj");
	Model lavamanos1("resources/objects/wc1/lavamanos.obj");
	Model mirror1("resources/objects/wc1/mirror.obj");
	Model papel1("resources/objects/wc1/papel.obj");
	Model regadera1("resources/objects/wc1/regadera.obj");
	Model sanitario1("resources/objects/wc1/sanitario.obj");

	//BAÑO GENERAL (2)
	Model cortina2("resources/objects/wc2/cortina2.obj");
	Model jabon2("resources/objects/wc2/jabon.obj");
	Model lavamanos2("resources/objects/wc2/lavamanos.obj");
	Model mirror2("resources/objects/wc2/espejo.obj");
	Model papel2("resources/objects/wc2/papel.obj");
	Model regadera2("resources/objects/wc2/regadera.obj");
	Model sanitario2("resources/objects/wc2/sanitario.obj");

	//COCHE
	Model coche("resources/objects/coche/car.obj");
	Model llanta("resources/objects/coche/llanta.obj");

	//AVE
	Model cuerpo("resources/objects/falcon/cuerpo.obj");
	Model alader("resources/objects/falcon/alader.obj");
	Model alaizq("resources/objects/falcon/alaizq.obj");

	//HELICOPTER
	Model body("resources/objects/helicopter/body.obj");
	Model prop("resources/objects/helicopter/prop.obj");

	//MODELOS DINÁMICOS
	// -----------
	ModelAnim running("resources/objects/Deportista/Running.dae");
	running.initShaders(animShader.ID);

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotAla = 0;
		KeyFrame[i].giro = 0;
	}

	//ANIMACIÓN KEYFRAMES CON ARCHIVO

	//1. Abrimos el archivo
	ifstream archivo;
	archivo.open("resources/animacion/keyframes.txt");

	//2. Leemos línea por línea
	if (archivo.is_open()) {
		for (int i = 0; i < MAX_FRAMES; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				getline(archivo, line);
				switch (j) {
				case 0: KeyFrame[i].posX = stof(line);
					break;
				case 1: KeyFrame[i].posY = stof(line);
					break;
				case 2: KeyFrame[i].posZ = stof(line);
					break;
				case 3: KeyFrame[i].rotAla = stof(line);
					break;
				case 4: KeyFrame[i].giro = stof(line);
					break;
				}
			}
		}
	}

	//3. Cerramos el archivo
	archivo.close();

	//imprimimos el contenido del arreglo de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		cout << "Frame Index: " << i << endl;
		cout << "PosX: " << KeyFrame[i].posX << endl;
		cout << "PosY: " << KeyFrame[i].posY << endl;
		cout << "PosZ: " << KeyFrame[i].posZ << endl;
		cout << "rotAla: " << KeyFrame[i].rotAla << endl;
		cout << "giro: " << KeyFrame[i].giro << endl;
	}

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);
		
		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(0.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setVec3("spotLight[0].position", glm::vec3(0.0f, 0.0f, 10.0f));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(0.0f, -1.0f, 0.0f));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.0009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.0005f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);
		

		// -------------------------------------------------------------------------------------------------------------------------
		// ANIMACIONES
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);
	
		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-255.936f + movSport_x, 8.3391f, -428.04f + movSport_z));
		model = glm::rotate(model, glm::radians(orientation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f));
		animShader.setMat4("model", model);
		running.Draw(animShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// ESCENARIO
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);

		//ARBUSTOS
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		arbustos.Draw(staticShader);

		//CASA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		casa.Draw(staticShader);

		//COCINA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		licuadora.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		comedor.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		estufa.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		mantel.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		microwave.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		mueble.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		platos.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		refrigerador.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		rollo.Draw(staticShader);

		//CUARTO1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		almohadas1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		base1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		cabecera1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		colchon1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		sabana1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		armario1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		conejos.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		mueble1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		planta.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		ropa.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		tv1.Draw(staticShader);

		//CUARTO 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		almohadas2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		base2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		cabecera2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		colchon2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		sabana2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		armario2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		calcetines.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		camisas.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		escritorio.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		lamp.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		laptop.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		libros2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		mueble2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		patos.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		ps4.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		sacos.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		toallas2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		toy.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		zapatos.Draw(staticShader);

		//CUARTO3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		almohadas3.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		base3.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		cabecera3.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		colchon3.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		sabana3.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		plantas.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		retrato.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		vestidor.Draw(staticShader);

		//PUERTAS
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		puertas.Draw(staticShader);

		//SALA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		alfombra.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		decoracion.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		mesa.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		repisa.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		sofa.Draw(staticShader);

		//VENTANAS
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		ventanas.Draw(staticShader);

		//BAÑO SUITE (1)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		cortina1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		jabon1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		lavamanos1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		mirror1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		papel1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		regadera1.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		sanitario1.Draw(staticShader);

		//BAÑO GENERAL (2)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		cortina2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		jabon2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		lavamanos2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		mirror2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		papel2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		regadera2.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		sanitario2.Draw(staticShader);

		//COCHE
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-91.692f + movAuto_x, 39.831f + movAuto_y, 92.421f + movAuto_z));
		tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(escala));
		staticShader.setMat4("model", model);
		coche.Draw(staticShader);
		
		model = glm::translate(tmp, glm::vec3(-24.8199f, -20.589f, -61.383f));
		model = glm::scale(model, glm::vec3(escala));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);//izq delantera

		model = glm::translate(tmp, glm::vec3(25.05f, -20.589f, -61.383f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(escala));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(-1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);//der delantera

		model = glm::translate(tmp, glm::vec3(-24.8199f, -20.589f, 29.823));
		model = glm::scale(model, glm::vec3(escala));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);//izq trasera

		model = glm::translate(tmp, glm::vec3(25.05f, -20.589f, 29.823f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(escala));
		model = glm::rotate(model, glm::radians(girollantas), glm::vec3(-1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);//der trasera


		//AVE
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(119.259f, 155.056f, 139.356f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		tmp = model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f));
		staticShader.setMat4("model", model);
		cuerpo.Draw(staticShader);

		//Ala izq
		model = glm::translate(tmp, glm::vec3(-2.883f, 7.0504f, 0.51212f));
		model = glm::rotate(model, glm::radians(-rotAla), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(20.0f));
		staticShader.setMat4("model", model);
		alaizq.Draw(staticShader);

		//Ala der
		model = glm::translate(tmp, glm::vec3(2.883f, 7.0504f, 0.51212f));
		model = glm::rotate(model, glm::radians(rotAla), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(20.0f));
		staticShader.setMat4("model", model);
		alader.Draw(staticShader);


		//Helicopter
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f + movHeli_x, 64.449f + movHeli_y, -370.619f + movHeli_z));
		tmp = model = glm::rotate(model, glm::radians(orient), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f));
		staticShader.setMat4("model", model);
		body.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(0.90765f, 5.5635f, 2.29545f));
		model = glm::scale(model, glm::vec3(30.0f));
		model = glm::rotate(model, glm::radians(giroProp), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		prop.Draw(staticShader);



		// -------------------------------------------------------------------------------------------------------------------------
		// Caja Transparente --- Siguiente Práctica
		// -------------------------------------------------------------------------------------------------------------------------
		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		cubo.Draw(staticShader);
		glEnable(GL_BLEND);*/
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		posY--;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		posY++;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotAla--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotAla++;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giro--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giro++;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		animacion ^= true;
	}

	//Reset car animation
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		movAuto_x = 0.0f;
		movAuto_y = 0.0f;
		movAuto_z = 0.0f;
		escala = 30.0f;
		car = 1;
	}

	//Helicopter animation
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		animacion2 ^= true;
	}

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			//std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}