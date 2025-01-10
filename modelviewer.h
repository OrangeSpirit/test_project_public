// modelviewer.h
#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include "mainwindow.h"

class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    ModelViewer(QWidget *parent = nullptr);
    ~ModelViewer() = default;

    void setModelData(const std::vector<Vector3>& vertices, const std::vector<Edge>& edges);
    void saveFrameAsJpeg();
    void saveFrameAsBMP();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::vector<Vector3> vertices; 
    std::vector<Edge> edges;        
};

#endif // MODELVIEWER_H
