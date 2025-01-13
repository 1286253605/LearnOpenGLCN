#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>

#include<Shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
#define RADIUS ( 20.f )


// 控制摄像机
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
// 在OpenGL中 Z轴正方向朝向观察者 如果设置cameraFront为(0.0f, 0.0f, 1.0f) [且相机初始Position.z > 0] 则无法观察到任何原点处的3D图形
/*
* X 轴：从左到右（正方向）
* Y 轴：从下到上（正方向）
* Z 轴：从屏幕内到屏幕外（正方向）
*/
// 具体看 processInput 函数的实现
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// 世界坐标系中的上向量
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float deltaTime = 0.0f;	// 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

// mouse
bool firstMouse = true;
float lastX = 400.0, lastY = 300.0;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;


int main()
{
     //glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 配置为核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
	// 将窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
	// 设置窗口大小改变时的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 获取鼠标位置
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 获取滚轮位置
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 使能深度测试
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vert", "fragmentShader.frag");

// 立方体顶点，包含顶点坐标、颜色和纹理坐标
float vertices[] = {
    // positions          // colors           // texture coords
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glVertexAttribPointer 是一个用于指定顶点属性数据的OpenGL函数，它将顶点属性的格式和数据源与当前的顶点缓冲对象关联起来。
    // texture coord attribute
	// 顶点属性的索引值为2 顶点属性的大小为2(包含两个分量) 顶点属性的类型为GL_FLOAT 顶点属性的是否标准化为GL_FALSE 顶点属性的步长为8*sizeof(float) 顶点属性的偏移量为6*sizeof(float)
	// 就是说 顶点属性的数据在VBO中的排列方式是 位置(3个float) 颜色(3个float) 纹理坐标(2个float) 所以纹理坐标的偏移量是6*sizeof(float) 
	// 如上所述 在第一块内存中 位置(3个float) 颜色(3个float) 纹理坐标(2个float) 所以纹理坐标的偏移量是6*sizeof(float)
    // 索引值为2就是在 Shader中 使用layout( location=2 ) 修饰的变量
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // 使能索引值为2 的变量
    glEnableVertexAttribArray(2);



    // 翻转一下图片
    // stbi_set_flip_vertically_on_load(true);


    // load and create a texture 
    // -------------------------
    unsigned int texture1;
	// 和生成VAO VBO EBO一样 生成纹理对象
    glGenTextures(1, &texture1);
	// 绑定纹理对象 之后所有的纹理操作都是针对这个纹理对象的
    glBindTexture(GL_TEXTURE_2D, texture1); 
	// 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 参数含义分别是 纹理目标 纹理过滤器 纹理缩小的过滤器 纹理放大的过滤器
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("./container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
		// 生成纹理 指定纹理目标 纹理的mipmap(多级渐远纹理)级别 把纹理存储成什么颜色格式(GL_RGB) 纹理的宽度 纹理的高度 纹理的边框宽度(0) 纹理的颜色格式(原图格式GL_RGB) 纹理的数据类型(存储为Byte数组) 纹理的数据
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// 生成多级渐远纹理
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    data = stbi_load("./awesomeface.png", &width, &height, &nrChannels, 0);
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters 设置纹理环绕方式 S轴和T轴
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    ourShader.use();
	// glGetUniformLocation 这个函数从Shader中找到名为 "texture1" 的uniform变量的位置
	// glUniform1i 这个函数把纹理单元的位置值赋给这个uniform变量
    /*
    * 在这个例子中，glUniform1i 函数将着色器程序中名为 texture1 的 uniform 变量设置为 0。
    * 这个值通常用于指定纹理单元的索引。在 OpenGL 中，纹理单元是一个可以绑定纹理的抽象概念，
    * 索引 0 对应于 GL_TEXTURE0，索引 1 对应于 GL_TEXTURE1，依此类推。
    */
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	// 这一行的效果和上面的效果是一样的 只是封装了起来而已
    ourShader.setInt("texture2", 1);



    // 使用三个坐标  创建lookAt矩阵
    glm::mat4 view;
    view = glm::lookAt( glm::vec3(0.0f, 0.0f, 3.0f),        // 摄像机位置 
                        glm::vec3(0.0f, 0.0f, 0.0f),        // 物体位置
                        glm::vec3(0.0f, 1.0f, 0.0f) );      // 世界坐标系上向量


	

    // render loop
    // -----------
	// 通过glfwWindowShouldClose函数检查GLFW是否被要求退出
    while (!glfwWindowShouldClose(window))
    {
		// 获取每一帧的时间
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // GL_DEPTH_BUFFER_BIT 深度缓冲区 GL_COLOR_BUFFER_BIT 颜色缓冲区
        // 深度缓冲区也需要清除 因为每一帧都会绘制一个新的场景 旧的深度信息不再有用 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // render container
        ourShader.use();

        glm::mat4 modelMatrix = glm::mat4(1.0f);
		// 模型矩阵 绕x轴旋转-55度
        // modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
        // 视图矩阵
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		// 投影矩阵
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		// 需要把 SCR_WIDTH 和 SCR_HEIGHT 转换为float类型，否则它们相除的结果会是0
		projectionMatrix = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(ourShader.ID, "modelMatrix");
		// 参数 分别是 uniform的位置 传递的矩阵的个数 转置矩阵的指针
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		int viewLoc = glGetUniformLocation(ourShader.ID, "viewMatrix");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		int projectionLoc = glGetUniformLocation(ourShader.ID, "projectionMatrix");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // 旋转视角
        //float camPosX = sin(glfwGetTime()) * RADIUS;
        //float camPosZ = cos(glfwGetTime()) * RADIUS;
        glm::mat4 view;
        //view = glm::lookAt( glm::vec3(camPosX, 0.0f, camPosZ),  // 摄像机位置随时间变化
        //                    glm::vec3(0.0f, 0.0f, 0.0f), 
        //                    glm::vec3(0.0f, 1.0f, 0.0f));

		// lookAt 函数参数 分别是 摄像机位置 摄像机看的位置 摄像机的上向量
		// 第二个参数为目标物位置 也就是说摄像机看向的位置 值定义为 cameraPos + cameraFront 让摄像机不会一直盯着物体看 
		// 简单来说就是让摄像机一直朝向一个方向(前方
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // view = glm::lookAt(cameraPos, cameraFront, cameraUp);
        ourShader.setMat4("view", view);


        // render container 画出立方体
        glBindVertexArray(VAO);
        // glDrawElements 会根据EBO中的索引值绘制出一个图形 参数分别是 图元类型 索引数量 索引的类型 索引的偏移量
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays 会从当前绑定的索引缓冲区中绘制图形 参数分别是 图元类型 起始索引 索引数量
        // 起始索引是什么？ 顶点数组中的第一个顶点的索引值是0，第二个顶点的索引值是1，以此类推。如果我们想要绘制第二个三角形，我们应该从第三个顶点开始，即索引值为2
        // glDrawArrays( GL_TRIANGLES, 0, 36);

        for( uint8_t i = 0; i < 10; i++ ) {
            glm::mat4 model = glm::mat4(1.0f);
            // translate 改变模型矩阵的位置
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if( i % 2 == 0 ) {
                angle = (float)glfwGetTime() * 25.0f;
            }
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	// 摄像机移动
	float cameraSpeed = static_cast<float>(2.5f * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		// cameraFront.z < 0; 按下W时摄像机向前移动( Z轴的值不断减小 越来越接近原点 )
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		// normalize 函数会将任何向量转换为单位向量 保持速度为匀速 否则在斜角移动时速度会变快
		// glm::cross 函数会返回两个向量的叉乘结果 得到右向量 ( 摄像机视角 X 摄像机垂直方向轴即y轴 得到 右向量 )
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    // 练习1答案 每次更改使camera的y轴坐标为0 则实现了FPS摄像机( 只能在XZ平面移动 )
    cameraPos.y = 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    // 修改摄像机的朝向
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}