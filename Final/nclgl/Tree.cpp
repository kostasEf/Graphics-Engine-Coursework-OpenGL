#include "Tree.h"

Mesh * Tree::branch = NULL;
Mesh * Tree::leaf = NULL;


Tree::Tree(float x, float y, float z, float scale) {
	// Optional , uncomment if you want a local origin marker !
	//SetMesh ( branch );

	memory += branch->GetMemory();
	memory += leaf->GetMemory();

	s = scale;
	scale1 = 0;
	scale2 = 0;
	scale3 = 0;
	scale4 = 0;
	scale5 = 0;

	base = new SceneNode(branch, Vector4(1, 0, 0, 1)); // Red !
	base->SetModelScale(Vector3(0, 0, 0));
	base->SetTransform(Matrix4::Translation(Vector3(x, y, z))*
		Matrix4::Rotation(0, Vector3(0, 0, 0)));
	AddChild(base);


	firstBranch = new SceneNode(branch, Vector4(0, 0, 1, 1)); // Blue !
	firstBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	firstBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(50, Vector3(0, 0, 1))*
		Matrix4::Rotation(50, Vector3(0, 1, 0))
		);
	base->AddChild(firstBranch);

	secondBranch = new SceneNode(branch, Vector4(0, 0, 1, 1)); // Blue !
	secondBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	secondBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(-50, Vector3(0, 0, 1))*
		Matrix4::Rotation(50, Vector3(0, 1, 0)));
	base->AddChild(secondBranch);

	thirdBranch = new SceneNode(branch, Vector4(0, 0, 1, 1)); // Blue !
	thirdBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	thirdBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(-50, Vector3(1, 0, 0))*
		Matrix4::Rotation(50, Vector3(0, 1, 0)));
	base->AddChild(thirdBranch);

	fourthBranch = new SceneNode(branch, Vector4(0, 0, 1, 1)); // Blue !
	fourthBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	fourthBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(50, Vector3(1, 0, 0))*
		Matrix4::Rotation(50, Vector3(0, 1, 0)));
	base->AddChild(fourthBranch);

	fifthBranch = new SceneNode(branch, Vector4(0, 0, 1, 1)); // Blue !
	fifthBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	fifthBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30))));
	base->AddChild(fifthBranch);

	addBranches(firstBranch, s / 2);
	addBranches(secondBranch, s / 2);
	addBranches(thirdBranch, s / 2);
	addBranches(fourthBranch, s / 2);
	addBranches(fifthBranch, s / 2);

	branch->SetTexture(SOIL_load_OGL_texture("../../Textures/wood.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));

	leaf->SetTexture(SOIL_load_OGL_texture("../../Textures/leaf.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0));
}




void Tree::addBranches(SceneNode* base, float s)
{

	SceneNode * firstBranch = new SceneNode(branch, Vector4(0, 0, 1, 1));
	firstBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	firstBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(45, Vector3(0, 0, 1)));
	base->AddChild(firstBranch);


	SceneNode * secondBranch = new SceneNode(branch, Vector4(0, 0, 1, 1));
	secondBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	secondBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(-45, Vector3(0, 0, 1)));
	base->AddChild(secondBranch);

	SceneNode * thirdBranch = new SceneNode(branch, Vector4(0, 0, 1, 1));
	thirdBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	thirdBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(-45, Vector3(1, 0, 0)));
	base->AddChild(thirdBranch);

	SceneNode * fourthBranch = new SceneNode(branch, Vector4(0, 0, 1, 1));
	fourthBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	fourthBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(45, Vector3(1, 0, 0)));
	base->AddChild(fourthBranch);

	SceneNode * fifthBranch = new SceneNode(branch, Vector4(0, 0, 1, 1)); // Blue !
	fifthBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	fifthBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30))));
	base->AddChild(fifthBranch);

	addMoreBranches(firstBranch, s / 2);
	addMoreBranches(secondBranch, s / 2);
	addMoreBranches(thirdBranch, s / 2);
	addMoreBranches(fourthBranch, s / 2);
	addMoreBranches(fifthBranch, s / 2);

	vctr.push_back(firstBranch);
	vctr.push_back(secondBranch);
	vctr.push_back(thirdBranch);
	vctr.push_back(fourthBranch);
	vctr.push_back(fifthBranch);

}

void Tree::addMoreBranches(SceneNode* base, float s)
{

	SceneNode * firstBranch = new SceneNode(branch, Vector4(0, 0, 1, 1));
	firstBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	firstBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(45, Vector3(0, 0, 1)));
	base->AddChild(firstBranch);


	SceneNode * secondBranch = new SceneNode(branch, Vector4(0, 0, 1, 1));
	secondBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	secondBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(-45, Vector3(0, 0, 1)));
	base->AddChild(secondBranch);

	SceneNode * thirdBranch = new SceneNode(branch, Vector4(0, 0, 1, 1));
	thirdBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	thirdBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(-45, Vector3(1, 0, 0)));
	base->AddChild(thirdBranch);

	SceneNode * fourthBranch = new SceneNode(branch, Vector4(0, 0, 1, 1));
	fourthBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	fourthBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(45, Vector3(1, 0, 0)));
	base->AddChild(fourthBranch);

	SceneNode * fifthBranch = new SceneNode(branch, Vector4(0, 0, 1, 1)); // Blue !
	fifthBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	fifthBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30))));
	base->AddChild(fifthBranch);

	addLeafs(firstBranch, s / 2);
	addLeafs(secondBranch, s / 2);
	addLeafs(thirdBranch, s / 2);
	addLeafs(fourthBranch, s / 2);
	addLeafs(fifthBranch, s / 2);

	vctr2.push_back(firstBranch);
	vctr2.push_back(secondBranch);
	vctr2.push_back(thirdBranch);
	vctr2.push_back(fourthBranch);
	vctr2.push_back(fifthBranch);
}

void Tree::addLeafs(SceneNode* base, float s)
{
	SceneNode * firstBranch = new SceneNode(leaf, Vector4(0, 0, 1, 1));
	firstBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	firstBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(45, Vector3(0, 0, 1)));
	base->AddChild(firstBranch);


	SceneNode * secondBranch = new SceneNode(leaf, Vector4(0, 0, 1, 1));
	secondBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	secondBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(-45, Vector3(0, 0, 1)));
	base->AddChild(secondBranch);

	SceneNode * thirdBranch = new SceneNode(leaf, Vector4(0, 0, 1, 1));
	thirdBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	thirdBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(-45, Vector3(1, 0, 0)));
	base->AddChild(thirdBranch);

	SceneNode * fourthBranch = new SceneNode(leaf, Vector4(0, 0, 1, 1));
	fourthBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	fourthBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30)))*
		Matrix4::Rotation(45, Vector3(1, 0, 0)));
	base->AddChild(fourthBranch);

	SceneNode * fifthBranch = new SceneNode(leaf, Vector4(0, 0, 1, 1)); // Blue !
	fifthBranch->SetModelScale(base->GetModelScale() *
		Vector3(0, 0, 0));
	fifthBranch->SetTransform(base->GetWorldTransform() *
		Matrix4::Translation(Vector3(s / 15, s, -(s / 30))));
	base->AddChild(fifthBranch);

	vctr3.push_back(firstBranch);
	vctr3.push_back(secondBranch);
	vctr3.push_back(thirdBranch);
	vctr3.push_back(fourthBranch);
	vctr3.push_back(fifthBranch);
}


void Tree::Update(float msec) {

	if (scale1 < s)
	{
		scale1 += (msec / (150 / s * 100));
		base->SetModelScale(Vector3(s / 15, scale1, s / 15));

	}
	else if (scale2 <scale1 / 2)
	{
		scale2 += (msec / (150 / s * 100));
		firstBranch->SetModelScale(Vector3(s / 30, scale2, s / 30));
		secondBranch->SetModelScale(Vector3(s / 30, scale2, s / 30));
		thirdBranch->SetModelScale(Vector3(s / 30, scale2, s / 30));
		fourthBranch->SetModelScale(Vector3(s / 30, scale2, s / 30));
		fifthBranch->SetModelScale(Vector3(s / 30, scale2, s / 30));

	}
	else if (scale3 <scale2 / 2)
	{
		scale3 += (msec / (150 / s * 100));

		for (int i = 0; i < vctr.size(); ++i) {

			vctr[i]->SetModelScale(Vector3(s / 60, scale3, s / 60));
		}

	}
	else if (scale4 < scale3 / 2)
	{
		scale4 += (msec / (150 / s * 100));

		for (int i = 0; i < vctr2.size(); ++i) {

			vctr2[i]->SetModelScale(Vector3(s / 120, scale4, s / 120));
		}
	}
	else if (scale5 < scale4 / 2)
	{
		scale5 += (msec / (150 / s * 100));

		for (int i = 0; i < vctr3.size(); ++i) {

			vctr3[i]->SetModelScale(Vector3(scale5 / 2, scale5 / 2, scale5 / 2));
		}
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_R))
	{
		reset();
	}

	SceneNode::Update(msec);
}


void Tree::reset()
{
	scale1 = 0;
	scale2 = 0;
	scale3 = 0;
	scale4 = 0;
	scale5 = 0;

	firstBranch->SetModelScale(Vector3(0, 0, 0));
	secondBranch->SetModelScale(Vector3(0, 0, 0));
	thirdBranch->SetModelScale(Vector3(0, 0, 0));
	fourthBranch->SetModelScale(Vector3(0, 0, 0));
	fifthBranch->SetModelScale(Vector3(0, 0, 0));

	for (int i = 0; i < vctr.size(); ++i) {

		vctr[i]->SetModelScale(Vector3(0, 0, 0));
	}

	for (int i = 0; i < vctr2.size(); ++i) {

		vctr2[i]->SetModelScale(Vector3(0, 0, 0));
	}
	for (int i = 0; i < vctr3.size(); ++i) {

		vctr3[i]->SetModelScale(Vector3(0, 0, 0));
	}
}