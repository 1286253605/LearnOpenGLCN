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

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vert", "fragmentShader.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
	// ֻ�涨���ĸ������ɫ���������� ����OpenGL�����Բ�ֵ������ͼ����
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // �����任����
        glm::mat4 trans(1.0f);
        // ���ž���
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        // ����һ����ת���� ��ת����z��(0.0, 0.0, 1.0) ��ת�Ƕ���90��
        trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));


        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // ���Ȳ�ѯ ��transform�� ��������ɫ���еĵ�ַ
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        // ���ݱ任������ɫ���� ͨ�� glUniform ��׺Ϊ Matrix4fv �ĺ��� 
        // �����ֱ��� uniform ������λ��ֵ 1������ĸ��� �Ƿ���Ҫת�þ����ֵ �����ֵ
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

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