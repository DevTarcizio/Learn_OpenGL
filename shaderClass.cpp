#include "shaderClass.hpp"
#include "VBO.hpp"

// Ler o conteudo dos arquivos de shader
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		return contents;
	}
	throw (errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Converte o conteudo do shader de string para string C-style
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Cria o vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Verificação do shader
	int successVertex;
	char infologVertex[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
	if (!successVertex) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infologVertex);
		std::cout << "Erro na compilacao: " << infologVertex << '\n';
	}

	// Cria o fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Verificação do shader
	int successFragment;
	char infologFragment[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
	if (!successFragment) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infologFragment);
		std::cout << "Erro na compilacao: " << infologFragment << '\n';
	}

	// Cria e configura o shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}