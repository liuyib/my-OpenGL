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
	// glfw ��ʼ��������
	// -----------------
	glfwInit(); // ��ʼ�� glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // �������汾�ţ�major��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // ���ôΰ汾�ţ�minor��
	// ʹ�ú���ģʽ��Core-profile����һ��ģʽ��������Ⱦģʽ��Immediate mode����Ҳ�ƹ̶���Ⱦ����
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������
	// --------
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My OpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Window create filed" << endl;
		glfwTerminate(); // �ͷ�������Դ
		return -1;
	}
	glfwMakeContextCurrent(window); //�����̵߳�������
	glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback); // �������ڴ�С

	// ���� glad��glfw �ĺ���ָ��⣩
	// ---------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "GLAD init filed" << endl;
		return -1;
	}

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) { // ���ָ�������Ƿ�Ҫ���˳�
		processInput(window); // ��������
			
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();        // ����Ƿ񴥷��¼�
		glfwSwapBuffers(window); // ������ɫ����
	}

	glfwTerminate(); // �ͷ�������Դ
	return 0;
}

// ע��֡�����С����
void frameBuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// ���� Esc �رմ���
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}