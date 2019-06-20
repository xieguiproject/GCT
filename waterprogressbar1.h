#ifndef WATERPROGRESSBAR1_H
#define WATERPROGRESSBAR1_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QtMath>
#include <QTimer>
//*水波进度条*/
namespace Ui {
class WaterProgressBar1;
}

class WaterProgressBar1 : public QWidget
{
    Q_OBJECT

public:
    explicit WaterProgressBar1(QWidget *parent = 0);
    ~WaterProgressBar1();
    void paintEvent(QPaintEvent *event);
     void drawWaterProgressBarWiget(QPainter *painter); //绘制控件
    void drawWaterProgressBarBoard(QPainter *painter); //绘制表盘
    void drawWaterProgressBarWave(QPainter *painter);//绘制水波效果
    void drawWaterProgressBarText(QPainter *painter); //绘制文本
    void setvalue(int value);
    void qParmInit();
private:
    Ui::WaterProgressBar1 *ui;
    QPoint qCircular;               //中心位置
    int  qRadius = 0;//半径
    int value = 10;
    int maxvalue = 100;
    QTimer *PaintTimer;//定时刷新
};

#endif // WATERPROGRESSBAR1_H
