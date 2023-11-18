#include "GraphicObject.h"


void GraphicObject::setPosition(vec3 position) {
	this->position = position;
}
vec3 GraphicObject::getPosition() {
	return this->position;
}
void GraphicObject::setAngle(float grad) {
	angle = grad;
}
float GraphicObject::getAngle() {
	return this->angle;
}
void GraphicObject::setСolor(vec3 color) {
	this->color = color;
}
vec3 GraphicObject::getColor() {
	return this->color;
}
// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix() {

	mat4 trans = translate(mat4(1.0f), position);
	mat4 rot = trans * rotate(mat4(1.0f), radians(angle), vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), -position);
	mat4 scal = scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));

	modelMatrix = scal * rot * trans;

}

void GraphicObject::setMaterial(const std::vector<std::shared_ptr<Material>>& material)
{
	this->material = material;
}

void GraphicObject::setMesh(shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

// вывести объект
void GraphicObject::draw() {
	recalculateModelMatrix();

	for (const auto& material : material) {
		if (material != nullptr) {
			material->apply();
		}
	}

	glPushMatrix();
	glMultMatrixf(&modelMatrix[0][0]);

	if (mesh != nullptr) {
		mesh->draw();
	}

	glPopMatrix();
}