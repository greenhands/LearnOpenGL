#include "OpenGLHeader.h"
#include "Camera.h"
#include "Shader.h"


void key_callback(GLFWwindow *window, GLint key, GLint scacode, GLint action, GLint mode);
void mouse_callback(GLFWwindow *window, double xPos, double yPos);
void scroll_callback(GLFWwindow *window, double xDelta, double yDelta);
void do_movement();

static Camera myCamera(0.0f, 0.0f);
static bool keys[1024];
static GLfloat lastTime = 0.0f;
static GLfloat deltaTime = 0.0f;
static double xLastPos = 0.0f, yLastPos = 0.0f;
static bool firstMouse = true;

glm::vec3 cube(0.0f, 0.0f, 0.0f);
glm::vec3 light(1.5f, 2.0f, 1.5f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

int main(){
	lglGlfwInit(3, 3, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(LGL_WINDOW_WIDTH, LGL_WINDOW_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	lglGlewInit();
	glViewport(0, 0, LGL_WINDOW_WIDTH, LGL_WINDOW_HEIGHT);

	Shader myShader("vertex.shader", "fragment.shader");
	Shader lightShader("lightVertex.shader", "lightFrag.shader");

	GLfloat vertices[] = {
		// Positions			// Normal
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	GLuint VBO, VAO;
	GLint attrSize[] = {3, 3, 2};
	lglCreateBuffer(&VBO, vertices, sizeof(vertices));
	lglCreateVertexArray(&VAO, VBO, attrSize, 3);

	GLuint texture1, texture2;
	lglCreateTexture(&texture1, GL_TEXTURE_2D, "wood.png");
	lglCreateTexture(&texture2, GL_TEXTURE_2D, "face.png");

	myCamera.MouseSensivity = 0.02f;
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//start
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat curTime = glfwGetTime();
		deltaTime = curTime - lastTime;
		lastTime = curTime;

		do_movement();

		//camera matrix
		glm::mat4 view = myCamera.GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(myCamera.Zoom), GLfloat(LGL_WINDOW_WIDTH) / LGL_WINDOW_HEIGHT, 0.1f, 100.0f);

		//texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//cube shader
		myShader.Use();

		glUniform1i(glGetUniformLocation(myShader.Program, "texture1"), 0);
		glUniform1i(glGetUniformLocation(myShader.Program, "texture2"), 0);
		
		glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model1;
		model1 = glm::translate(model1, cube);
		model1 = glm::rotate(model1, glm::radians(curTime * 45.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model1));

		glUniform3f(glGetUniformLocation(myShader.Program, "viewPos"), myCamera.Position.x, myCamera.Position.y, myCamera.Position.z);
		glUniform3f(glGetUniformLocation(myShader.Program, "lightPos"), light.x, light.y, light.z);
		glUniform3f(glGetUniformLocation(myShader.Program, "lightColor"), lightColor.x, lightColor.y, lightColor.z);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//light shader
		lightShader.Use();

		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model2;
		model2 = glm::translate(model2, light);
		model2 = glm::scale(model2, glm::vec3(1.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model2));

		glUniform3f(glGetUniformLocation(lightShader.Program, "lightColor"), lightColor.x, lightColor.y, lightColor.z);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//end
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos){
	if (firstMouse)
	{
		xLastPos = xPos;
		yLastPos = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - xLastPos;
	GLfloat yOffset = yLastPos - yPos;
	xLastPos = xPos;
	yLastPos = yPos;
	myCamera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow *window, double xDelta, double yDelta){
	myCamera.ProcessMouseScroll(yDelta);
}

void do_movement(){
	if (keys[GLFW_KEY_W])
	{
		myCamera.ProcessKeyBoard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S])
	{
		myCamera.ProcessKeyBoard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_D])
	{
		myCamera.ProcessKeyBoard(RIGHT, deltaTime);
	}
	if (keys[GLFW_KEY_A])
	{
		myCamera.ProcessKeyBoard(LEFT, deltaTime);
	}
}