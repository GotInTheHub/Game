#include "openGL_error.h"
#include "logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
    void OpenGLError::clear()
    {
        while (glGetError() != GL_NO_ERROR) {}
    }

    bool OpenGLError::check(const std::string& context)
    {
        GLenum err = glGetError();

        if (err != GL_NO_ERROR) {
            std::string errorMsg = "OpenGL Error";

            if (!context.empty()) {
                errorMsg += " in " + context;
            }

            errorMsg += ": " + std::to_string(err);

            switch (err) {
            case GL_INVALID_ENUM: errorMsg += " (GL_INVALID_ENUM)"; break;
            case GL_INVALID_VALUE: errorMsg += " (GL_INVALID_VALUE)"; break;
            case GL_INVALID_OPERATION: errorMsg += " (GL_INVALID_OPERATION)"; break;
            case GL_OUT_OF_MEMORY: errorMsg += " (GL_OUT_OF_MEMORY)"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: errorMsg += " (GL_INVALID_FRAMEBUFFER_OPERATION)"; break;
            }

            Logger::error(LogCategory::RENDER, errorMsg.c_str());
            return true;
        }

        return false;
    }

    bool OpenGLError::checkThrottled(const std::string& context, float throttleSeconds)
    {
        GLenum err = glGetError();

        if (err != GL_NO_ERROR) {
            static float lastLogTime = 0.0f;
            float currentTime = (float)glfwGetTime();

            if (currentTime - lastLogTime > throttleSeconds) {
                std::string errorMsg = "OpenGL Error";

                if (!context.empty()) {
                    errorMsg += " in " + context;
                }

                errorMsg += ": " + std::to_string(err);

                switch (err) {
                case GL_INVALID_ENUM: errorMsg += " (GL_INVALID_ENUM)"; break;
                case GL_INVALID_VALUE: errorMsg += " (GL_INVALID_VALUE)"; break;
                case GL_INVALID_OPERATION: errorMsg += " (GL_INVALID_OPERATION)"; break;
                case GL_OUT_OF_MEMORY: errorMsg += " (GL_OUT_OF_MEMORY)"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: errorMsg += " (GL_INVALID_FRAMEBUFFER_OPERATION)"; break;
                }

                Logger::error(LogCategory::RENDER, errorMsg.c_str());
                lastLogTime = currentTime;
            }

            return true;
        }

        return false;
    }
}