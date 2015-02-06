#pragma once

#include "../../nclgl/SceneNode.h"
#include "../../nclgl/Mesh.h"


class Tree : public SceneNode {
public:
	Tree(float x, float y, float z, float scale);
	~Tree(void){};
	virtual void Update(float msec);
	
	static void CreateBranch()
	{
		Mesh * m = new Mesh();
		branch = m->GenerateWood();
	}

	static void CreateLeaf()
	{
		Mesh * m = new Mesh();
		leaf = m->GenerateQuad();
	}

	static void DeleteBranch(){ delete branch; }
	static void DeleteLeaf(){ delete leaf; }

	int GetMemory(){ return memory; }

	void addBranches(SceneNode* base, float scale);
	void addMoreBranches(SceneNode* base, float scale);
	void addLeafs(SceneNode* base, float s);

	void reset();

protected:

	static Mesh * branch;
	static Mesh * leaf;
	SceneNode * base;

	SceneNode * firstBranch;
	SceneNode * secondBranch;
	SceneNode * thirdBranch;
	SceneNode * fourthBranch;
	SceneNode * fifthBranch;

	float  scale1;
	float  scale2;
	float  scale3;
	float  scale4;
	float  scale5;
	float s;
	int memory = 0;

	vector<SceneNode*> vctr;
	vector<SceneNode*> vctr2;
	vector<SceneNode*> vctr3;
};
