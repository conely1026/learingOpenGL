#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<shader.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	
	//shader
	shader myShader("shader.vs", "shader.fs");
	
	// set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
	float firstTriangle[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};
	float vertices[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};


	//float vertices[] = {
	//0.5f, 0.5f, 0.0f,   // 右上角
	//0.5f, -0.5f, 0.0f,  // 右下角
	//-0.5f, -0.5f, 0.0f, // 左下角
	//-0.5f, 0.5f, 0.0f   // 左上角
	//};

	//unsigned int indices[] = {
	//	// 注意索引从0开始! 
	//	// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
	//	// 这样可以由下标代表顶点组合成矩形

	//	0, 1, 3, // 第一个三角形
	//	1, 2, 3  // 第二个三角形
	//};

	//创建对象 
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	/*unsigned int EBO;
	glGenBuffers(1, &EBO);*/
	
	//绑定到当前上下文 ,`GL_ARRAY_BUFFER` 表示我们希望创建的缓冲区对象存储的是顶点属性数据
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//复制之前定义的顶点数据到缓冲的内存中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 解释顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //位置
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //颜色
	//启用顶点属性
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	////调用 glVertexAttribPointer 会将 VBO 注册为顶点属性的绑定顶点缓冲对象，因此之后我们可以安全地解绑
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	////解绑防止其他VAO调用修改这个VAO，，但这种情况很少出现。
	////修改其他的 VAO 需要调用`glBindVertexArray`函数，因此一般不需要在不需要的情况下解绑 VAO（或者 VBO）
	//glBindVertexArray(0);

	//glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	//glEnableVertexAttribArray(0);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw triangle
		myShader.use();
		myShader.setFloat("horizontalOffset", 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式

		// draw the first triangle using the data from our first VAO
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output an orange triangle
		// then we draw the second triangle using the data from the second VAO
		// when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
		
		
		// glBindVertexArray(0); // no need to unbind it every time 

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	// optional: de-allocate all resources once they've outlived their purpose:
   // ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
