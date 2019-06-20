#include "dashboard1.h"
#include "ui_dashboard1.h"

Dashboard1::Dashboard1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard1)
{
    ui->setupUi(this);
    PaintTimer = new QTimer();

    connect(PaintTimer,SIGNAL(timeout()),this,SLOT(update()));
    PaintTimer->start(100);
}

Dashboard1::~Dashboard1()
{
    delete ui;
}

void Dashboard1::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
    this->drawDashBoardWiget(&painter);
}

void Dashboard1::qParmInit()
{
    qCircular = QPoint(width() / 2,height() / 2);//圆心位置刷新
    qRadius = (width() / 2);//外圆形的半径
    //qDialDivideSize = (qDialEdgeSize + qDialEdgeSize * 1.5);//刻度盘的大小
}


void Dashboard1::setOtherBackgroud(bool status,QPainter *painter)
{
    if(status == true)
    {
        painter->save();

        painter->setBrush(Qt::transparent);
        painter->fillRect(this->rect(), QColor(0, 0, 0, 0));
        painter->restore();
    }
}
//绘制控件
void Dashboard1::drawDashBoardWiget(QPainter *painter)
{
    //全局参数初始化
    qParmInit();
    setOtherBackgroud(true,painter);
    //绘制表盘
    drawDashBoard(painter);
    //绘制刻度尺
    drawDivideRule(painter);
    //绘制指针
    drawDishBoardPointer(painter);
    //绘制表盘文字
    drawDashBoardText(painter);
}

//绘制仪表盘
void Dashboard1::drawDashBoard(QPainter *painter)
{
    painter->save();

    painter->setBrush(Qt::transparent);
    painter->fillRect(this->rect(), QColor(0, 0, 0, 0));


    QBrush qBrush = QBrush(qDialEdgeColor);//灰色画刷,设置表盘边缘原色

    painter->setBrush(qBrush);//使用画刷

    painter->drawEllipse(qCircular,qRadius,qRadius);//绘制最外层圆盘

    qBrush.setColor(qDialDivideBackgroudColor);//黑色画刷

    painter->setBrush(qBrush);

    painter->drawEllipse(qCircular,qRadius - qDialEdgeSize,qRadius - qDialEdgeSize);//绘制黑色条带

    qBrush.setColor(qDialEdgeColor);//灰色画刷
    painter->setBrush(qBrush);
    painter->drawEllipse(qCircular,qRadius - qDialDivideSize,qRadius - qDialDivideSize);//绘制内层灰色圆盘

    qBrush =  QColor(162,88,88);//粉色画刷
    painter->setBrush(qBrush);
    painter->drawEllipse(qCircular,30,30);//内部最大粉色圆盘


    painter->restore();
}

void Dashboard1::drawDivideRule(QPainter *painter)
{
    painter->save();

    //下面开始绘制刻度，90度的间隔
    //x2 + y2 = r2
    //则圆上任一点为：（x1,y1）
    //x1   =   x0   +   r   *   cos(ao   *   3.14   /180   )
    //y1   =   y0   +   r   *   sin(ao   *   3.14   /180   )


    float fRadius = 0.0;
    //为了对称好看我们一般从逆时针90度位置开始绘制

    QPen qPen(Qt::white);
    qPen.setWidth(2);   //设置画笔的粗细
    painter->setPen(qPen);
    //先绘制左侧


#if 1
    for(int uiLoop = 0;uiLoop < (fMaxDivide * fMinDivide) + 1 ;uiLoop++)
    {
        float fAngle = (BaseAngle + ((float)270 / (fMaxDivide * fMinDivide)) * uiLoop);

        fRadius = (qRadius - 21);

        int x1Start = qCircular.x() + fRadius * cos(fAngle * 3.14 / 180);
        int y1Start = qCircular.y() + fRadius * sin(fAngle * 3.14 / 180);

        if(uiLoop % fMinDivide == 0)
        {

            fRadius = qRadius - qDialDivideSize + 1;
        }
        else
        {
            fRadius = qRadius - (qDialDivideSize / 1.3);
        }
        int x2End = qCircular.x() + fRadius * cos(fAngle * 3.14 / 180);
        int y2End =  qCircular.y() + fRadius * sin(fAngle * 3.14 / 180);

        painter->drawLine(QPoint(x1Start,y1Start),QPoint(x2End,y2End));
    }
#endif
    painter->restore();
}

void Dashboard1::drawDashBoardText(QPainter *painter)
{
    painter->save();

    QPen qPen(Qt::white);
    qPen.setWidth(2);   //设置画笔的粗细
    painter->setPen(qPen);

    //绘制表盘文字
    QFont qFont("楷体",28,QFont::Bold,false);
    painter->setFont(qFont);
    painter->drawText(QRectF(qCircular.x() - 17,qCircular.y() + 85,80,80),QString::number(qValue));
    float fRadius = 0.0;
    //通过公式计算刻度文字的位置信息。
    for(int uiLoop = 0;uiLoop < (fMaxDivide ) + 1 ;uiLoop++)
    {
        int PointeNum = ((fMaxValue / fMaxDivide) * uiLoop);

        float fAngle = (BaseAngle + ((float)270 / (fMaxDivide)) * uiLoop);


        fRadius = (qRadius - 80 - 18);
        fAngle += 4;


        int x1Start = qCircular.x() + fRadius * cos(fAngle * 3.14 / 180);
        int y1Start = qCircular.y() + fRadius * sin(fAngle * 3.14 / 180);

        QFont qFonts("楷体",12,QFont::Bold,false);
        painter->setFont(qFonts);

        painter->drawText(QRectF(x1Start,y1Start,80,80),QString::number((fMaxValue / fMaxDivide) * uiLoop));
    }

    painter->restore();
}

void Dashboard1::drawDishBoardPointer(QPainter *painter)
{
    painter->save();

    QBrush qBrush = QBrush(QColor(Qt::red));

    painter->setBrush(qBrush);


    QPen qPen(Qt::red);
    qPen.setWidth(2);   //设置画笔的粗细
    painter->setPen(qPen);

    float fRadius = 0.0;
    if(qValue > fMaxValue)
    {
        qValue = fMaxValue;
    }

    float fAngle = (BaseAngle + ((float)270 / (fMaxValue)) * qValue);//指针中心角度信息。
    float fRightAngle = fAngle + 90;//右侧角度
    float fLeftAngle = fAngle - 90;//左侧角度

    fRadius = (qRadius - 21);

    int x1Start = qCircular.x() + (qRadius - qDialDivideSize - 3) * cos(fAngle * 3.14 / 180);
    int y1Start = qCircular.y() + (qRadius - qDialDivideSize - 3) * sin(fAngle * 3.14 / 180);


    fRadius = qRadius - (qDialDivideSize / 1.3);

    int x2End = qCircular.x(); //+ fRadius * cos(fAngle * 3.14 / 180);
    int y2End =  qCircular.y(); //+ fRadius * sin(fAngle * 3.14 / 180);

    int x3End = qCircular.x() + 10 * cos(fRightAngle * 3.14 / 180);//过圆心的右侧切点
    int y3End = qCircular.x() + 10 * sin(fRightAngle * 3.14 / 180);

    int x4End = qCircular.x() + 10 * cos(fLeftAngle * 3.14 / 180);//过圆心的左侧切点
    int y4End = qCircular.x() + 10 * sin(fLeftAngle * 3.14 / 180);


    QPointF qTriangle[3] = {QPoint(x1Start,y1Start),QPoint(x3End,y3End),QPoint(x4End,y4End)};

    painter->drawPolygon(qTriangle,3);
    painter->drawEllipse(qCircular,15,15);//内部小粉色圆盘
    painter->restore();
}

void Dashboard1::setValue(int qValue)
{
    this->qValue = qValue;
}

void Dashboard1::setMaxValue(float fMaxValue)
{
    this->fMaxValue = fMaxValue;
}

void Dashboard1::setDashBoardEdgeColor(QColor &qColor)
{
    qDialEdgeColor = qColor;
}

void Dashboard1::setDashDivideBackgroudColor(QColor &qColor)
{
    qDialDivideBackgroudColor = qColor;
}
