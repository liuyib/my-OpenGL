# OpenGL

学习网址：[LearnOpenGL CN](https://learnopengl-cn.github.io/)

## 一些名词的概念

- OpenGL

OpenGL 函数库相关的 API 有核心库(gl)，实用库(glu)，辅助库(aux)、实用工具库(glut)，窗口库(glx、agl、wgl)和扩展函数库等。gl 是核心，glu 是对 gl 的部分封装。glx、agl、wgl 是针对不同窗口系统的函数。glut 是为跨平台的 OpenGL 程序的工具包，比 aux 功能强大（aux 很大程度上已经被 glut 库取代。）。

- glut（OpenGL Utility Toolkit）

是 OpenGL 的工具库。这部分函数以 glut 开头，主要包括窗口操作函数，窗口初始化、窗口大小、窗口位置等函数；回调函数：响应刷新消息、键盘消息、鼠标消息、定时器函数等；创建复杂的三维物体；菜单函数；程序运行函数。gult 对应的开源实现是 freegult。[freegult 官网](http://freeglut.sourceforge.net/)

- glew

glut（或 freeglut）主要是 1.0 的基本函数功能；glew 是使用 OpenGL2.0 之后的一个工具函数。不同的显卡公司，也会发布一些只有自家显卡才支持的扩展函数，你要想用这数函数，不得不去寻找最新的 glext.h,有了 glew 扩展库，你就再也不用为找不到函数的接口而烦恼，因为 glew 能自动识别你的平台所支持的全部 OpenGL 高级扩展函数。也就是说，只要包含一个 glew.h 头文件，你就能使用 gl,glu,glext,wgl,glx 的全部函数。glew 库提供高版本 gl 函数的支持。如果不嫌麻烦的话，也可以手写函数指针，来判断各个 opengl 高版本函数是否支持，但是 glew 库 做了大大的简化，使得 opengl 各个版本的函数像原生函数一样，可以随意调用。

- glfw

glfw 无愧于其号称的 lightweight 的 OpenGL 框架，的确是除了跨平台必要做的事情都没有做，所以一个头文件，很少量的 API，就完成了任务。glfw 的开发目的是用于替代 glut 的，从代码和功能上来看，我想它已经完全的完成了任务。一个轻量级的，开源的，跨平台的 library。支持 OpenGL 及 OpenGL ES，用来管理窗口，读取输入，处理事件等。因为 OpenGL 没有窗口管理的功能，所以很多热心的人写了工具来支持这些功能，比如早期的 glut，现在的 freeglut 等。

OpenGL 中，任何事物都是在 3D 空间中，而屏幕而是 2D 的，所以 OpenGL 的大部分工作是将 3D 坐标转换为 2D 的过程。这个处理过程由 OpenGL 的 **图形渲染管线**（Graphics Pipeline）进行管理。

- glad

简单说glad是glew的升级版。用哪个都行。glew比较老，glad比较新。

> 综上所述：
> 1. glfw 是 glut 的升级和改进
> 2. glew 包含了 OpenGL 所需的核心
> 3. glad 是 glew 的升级版

推荐使用：`glfw + glad` 进行开发。

## 图形渲染管线

图形渲染管线分为两部分：

1. 把 3D 坐标转换为 2D 坐标
2. 把 2D 坐标转换为实际的有颜色的像素

> 双缓冲 (Double Buffer)
>
> 应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。这是因为生成的图像不是一下子被绘制出来，而是从左到右，从上到下逐像素绘制而成。最终图像不是在瞬间显示给用户，而是通过一步步生成的，这会导致显然的结果很不真实。为了规避这些问题，可以使用双缓冲来渲染窗口应用程序。**前** 缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的渲染指令都会保存在 **后** 缓冲上绘制。当所有的渲染指令执行完毕后，**交换** 前后缓冲，这样图片就立即显示出来了，之前的不真实感就消除了。

当今大多数显卡都有成千上万的小处理核心，它们在 GPU 上为每一个（渲染管线）阶段运行各自的小程序，从而在图形渲染管线中快速处理你的数据。这些小程序叫做 **着色器**(Shader)。OpenGL 着色器使用 OpenGL **着色器语言**（OpenGL Shading Language, GLSL）写成的。

图形渲染管线示意图：

![](./public/pipeline.png)

图形渲染管线的过程是复杂的，通常我们只需要配置 **顶点** 和 **片段着色器** 即可。几何着色器是可选的，通常我们使用默认的即可。

## 一些示例代码

- 初始配置 glfw 窗口

  ```C++
  int main() {
    glfwInit();
    glfwWindowHint(glfw_CONTEXT_VERSION_MAJOR, 3); // 主版本号
    glfwWindowHint(glfw_CONTEXT_VERSION_MINOR, 3); // 次版本号
    glfwWindowHint(glfw_OPENGL_PROFILE, glfw_OPENGL_CORE_PROFILE); // 设置 OpenGL 的模式（核心模式 / 立即渲染模式）
    // glfwWindowHint(glfw_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac 系统需要添加这一行代码

    return 0;
  }
  ```

- 初始化 GLAD

  ```C++
  if (!gladLoadGLLoder((GLADloadproc)glfwGetProcAddress)) {
    cout << "Filed to init glad" << endl;
    return -1;
  }
  ```

- 窗口大小改变时调整视口大小

  ```C++
  void frameBuffer_size_callback(glfwwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  }

  glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);
  ```

- 响应按键操作

  ```C++
  void processInput() {
    if (glfwGetKey(window, glfw_KEY_ESCAPE) == glfw_PRESS) { // 按下 Esc，关闭窗口
      glfwSetWindowShouldClose(window, true);
    }
  }
  ```

- 将渲染操作放入渲染循环中

  ```C++
  while (!glfwWindowShouldClose(window)) {
    // 按键操作
    processInput(window);

    // 渲染指令
    // ...

    // 轮询是否有事件需要调用，交换缓冲
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  ```

## OpenGL API

- `glClear(buffer)`

  用来清空缓冲，清空的缓冲类型由参数指定。
  参数是一个缓冲位，取值有：`GL_COLOR_BUFFER_BIT`, `GL_DEPTH_BUFFER_BIT`, `GL_STENCIL_BUFFER_BIT`

- `glClearColor(r, g, b, a)`

  设置清空屏幕所用的颜色。
  参数是一个颜色的 RGBA 值

- `glViewport(posX, posY, width, height)`

  设置视口的维度（Dimension）

## glfw API

[官网](https://www.glfw.org/)

[窗口相关的函数和类型](https://www.glfw.org/docs/latest/group__window.html)

- `glfwInit()`

  实例化 glfw 窗口。

- `glfwWindowHint(glfw_*, num)`

  配置 glfw 窗口。
  第一个参数代表选项名称。这个选项名称可以从很多 `glfw_` 开头的枚举值中选择。第二个参数是这个选项的值。

  > 第一个参数对应的所有选项都可以在这找到：[glfw’s window handling](https://www.glfw.org/docs/latest/window.html#window_hints)

- `glfwCreateWindow(width, height, name, NULL, NULL)`

  创建一个 glfw 窗口，并返回一个 glfwwindow 对象。

  由于这个函数返回的 glfwwindow 对象，在后面会经常用到，所以可以这样保存起来：

  ```C++
  // 最后两个参数暂时先设为 NULL
  glfwwindow* window = glfwWindow(800, 600, "liuyibo", NULL, NULL);
  ```

- `glfwMakeContextCurrent(glfwwindow* window)`

  使指定的窗口的上下文在调用线程上最新。

- `glfwSetFramebufferSizeCallback(glfwwindow* window, callback)`

  监听指定的窗口，当期大小改变时，执行回调函数。

- `glfwWindowShouldClose(glfwwindow* window)`

  返回指定窗口的关闭标志的值

- `glfwSwapBuffers(glfwwindow* window)`

  用于交换指定窗口的前缓冲区和后缓冲区。（指定的窗口必须具有 OpenGL 或 OpenGL ES 上下文，否则会抛错）

- `glfwPollEvents()`

  检测是否有事件触发，即执行事件队列中的事件，然后立即返回。（执行事件意味着会调用与事件相关的窗口和回调函数）`Poll: 轮询`

- `glfwTerminate()`

  释放之前分配的所有资源。

- `glfwGetKey(glfwwindow* window, key)`

  返回指定按键的最后的状态。返回的状态有：`glfw_PRESS` 或 `glfw_RELEASE`。
  全部键的取值：[Keyboard keys](https://www.glfw.org/docs/latest/group__keys.html)

  > 不要用此方法实现文本输入功能

- `glfwSetWindowShouldClose(glfwwindow* window, value)`

  设置指定窗口关闭标志的值。（value 为 true，直接关闭窗口）
