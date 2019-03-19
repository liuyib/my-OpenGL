#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void frameBuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw 初始化和配置
	// -----------------
	glfwInit(); // 初始化 glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 设置主版本号（major）
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 设置次版本号（minor）
	// 使用核心模式（Core-profile）另一种模式是立即渲染模式（Immediate mode），也称固定渲染管线
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口
	// --------
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My OpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Window create filed" << endl;
		glfwTerminate(); // 释放所有资源
		return -1;
	}
	glfwMakeContextCurrent(window); //设置线程的上下文
	glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback); // 监听窗口大小

	// 加载 glad（glfw 的函数指针库）
	// ---------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "GLAD init filed" << endl;
		return -1;
	}

	// 渲染循环
	while (!glfwWindowShouldClose(window)) { // 检查指定窗口是否要求退出
		processInput(window); // 按键操作
			
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();        // 检查是否触发事件
		glfwSwapBuffers(window); // 交换颜色缓冲
	}

	glfwTerminate(); // 释放所有资源
	return 0;
}

// 注册帧缓冲大小函数
void frameBuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// 按下 Esc 关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}