#include <cstddef>
#include "Sprite.h"
#include "Vertex.h"
#include "resourceManager.h"

namespace PlotterEngine {

	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (_vboID != 0)//free buffer
			glDeleteBuffers(1, &_vboID);
	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = resourceManager::getTexture(texturePath);

		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		Vertex vertex[6];
		//Triangle 1

		vertex[0].setPosition(x + width, y + height);
		vertex[0].setUV(1.0f, 1.0f);

		vertex[1].setPosition(x, y + height);
		vertex[1].setUV(0.0f, 1.0f);

		vertex[2].setPosition(x, y);
		vertex[2].setUV(0.0f, 0.0f);

		//Triangle 2
		vertex[3].setPosition(x, y);
		vertex[3].setUV(0.0f, 0.0f);

		vertex[4].setPosition(x + width, y);
		vertex[4].setUV(1.0f, 0.0f);

		vertex[5].setPosition(x + width, y + height);
		vertex[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++) {
			vertex[i].setColor(155, 123, 201, 199);
		}

		vertex[4].setColor(12, 0, 255, 255);
		vertex[4].setColor(223, 155, 232, 255);



		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);// unbind
	}
	void Sprite::draw()
	{

		glBindTexture(GL_TEXTURE_2D, _texture.id);
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glEnableVertexAttribArray(0);//only position!


		//pos att pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // 2 -> x and y// 3 x and y and z

		//color
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);


		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);// unbind
	}

}