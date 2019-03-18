#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

void frameBuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

struct SIZE {
	int WIDTH;
	int HEIGHT;
} SCR_SIZE = { 800, 600 }; // ����ߴ�

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
	GLFWwindow * window = glfwCreateWindow(SCR_SIZE.WIDTH, SCR_SIZE.HEIGHT, "My OpenGL", NULL, NULL);
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

	while (!glfwWindowShouldClose(window)) { // ��� GLFW �Ƿ�Ҫ���˳�
		processInput(window); // �Ƿ�رմ���

		glfwSwapBuffers(window); // ������ɫ����
		glfwPollEvents();        // ����Ƿ񴥷��¼�
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