#pragma once

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <glwidget277.h>
#include <la.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>
#include <scene/camera.h>
#include <la.h>
#include <mesh.h>
#include <point.h>
#include <scene/line.h>
#include <scene/lineface.h>
#include <objreader.h>
#include <joint.h>
#include <scene/wiresphere.h>
#include <skeletonFileReader.h>
#include <algorithm>


class MyGL
    : public GLWidget277
{
    Q_OBJECT
private:
    QOpenGLVertexArrayObject vao;

    Cylinder geom_cylinder;
    Sphere geom_sphere;
    Mesh geom_mesh;
    Point geom_point;
    Line geom_line;
    LineFace geom_lineface;
    Joint geom_joint;
    WireSphere geom_wireSphere;
    ShaderProgram prog_lambert;
    ShaderProgram prog_wire;
    ShaderProgram prog_joint;
    ObjReader fileReader;
    SkeletonFileReader JSONReader;

    Face* selectedFace;
    Vertex* selectedVertex;
    HalfEdge* selectedEdge;

    bool faceSelect;
    bool edgeSelect;
    bool vertSelect;

    std::vector<Joint*> allJoints;
    std::vector<Joint*> vertexJoints;
    std::vector<glm::mat4> allBindMatrices;
    std::vector<glm::mat4> allJointTransformations;

    bool skinned;

    Joint* selectedJoint;

    Joint * rootJoint;
    Camera camera;

public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    std::vector<QListWidgetItem*> meshVertices;
    std::vector<QListWidgetItem*> meshEdges;
    std::vector<QListWidgetItem*> meshFaces;

    bool vertPosUpdate;
    bool splitEdge;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void selectEdge(HalfEdge* e);
    void selectVertex(Vertex* v);
    void selectFace(Face* f);

    void updateVertexPos(glm::vec4 p);
    void updateFaceCol(glm::vec4 c);

    void addVertex();
    void triangulateFace();
    void deleteVertex();
    void deleteFace();

    void createCentroid();

    void importObj();
    void sharpen(int check);

    void setJointRoot(Joint * r);
    void addAllJoints(Joint* root);

    void importJSON();

    void skin();
    void getNearestJoint(Joint* j, glm::vec4 vPos);

    void drawJoints(Joint* root, glm::mat4 T);

    void selectJoint(QTreeWidgetItem * i);

    Joint *getSelectedJoint() const;
    void setSelectedJoint(Joint *value);


    void updateJointPosition(glm::vec3 p);
    void updateMesh();


    void assignJointTransformations();
signals:
    void sig_populateVert(QListWidgetItem* i);
    void sig_populateFace(QListWidgetItem* i);
    void sig_populateEdge(QListWidgetItem* i);

    void sig_clearList();

    void sig_addTreeRoot(QTreeWidgetItem * jRoot);
protected:
    void keyPressEvent(QKeyEvent *e);
};
