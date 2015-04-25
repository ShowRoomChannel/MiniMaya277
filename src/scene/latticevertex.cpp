#include "LatticeVertex.h"
#include <iostream>

LatticeVertex::LatticeVertex()
{
    position = glm::vec4(0);
    latticeVertices = {};

}
glm::vec4 LatticeVertex::getPosition() const
{
    return position;
}

void LatticeVertex::setPosition(const glm::vec4 &value)
{
    position = value;
}
std::vector<Vertex *> LatticeVertex::getLatticeVertices() const
{
    return latticeVertices;
}

void LatticeVertex::setLatticeVertices(const std::vector<Vertex *> &value)
{
    latticeVertices = value;
}

void LatticeVertex::addVertex(Vertex* v) {
    latticeVertices.push_back(v);
}

ShaderProgram::Drawable *LatticeVertex::getSphere()
{
    return sphere;
}

void LatticeVertex::setSphere(ShaderProgram::Drawable *value)
{
    sphere = value;
}
glm::mat4 LatticeVertex::getTransformationMatrix() const
{
    return transformationMatrix;
}

void LatticeVertex::setTransformationMatrix(const glm::mat4 &value)
{
    transformationMatrix = value;
}










