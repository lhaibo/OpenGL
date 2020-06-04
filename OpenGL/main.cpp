#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//顶点数据
float vertices[] = {
	-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
	0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
	0.0f,0.5f,0.0f,0.0f,0.0f,1.0f,
	//-0.5f,-0.5f,0.0f,
	//0.5f,-0.5f,0.0f,
	0.8f,-0.8f,0.0f,1.0f,0.0f,1.0f,
};

unsigned int indices[] = {
	0,1,2,
	0,1,3
};

//Vertex Shader
const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 6) in vec3 aColor;\n"
"out vec4 vertexColor;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	vertexColor= vec4(aColor.x,aColor.y,aColor.z,1.0);\n"
"}\n";

//Fragment Shader
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"uniform vec4 myColor;\n"
"void main(){\n"
"	FragColor = vec4(vertexColor.x,vertexColor.y,vertexColor.z,vertexColor.w);}\n";

// The MAIN function, from here we start the application and run the game loop
int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW 初始化GLFW
	glfwInit();
	// Set all the required options for GLFW 设置GLFW需要的选项
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions 创建一个可以应用GLFW里面的方法的GLFW窗口对象
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);//设置opengl渲染窗口的尺寸大小

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);//不渲染背面

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//绑定回调函数

	//
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	////实例化顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//将顶点缓冲对象绑定到GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//把数据复制到当前绑定缓冲
	//
	unsigned int EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//创建顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//创建片面着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//创建着色器程序
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(6);

	// Game loop 游戏循环
	while (!glfwWindowShouldClose(window))//渲染循环
	{
		//输入
		processInput(window);//在每一帧中检测

		//状态设置函数
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//用一种颜色清空屏幕
		//状态使用函数
		glClear(GL_COLOR_BUFFER_BIT);//清空颜色缓冲

		// 渲染指令
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		float redValue= (cos(timeValue) / 2.0f) + 0.5f;
		float blueValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
		//检测并调用事件
		glfwPollEvents();
		glfwSwapBuffers(window);//每一帧绘制（交换缓冲）
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
//回调函数，每当窗口大小更改时，调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//检测用户是否按键
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}