#include "Mesh.h"

Mesh::Mesh(void) {
	for (int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
	}

	glGenVertexArrays(1, &arrayObject);
	
	numVertices = 0;
	vertices = NULL;
	colours = NULL;
	type = GL_TRIANGLES;

	texture = 0;
	textureCoords = NULL;

	indices = NULL;
	numIndices = 0;

	normals = NULL;

	tangents = NULL;
	bumpTexture = 0;

	memory = 0;
	
}

Mesh ::~Mesh(void) {
	glDeleteVertexArrays(1, &arrayObject);
	glDeleteBuffers(MAX_BUFFER, bufferObject);
	delete[] vertices;
	delete[] colours;

	glDeleteTextures(1, &texture);
	delete[]textureCoords;
	
	delete[] indices;

	delete[]normals;

	delete[] tangents;
	glDeleteTextures(1, &bumpTexture); // Just like the texture map ...


}

Mesh * Mesh::GenerateTriangle() {
	Mesh * m = new Mesh();
	m -> numVertices = 3;
	
	m -> vertices = new Vector3[m -> numVertices];
	m -> vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
	m -> vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
	m -> vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);


	m -> textureCoords = new Vector2[m -> numVertices];
	m -> textureCoords[0] = Vector2(0.5f, 0.0f);
	m -> textureCoords[1] = Vector2(1.0f, 1.0f);
	m -> textureCoords[2] = Vector2(0.0f, 1.0f);

	
	m -> colours = new Vector4[m -> numVertices];
	m -> colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m -> colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m -> colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	

	for (int i = 0; i < m->numVertices; i++)
	{
		m->memory += sizeof(Vector3) + sizeof(Vector2) + sizeof(Vector4);
	}

	m -> BufferData();
	return m;
	
}

Mesh * Mesh::GenerateQuad() {
	Mesh * m = new Mesh();
	
	m -> numVertices = 4;
	m -> type = GL_TRIANGLE_STRIP;
	
	m -> vertices = new Vector3[m -> numVertices];
	m -> textureCoords = new Vector2[m -> numVertices];
	m -> colours = new Vector4[m -> numVertices];
	m -> normals = new Vector3[m -> numVertices];
	m -> tangents = new Vector3[m -> numVertices];
	
	m -> vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
	m -> vertices[1] = Vector3(-1.0f, 1.0f, 0.0f);
	m -> vertices[2] = Vector3(1.0f, -1.0f, 0.0f);
	m -> vertices[3] = Vector3(1.0f, 1.0f, 0.0f);
	
	m -> textureCoords[0] = Vector2(0.0f, 1.0f);
	m -> textureCoords[1] = Vector2(0.0f, 0.0f);
	m -> textureCoords[2] = Vector2(1.0f, 1.0f);
	m -> textureCoords[3] = Vector2(1.0f, 0.0f);
	
	for (int i = 0; i < 4; ++i) {
		m -> colours[i] = Vector4(1.0f, 1.0f, 1.0f, 0.5f);
		m -> normals[i] = Vector3(0.0f, 0.0f, -1.0f);
		m -> tangents[i] = Vector3(1.0f, 0.0f, 0.0f);
		
	}

	for (int i = 0; i < m->numVertices; i++)
	{
		m->memory += sizeof(Vector3)+sizeof(Vector2)+sizeof(Vector4)+sizeof(Vector3)+sizeof(Vector3);
	}

	cout << "SIZEOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOF Quad" << m->GetMemory() << endl;
	
	m -> BufferData();
	
	return m;
	
}


Mesh * Mesh::GenerateWood()
{
	Mesh * m = new Mesh();
	m->numVertices = 90;
	m->type = GL_TRIANGLES;

	m->vertices = new Vector3[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];
	m->colours = new Vector4[m->numVertices];
	m->normals = new Vector3[m->numVertices];
	m->tangents = new Vector3[m->numVertices];

	for (int i = 0; i < 90; i += 3)
	{
		m->textureCoords[i] = Vector2(0.5f, 0.0f);
		m->textureCoords[i + 1] = Vector2(1.0f, 1.0f);
		m->textureCoords[i + 2] = Vector2(0.0f, 1.0f);
	}

	for (int i = 0; i < 90; ++i) {
		m->colours[i] = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		m->normals[i] = Vector3(0.0f, 0.0f, -1.0f);
		m->tangents[i] = Vector3(1.0f, 0.0f, 0.0f);

	}

	for (int i = 0; i < m->numVertices; i++)
	{
		m->memory += sizeof(Vector3)+sizeof(Vector2)+sizeof(Vector4)+sizeof(Vector3)+sizeof(Vector3);
	}

	cout << "SIZEOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOF Wood" << m->GetMemory() << endl;


	//Sides
	m->vertices[0] = Vector3(1.0f, 0.0f, 0.0f);
	m->vertices[1] = Vector3(2.0f, 0.0f, 0.0f);
	m->vertices[2] = Vector3(2.0f, 1.0f, 0.0f);
	m->vertices[3] = Vector3(1.0f, 0.0f, 0.0f);
	m->vertices[4] = Vector3(2.0f, 1.0f, 0.0f);
	m->vertices[5] = Vector3(1.0f, 1.0f, 0.0f);

	m->vertices[6] = Vector3(2.0f, 0.0f, 0.0f);
	m->vertices[7] = Vector3(3.0f, 0.0f, -1.0f);
	m->vertices[8] = Vector3(3.0f, 1.0f, -1.0f);
	m->vertices[9] = Vector3(2.0f, 0.0f, 0.0f);
	m->vertices[10] = Vector3(3.0f, 1.0f, -1.0f);
	m->vertices[11] = Vector3(2.0f, 1.0f, 0.0f);

	m->vertices[12] = Vector3(3.0f, 0.0f, -1.0f);
	m->vertices[13] = Vector3(3.0f, 0.0f, -2.0f);
	m->vertices[14] = Vector3(3.0f, 1.0f, -2.0f);
	m->vertices[15] = Vector3(3.0f, 0.0f, -1.0f);
	m->vertices[16] = Vector3(3.0f, 1.0f, -2.0f);
	m->vertices[17] = Vector3(3.0f, 1.0f, -1.0f);

	m->vertices[18] = Vector3(3.0f, 0.0f, -2.0f);
	m->vertices[19] = Vector3(2.0f, 0.0f, -3.0f);
	m->vertices[20] = Vector3(2.0f, 1.0f, -3.0f);
	m->vertices[21] = Vector3(3.0f, 0.0f, -2.0f);
	m->vertices[22] = Vector3(2.0f, 1.0f, -3.0f);
	m->vertices[23] = Vector3(3.0f, 1.0f, -2.0f);

	m->vertices[24] = Vector3(2.0f, 0.0f, -3.0f);
	m->vertices[25] = Vector3(1.0f, 0.0f, -3.0f);
	m->vertices[26] = Vector3(1.0f, 1.0f, -3.0f);
	m->vertices[27] = Vector3(2.0f, 0.0f, -3.0f);
	m->vertices[28] = Vector3(1.0f, 1.0f, -3.0f);
	m->vertices[29] = Vector3(2.0f, 1.0f, -3.0f);

	m->vertices[30] = Vector3(1.0f, 0.0f, -3.0f);
	m->vertices[31] = Vector3(0.0f, 0.0f, -2.0f);
	m->vertices[32] = Vector3(0.0f, 1.0f, -2.0f);
	m->vertices[33] = Vector3(1.0f, 0.0f, -3.0f);
	m->vertices[34] = Vector3(0.0f, 1.0f, -2.0f);
	m->vertices[35] = Vector3(1.0f, 1.0f, -3.0f);

	m->vertices[36] = Vector3(0.0f, 0.0f, -2.0f);
	m->vertices[37] = Vector3(0.0f, 0.0f, -1.0f);
	m->vertices[38] = Vector3(0.0f, 1.0f, -1.0f);
	m->vertices[39] = Vector3(0.0f, 0.0f, -2.0f);
	m->vertices[40] = Vector3(0.0f, 1.0f, -1.0f);
	m->vertices[41] = Vector3(0.0f, 1.0f, -2.0f);

	m->vertices[42] = Vector3(0.0f, 0.0f, -1.0f);
	m->vertices[43] = Vector3(1.0f, 0.0f, -0.0f);
	m->vertices[44] = Vector3(1.0f, 1.0f, 0.0f);
	m->vertices[45] = Vector3(0.0f, 0.0f, -1.0f);
	m->vertices[46] = Vector3(1.0f, 1.0f, 0.0f);
	m->vertices[47] = Vector3(0.0f, 1.0f, -1.0f);

	//Top
	m->vertices[48] = Vector3(1.0f, 1.1f, -1.0f);
	m->vertices[49] = Vector3(2.0f, 1.1f, -1.0f);
	m->vertices[50] = Vector3(2.0f, 1.1f, -2.0f);
	m->vertices[51] = Vector3(1.0f, 1.1f, -1.0f);
	m->vertices[52] = Vector3(2.0f, 1.1f, -2.0f);
	m->vertices[53] = Vector3(1.0f, 1.1f, -2.0f);

	m->vertices[54] = Vector3(1.0f, 1.0f, 0.0f);
	m->vertices[55] = Vector3(2.0f, 1.0f, 0.0f);
	m->vertices[56] = Vector3(2.0f, 1.1f, -1.0f);
	m->vertices[57] = Vector3(1.0f, 1.0f, 0.0f);
	m->vertices[58] = Vector3(2.0f, 1.1f, -1.0f);
	m->vertices[59] = Vector3(1.0f, 1.1f, -1.0f);

	m->vertices[60] = Vector3(2.0f, 1.0f, 0.0f);
	m->vertices[61] = Vector3(3.0f, 1.0f, -1.0f);
	m->vertices[62] = Vector3(2.0f, 1.1f, -1.0f);

	m->vertices[63] = Vector3(3.0f, 1.0f, -1.0f);
	m->vertices[64] = Vector3(3.0f, 1.0f, -2.0f);
	m->vertices[65] = Vector3(2.0f, 1.1f, -2.0f);
	m->vertices[66] = Vector3(3.0f, 1.0f, -1.0f);
	m->vertices[67] = Vector3(2.0f, 1.1f, -2.0f);
	m->vertices[68] = Vector3(2.0f, 1.1f, -1.0f);

	m->vertices[69] = Vector3(3.0f, 1.0f, -2.0f);
	m->vertices[70] = Vector3(2.0f, 1.0f, -3.0f);
	m->vertices[71] = Vector3(2.0f, 1.1f, -2.0f);

	m->vertices[72] = Vector3(2.0f, 1.0f, -3.0f);
	m->vertices[73] = Vector3(1.0f, 1.0f, -3.0f);
	m->vertices[74] = Vector3(1.0f, 1.1f, -2.0f);
	m->vertices[75] = Vector3(2.0f, 1.0f, -3.0f);
	m->vertices[76] = Vector3(1.0f, 1.1f, -2.0f);
	m->vertices[77] = Vector3(2.0f, 1.1f, -2.0f);

	m->vertices[78] = Vector3(1.0f, 1.0f, -3.0f);
	m->vertices[79] = Vector3(0.0f, 1.0f, -2.0f);
	m->vertices[80] = Vector3(1.0f, 1.1f, -2.0f);

	m->vertices[81] = Vector3(0.0f, 1.0f, -2.0f);
	m->vertices[82] = Vector3(0.0f, 1.0f, -1.0f);
	m->vertices[83] = Vector3(1.0f, 1.1f, -1.0f);
	m->vertices[84] = Vector3(0.0f, 1.0f, -2.0f);
	m->vertices[85] = Vector3(1.0f, 1.1f, -1.0f);
	m->vertices[86] = Vector3(1.0f, 1.1f, -2.0f);

	m->vertices[87] = Vector3(0.0f, 1.0f, -1.0f);
	m->vertices[88] = Vector3(1.0f, 1.0f, 0.0f);
	m->vertices[89] = Vector3(1.0f, 1.1f, -1.0f);

	m->GenerateNormals();
	m->GenerateTangents();

	m->BufferData();
	return m;
}

void Mesh::GenerateNormals() {
	if (!normals) {
		normals = new Vector3[numVertices];
	}
	for (GLuint i = 0; i < numVertices; ++i){
		normals[i] = Vector3();
	}
	if (indices) { // Generate per - vertex normals
		for (GLuint i = 0; i < numIndices; i += 3){
			unsigned int a = indices[i];
			unsigned int b = indices[i + 1];
			unsigned int c = indices[i + 2];
			
			Vector3 normal = Vector3::Cross(
				(vertices[b] - vertices[a]), (vertices[c] - vertices[a]));
	
			normals[a] += normal;
			normals[b] += normal;
			normals[c] += normal;
			
		}
		
	}
	else { // It ’s just a list of triangles , so generate face normals
		for (GLuint i = 0; i < numVertices; i += 3){
			Vector3 & a = vertices[i];
			Vector3 & b = vertices[i + 1];
			Vector3 & c = vertices[i + 2];
			
			Vector3 normal = Vector3::Cross(b - a, c - a);
			
			normals[i] = normal;
			normals[i + 1] = normal;
			normals[i + 2] = normal;	
		}
	}
	
	for (GLuint i = 0; i < numVertices; ++i){
		normals[i].Normalise();
	}
}

void Mesh::GenerateTangents() {
	if (!tangents) {
		tangents = new Vector3[numVertices];
	}
	for (GLuint i = 0; i < numVertices; ++i){
		tangents[i] = Vector3();
	}
	
	if (indices) {
		for (GLuint i = 0; i < numIndices; i += 3){
			int a = indices[i];
			int b = indices[i + 1];
			int c = indices[i + 2];
			
			Vector3 tangent = GenerateTangent(vertices[a], vertices[b],
				vertices[c], textureCoords[a],
				textureCoords[b], textureCoords[c]);
			
			tangents[a] += tangent;
			tangents[b] += tangent;
			tangents[c] += tangent;
		}
		
	}
	else {
		for (GLuint i = 0; i < numVertices; i += 3){
			Vector3 tangent = GenerateTangent(vertices[i], vertices[i + 1],
				vertices[i + 2], textureCoords[i],
				textureCoords[i + 1], textureCoords[i + 2]);
			
			tangents[i] += tangent;
			tangents[i + 1] += tangent;
			tangents[i + 2] += tangent;
		}
		
	}
	for (GLuint i = 0; i < numVertices; ++i){
		tangents[i].Normalise();
	}
}

Vector3 Mesh::GenerateTangent(const Vector3 &a, const Vector3 &b,
	const Vector3 &c, const Vector2 & ta,
	const Vector2 & tb, const Vector2 & tc) 
{
	Vector2 coord1 = tb - ta;
	Vector2 coord2 = tc - ta;
	
	Vector3 vertex1 = b - a;
	Vector3 vertex2 = c - a;
	
	Vector3 axis = Vector3(vertex1 * coord2.y - vertex2 * coord1.y);
	
	float factor = 1.0f / (coord1.x * coord2.y - coord2.x * coord1.y);
	
	return axis * factor;
}

void Mesh::BufferData() {
	glBindVertexArray(arrayObject);
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (Vector3),
		vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	if (textureCoords) { // This bit is new !
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (Vector2),
			textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	if (colours) {
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof (Vector4),
			colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	if (indices) {
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
			bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof (GLuint),
			indices, GL_STATIC_DRAW);
	}

	if (normals) {
		glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3),
			normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	if (tangents) {
		glGenBuffers(1, &bufferObject[TANGENT_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TANGENT_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vector3),
			tangents, GL_STATIC_DRAW);
		glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TANGENT_BUFFER);
	}


	glBindVertexArray(0);
}


void Mesh::Draw() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1); // New !!!
	glBindTexture(GL_TEXTURE_2D, bumpTexture); // New !!!
	
	glBindVertexArray(arrayObject);
	if (bufferObject[INDEX_BUFFER]) {// Added by the index buffers tut ...
		glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(type, 0, numVertices);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}
