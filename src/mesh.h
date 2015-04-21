#pragma once

#include <shaderprogram.h>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <vector>

#include "halfedge.h"
#include "vertex.h"
#include "face.h"


class Mesh : public ShaderProgram::Drawable
{
private:
    int count;
    bool imported;
    bool vertexWasDeleted;
    std::vector<QListWidgetItem*> edges;
    std::vector<QListWidgetItem*> faces;
    std::vector<QListWidgetItem*> vertices;
    std::vector<glm::vec4> orderedNormals;

    std::vector<int> visitedEdges;
    std::vector<int> visitedFaces;
    std::vector<int> visitedVertices;

    std::vector<HalfEdge*> edgesToLink;

    int maxNumFaces;
    int maxNumVerts;
    int maxNumEdges;

    QOpenGLBuffer bufIdx;
    QOpenGLBuffer bufPos;
    QOpenGLBuffer bufNor;
    QOpenGLBuffer bufCol;
    QOpenGLBuffer bufJointId;
    QOpenGLBuffer bufJointWeight;

    std::vector<Joint*> allJoints;

    glm::ivec2 influenceJoints;
    glm::vec2 weights;

    //Can be used to pass per-vertex color information to the shader, but is currently unused.

public:
    Mesh();

    void create();

    void updateMesh();

    void destroy();

    void createCube();

    glm::vec4 calculateVertexNormal(Vertex* v2, Face* f);

    void calculateAllNormals();

    void addVertex(HalfEdge * e);
    void triangulateFace(Face* f);
    void deleteVertex(Vertex* v);
    void deleteVertFromFace(Face* f, Vertex* v);
    HalfEdge* getInboundEdge(Face* f, Vertex* v);

    void deleteFace(Face* f);

    void setOrigFaceVerts(Face* f);
    Vertex* createFaceCentroid(Face* f);
    void createEdgePoints(Face* f);
    void splitAllEdges();
    void smoothOriginalVertices(Face* f);
    void quadrangulateFace(Face* f);

    void importMesh(std::vector<QListWidgetItem*> v, std::vector<QListWidgetItem*> e, std::vector<QListWidgetItem*> f, std::vector<glm::vec4> n);

    void setVertices(std::vector<QListWidgetItem*> v);
    void setEdges(std::vector<QListWidgetItem*> e);
    void setFaces(std::vector<QListWidgetItem*> f);

    void setWasVertexDeleted(bool b);
    bool getWasVertexDeleted();



    std::vector<QListWidgetItem*> getVerts();
    std::vector<QListWidgetItem*> getEdges();
    std::vector<QListWidgetItem*> getFaces();

//    void createMeshVertexPositions(std::vector<glm::vec4> mesh_vert_pos);
//    void createMeshVertexNormals(std::vector<glm::vec4> mesh_vert_nor);
//    void createMeshColors(std::vector<glm::vec4> mesh_vert_col);
//    void createMeshIndices(std::vector<GLuint> mesh_idx);

    virtual GLenum drawMode();
    virtual int elemCount();
    virtual bool bindIdx();
    virtual bool bindPos();
    virtual bool bindNor();
    virtual bool bindCol();
    virtual bool bindIds();
    virtual bool bindWts();
    std::vector<Joint *> getAllJoints() const;
    void setAllJoints(const std::vector<Joint *> &value);
};

