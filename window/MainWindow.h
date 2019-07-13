#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QMainWindow>
#include <QSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QToolBar> 
#include "../view/heatview.h"
#include "ui_MainWindow.h"
#include "sink/MainWindowPropertySink.h"
#include "sink/MainWindowCommandSink.h"
#include "../view/myheader.h"
#include "../view/QtGuiClass.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT

signals:
	void select_function(int function, int shape = LINE, QString path = QString());
public:

	void CreateActions();
	void CreateButtons();
	void CreateSpinBox();
	void closeEvent(QCloseEvent* event);
	bool saved;
	QString filename, filename2;
	QMenu *pMenu;
	QAction *Help, *Line, *Rectangle, *Ellipse, *Polygon, *Delete, *Picture, *Select, *Move, *RotateL, *RotateR, *Amplify, *Shrink, *Random, *Text;
	QAction *New, *Open, *Save, *SaveAs;
	QAction *Generate;
	QToolBar *pToolBar;
	QAction *Property_Normal, *Property_HeatIsulation, *Property_HeatSource;
	QSpinBox *SpinBoxPainterWidth, *SpinBoxPainterColorR, *SpinBoxPainterColorG, *SpinBoxPainterColorB;
	QDoubleSpinBox *SpinBoxTem;
	QtGuiClass *qt_gui_class;
	QSlider *pSliderColorR, *pSliderColorG, *pSliderColorB, *pSliderWidth;
	QAction *LineWidth, *LineColor;
	QAction *Eraser;

private slots:
	void visualize_LineWidthChange();
	void visualize_ColorChange();
	void windowResize(int w, int h);

	void draw_line();
	void draw_random();
	void draw_rectangle();
	void draw_ellipse();
	void draw_polygon();
	void draw_picture();
	void draw_text();

	void RotateL_figure();
	void RotateR_figure();
	void Delete_figure();
	void set_drawshape_to_Default();
	void set_drawshape_to_Move();
	void Amplify_figure();
	void Shrink_figure();
	void set_eraser();
	void set_property_normal();
	void set_property_heatinsulation();
	void set_property_heatsource();
	void help();

	void new_file();
	void open_file();
	void save_file();
	void save_as();


public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void init();
	void set_CalcCommand(const std::shared_ptr<ICommandBase>& cmd) throw();
	std::shared_ptr<IPropertyNotification> get_PropertySink() throw();
	std::shared_ptr<ICommandNotification> get_CommandSink() throw();
	void Transport(CType type, double changeval);

	HeatView *view;

private:
	QTimer *m_timer;
	int count;
	void InitTimer();
	void Updatewb();

	workboard initial_condition;


private:
	std::shared_ptr<ICommandBase> m_cmdCalc;
	std::shared_ptr<MainWindowPropertySink> m_sinkProperty;
	std::shared_ptr<MainWindowCommandSink> m_sinkCommand;
public Q_SLOTS:
	void Generate_HeatView();
	void TimerTimeOut();
private Q_SLOTS:
	void RecieveTime(int val);
private:
	Ui_MainWindowClass *ui;

};

#endif // MAINWINDOW_H
