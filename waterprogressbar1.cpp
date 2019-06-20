#include "waterprogressbar1.h"
#include "ui_waterprogressbar1.h"

WaterProgressBar1::WaterProgressBar1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaterProgressBar1)
{
    ui->setupUi(this);
    PaintTimer = new QTimer();

    connect(PaintTimer,SIGNAL(timeout()),this,SLOT(update()));
    PaintTimer->start(100);
}

WaterProgressBar1::~WaterProgressBar1()
{
    delete ui;
}

void WaterProgressBar1::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//抗锯齿

    qParmInit();
    this->drawWaterProgressBarWiget(&painter);

    drawWaterProgressBarWave(&painter);
    drawWaterProgressBarText(&painter);
}

void WaterProgressBar1::drawWaterProgressBarWiget(QPainter *painter)
{
    drawWaterProgressBarBoard(painter);
}

void WaterProgressBar1::drawWaterProgressBarBoard(QPainter *painter)
{
     painter->save();

     QBrush qBrush = QBrush(QColor(80,80,80));//灰色画刷,设置表盘边缘原色

     painter->setBrush(qBrush);//使用画刷

     painter->drawEllipse(qCircular,qRadius,qRadius);

     painter->restore();
}

void WaterProgressBar1::drawWaterProgressBarWave(QPainter *painter)
{

    painter->save();
    QPainterPath QPainterPaths;

    QPen qPen(QColor(13,235,235));
    qPen.setWidth(1);   //设置画笔的粗细
    painter->setPen(qPen);
    painter->setBrush(QBrush(QColor(13,235,235)));

    if(value > maxvalue)
    {
     value = maxvalue;
    }
    int fAngle = 270 - value * 180 / maxvalue;//值对应的角度关系是90-270

    painter->setRenderHint(QPainter:: Antialiasing, true);  //设置渲染,启动反锯齿

    QPainterPaths.arcMoveTo(qCircular.x() - qRadius ,qCircular.y() - qRadius, 2 * qRadius,
                            2 * qRadius,fAngle);

    QPainterPaths.arcTo(qCircular.x() - qRadius ,qCircular.y() - qRadius, 2 * qRadius,
                         2 * qRadius,fAngle,360 - (fAngle - 90) * 2);       //绘画角度为30°~(30+150°)//绘制曲线部分

    painter->drawPath(QPainterPaths);
    painter->restore();
}

void WaterProgressBar1::drawWaterProgressBarText(QPainter *painter)
{

    painter->save();
    int FontSize = 50;
    QPen qPen = QPen(Qt::white);
    //绘制表盘文字
    QFont qFont("楷体",FontSize,QFont::Bold,false);
    painter->setFont(qFont);
    painter->setPen(qPen);
    QString PercentageStr = QString::number(value);
    PercentageStr.append("%");

    if(value > 9)
    {
        painter->drawText(QRectF(qCircular.x() - FontSize,qCircular.y() - FontSize / 2,
                                FontSize * PercentageStr.length(),FontSize * PercentageStr.length()),
                                  PercentageStr);
    }
    else
    {
     painter->drawText(QRectF(qCircular.x() - FontSize / 2,qCircular.y() - FontSize / 2,
                             FontSize * PercentageStr.length(),FontSize * PercentageStr.length()),
                               PercentageStr);
    }

    painter->restore();
}

void WaterProgressBar1::setvalue(int value)
{
    this->value = value;
}

void WaterProgressBar1::qParmInit()
{
     qCircular = QPoint(width() / 2,height() / 2);//圆心位置刷新
     qRadius = (width() - 5) / 2;
}

