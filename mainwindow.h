#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QOpenGLWidget>  
#include "parser.h"    
#include "modelviewer.h" 

class ModelViewer; 

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectFileClicked(); 
    void onMoveModelButtonClicked();

    void onRotateModelButtonClicked();
    void onScaleModelButtonClicked();

    void onScreenJpgButtonClicked();
    void onScreenBMPButtonClicked();

private:
    QLabel *fileNameLabel;     
    QLabel *vertexCountLabel;   
    QLabel *edgeCountLabel; 

    QLineEdit *fileNameEdit;  
    QSlider *moveSliderX;  
    QSlider *moveSliderY;     
    ModelViewer *modelViewer;

    QLineEdit *rotateXEdit;
    QLineEdit *rotateYEdit;
    QLineEdit *rotateZEdit;
    QPushButton *rotateModelButton;

    QLineEdit *scaleEdit;
    QPushButton *scaleModelButton;

    QPushButton *screenJpgButton;
    QPushButton *screenBMPButton;

    void setupUI();
    void createFileSelectionUI(QVBoxLayout* layout);
    void createScreenJpgUI(QVBoxLayout* layout);
    void createScreenBMPUI(QVBoxLayout* layout);
    void createMoveUI(QVBoxLayout* layout);
    void createRotateUI(QVBoxLayout* layout);
    void createScaleUI(QVBoxLayout* layout);
};

#endif // MAINWINDOW_H
