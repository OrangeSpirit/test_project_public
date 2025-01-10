#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include "parser.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    fileNameEdit(new QLineEdit(this)),
    moveSliderX(new QSlider(Qt::Horizontal, this)),
    moveSliderY(new QSlider(Qt::Horizontal, this)),
    modelViewer(new ModelViewer(this)),
    rotateXEdit(new QLineEdit(this)),
    rotateYEdit(new QLineEdit(this)),
    rotateZEdit(new QLineEdit(this)),
    rotateModelButton(new QPushButton("Rotate Model", this)),
    scaleEdit(new QLineEdit(this)),
    scaleModelButton(new QPushButton("Scale Model", this))
{
    setWindowTitle("3D Viewer");
    resize(900, 900);
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createFileSelectionUI(QVBoxLayout* layout) {
    fileNameEdit = new QLineEdit(this);
    fileNameEdit->setPlaceholderText("File name");

    fileNameLabel = new QLabel("File: Not selected", this);   
    vertexCountLabel = new QLabel("Vertices: 0", this);          
    edgeCountLabel = new QLabel("Edges: 0", this);              

    QPushButton *selectFileButton = new QPushButton("Select model file", this);
    connect(selectFileButton, &QPushButton::clicked, this, &MainWindow::onSelectFileClicked);

    layout->addWidget(fileNameEdit);
    layout->addWidget(selectFileButton);
    layout->addWidget(fileNameLabel);       
    layout->addWidget(vertexCountLabel);    
    layout->addWidget(edgeCountLabel); 
}

void MainWindow::createScreenJpgUI(QVBoxLayout* layout) {
    QPushButton *screenJpgButton = new QPushButton("Jpeg", this);
    layout->addWidget(screenJpgButton);
    connect(screenJpgButton, &QPushButton::clicked, this, &MainWindow::onScreenJpgButtonClicked);
}

void MainWindow::createScreenBMPUI(QVBoxLayout* layout) {
    QPushButton *screenBMPButton = new QPushButton("BMP", this);
    layout->addWidget(screenBMPButton);
    connect(screenBMPButton, &QPushButton::clicked, this, &MainWindow::onScreenBMPButtonClicked);
}

void MainWindow::createMoveUI(QVBoxLayout* layout) {
    QLabel *moveLabelX = new QLabel("Move X:", this);
    moveSliderX = new QSlider(Qt::Horizontal, this);
    moveSliderX->setRange(-100, 100);
    connect(moveSliderX, &QSlider::valueChanged, this, &MainWindow::onMoveModelButtonClicked);

    QLabel *moveLabelY = new QLabel("Move Y:", this);
    moveSliderY = new QSlider(Qt::Horizontal, this);
    moveSliderY->setRange(-100, 100);
    connect(moveSliderY, &QSlider::valueChanged, this, &MainWindow::onMoveModelButtonClicked);

    layout->addWidget(moveLabelX);
    layout->addWidget(moveSliderX);
    layout->addWidget(moveLabelY);
    layout->addWidget(moveSliderY);
}

void MainWindow::createRotateUI(QVBoxLayout* layout) {
    QLabel *rotateLabelX = new QLabel("Rotate X (degrees):", this);
    rotateXEdit = new QLineEdit(this);
    rotateXEdit->setPlaceholderText("0");

    QLabel *rotateLabelY = new QLabel("Rotate Y (degrees):", this);
    rotateYEdit = new QLineEdit(this);
    rotateYEdit->setPlaceholderText("0");

    QLabel *rotateLabelZ = new QLabel("Rotate Z (degrees):", this);
    rotateZEdit = new QLineEdit(this);
    rotateZEdit->setPlaceholderText("0");

    rotateModelButton = new QPushButton("Rotate Model", this);
    connect(rotateModelButton, &QPushButton::clicked, this, &MainWindow::onRotateModelButtonClicked);

    layout->addWidget(rotateLabelX);
    layout->addWidget(rotateXEdit);
    layout->addWidget(rotateLabelY);
    layout->addWidget(rotateYEdit);
    layout->addWidget(rotateLabelZ);
    layout->addWidget(rotateZEdit);
    layout->addWidget(rotateModelButton);
}

void MainWindow::createScaleUI(QVBoxLayout* layout) {
    QLabel *scaleLabel = new QLabel("Scale (e.g., 1.0):", this);
    scaleEdit = new QLineEdit(this);
    scaleEdit->setPlaceholderText("1.0");

    scaleModelButton = new QPushButton("Scale Model", this);
    connect(scaleModelButton, &QPushButton::clicked, this, &MainWindow::onScaleModelButtonClicked);

    layout->addWidget(scaleLabel);
    layout->addWidget(scaleEdit);
    layout->addWidget(scaleModelButton);
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    createFileSelectionUI(layout);
    modelViewer->setMinimumSize(300, 300);
    layout->addWidget(modelViewer);

    createScreenJpgUI(layout);
    createScreenBMPUI(layout);

    createMoveUI(layout);
    createRotateUI(layout);
    createScaleUI(layout);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

// Обработка выбора файла
void MainWindow::onSelectFileClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Model File", "", "Model Files (*.obj *.stl);;All Files (*)");
    if (!filePath.isEmpty()) {
        fileNameEdit->setText(filePath);

        ObjParser parser;
        if (parser.parse(filePath.toStdString())) {
            qDebug() << "Файл успешно распарсен!";
            const auto& vertices = parser.getVertices();
            const auto& edges = parser.getEdges();
            modelViewer->setModelData(vertices, edges);

            fileNameLabel->setText("File: " + filePath);                    
            vertexCountLabel->setText("Vertices: " + QString::number(vertices.size()));  
            edgeCountLabel->setText("Edges: " + QString::number(edges.size())); 
            modelViewer->update();
        } else {
            qDebug() << "Ошибка парсинга файла.";
        }
    }
}

// Обработка перемещения модели
void MainWindow::onMoveModelButtonClicked()
{
    int xValue = moveSliderX->value();
    int yValue = moveSliderY->value();
    qDebug() << "Move Model: X = " << xValue << ", Y = " << yValue;
    modelViewer->update();
}

// Обработка поворота модели
void MainWindow::onRotateModelButtonClicked()
{
    float rotateX = rotateXEdit->text().toFloat();
    float rotateY = rotateYEdit->text().toFloat();
    float rotateZ = rotateZEdit->text().toFloat();

    qDebug() << "Rotate Model: X = " << rotateX << ", Y = " << rotateY << ", Z = " << rotateZ;
    modelViewer->update();
}

// Обработка масштабирования модели
void MainWindow::onScaleModelButtonClicked()
{
    float scale = scaleEdit->text().toFloat();
    qDebug() << "Scale Model: Factor = " << scale;
    modelViewer->update();
}

// Скрин в формате Jpeg
void MainWindow::onScreenJpgButtonClicked()
{
    modelViewer->saveFrameAsJpeg();
}

// Скрин в формате BMP
void MainWindow::onScreenBMPButtonClicked()
{
    modelViewer->saveFrameAsBMP();
}
