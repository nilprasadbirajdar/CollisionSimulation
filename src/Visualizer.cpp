#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include "Orbit.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    connect(mpushButtonRead, &QPushButton::clicked, this, &Visualizer::readSTL);
    connect(mpushButtonBBox, &QPushButton::clicked, this, &Visualizer::drawBoundingBox);
    connect(mpushButtonStart, &QPushButton::clicked, this, &Visualizer::startBtn);
    connect(mpushButtonStop, &QPushButton::clicked, this, &Visualizer::stopBtn);
    connect(mpushButtonReset, &QPushButton::clicked, this, &Visualizer::resetBtn);
}

Visualizer::~Visualizer()
{

}

void Visualizer::setupUi() {
    resize(800, 600);

    mpushButtonRead = new QPushButton(this);
    mpushButtonRead->setText("Generate");
    mpushButtonRead->setGeometry(QRect(1550, 300, 100, 25));

    mpushButtonBBox = new QPushButton(this);
    mpushButtonBBox->setText("BBox");
    mpushButtonBBox->setGeometry(QRect(1550, 350, 100, 25));

    mpushButtonStart = new QPushButton(this);
    mpushButtonStart->setText("Start");
    mpushButtonStart->setGeometry(QRect(1550, 400, 100, 25));

    mpushButtonStop = new QPushButton(this);
    mpushButtonStop->setText("Stop");
    mpushButtonStop->setGeometry(QRect(1550, 450, 100, 25));

    mpushButtonReset = new QPushButton(this);
    mpushButtonReset->setText("Reset");
    mpushButtonReset->setGeometry(QRect(1550, 500, 100, 25));

    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mRenderer->setGeometry(QRect(30,200, 1400, 800));
    setWindowTitle(QCoreApplication::translate("Collision Viewer", "Collision Viewer", nullptr));
}

void Visualizer::readSTL()
{
    std::string filePath = "D:/sphere3.stl";

    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return;
    }

    std::string line;
    //int c = 100;
    while (std::getline(dataFile, line))
    {
      
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;
            mVertices << x *0.1 << y*0.1 << z*0.1;
            mColors << 1.0f << 0.0f << 0.0f;
           
        }
    }
    
    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
    /*mVertices.clear();
    mColors.clear();
    dataFile.close();*/
    update();
}
   
//bounding box for collision detection
void Visualizer::drawBoundingBox()
{
    std::string filePath = "D:/sphere3.stl";

    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return;
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();
    double maxZ = std::numeric_limits<double>::min();

    std::string line;
    while (std::getline(dataFile, line))
    {
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;

            // Update bounding box coordinates
            minX = std::min(minX, x);
            minY = std::min(minY, y);
            minZ = std::min(minZ, z);
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);
            maxZ = std::max(maxZ, z);
        }
    }
    //bottom side vertices
    mVertices << minX * 0.1 << minY * 0.1 << minZ * 0.1;
    mVertices << maxX * 0.1 << minY * 0.1 << minZ * 0.1;
    mVertices << maxX * 0.1 << minY * 0.1 << maxZ * 0.1;
    mVertices << minX * 0.1 << minY * 0.1 << maxZ * 0.1;
    //top side vertices
    mVertices << minX * 0.1 << minY * 0.1 << minZ * 0.1;
    mVertices << minX * 0.1 << maxY * 0.1 << minZ * 0.1;
    mVertices << maxX * 0.1 << maxY * 0.1 << minZ * 0.1;
    mVertices << maxX * 0.1 << maxY * 0.1 << maxZ * 0.1;
    //front side vertices
    mVertices << minX * 0.1 << maxY * 0.1 << maxZ * 0.1;
    mVertices << minX * 0.1 << maxY * 0.1 << minZ * 0.1;
    mVertices << minX * 0.1 << maxY * 0.1 << maxZ * 0.1;
    mVertices << minX * 0.1 << minY * 0.1 << maxZ * 0.1;
    //remaining side vertices
    mVertices << maxX * 0.1 << minY * 0.1 << maxZ * 0.1;
    mVertices << maxX * 0.1 << maxY * 0.1 << maxZ * 0.1;
    mVertices << maxX * 0.1 << maxY * 0.1 << minZ * 0.1;
    mVertices << maxX * 0.1 << minY * 0.1 << minZ * 0.1;

    //Colors
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;

    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;

    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;
    mColors << 0.0f << 0.0f << 1.0f;

    //orbit1 
    orbit.drawCircle(mTempVertices, mTempColors, 0, 0, 16, 100);
    for (int i = 0; i < mTempVertices.size(); i++)
    {
        mVertices << mTempVertices[i];
        mColors << mTempColors[i];
    }

    //orbit2
    orbit.drawCircle(mTempVertices, mTempColors, 0, 0, 25, 100);
    for (int i = 0; i < mTempVertices.size(); i++)
    {
        mVertices << mTempVertices[i];
        mColors << mTempColors[i];
    }

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
    mVertices.clear();
    mColors.clear();
    dataFile.close();
    update();
}


void Visualizer::startBtn()

{

    mRenderer->startRendering(mVelocity, mSize, mAltitude);

}

void Visualizer::stopBtn()

{

    mRenderer->stopRevolving();

}

void Visualizer::resetBtn()

{

    mRenderer->resetPositions();

}