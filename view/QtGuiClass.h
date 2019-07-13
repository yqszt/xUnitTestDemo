#pragma once

#include <vector>
#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPen>
#include <QStaticText>
#include <QLineEdit>
#include <QTextEdit>
#include "ui_QtGuiClass.h"
#include "myheader.h"
class QtGuiClass : public QWidget
{
	Q_OBJECT

public:
	QtGuiClass(QWidget *parent = Q_NULLPTR);
	~QtGuiClass();

public slots:
	void changeState(int function, int shape, QString path);
	void setPenColor(const QColor &color);
	void setPenSize(const int width);
	void setProperty(_PROPERTY p);
	void setTemperature(double T);
signals:
	void resizeWindow(int w, int h);

private:
	Ui::QtGuiClass ui;

	bool is_equal;
	bool encap;
	int draw_shape;
	int function_state;

	QPoint start_point;
	QPoint end_point;
	QPoint *temp;
	QPixmap *pix;
	QPen *pen;
	_PROPERTY _property;
	double Temperature;
	//QLineEdit *edit;
	QTextEdit *edit;

	std::vector<Figure*> figure_array;
	std::vector<QPoint*> polygon_vertice;

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void paintEvent(QPaintEvent *);

	void drawCurrentFigure(QPainter &painter, QPoint &start, QPoint &end);
	void saveCurrentFigure(const int shape, const QPoint &start, const QPoint &end);
	void drawAllFigure(QPainter &painter, const std::vector<Figure*> &figure_array);

public:
	void RotateL_selected(void);
	void RotateR_selected(void);
	void Delete_selected(void);
	void Amplify_selected(void);
	void Shrink_selected(void);
	void set_selected_color(const QColor &color);
	void set_selected_size(const int width);
	void set_selected_property(_PROPERTY p);
	void set_selected_temperature(double T);
	const std::vector<Figure*>& getFigureArray(void);
};