#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMainWindow>
#include <QQuaternion>
#include <QWheelEvent>
#include "Orbit.h"
#include "CollisionSimulator.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;
class CollisionSimulator;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

    void stopRevolving();
    void resetPositions();
    void updateSolarSystemData();
    void startRendering(float& speed, float& size, float& altitude);
    void stopRendering();
    void setVectorOfLines(QVector<GLfloat>& vectorOfLines);
    void setColorOfLines(QVector<GLfloat>& colorOfLines);
    void updateData(QVector<GLfloat>& vertices,QVector<GLfloat>& colors);
    void mouseMoveEvent(QMouseEvent* event);
   
protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();


signals:
    void shapeUpdate();

private:
    QTimer* timer;
    CollisionSimulator* collision;

    QOpenGLShaderProgram* mProgram = nullptr;

    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;
    
    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    
    QList<QVector3D> mVertices;
    QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;
    double mVertexAttr;
    double mNormalAttr;
    double mMatrixUniform;
    QColor mBackground;
    bool mIsRevolving;
    double xMin, yMin, xMax, yMax, inside, rht, lft, bottom, top;
    double startX, startY, endX, endY;
    GLfloat orbitRadius;

    QMetaObject::Connection mContextWatchConnection;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    GLint m_rotationAngleUniform;

    QQuaternion rotationAngle;
    QPoint lastPos;

    QVector<GLfloat> verticesOfOrignalLine;
    QVector<GLfloat> colorOfOrignalLine;

    std::vector<float> mVerticess;
    std::vector<float> mColorss;
    float zoomFactor = 1.0f;
    
};
