/*
	Graphics pipline:
	1. Vertex Shader: transform 3D coordinates into different 3D coordinates
	2. Primative Assembly: assembles all points in the primative shape given
	3. Geometry Shader: has the ability to generate other shapes by emitting new vertices to form new (or other) primatives.
	4. Rasterization Stage: maps the resulting primatives to the corresponding pixels on the final screen, resulting in fragments for the fragments shader to use.
	clipping is performed before the fragment shader runs
	5. Fragment Shader: calculate the final color of a pixel and this is usually the stage where all the advanced OpenGL affects occur.
	   Ususally, the fragment shader contains data about the 3D scene that it can use to calculate the final pixel color (like lights, shadows, color of the light and so on).
	6. Alpha Test and Blending Stage: This stage checks all corresponding depth (and stencil) value of the fragment and uses those to check if the resulting fragment is
	   in front or behind other objects and should be discarded accordingly. This stage also checks the alpha value and blends accordingly.

	In Modern OpenGL we are required to define at least a vertex and fragment shader of our own (there is no default vertex/fragment shaders on the GPU).


	Normalized Device Coordinates (NDC)
	Once vertex coordinates have been processed by the vertex shader, they should be in normalized device coordinates which is a small space where the
	x, y, and z values vary from -1.0 to 1.0. Any coordinates that fall outside this range will be discarded/clipped and won't be visible on your screen.

*/

//#include<iostream>
//#include<fstream>
//#include<string>
//#include<sstream>
//#define GLEW_STATIC //static binding of extension wrangler lib
//#include<GL/glew.h> //included GLEW first. The include file contains the correct OpenGL header includes.
//#include<GLFW/glfw3.h>

#include"utility.h"
#include"Camera.h"


void KeyPress(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
void CursorPos(GLFWwindow* window, double xpos, double ypos);
std::string ReadShaderFile(const GLchar* filepath);
bool CheckShaderCompilation(GLuint shader);
bool CheckShaderLinking(GLuint program);

jml::Camera camera;

GLfloat lastX = 0.0f;
GLfloat lastY = 0.0f;
GLboolean firstMouse = true;
int main(int argc, char* argv[]) {

	glfwInit(); //initialized glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //GLFW will not run if the user does not have the proper OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //this causes an invalid operation error if a legacy (immediate profile) function is called
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create a window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	
	if (window == nullptr) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window); //tell GLFW to make the context of our window the main context on the current thread

									//NOTE: I put this code before creating a window object, and GLEW init failed.
									//GLEW manages function pointers for OpenGL. It needs to be initalized before calling any OpenGL functions.
	glewExperimental = GL_TRUE; //ensures GLEW uses more modern techniques. Leaving default value and using core profile can cause problems.
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	//Tell OpenGL the size of the rendering window so OpenGL knows how we want to display the data and coordinates with 
	//respect to the window. We can set those dimensions via the glViewport function
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//the viewport can be set to smaller dimensions tha GLFW's dimensions; then all the OpenGL rendering would be displayed
	//in a smaller window and we could display other elments outside the OpenGL viewport


	//register callback functions
	glfwSetKeyCallback(window, KeyPress);
	glfwSetCursorPosCallback(window, CursorPos);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	GLfloat T1[] = {
		0.5f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	GLfloat T2[] = {
		-0.5f, 0.5f, 0.0f,
		 0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f
	};

	GLfloat T3[] = {
		 0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f,
		 0.0f,  0.5f,  0.0f
	};


	GLfloat T4[] = {
		 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f
	};

	GLfloat T5[] = {
		 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, //Top-Right
		 0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, //Bottom-Right
		-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, //Bottom-Left
		-0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f  //Top-Left
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLfloat T6[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	GLuint VAOs[6], VBOs[6], EBO;
	glGenVertexArrays(6, VAOs);
	glGenBuffers(6, VBOs);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T1), T1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T2), T2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T3), T3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T4), T4, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	
	glBindVertexArray(VAOs[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T5), T5, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	glBindVertexArray(VAOs[5]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T6), T6, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);



	//vertex shader source
	std::string vertexShaderSourceStr = ReadShaderFile("shaders\\core.vs");
	const GLchar* vertexShaderSource = vertexShaderSourceStr.c_str();
	std::cout << vertexShaderSource[0] << std::endl;
	//create shader object
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach source code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile vertex shader
	glCompileShader(vertexShader);
	//check if compilation was successful
	CheckShaderCompilation(vertexShader);

	//get fragment shader source
	std::string fragmentShaderSourceStr = ReadShaderFile("shaders/core.frag");
	const GLchar* fragmentShaderSource = fragmentShaderSourceStr.c_str();
	//create fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	CheckShaderCompilation(fragmentShader);
	
	std::string yellowShaderSourceStr = ReadShaderFile("shaders/yellow.frag");
	const GLchar* yellowShaderSource = yellowShaderSourceStr.c_str();
	GLuint yellowShader;
	yellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowShader, 1, &yellowShaderSource, NULL);
	glCompileShader(yellowShader);
	CheckShaderCompilation(yellowShader);

	std::string greenTimeShaderSourceStr = ReadShaderFile("shaders/greentime.frag");
	const GLchar* greenTimeShaderSource = greenTimeShaderSourceStr.c_str();

	GLuint greenTimeShader;
	greenTimeShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(greenTimeShader, 1, &greenTimeShaderSource, NULL);
	glCompileShader(greenTimeShader);
	CheckShaderCompilation(greenTimeShader);

	std::string multiColorVertexSourceStr = ReadShaderFile("shaders/multicolor.vs");
	std::string multiColorFragSourceStr = ReadShaderFile("shaders/multicolor.frag");
	const GLchar* multiColorVertexSource = multiColorVertexSourceStr.c_str();
	const GLchar* multiColorFragSource = multiColorFragSourceStr.c_str();
	GLuint multiColorVertexShader, multiColorFragShader, multiColorProgram;
	multiColorVertexShader = glCreateShader(GL_VERTEX_SHADER);
	multiColorFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(multiColorVertexShader, 1, &multiColorVertexSource, NULL);
	glShaderSource(multiColorFragShader, 1, &multiColorFragSource, NULL);
	glCompileShader(multiColorVertexShader);
	glCompileShader(multiColorFragShader);
	CheckShaderCompilation(multiColorVertexShader);
	CheckShaderCompilation(multiColorFragShader);
	multiColorProgram = glCreateProgram();
	glAttachShader(multiColorProgram,multiColorVertexShader);
	glAttachShader(multiColorProgram,multiColorFragShader);
	glLinkProgram(multiColorProgram);
	CheckShaderLinking(multiColorProgram);

	/*
		shader program
		When linking the shaders into a program it links the outputs of each shader to the inputs of the next shader. This is
		also where you'll get linking errors if your outputs and inputs do not match.
	*/

	//create program object
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	GLuint yellowProgram;
	yellowProgram = glCreateProgram();
	glAttachShader(yellowProgram, vertexShader);
	glAttachShader(yellowProgram, yellowShader);
	glLinkProgram(yellowProgram);
	CheckShaderLinking(yellowProgram);

	GLuint greenTimeProgram;
	greenTimeProgram = glCreateProgram();
	glAttachShader(greenTimeProgram, vertexShader);
	glAttachShader(greenTimeProgram, greenTimeShader);
	glLinkProgram(greenTimeProgram);
	CheckShaderLinking(greenTimeProgram);


	//use program object
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(yellowShader);
	glDeleteShader(greenTimeShader);
	glDeleteShader(multiColorFragShader);
	glDeleteShader(multiColorVertexShader);

	GLfloat timeValue, greenValue, blueValue, blendValue;
	GLint vertexColorLocation;
	jml::ShaderProgram sp("shaders/multicolor.vs","shaders/multicolor.frag");

	GLuint texture = jml::GenerateTexture("images/container.jpg");
	GLuint texture2 = jml::GenerateTexture("images/awesomeface.png");
	jml::ShaderProgram texProgram("shaders/tex.vs", "shaders/tex.frag");
	jml::ShaderProgram threedProgram("shaders/threed.vs", "shaders/threed.frag");
	//game loop
	while (!glfwWindowShouldClose(window)) { //should close function checks if the window has been instructed to close
		glfwPollEvents(); //checks if any events are triggered (like keyboard input or mouse movement events) and call the corresponding functions (which we set via callback methods).
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //STATE-SETTING set the color to clear the screen with
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //STATE-USING the entire color buffer will be filled with the color as configured by glClearColor.
		threedProgram.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(threedProgram.Program(), "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(threedProgram.Program(), "ourTexture2"), 1);
		glm::mat4 view;
		view = camera.lookAt();
		glm::mat4 projection;
		projection = glm::perspective(45.0f, float(width / height), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(threedProgram.Program(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(threedProgram.Program(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(VAOs[5]);
		GLuint modelLoc = glGetUniformLocation(threedProgram.Program(), "model");
		for (GLuint i = 0; i < 10; i++) {
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			if (i % 3 == 0) {
				angle += .5f * glfwGetTime();
			}
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glBindVertexArray(0);
		glfwSwapBuffers(window); //swap the color buffer (a large buffer that contains color values for each pixel in GLFW's window) that has been used to draw this iteration and show it as output to the screen.
	}
	glDeleteVertexArrays(5, VAOs);
	glDeleteBuffers(5, VBOs);
	glfwTerminate();

	return EXIT_SUCCESS;
}

void KeyPress(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode) {
	//When a user presses the escape key, we set the WindowShouldClose property to true,
	//closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}
	camera.KeyPress(key, scancode, action, mode, glfwGetTime());

}

std::string ReadShaderFile(const GLchar* filepath) {
	std::ifstream file;
	std::stringstream fileStream;
	file.open(filepath);
	if (!file) {
		std::cerr << "ERROR::SHADER::SOURCE::FILE_ERROR\n" << std::endl;
		return nullptr;
	}
	fileStream << file.rdbuf();
	file.close();
	std::cout << fileStream.str().c_str() << std::endl;
	return fileStream.str();
}

bool CheckShaderCompilation(GLuint shader) {
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	} else {
		return true;
	}
}

bool CheckShaderLinking(GLuint program) {
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	} else {
		return true;
	}
}

void CursorPos(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	camera.CursorPos(xpos - lastX, lastY - ypos);
	lastX = xpos;
	lastY = ypos;
}

