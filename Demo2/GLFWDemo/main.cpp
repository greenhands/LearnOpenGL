#define GLEW_STATIC //��̬����
#include <GL/glew.h> //glew.h������OpenGLͷ�ļ������Ҫ������������֮ǰ
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"ourColor = color;\n"
"}\n\0";

//����һ��uniform vec4��ourColor,����������Shader������ɫ
const GLchar * fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(ourColor, 1.0f);\n"
"}\n\0";

int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ��OpenGL����ģʽ
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//��������
	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//ע��ص�����
	glfwSetKeyCallback(window, key_callback);

	//GLEW��ʼ����GLEW����������OpenGL�ĺ���ָ���,�����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	//GLEW��ʼ������

	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height); //��Ⱦ���ڵ�λ�úʹ�С

	GLuint vertexShader; //����������ɫ��
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//����ɫ��Դ�븽�ӵ���ɫ������Ȼ�����
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram; //������ɫ������
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); //������ɫ��������
	glDeleteShader(vertexShader); //������ɺ�ɾ����ɫ��
	glDeleteShader(fragmentShader);

	//��������(x,y,z),z�������Ϊ��������
	GLfloat vertices[] = {
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//���㻺��Զ�����GPU�ڴ�(ͨ������Ϊ�Դ�)�д����������
	GLuint VBO;
	glGenBuffers(1, &VBO);

	//��������������Ķ������Ե��ú�VBO���ᴢ�������VAO��
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	//���½��Ļ���󶨵�GL_ARRAY_BUFFER�ϣ����к�����һ�ֻ�������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//���������ݸ��Ƶ��󶨵Ļ���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//����λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//������ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//��Ϸѭ��
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //�����û�д���ʲô�¼�,Ȼ����ö�Ӧ�Ļص�����

		//ִ����Ⱦ��ʼ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //������ջ������ɫ
		glClear(GL_COLOR_BUFFER_BIT);
		
		//--����ͼ��--
		glUseProgram(shaderProgram); //������ɫ������
		/*
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2 )+0.5;
		//��ȡuniform ����ourColor�ĵ�ַ
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); //����uniform������ֵ
		*/

		glBindVertexArray(VAO);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //ʹ����䣨Ĭ�ϣ�ģʽ����
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		//ִ����Ⱦ����

		glfwSwapBuffers(window); 
		/*Ӧ��˫��������Ⱦ����Ӧ�ó���
		  ǰ��Ļ�����������ʾ
		  ��������ڼ��㣬����Ⱦ����ִ�н�����
		  ����ǰ��̨��������ͼ�����ʾ������
		 */
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate(); //�ͷ�GLFW������ڴ�
	return 0;
}

//�����ص�����
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}