#ifndef SHADER_H_
#define SHADER_H_

#include "core.h"

extern const char* vertexShaderSource;

extern const char* fragmentShaderSource;

namespace MinecraftClone
{
	struct Shader
	{
		uint32 programId;

		void bind();
		void compile();
	};
}

#endif // !SHADER_H_
