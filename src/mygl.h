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
#include <scene/wirebox.h>
#include <scene/lattice.h>
#include <scene/latticevertex.h>
#include <objreader.h>
#include <joint.h>
#include <scene/wiresphere.h>
#include <skeletonFileReader.h>
#include <algorithm>
#include <vector>


class MyGL
    : public GLWidget277
{
    Q_OBJECT

public slots:
    //<kerem>
    void slot_raytrace();
    void slot_mesh_selected(QListWidgetItem*);
    void slot_x_inc();
    void slot_x_dec();
    void slot_y_inc();
    void slot_y_dec();
    void slot_z_inc();
    void slot_z_dec();
    void slot_new_cube();
    void slot_refraction(double);
    void slot_refraction_idx(double);
    void slot_reflection(double);
    //</kerem>
private:
    QOpenGLVertexArrayObject vao;


    Cylinder geom_cylinder;
    Sphere geom_sphere;
    Mesh *geom_mesh;
    Point geom_point;
    Line geom_line;
    LineFace geom_lineface;
    Joint geom_joint;
    WireSphere geom_wireSphere;
    wirebox geom_wireBox;
    Lattice geom_lattice;
    ray geom_ray;

    ShaderProgram prog_lambert;
    ShaderProgram prog_wire;
    ShaderProgram prog_joint;
    ShaderProgram prog_toon;
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

    // raycasting
    float tMin;
    bool selected;
    glm::vec4 ray_o;
    glm::vec4 ray_d;

    // deformation
    bool drawLattice;
    bool latticeCreated;
    LatticeVertex* closestLatticeVertex;

    int latticeDivsX;
    int latticeDivsY;
    int latticeDivsZ;

    std::vector<std::vector<LatticeVertex*>> allXSlices;
    std::vector<std::vector<LatticeVertex*>> allYSlices;
    std::vector<std::vector<LatticeVertex*>> allZSlices;

    //<kerem>
    glm::vec3 recursiveRayTrace(ray r, int recursion);
    //</kerem>

public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    std::vector<QListWidgetItem*> meshVertices;
    std::vector<QListWidgetItem*> meshEdges;
    std::vector<QListWidgetItem*> meshFaces;

    std::vector<QListWidgetItem*> latticeVertices;
    std::vector<QListWidgetItem*> latticeEdges;
    std::vector<QListWidgetItem*> latticeFaces;

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

    std::vector<wirebox*> latticeCells;
    std::vector<glm::mat4> latticePoints;

    void createLatticeCells(float dx, float dy, float dz);
    void latticeRayTraverse();
    void assignCellsToLatticeVertices();
    void resetVertexPositions();


    LatticeVertex *getClosestLatticeVertex() const;
    void setClosestLatticeVertex(LatticeVertex *value);
    void deformMesh();
    void createLatticeSlices(int dx, int dy, int dz);
    void resetLattice();
    void specialLatticeDeformation(float amount, int type, int axis);



    bool getDrawLattice() const;
    void setDrawLattice(bool value);

public slots:
    void slot_update();
signals:
    void sig_populateVert(QListWidgetItem* i);
    void sig_populateFace(QListWidgetItem* i);
    void sig_populateEdge(QListWidgetItem* i);

    void sig_clearList();

    void sig_addTreeRoot(QTreeWidgetItem * jRoot);

    void sig_selectLatticeVertex();

    void sig_set_lattice_checkbox(bool arg1);

    //<kerem>
    void sig_set_meshList();
    //</kerem>
protected:
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *m);
};
