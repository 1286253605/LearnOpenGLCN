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

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
#define RADIUS ( 70.f )

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // ����Ϊ����ģʽ
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
	// �����ڵ�����������Ϊ��ǰ�̵߳���������
    glfwMakeContextCurrent(window);
	// ���ô��ڴ�С�ı�ʱ�Ļص�����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ʹ����Ȳ���
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vert", "fragmentShader.frag");
er(s)) and configure vertex attributes
    // ---------------------------
    // set up vertex data (and buff---------------------------------------
	// ֻ�涨���ĸ������ɫ���������� ����OpenGL�����Բ�ֵ������ͼ����
    // float vertices[] = {
    //     // positions          // colors           // texture coords
    //      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    //      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    // };

    // �����嶥��  ��������ɫ ֻ�ж������Ժ������������� ����3Dͼ�����
    //    float vertices[] = {
    //     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    //      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    //      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    //      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    //      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    //      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    //     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    // };
// �����嶥�㣬�����������ꡢ��ɫ����������
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
    // glVertexAttribPointer ��һ������ָ�������������ݵ�OpenGL�����������������Եĸ�ʽ������Դ�뵱ǰ�Ķ��㻺��������������
    // texture coord attribute
	// �������Ե�����ֵΪ2 �������ԵĴ�СΪ2(������������) �������Ե�����ΪGL_FLOAT �������Ե��Ƿ��׼��ΪGL_FALSE �������ԵĲ���Ϊ8*sizeof(float) �������Ե�ƫ����Ϊ6*sizeof(float)
	// ����˵ �������Ե�������VBO�е����з�ʽ�� λ��(3��float) ��ɫ(3��float) ��������(2��float) �������������ƫ������6*sizeof(float) 
	// �������� �ڵ�һ���ڴ��� λ��(3��float) ��ɫ(3��float) ��������(2��float) �������������ƫ������6*sizeof(float)
    // ����ֵΪ2������ Shader�� ʹ��layout( location=2 ) ���εı���
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // ʹ������ֵΪ2 �ı���
    glEnableVertexAttribArray(2);



    // ��תһ��ͼƬ
    // stbi_set_flip_vertically_on_load(true);


    // load and create a texture 
    // -------------------------
    unsigned int texture1;
	// ������VAO VBO EBOһ�� �����������
    glGenTextures(1, &texture1);
	// ��������� ֮�����е��������������������������
    glBindTexture(GL_TEXTURE_2D, texture1); 
	// 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// ��������ֱ��� ����Ŀ�� ��������� ������С�Ĺ����� ����Ŵ�Ĺ�����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("./container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
		// �������� ָ������Ŀ�� �����mipmap(�༶��Զ����)���� ������洢��ʲô��ɫ��ʽ(GL_RGB) ����Ŀ�� ����ĸ߶� ����ı߿���(0) �������ɫ��ʽ(ԭͼ��ʽGL_RGB) �������������(�洢ΪByte����) ���������
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// ���ɶ༶��Զ����
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
    // set the texture wrapping parameters ���������Ʒ�ʽ S���T��
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
	// glGetUniformLocation ���������Shader���ҵ���Ϊ "texture1" ��uniform������λ��
	// glUniform1i �������������Ԫ��λ��ֵ�������uniform����
    /*
    * ����������У�glUniform1i ��������ɫ����������Ϊ texture1 �� uniform ��������Ϊ 0��
    * ���ֵͨ������ָ������Ԫ���������� OpenGL �У�����Ԫ��һ�����԰�����ĳ�����
    * ���� 0 ��Ӧ�� GL_TEXTURE0������ 1 ��Ӧ�� GL_TEXTURE1���������ơ�
    */
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	// ��һ�е�Ч���������Ч����һ���� ֻ�Ƿ�װ����������
    ourShader.setInt("texture2", 1);

    // ʹ����������  ����lookAt����
    glm::mat4 view;
    view = glm::lookAt( glm::vec3(0.0f, 0.0f, 3.0f),        // �����λ�� 
                        glm::vec3(0.0f, 0.0f, 0.0f),        // ����λ��
                        glm::vec3(0.0f, 1.0f, 0.0f) );      // ��������ϵ������

    // render loop
    // -----------
	// ͨ��glfwWindowShouldClose�������GLFW�Ƿ�Ҫ���˳�
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // GL_DEPTH_BUFFER_BIT ��Ȼ����� GL_COLOR_BUFFER_BIT ��ɫ������
        // ��Ȼ�����Ҳ��Ҫ��� ��Ϊÿһ֡�������һ���µĳ��� �ɵ������Ϣ�������� 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // render container
        ourShader.use();

        glm::mat4 modelMatrix = glm::mat4(1.0f);
		// ģ�;��� ��x����ת-55��
        // modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
        // ��ͼ����
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		// ͶӰ����
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		// ��Ҫ�� SCR_WIDTH �� SCR_HEIGHT ת��Ϊfloat���ͣ�������������Ľ������0
		projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(ourShader.ID, "modelMatrix");
		// ���� �ֱ��� uniform��λ�� ���ݵľ���ĸ��� ת�þ����ָ��
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		int viewLoc = glGetUniformLocation(ourShader.ID, "viewMatrix");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		int projectionLoc = glGetUniformLocation(ourShader.ID, "projectionMatrix");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // ��ת�ӽ�
        float camPosX = sin(glfwGetTime()) * RADIUS;
        float camPosZ = cos(glfwGetTime()) * RADIUS;
        glm::mat4 view;
        view = glm::lookAt( glm::vec3(camPosX, 0.0f, camPosZ),  // �����λ����ʱ��仯
                            glm::vec3(0.0f, 0.0f, 0.0f), 
                            glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("view", view);


        // render container ����������
        glBindVertexArray(VAO);
        // glDrawElements �����EBO�е�����ֵ���Ƴ�һ��ͼ�� �����ֱ��� ͼԪ���� �������� ���������� ������ƫ����
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays ��ӵ�ǰ�󶨵������������л���ͼ�� �����ֱ��� ͼԪ���� ��ʼ���� ��������
        // ��ʼ������ʲô�� ���������еĵ�һ�����������ֵ��0���ڶ������������ֵ��1���Դ����ơ����������Ҫ���Ƶڶ��������Σ�����Ӧ�ôӵ��������㿪ʼ��������ֵΪ2
        // glDrawArrays( GL_TRIANGLES, 0, 36);

        for( uint8_t i = 0; i < 10; i++ ) {
            glm::mat4 model = glm::mat4(1.0f);
            // translate �ı�ģ�;����λ��
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}