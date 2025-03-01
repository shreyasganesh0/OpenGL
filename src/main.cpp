#include "glad.c"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height){

    glViewport(0, 0, 800, 600);
}

void processInput(GLFWwindow *window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "TestWindow", NULL, NULL);
    if (window == NULL){

        printf("Failed to create GLFW Window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    
    float vertices[] = { 1.0f, 1.0f, 0.0f,  
                        -1.0f, -0.4f, 0.4f,
                        -0.3f, 0.7f, 0.43f
                        };

    unsigned int VBO;

    glGenBuffers(1, &VBO);
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //vertex shader attrs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // vertex shader
    const char *vertex_shader_code = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    unsigned int vertex_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);

    glCompileShader(vertex_shader);

    int success;

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        printf("Failed to compile shader\n");
    }

    //fragment shader
    const char *fragment_shader_code = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); 

    glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);

    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        printf("Failed to compile fragment shader \n");
    }

    //shader program
    unsigned int shader_program;

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);


    glGetShaderiv(shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        printf("Failed to link shader program\n");
    }




    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.3f, 0.4f, 0.2f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);


        glBindVertexArray(VAO);
        glUseProgram(shader_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return 0;

}

