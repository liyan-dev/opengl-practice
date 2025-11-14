#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"   // 只需要 include；实现放在 stb_impl.cpp 里
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// 摄像机朝向欧拉角
float yaw = -90.0f;   // 初始指向 -Z（很关键）
float pitch = 0.0f;

// 鼠标状态
bool  firstMouse = true;
float lastX = 400.0f;   // 会在创建窗口后改成实际中心
float lastY = 300.0f;

// 视野(zoom)
float fov = 45.0f;


// 窗口尺寸变化时更新视口
static void framebuffer_size_callback(GLFWwindow*, int w, int h) {
    glViewport(0, 0, w, h);

}
void processInput(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;

    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraRight * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += cameraRight * cameraSpeed;

    // 可选：上下移动
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraUp * cameraSpeed;
}

void mouse_callback(GLFWwindow* /*window*/, double xpos, double ypos)
{
    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;  // y 反向（屏幕坐标向下为正）
    lastX = (float)xpos;
    lastY = (float)ypos;

    const float sensitivity = 0.1f; // 鼠标灵敏度
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // 限制俯仰，避免视线翻转
    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // 由 yaw/pitch 计算前向向量
    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(dir);
}

void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)  fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}


int main() {
    // ---- 初始化 GLFW / 创建窗口 ----
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Easy Materials", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // ---- 初始化 GLAD ----
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        glfwTerminate(); return -1;
    }

    glEnable(GL_DEPTH_TEST);

    float cubeVertices[] = {
        // 位置              // 法线
        -0.5f,-0.5f,-0.5f,   0.0f,  0.0f,-1.0f,
         0.5f,-0.5f,-0.5f,   0.0f,  0.0f,-1.0f,
         0.5f, 0.5f,-0.5f,   0.0f,  0.0f,-1.0f,
         0.5f, 0.5f,-0.5f,   0.0f,  0.0f,-1.0f,
        -0.5f, 0.5f,-0.5f,   0.0f,  0.0f,-1.0f,
        -0.5f,-0.5f,-0.5f,   0.0f,  0.0f,-1.0f,

        -0.5f,-0.5f, 0.5f,   0.0f,  0.0f, 1.0f,
         0.5f,-0.5f, 0.5f,   0.0f,  0.0f, 1.0f,
         0.5f, 0.5f, 0.5f,   0.0f,  0.0f, 1.0f,
         0.5f, 0.5f, 0.5f,   0.0f,  0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,   0.0f,  0.0f, 1.0f,
        -0.5f,-0.5f, 0.5f,   0.0f,  0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f,  -1.0f,  0.0f, 0.0f,
        -0.5f, 0.5f,-0.5f,  -1.0f,  0.0f, 0.0f,
        -0.5f,-0.5f,-0.5f,  -1.0f,  0.0f, 0.0f,
        -0.5f,-0.5f,-0.5f,  -1.0f,  0.0f, 0.0f,
        -0.5f,-0.5f, 0.5f,  -1.0f,  0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,  -1.0f,  0.0f, 0.0f,

         0.5f, 0.5f, 0.5f,   1.0f,  0.0f, 0.0f,
         0.5f, 0.5f,-0.5f,   1.0f,  0.0f, 0.0f,
         0.5f,-0.5f,-0.5f,   1.0f,  0.0f, 0.0f,
         0.5f,-0.5f,-0.5f,   1.0f,  0.0f, 0.0f,
         0.5f,-0.5f, 0.5f,   1.0f,  0.0f, 0.0f,
         0.5f, 0.5f, 0.5f,   1.0f,  0.0f, 0.0f,

        -0.5f,-0.5f,-0.5f,   0.0f, -1.0f, 0.0f,
         0.5f,-0.5f,-0.5f,   0.0f, -1.0f, 0.0f,
         0.5f,-0.5f, 0.5f,   0.0f, -1.0f, 0.0f,
         0.5f,-0.5f, 0.5f,   0.0f, -1.0f, 0.0f,
        -0.5f,-0.5f, 0.5f,   0.0f, -1.0f, 0.0f,
        -0.5f,-0.5f,-0.5f,   0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f,-0.5f,   0.0f,  1.0f, 0.0f,
         0.5f, 0.5f,-0.5f,   0.0f,  1.0f, 0.0f,
         0.5f, 0.5f, 0.5f,   0.0f,  1.0f, 0.0f,
         0.5f, 0.5f, 0.5f,   0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,   0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f,-0.5f,   0.0f,  1.0f, 0.0f
    };

    unsigned int VBO, cubeVAO, lightVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // aPos -> location=0, 3 floats, stride=6*sizeof(float), offset=0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // aNormal -> location=1, 3 floats, stride=6*sizeof(float), offset=3*sizeof(float)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 绑定 lightVAO：仍然复用同一 VBO，但只用位置属性（注意 stride 改为 6*float）
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);     // 光源位置

    GLuint lightingShaderProg;
    GLuint lightCubeShaderProg;


    // ====== 物体着色器 ======
    const char* lightingVertexSrc = R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;   // 世界空间片元位置
out vec3 Normal;    // 世界空间法线

void main(){
    vec4 worldPos = model * vec4(aPos, 1.0);
    FragPos = worldPos.xyz;

    // 法线矩阵：transpose(inverse(mat3(model)))
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * worldPos;
}


)";

    const char* lightingFragSrc = R"(
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

struct Material {
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 viewPos; // 相机位置(世界空间)

void main(){
    // 环境光
    vec3 ambient = light.ambient * material.ambient;

    // 漫反射
    vec3 N = normalize(Normal);
    vec3 L = normalize(light.position - FragPos);
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // 高光
    vec3 V = normalize(viewPos - FragPos);
    vec3 R = reflect(-L, N);
    float spec = pow(max(dot(V, R), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 color = ambient + diffuse + specular;
    FragColor = vec4(color, 1.0);
}


)";

    auto makeShader = [](GLenum type, const char* src) {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        GLint ok; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char log[512];
            glGetShaderInfoLog(s, 512, nullptr, log);
            std::cerr << "Shader compile error:\n" << log << std::endl;
        }
        return s;
        };

    GLuint vs = makeShader(GL_VERTEX_SHADER, lightingVertexSrc);
    GLuint fs = makeShader(GL_FRAGMENT_SHADER, lightingFragSrc);
    lightingShaderProg = glCreateProgram();
    glAttachShader(lightingShaderProg, vs);
    glAttachShader(lightingShaderProg, fs);
    glLinkProgram(lightingShaderProg);
    glDeleteShader(vs);
    glDeleteShader(fs);

    // ====== 光源立方体着色器 ======
    const char* lightVertexSrc = R"(
#version 330 core
layout(location=0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

)";
    const char* lightFragSrc = R"(
#version 330 core
out vec4 FragColor;
void main(){ FragColor = vec4(1.0); }

)";
    vs = makeShader(GL_VERTEX_SHADER, lightVertexSrc);
    fs = makeShader(GL_FRAGMENT_SHADER, lightFragSrc);
    lightCubeShaderProg = glCreateProgram();
    glAttachShader(lightCubeShaderProg, vs);
    glAttachShader(lightCubeShaderProg, fs);
    glLinkProgram(lightCubeShaderProg);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(lightingShaderProg);
    // 光源强度（可调）
    glUniform3f(glGetUniformLocation(lightingShaderProg, "light.ambient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(lightingShaderProg, "light.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(lightingShaderProg, "light.specular"), 1.0f, 1.0f, 1.0f);

    // 物体材质（可换成不同材料）
    glUniform3f(glGetUniformLocation(lightingShaderProg, "material.ambient"), 1.0f, 0.5f, 0.31f);
    glUniform3f(glGetUniformLocation(lightingShaderProg, "material.diffuse"), 1.0f, 0.5f, 0.31f);
    glUniform3f(glGetUniformLocation(lightingShaderProg, "material.specular"), 0.5f, 0.5f, 0.5f);
    glUniform1f(glGetUniformLocation(lightingShaderProg, "material.shininess"), 32.0f);


    while (!glfwWindowShouldClose(window))
    {
        // 更新时间
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 摄像机矩阵
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        int fbw, fbh; glfwGetFramebufferSize(window, &fbw, &fbh);
        float aspect = (fbh == 0) ? 1.333f : (float)fbw / (float)fbh;
        glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);

        // ============== 绘制主立方体（受光照） ==============
        glUseProgram(lightingShaderProg);

        // 仅更新会变的 uniform
        glUniform3f(glGetUniformLocation(lightingShaderProg, "viewPos"),
            cameraPos.x, cameraPos.y, cameraPos.z);
        glUniform3f(glGetUniformLocation(lightingShaderProg, "light.position"),
            lightPos.x, lightPos.y, lightPos.z);

        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(lightingShaderProg, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(lightingShaderProg, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightingShaderProg, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ============== 绘制光源立方体（可视化光源） ==============
        glUseProgram(lightCubeShaderProg);
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShaderProg, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShaderProg, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightCubeShaderProg, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }





    // ---- 资源清理 ----
    glDeleteVertexArrays(1, &cubeVAO); 
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(lightingShaderProg);
    glDeleteProgram(lightCubeShaderProg);
    glfwTerminate();
  
}
