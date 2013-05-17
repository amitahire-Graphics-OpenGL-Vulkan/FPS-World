#include <GL\glew.h>
#include <GL\glfw.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Box.h"
#include "GPUProgram.h"
#include "Camera.h"

Box::Box()
	: shader(nullptr)
	, vertexArrayID(0)
{
}

Box::~Box()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	delete shader;
}

void Box::prepareMaterial(Camera* camera)
{
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	shader = new GPUProgram;

	shader->loadFragmentShaderFromFile("box.frag");
	shader->loadVertexShaderFromFile("box.vert");

	shader->link();

	static const GLfloat vertexBufferData[] = {
	
		// bottom
        -1.0f,-1.0f,-1.0f,  // 0.0f, 0.0f,
         1.0f,-1.0f,-1.0f,  // 1.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,  // 0.0f, 1.0f,
         1.0f,-1.0f,-1.0f,  // 1.0f, 0.0f,
         1.0f,-1.0f, 1.0f,  // 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,  // 0.0f, 1.0f,

        // top
        -1.0f, 1.0f,-1.0f, //  0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, //  0.0f, 1.0f,
         1.0f, 1.0f,-1.0f, //  1.0f, 0.0f,
         1.0f, 1.0f,-1.0f,  // 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,//   0.0f, 1.0f,
         1.0f, 1.0f, 1.0f,  // 1.0f, 1.0f,

        // front
        -1.0f,-1.0f, 1.0f,  // 1.0f, 0.0f,
         1.0f,-1.0f, 1.0f,  // 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f,  // 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,   //0.0f, 0.0f,
         1.0f, 1.0f, 1.0f,   //0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   //1.0f, 1.0f,

        // back
        -1.0f,-1.0f,-1.0f,  // 0.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,  // 0.0f, 1.0f,
         1.0f,-1.0f,-1.0f,  // 1.0f, 0.0f,
         1.0f,-1.0f,-1.0f, //  1.0f, 0.0f,
        -1.0f, 1.0f,-1.0f,  // 0.0f, 1.0f,
         1.0f, 1.0f,-1.0f,   //1.0f, 1.0f,

        // left
        -1.0f,-1.0f, 1.0f,   //0.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,  // 1.0f, 0.0f,
        -1.0f,-1.0f,-1.0f,  // 0.0f, 0.0f,
        -1.0f,-1.0f, 1.0f,  // 0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,   //1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,   //1.0f, 0.0f,

        // right
         1.0f,-1.0f, 1.0f,   //1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,   //1.0f, 0.0f,
         1.0f, 1.0f,-1.0f,   //0.0f, 0.0f,
         1.0f,-1.0f, 1.0f,   //1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,  // 0.0f, 0.0f,
         1.0f, 1.0f, 1.0f,   //0.0f, 1.0f
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	// transform the object to different position in world space
	transform = glm::translate(glm::mat4(), glm::vec3(-1,0,0)) * glm::scale(glm::mat4(), glm::vec3(0.30, 0.30, 0.30));
}

void Box::drawBox(Camera* camera)
{
	shader->use();

	shader->setUniform("camera", camera->matrix());
	shader->setUniform("model", transform);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//shader->stopUsing();
}