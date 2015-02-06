#include "Renderer.h"

Renderer::Renderer(Window & parent) : OGLRenderer(parent) {

	fps = 0;
	frame = 0;
	time = 0;
	wglSwapIntervalEXT(0); //Disable VSync

	camera = new Camera(0.0f, 0.0f, Vector3(
		RAW_WIDTH * HEIGHTMAP_X / 2.0f, 500, RAW_HEIGHT * HEIGHTMAP_Z));
	Tree::CreateLeaf();
	Tree::CreateBranch();

	
	quad = Mesh::GenerateQuad();
	

	light = new Light(Vector3((RAW_HEIGHT * HEIGHTMAP_X / 2.0f),
		500.0f, (RAW_HEIGHT * HEIGHTMAP_Z / 2.0f)),
		Vector4(1, 1, 1, 1), Vector4(0, 0, 1, 1), (RAW_WIDTH * HEIGHTMAP_X) );

	textShader = new Shader(SHADERDIR"TexturedVertex.glsl", 
		SHADERDIR"TexturedFragment.glsl");

	particleShader = new Shader(SHADERDIR"vertex.glsl",
		SHADERDIR"fragment.glsl",
		SHADERDIR"geometry.glsl");

	if (!textShader->LinkProgram() || !particleShader->LinkProgram()) {
		return;
	}
	//A new particle emitter!
	emitter = new ParticleEmitter();

	basicFont = new Font(SOIL_load_OGL_texture(TEXTUREDIR"tahoma.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_COMPRESS_TO_DXT), 16, 16);


	reflectShader = new Shader("../../Shaders/PerPixelVertex.glsl",
		"../../Shaders/reflectFragment.glsl");
	skyboxShader = new Shader("../../Shaders/skyboxVertex.glsl",
		"../../Shaders/skyboxFragment.glsl");
	lightShader = new Shader("../../Shaders/PerPixelVertex.glsl",
		"../../Shaders/PerPixelFragment.glsl");
	
	if (!reflectShader->LinkProgram() || !lightShader->LinkProgram() ||
		!skyboxShader->LinkProgram()) {
		return;
	}

	quad->SetTexture(SOIL_load_OGL_texture("../../Textures/water.tga",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	
	heightMap = new HeightMap(TEXTUREDIR"terrain.raw");
	heightMap->SetTexture(SOIL_load_OGL_texture(
		TEXTUREDIR"Barren Reds.JPG", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	heightMap->SetBumpMap(SOIL_load_OGL_texture(
		TEXTUREDIR"Barren RedsDOT3.jpg", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	cubeMap = SOIL_load_OGL_cubemap(
		"../../Textures/D2.png ", "../../Textures/D4.png",
		"../../Textures/D1.png ", "../../Textures/D6.png",
		"../../Textures/D5.png ", "../../Textures/D3.png",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID, 0
		);
	
	if (!cubeMap || !quad->GetTexture() || !heightMap->GetTexture() ||
		!heightMap->GetBumpMap()) {
		return;
	}

	SetTextureRepeating(quad->GetTexture(), true);
	SetTextureRepeating(heightMap->GetTexture(), true);
	SetTextureRepeating(heightMap->GetBumpMap(), true);

	init = true;
	waterRotate = 0.0f;

	root = new SceneNode();
	
	Tree * myTree = new Tree(1750, 50, 1700, 1000);
	
	
	root->AddChild(myTree);
	

	memory = myTree->GetMemory();

	projMatrix = Matrix4::Perspective(1.0f, 15000.0f,
		(float)width / (float)height, 45.0f);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	//glBlendFunc(GL_ONE, GL_ZERO);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	
}

Renderer ::~Renderer(void) {

	delete particleShader;
	delete skyboxShader;
	delete lightShader;
	delete heightMap;
	delete emitter;
	delete camera;
	delete light;
	delete root;
	
	Tree::DeleteBranch();
	Tree::DeleteLeaf();

	currentShader = 0;
}


void Renderer::UpdateScene(float msec) {

	viewMatrix = camera->BuildViewMatrix();
	waterRotate += msec / 1000.0f;
	camera->UpdateCamera(msec);
	emitter->Update(msec);
	root->Update(msec);
	
	frame++;
	time += msec;
	
	if (time > 1000)
	{
		fps = frame;
		time = 0;
		frame = 0;
	}
}

void Renderer::RenderScene() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	
	DrawSkybox();

	DrawHeightMap();

	DrawWater();
	DrawNode(root);
	DrawTekst();
	DrawEmitter();
	
	SwapBuffers();
}

void Renderer::DrawEmitter()
{
	SetCurrentShader(particleShader);
	glUseProgram(currentShader->GetProgram());
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);

	modelMatrix = Matrix4::Translation(Vector3(2000, 5000, 2000)) *
	Matrix4::Rotation(0, Vector3(0, 1, 0)) *
	Matrix4::Scale(Vector3(1, 1, 1));
	glUniformMatrix4fv(
	glGetUniformLocation(currentShader->GetProgram(),
	"modelMatrix"), 1, false, (float *)& modelMatrix);

	SetShaderParticleSize(emitter->GetParticleSize());
	emitter->SetParticleSize(8.0f);
	emitter->SetParticleVariance(112.0f);
	emitter->SetLaunchParticles(16.0f);
	emitter->SetParticleLifetime(15000.0f);
	emitter->SetParticleSpeed(0.5f);
	UpdateShaderMatrices();

	emitter->Draw();

	glUseProgram(0);
}

void Renderer::SetShaderParticleSize(float f) {
	glUniform1f(glGetUniformLocation(currentShader->GetProgram(), "particleSize"), f);
}

void Renderer::DrawTekst()
{
	SetCurrentShader(textShader);
	glUseProgram(currentShader->GetProgram());	//Enable the shader...
	//And turn on texture unit 0
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);

	//Render function to encapsulate our font rendering!
	DrawText("Total tree memory:" + std::to_string(memory), Vector3(0, 0, 0), 16.0f);
	DrawText("FPS:" + std::to_string(fps), Vector3(0, 16, 0), 16.0f);
	

	glEnable(GL_DEPTH_TEST);
	glUseProgram(0);	//That's everything!
}

void Renderer::DrawWater() {
	SetCurrentShader(reflectShader);
	SetShaderLight(*light);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(),
		"cameraPos"), 1, (float *)& camera->GetPosition());

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
		"diffuseTex"), 0);

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
		"cubeTex"), 2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	float heightX = (RAW_WIDTH * HEIGHTMAP_X / 2.0f);

	float heightY = 256 * HEIGHTMAP_Y / 3.0f;

	float heightZ = (RAW_HEIGHT * HEIGHTMAP_Z / 2.0f);

	modelMatrix =
		Matrix4::Translation(Vector3(heightX, heightY, heightZ)) *
		Matrix4::Scale(Vector3(heightX, 1, heightZ)) *
		Matrix4::Rotation(90, Vector3(1.0f, 0.0f, 0.0f));

	textureMatrix = Matrix4::Scale(Vector3(10.0f, 10.0f, 10.0f)) *
		Matrix4::Rotation(waterRotate, Vector3(0.0f, 0.0f, 1.0f));

	UpdateShaderMatrices();
	textureMatrix = Matrix4();
	quad->Draw();

	glUseProgram(0);
}

void Renderer::DrawText(const std::string &text, const Vector3 &position, const float size, const bool perspective)	{
	//Create a new temporary TextMesh, using our line of text and our font
	TextMesh* mesh = new TextMesh(text, *basicFont);

	//This just does simple matrix setup to render in either perspective or
	//orthographic mode, there's nothing here that's particularly tricky.
	if (perspective) {
		modelMatrix = Matrix4::Translation(position) * Matrix4::Scale(Vector3(size, size, 1));
		viewMatrix = camera->BuildViewMatrix();
		projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);
	}
	else{
		//In ortho mode, we subtract the y from the height, so that a height of 0
		//is at the top left of the screen, which is more intuitive
		//(for me anyway...)
		modelMatrix = Matrix4::Translation(Vector3(position.x, height - position.y, position.z)) * Matrix4::Scale(Vector3(size, size, 1));
		viewMatrix.ToIdentity();
		projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)width, 0.0f, (float)height, 0.0f);
	}
	//Either way, we update the matrices, and draw the mesh
	UpdateShaderMatrices();
	mesh->Draw();

	modelMatrix = Matrix4::Translation(position) * Matrix4::Scale(Vector3(size, size, 1));
	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);

	delete mesh; //Once it's drawn, we don't need it anymore!
}

void Renderer::DrawHeightMap()
{
	SetCurrentShader(lightShader);
	SetShaderLight(*light);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(),
		"cameraPos"), 1, (float *)& camera->GetPosition());

	glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
		"diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
		"bumpTex"), 1);

	/*modelMatrix = Matrix4::Translation(Vector3(-1000, -1000, 1000)) *
		Matrix4::Rotation(0, Vector3(0, 1, 0)) *
		Matrix4::Scale(Vector3(1, 1, 1));
	glUniformMatrix4fv(
		glGetUniformLocation(currentShader->GetProgram(),
		"modelMatrix"), 1, false, (float *)& modelMatrix);*/

	modelMatrix.ToIdentity();
	textureMatrix.ToIdentity();

	UpdateShaderMatrices();

	heightMap->Draw();

	glUseProgram(0);
}

void Renderer::DrawSkybox() {
	glDepthMask(GL_FALSE);
	SetCurrentShader(skyboxShader);

	UpdateShaderMatrices();
	quad->Draw();

	glUseProgram(0);
	glDepthMask(GL_TRUE);
}

void Renderer::DrawNode(SceneNode * n) {

	SetCurrentShader(lightShader);
	
	if (n->GetMesh()) {
		Matrix4 transform = n->GetWorldTransform() *
			Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(
			glGetUniformLocation(currentShader->GetProgram(),
			"modelMatrix"), 1, false, (float *)& transform);

		glUniform4fv(glGetUniformLocation(currentShader->GetProgram(),
			"nodeColour"), 1, (float *)& n->GetColour());

		glUniform1i(glGetUniformLocation(currentShader->GetProgram(),
			"useTexture"), (int)n->GetMesh()->GetTexture());
		n->Draw(*this);
	}

	for (vector < SceneNode * >::const_iterator
		i = n->GetChildIteratorStart();
		i != n->GetChildIteratorEnd(); ++i)
	{
		DrawNode(*i);
	}
	glUseProgram(0);
}

