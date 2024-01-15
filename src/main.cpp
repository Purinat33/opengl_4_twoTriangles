#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(1080, 720, "Triangle", NULL, NULL);
    if(window == NULL){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "GL Error\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,1080,720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Triangle 1
    float vertices[]={
        // x , y, z
        -0.5f, 0.f, 0.f,
        0.f, 0.5f, 0.f,
        0.5f, 0.f, 0.f
    };

    unsigned int VAO[2];
    glGenVertexArrays(sizeof(VAO)/sizeof(VAO[0]), VAO);

    unsigned int buffer[2];
    glGenBuffers(sizeof(buffer) / sizeof(buffer[0]), buffer);
    
    // Triangle 1
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*) 0);
    glEnableVertexAttribArray(0);


    // Triangle 2
    float vert[] = {
        // x , y, z
        0.3f, -1.f, 
        0.f, -0.3f,
        -0.3f, -1.f
        };
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Shader
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n" // layout (location = 0) means index 0 from glVertexAttribPointer() and copied it into aPos variable
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos, 1.0f);\n"
                                     "}\0";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);   
    glCompileShader(vertexShader);

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.6f, 0.2f, 1.0f);\n"
                                       "}\0";

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    while(!glfwWindowShouldClose(window)){

        processInput(window);
        glClearColor(0.2f, 0.7f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);

        // We can just bind different VAO instead of binding the VBO buffer to draw a different thing
        if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
            glBindVertexArray(VAO[0]);
        }
        else{
            glBindVertexArray(VAO[1]);
        }
        
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
