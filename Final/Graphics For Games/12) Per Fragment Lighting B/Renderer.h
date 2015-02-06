# pragma once

#include "../../nclgl/OGLRenderer.h"
#include "../../nclgl/Camera.h"
#include "../../nclgl/HeightMap.h"
#include "../../nclgl/Tree.h"
#include "../../nclgl/TextMesh.h"
#include "../../nclgl/ParticleEmitter.h"

class Renderer : public OGLRenderer {
public:
	Renderer(Window & parent);
	virtual ~Renderer(void);

	virtual void RenderScene();
	virtual void UpdateScene(float msec);
	

	void	DrawText(const std::string &text, const Vector3 &position, const float size = 10.0f, const bool perspective = false);
	int fps;
	int frame;
	int time;
	int memory;

protected:

	ParticleEmitter * emitter;
	Font * basicFont;
	SceneNode * root;
	Mesh * heightMap;
	Camera * camera;
	GLuint cubeMap;
	Light * light;
	Mesh * quad;
	Tree * tree;

	void SetShaderParticleSize(float f);	//And a new setter
	void DrawNode(SceneNode * n);
	void DrawHeightMap();
	void DrawEmitter();
	void DrawSkybox();
	void DrawWater();
	void DrawTekst();
	
	Shader * heightMapShader;
	Shader * particleShader;
	Shader * reflectShader;
	Shader * skyboxShader;
	Shader * lightShader;
	Shader * textShader;
	
	float waterRotate;

};
