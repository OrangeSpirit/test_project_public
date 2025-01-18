// modelviewer.h
#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>

#include "parser.h"
#include "gif/gifimage/qgifimage.h"
//#include "gif/gifimage/qgifimage_p.h"

class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    ModelViewer(QWidget *parent = nullptr);
    ~ModelViewer() = default;

    void setModelData(const std::vector<Vector3>& vertices, const std::vector<Edge>& edges);
    void saveFrameAsJpeg();
    void saveFrameAsBMP();
    void startGif();
    int getFrameCount();
    void addFrameToGif();
    void endGif(QString filepath);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    std::vector<Vector3> vertices; 
    std::vector<Edge> edges;
    QGifImage *gif;       
    bool isRecord;
};

#endif // MODELVIEWER_H
