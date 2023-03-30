#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ctest1.h"
#include "ctest2.h"
#include "utils.h"
//#include "glm/glm.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);


GLFWwindow* init() {
	if (!glfwInit()) {
		printf("glfwInt() got rekt");
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Crea una finestra con una larghezza di 640 e un'altezza di 480
	GLFWwindow *window = glfwCreateWindow(640, 480, "DIO BUCO DI CULO", NULL, NULL);
	if (!window) {
		printf("window got rekt");
		glfwTerminate();
		return NULL;
	}

	// Associa la finestra all'area di visualizzazione corrente
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		printf("Failed to initialize GLAD");
		return NULL;
	}

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	glClearColor(0.6f, 0.3f, 0.3f, 1.0f);

	return window;
}

char* textFileToStringChar(char const *file_name) {
	char *shaderSourceCode;
	long numOfBytes = 0;

	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("File error\n");
	}
	fseek(fp, 0, SEEK_END);
	numOfBytes = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	printf("Number of bytes: %ld\n", numOfBytes);
	shaderSourceCode = (char*) malloc(numOfBytes);
	if (shaderSourceCode == NULL) {
		printf("malloc error\n");
	}
	fread(shaderSourceCode, sizeof(char), numOfBytes + 1, fp);
	fclose(fp);
	*(shaderSourceCode + numOfBytes) = '\0';
	printf("The file: %s\n\n", shaderSourceCode);
	return shaderSourceCode;
}
GLuint shaderProgramID = 0;
void installShaders() {

	char const *fname_shader = "./shader.gls";
	char const *fname_fragment = "./fragment.gls";
	char *vertexShaderSource = textFileToStringChar(fname_shader);
	char *fragmentShaderSource = textFileToStringChar(fname_fragment);

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShaderID);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
	}
	// fragment shader
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderID);
	// check for shader compile errors
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
	}
	// link shaders
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	glLinkProgram(shaderProgramID);
	// check for linking errors
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glUseProgram(shaderProgramID);
	free(vertexShaderSource);
	free(fragmentShaderSource);

}

//@formatter:off
	float triangle_data[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.6f, 0.0f,
			0.0f, 0.5f,0.0f
	};

	float vertices2[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			1.0f, -1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,

			-1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			-1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			0.5f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f
	};

	float triangle_colors[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
	};
//@formatter:on

GLuint VAOs[10];
GLuint VBOs[10];

void loadSimpleTriangle() {
	glGenVertexArrays(1, &VAOs[0]);
	glGenBuffers(1, &VBOs[0]);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
}

void loadTrinagleAndColors() {
	glGenVertexArrays(1, &VAOs[1]);
	glGenBuffers(1, &VBOs[1]);
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

float transform[] = {1,2};

int main(int argc, char **argv) {
	helloUtils();
	printf("size: %d ", sizeof(triangle_data));
	int x;
	ctest1(&x);
	ctest2(&x);
	printf("Vasslx=%d\n", x);

	GLFWwindow *window = init();

	installShaders();

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	GLuint ID_triangle_vbo;
	GLuint ID_vertices2_vbo;
	GLuint ID_colours_vbo;
	GLuint VAO1, VAO2;
	//unsigned int VBO, VAO;
	/*
	 glGenVertexArrays(1, &VAO1);
	 glGenVertexArrays(1, &VAO2);
	 glGenBuffers(1, &ID_triangle_vbo);
	 glGenBuffers(1, &ID_vertices2_vbo);
	 glGenBuffers(1, &ID_colours_vbo);
	 // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	 glBindVertexArray(VAO1);

	 glBindBuffer(GL_ARRAY_BUFFER, ID_triangle_vbo);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);
	 glBindBuffer(GL_ARRAY_BUFFER, ID_colours_vbo);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors, GL_STATIC_DRAW);
	 glBindBuffer(GL_ARRAY_BUFFER, ID_vertices2_vbo);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	 //glBindBuffer(GL_ARRAY_BUFFER, ID_triangle_data);
	 glBindBuffer(GL_ARRAY_BUFFER, ID_vertices2_vbo);
	 //glBindBuffer(GL_ARRAY_BUFFER, ID_colours_vbo);
	 //glBindVertexArray(VAO2);

	 //	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

	 glEnableVertexAttribArray(0);
	 glEnableVertexAttribArray(1);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	 */
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	loadSimpleTriangle();
	loadTrinagleAndColors();
	//loadSimpleTriangle();
	//glBindVertexArray(VAO1);
	//glBindVertexArray(VAOs[0]);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(VAO1);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//PFNGLUSEPROGRAMPROC glUseProgram;
	//glUseProgram = (PFNGLUSEPROGRAMPROC) glfwGetProcAddress("glUseProgram");

	// render loop
	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(VAOs[0]);
	while (!glfwWindowShouldClose(window)) {

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		GLuint vertexColorLocation = glGetUniformLocation(shaderProgramID, "culo");
		//glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.0f, 1.0f);
		glUniform1f(vertexColorLocation, 1.0f);

		//processInput(window);
		// draw our first triangle
		//glBindVertexArray(VAO1); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_LINES, 0, 6);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Termina GLFW
	glfwTerminate();

	printf("Good Bye GayLord\n");

	return 0;
}

void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
	//printf("Mouse\n");
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//int w_width, w_height;
		int fb_width, fb_height;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		glfwGetFramebufferSize(window, &fb_width, &fb_height);
		//glfwGetWindowSize(window, &w_width, &w_height);

		printf("x:\t\t%f\ny:\t\t%f\n", x, y);
		//printf("w_width:\t%d\nw_height:\t%d\n", w_width, w_height);
		//printf("fb_width:\t%d\nfb_height:\t%d\n", fb_width, fb_height);
		printf("X ratio:\t%f\n", x / fb_width);
		printf("Y ratio:\t%f\n", y / fb_height);
		printf("X NDC:\t\t%f\n", (x / fb_width) * 2 - 1);
		printf("Y NDC:\t\t%f\n\n", -((y / fb_height) * 2 - 1));

	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	printf("Oh yea\n");
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	//printf("YOLO\n");
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_A)
			glBindVertexArray(VAOs[0]);
		if (key == GLFW_KEY_S)
			glBindVertexArray(VAOs[1]);
		if (key == GLFW_KEY_D)
			glBindVertexArray(0);

	}
	printf("PRESS\n");
	if (action == GLFW_REPEAT)
		printf("REPEAT\n");
	if (action == GLFW_RELEASE)
		printf("RELEASE\n");

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		printf("Good Bye Gaylord\n");
		glfwSetWindowShouldClose(window, true);
	}
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

