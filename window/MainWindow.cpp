
#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui_MainWindowClass),
	m_sinkProperty(std::make_shared<MainWindowPropertySink>(this)),
	m_sinkCommand(std::make_shared<MainWindowCommandSink>(this))

{
	ui->setupUi(this);
	view = new HeatView;
	init();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::init()
{
	count = 0;
	m_timer = new QTimer(this);
	//定时器触发信号槽
	connect(m_timer, SIGNAL(timeout()), this, SLOT(TimerTimeOut()));
	connect(view, SIGNAL(SendTime(int)), this, SLOT(RecieveTime(int)));

	qt_gui_class = new QtGuiClass(this);
	CreateActions();
	CreateButtons();
	CreateSpinBox();
	setCentralWidget(qt_gui_class);

	//change
	//resize(1024, 768);
	saved = false;
	connect(this, SIGNAL(select_function(int, int, QString)), qt_gui_class, SLOT(changeState(int, int, QString)));
	connect(qt_gui_class, SIGNAL(resizeWindow(int, int)), this, SLOT(windowResize(int, int)));

}

/* * @brief   create buttons in the ToolBar
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::CreateButtons()
{
	//changed
	//create a menu
	pMenu = menuBar()->addMenu(tr("File"));
	pMenu->addAction(New);
	pMenu->addAction(Open);
	pMenu->addAction(Save);
	pMenu->addAction(SaveAs);

	/*pMenu = menuBar()->addMenu(tr("Tool"));
	pMenu->addAction(LineWidth);
	pMenu->addAction(LineColor);
	*/
	pMenu = menuBar()->addMenu(tr("Figure"));
	pMenu->addAction(Line);
	pMenu->addAction(Rectangle);
	pMenu->addAction(Ellipse);
	pMenu->addAction(Polygon);

	pMenu = menuBar()->addMenu(tr("Property"));
	pMenu->addAction(Property_Normal);
	pMenu->addAction(Property_HeatSource);
	pMenu->addAction(Property_HeatIsulation);

	pMenu = menuBar()->addMenu(tr("Help"));
	pMenu->addAction(Help);

	//create a toobar named Bar
	pToolBar = this->addToolBar(tr("Bar"));
	//add actions to Bar
	pToolBar->addAction(Generate);
	pToolBar->addAction(Random);
	//pToolBar->addAction(Eraser);
	pToolBar->addAction(Select);
	pToolBar->addAction(Move);
	pToolBar->addAction(Amplify);
	pToolBar->addAction(Shrink);
	//pToolBar->addAction(RotateL);
	//pToolBar->addAction(RotateR);
	//pToolBar->addAction(Picture);
	//pToolBar->addAction(Text);
	pToolBar->addAction(Delete);
	
}

/* * @brief   create actions
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::CreateActions()
{
	//create New Action, click to create a new file
	New = new QAction(tr("New file"), this);
	New->setShortcut(tr("ctrl+n"));
	connect(New, &QAction::triggered, this, &MainWindow::new_file);

	//create Open Action, click to open a file
	Open = new QAction(tr("Open"), this);
	Open->setShortcut(tr("ctrl+o"));
	connect(Open, &QAction::triggered, this, &MainWindow::open_file);

	//create Save Action, click to save current file
	Save = new QAction( tr("Save"), this);
	Save->setShortcut(tr("ctrl+s"));
	connect(Save, &QAction::triggered, this, &MainWindow::save_file);

	//create SaveAs Action, click to save current file elsewhere or in other format
	SaveAs = new QAction( tr("Save as"), this);
	connect(SaveAs, &QAction::triggered, this, &MainWindow::save_as);

	//create Random Action, click to draw a free line
	Random = new QAction(tr("Random"), this);
	Random->setStatusTip(tr("Draw free lines"));
	connect(Random, &QAction::triggered, this, &MainWindow::draw_random);

	//create Line Action, click to draw a straight line
	Line = new QAction(tr("line"), this);
	Line->setStatusTip(tr("Draw a straight line"));
	connect(Line, &QAction::triggered, this, &MainWindow::draw_line);

	//create Rectangle Action, click to draw a rectangle
	Rectangle = new QAction( tr("Rectangle"), this);
	Rectangle->setStatusTip(tr("Draw a rectangle"));
	connect(Rectangle, &QAction::triggered, this, &MainWindow::draw_rectangle);

	//create Ellipse Action, click to draw an ellipse
	Ellipse = new QAction(tr("Ellipse"), this);
	Ellipse->setStatusTip(tr("Draw an ellipse"));
	connect(Ellipse, &QAction::triggered, this, &MainWindow::draw_ellipse);

	//create Polygon Action, click to draw a polygon
	Polygon = new QAction( tr("Polygon"), this);
	Polygon->setStatusTip(tr("Draw a polygon"));
	connect(Polygon, &QAction::triggered, this, &MainWindow::draw_polygon);

	//create Picture Action, click to draw an external picture
	Picture = new QAction(tr("Picture"), this);
	Picture->setStatusTip(tr("Draw a picture"));
	connect(Picture, &QAction::triggered, this, &MainWindow::draw_picture);

	//create Select Action, click to select several figures
	Select = new QAction(tr("Select"), this);
	Select->setStatusTip(tr("Select figures"));
	connect(Select, &QAction::triggered, this, &MainWindow::set_drawshape_to_Default);

	//create Move Action, click to move the selected figures
	Move = new QAction( tr("Move"), this);
	Move->setStatusTip(tr("Move selected figures"));
	connect(Move, &QAction::triggered, this, &MainWindow::set_drawshape_to_Move);

	//create RotateL Action, click to rotateL the selected figures
	RotateL = new QAction( tr("RotateL"), this);
	RotateL->setStatusTip(tr("Rotate selected figure counterclockwise"));
	connect(RotateL, &QAction::triggered, this, &MainWindow::RotateL_figure);

	//create RotateR Action, click to rotateR the selected figures
	RotateR = new QAction(tr("RotateR"), this);
	RotateR->setStatusTip(tr("Rotate selected figure clockwise"));
	connect(RotateR, &QAction::triggered, this, &MainWindow::RotateR_figure);

	//create RotateR Action, click to amplify the selected figures
	Amplify = new QAction( tr("Amplify"), this);
	Amplify->setStatusTip(tr("Amplify a figure"));
	connect(Amplify, &QAction::triggered, this, &MainWindow::Amplify_figure);

	//create RotateR Action, click to shrink the selected figures
	Shrink = new QAction( tr("Shrink"), this);
	Shrink->setStatusTip(tr("Shrink a figure"));
	connect(Shrink, &QAction::triggered, this, &MainWindow::Shrink_figure);

	//create Delete Action, click to delete the selected figures
	Delete = new QAction(tr("Delete"), this);
	Delete->setStatusTip(tr("Delete selected figure"));
	connect(Delete, &QAction::triggered, this, &MainWindow::Delete_figure);

	//create Help Action, click to offer help, but nothing to provide
	Help = new QAction(tr("Help"), this);
	Help->setStatusTip(tr("Offer help"));
	Help->setShortcut(tr("f1"));
	connect(Help, &QAction::triggered, this, &MainWindow::help);

	//create Text Action, click to input texts
	Text = new QAction( tr("Text"), this);
	Text->setStatusTip(tr("Input texts"));
	connect(Text, &QAction::triggered, this, &MainWindow::draw_text);

	//create LineWidth Action, click to change line width
	LineWidth = new QAction( tr("LineWidth"), this);
	LineWidth->setStatusTip(tr("Set line width"));
	connect(LineWidth, &QAction::triggered, this, &MainWindow::visualize_LineWidthChange);

	//create LineColor Action, click to change line color
	LineColor = new QAction( tr("LineColor"), this);
	LineColor->setStatusTip(tr("Set line color"));
	connect(LineColor, &QAction::triggered, this, &MainWindow::visualize_ColorChange);

	//create Eraser Action, click to use eraser
	Eraser = new QAction(tr("Eraser"), this);
	Eraser->setStatusTip(tr("Set eraser"));
	connect(Eraser, &QAction::triggered, this, &MainWindow::set_eraser);

	//create Generate Action, click to Generate
	Generate = new QAction(tr("Generate"), this);
	Generate->setStatusTip("Generate Heatdim");
	connect(Generate, &QAction::triggered, this, &MainWindow::Generate_HeatView);

	//new
	Property_Normal = new QAction(tr("Normal"), this);
	Property_Normal->setStatusTip("NORMAL");
	connect(Property_Normal, &QAction::triggered, this, &MainWindow::set_property_normal);
	Property_HeatSource = new QAction(tr("HeatSource"), this);
	Property_HeatSource->setStatusTip("HEATSOURCE");
	connect(Property_HeatSource, &QAction::triggered, this, &MainWindow::set_property_heatsource);
	Property_HeatIsulation = new QAction(tr("HeatInsulation"), this);
	Property_HeatIsulation->setStatusTip("HEATINSULATION");
	connect(Property_HeatIsulation, &QAction::triggered, this, &MainWindow::set_property_heatinsulation);
	
}

/* * @brief   create spinbox
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::CreateSpinBox() {
	SpinBoxTem = new QDoubleSpinBox(this);
	SpinBoxTem->setFixedWidth(70);
	SpinBoxTem->setFixedHeight(20);
	SpinBoxTem->unsetCursor();
	SpinBoxTem->setRange(0, 10000);
	SpinBoxTem->setSingleStep(10);
	SpinBoxTem->setDecimals(2);
	SpinBoxTem->setValue(293);
	SpinBoxTem->setSuffix("K");
	SpinBoxTem->setWrapping(true);
	SpinBoxTem->setGeometry(0, 50, 70, 20);
	//connect spinbox to its working function
	connect(SpinBoxTem, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		[=](double value) {
		qt_gui_class->setTemperature(value - 273.0);
		qt_gui_class->set_selected_temperature(value - 273.0);
	});

	int start = 320;
	//create a spinbox to represent and change the width
	SpinBoxPainterWidth = new QSpinBox(this);
	//set the size of spinbox
	SpinBoxPainterWidth->setFixedWidth(70);
	SpinBoxPainterWidth->setFixedHeight(40);
	SpinBoxPainterWidth->unsetCursor();
	//set range and single step of width
	SpinBoxPainterWidth->setRange(1, 10);
	SpinBoxPainterWidth->setSingleStep(1);
	//set initial value
	SpinBoxPainterWidth->setValue(3);
	SpinBoxPainterWidth->setWrapping(true);
	//set position
	SpinBoxPainterWidth->setGeometry(start, 0, 50, 40);
	//connect spinbox to its working function
	connect(SpinBoxPainterWidth, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		[=](int value) {
		qt_gui_class->setPenSize(value);
		qt_gui_class->set_selected_size(value);
	});

	//create a spinbox to represent and change the color R
	SpinBoxPainterColorR = new QSpinBox(this);
	SpinBoxPainterColorR->setFixedWidth(70);
	SpinBoxPainterColorR->setFixedHeight(40);
	SpinBoxPainterColorR->unsetCursor();
	SpinBoxPainterColorR->setRange(0, 255);
	SpinBoxPainterColorR->setSingleStep(1);
	SpinBoxPainterColorR->setValue(0);
	SpinBoxPainterColorR->setSuffix("R");
	SpinBoxPainterColorR->setWrapping(true);
	SpinBoxPainterColorR->setGeometry(start, 0, 70, 40);

	//create a spinbox to represent and change the color G
	SpinBoxPainterColorG = new QSpinBox(this);
	SpinBoxPainterColorG->setFixedWidth(70);
	SpinBoxPainterColorG->setFixedHeight(40);
	SpinBoxPainterColorG->unsetCursor();
	SpinBoxPainterColorG->setRange(0, 255);
	SpinBoxPainterColorG->setSingleStep(1);
	SpinBoxPainterColorG->setValue(0);
	SpinBoxPainterColorG->setSuffix("G");
	SpinBoxPainterColorG->setWrapping(true);
	SpinBoxPainterColorG->setGeometry(start + 160, 0, 70, 40);

	//create a spinbox to represent and change the color B
	SpinBoxPainterColorB = new QSpinBox(this);
	SpinBoxPainterColorB->setFixedWidth(70);
	SpinBoxPainterColorB->setFixedHeight(40);
	SpinBoxPainterColorB->unsetCursor();
	SpinBoxPainterColorB->setRange(0, 255);
	SpinBoxPainterColorB->setSingleStep(1);
	SpinBoxPainterColorB->setValue(0);
	SpinBoxPainterColorB->setSuffix("B");
	SpinBoxPainterColorB->setWrapping(true);
	SpinBoxPainterColorB->setGeometry(start + 320, 0, 70, 40);

	//connect spinbox ColorR to its working function
	connect(SpinBoxPainterColorR, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		[=](int value) {
		qt_gui_class->setPenColor(QColor(SpinBoxPainterColorR->value(),
			SpinBoxPainterColorG->value(), SpinBoxPainterColorB->value()));
		qt_gui_class->set_selected_color(QColor(SpinBoxPainterColorR->value(),
			SpinBoxPainterColorG->value(), SpinBoxPainterColorB->value()));
	});

	//connect spinbox ColorG to its working function
	connect(SpinBoxPainterColorG, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		[=](int value) {
		qt_gui_class->setPenColor(QColor(SpinBoxPainterColorR->value(),
			SpinBoxPainterColorG->value(), SpinBoxPainterColorB->value()));
		qt_gui_class->set_selected_color(QColor(SpinBoxPainterColorR->value(),
			SpinBoxPainterColorG->value(), SpinBoxPainterColorB->value()));
	});

	//connect spinbox ColorB to its working function
	connect(SpinBoxPainterColorB, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		[=](int value) {
		qt_gui_class->setPenColor(QColor(SpinBoxPainterColorR->value(),
			SpinBoxPainterColorG->value(), SpinBoxPainterColorB->value()));
		qt_gui_class->set_selected_color(QColor(SpinBoxPainterColorR->value(),
			SpinBoxPainterColorG->value(), SpinBoxPainterColorB->value()));
	});

	SpinBoxPainterWidth->setVisible(false);
	SpinBoxPainterColorR->setVisible(false);
	SpinBoxPainterColorG->setVisible(false);
	SpinBoxPainterColorB->setVisible(false);
	//new
	pSliderColorR = new QSlider(this);
	pSliderColorR->setOrientation(Qt::Horizontal);  
	pSliderColorR->setMinimum(0);  
	pSliderColorR->setMaximum(255);  
	pSliderColorR->setSingleStep(1);  
	pSliderColorR->setGeometry(SpinBoxPainterColorR->geometry().x()
		+ SpinBoxPainterColorR->geometry().width(), 0, 90, 40);

	
	connect(SpinBoxPainterColorR, SIGNAL(valueChanged(int)), pSliderColorR, SLOT(setValue(int)));
	connect(pSliderColorR, SIGNAL(valueChanged(int)), SpinBoxPainterColorR, SLOT(setValue(int)));
	pSliderColorR->setVisible(false);

	pSliderColorG = new QSlider(this);
	pSliderColorG->setOrientation(Qt::Horizontal);  
	pSliderColorG->setMinimum(0);  
	pSliderColorG->setMaximum(255);  
	pSliderColorG->setSingleStep(1); 
	pSliderColorG->setGeometry(SpinBoxPainterColorG->geometry().x()
		+ SpinBoxPainterColorG->geometry().width(), 0, 90, 40);

	// 
	connect(SpinBoxPainterColorG, SIGNAL(valueChanged(int)), pSliderColorG, SLOT(setValue(int)));
	connect(pSliderColorG, SIGNAL(valueChanged(int)), SpinBoxPainterColorG, SLOT(setValue(int)));
	pSliderColorG->setVisible(false);
	//
		//new
	pSliderColorB = new QSlider(this);
	pSliderColorB->setOrientation(Qt::Horizontal);  
	pSliderColorB->setMinimum(0);  
	pSliderColorB->setMaximum(255);  
	pSliderColorB->setSingleStep(1); 
	pSliderColorB->setGeometry(SpinBoxPainterColorB->geometry().x()
		+ SpinBoxPainterColorB->geometry().width(), 0, 90, 40);

	
	connect(SpinBoxPainterColorB, SIGNAL(valueChanged(int)), pSliderColorB, SLOT(setValue(int)));
	connect(pSliderColorB, SIGNAL(valueChanged(int)), SpinBoxPainterColorB, SLOT(setValue(int)));
	pSliderColorB->setVisible(false);
	//
		//new
	pSliderWidth = new QSlider(this);
	pSliderWidth->setOrientation(Qt::Horizontal); 
	pSliderWidth->setMinimum(1);  
	pSliderWidth->setMaximum(10);  
	pSliderWidth->setSingleStep(1);  
	pSliderWidth->setValue(3);
	pSliderWidth->setGeometry(SpinBoxPainterWidth->geometry().x()
		+ SpinBoxPainterWidth->geometry().width(), 0, 100, 40);

	connect(SpinBoxPainterWidth, SIGNAL(valueChanged(int)), pSliderWidth, SLOT(setValue(int)));
	connect(pSliderWidth, SIGNAL(valueChanged(int)), SpinBoxPainterWidth, SLOT(setValue(int)));
	pSliderWidth->setVisible(false);
	//
}

/* * @brief    prepare to draw line
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::draw_line()
{
	emit select_function(WAIT, LINE);
}

/* * @brief    draw free lines
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::draw_random()
{
	emit select_function(WAIT, RANDOM);
}

/* * @brief    prepare to draw rectangle
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::draw_rectangle()
{
	emit select_function(WAIT, RECTANGLE);
}

/* * @brief    prepare to draw ellipse
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::draw_ellipse()
{
	emit select_function(WAIT, ELLIPSE);
}

/* * @brief    prepare to draw polygon
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::draw_polygon()
{
	emit select_function(WAIT, POLYGON);
}

/* * @brief    prepare to draw external picture
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::draw_picture() {
	//pop out a window and request a path
	QString filename;
	filename = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Images (*.png *.jpg *.bmp)"));
	if (!filename.isEmpty()) {
		emit select_function(DRAWING, PIXMAP, filename);
	}
}

/* * @brief    rotateL the selected figure
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::RotateL_figure() {
	emit select_function(ROTATE_LEFT);
}

/* * @brief    rotateR the selected figure
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::RotateR_figure() {
	emit select_function(ROTATE_RIGHT);
}

/* * @brief    delete the selected figure
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::Delete_figure() {
	emit select_function(DELETEIT);
}

/* * @brief    prepare for frame selection
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::set_drawshape_to_Default() {
	emit select_function(DEFAULT);
}

/* * @brief    prepare to move the selected figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::set_drawshape_to_Move() {
	emit select_function(MOVE);
}

/* * @brief    amplify the selected figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::Amplify_figure() {
	emit select_function(AMPLIFY);
}

/* * @brief    shrink the selected figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::Shrink_figure() {
	emit select_function(SHRINK);
}

/* * @brief    draw text on the picture
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::draw_text()
{
	emit select_function(WAIT, TEXT);
}

/* * @brief    erase figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::set_eraser() {
	emit select_function(WAIT, ERASE);
}

void MainWindow::set_property_normal() {
	qt_gui_class->setProperty(NORMAL);
	qt_gui_class->set_selected_property(NORMAL);
}

void MainWindow::set_property_heatinsulation(){
	qt_gui_class->setProperty(HEATINSULATION);
	qt_gui_class->set_selected_property(HEATINSULATION);
}

void MainWindow::set_property_heatsource(){
	qt_gui_class->setProperty(HEATSOURCE);
	qt_gui_class->set_selected_property(HEATSOURCE);
}


/* * @brief    open a window to offer help
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::help()
{
	QString helptext1("1. Press left button to draw free lines.\n2. Single click to draw a figure and click again to finish.\n3. Click right button to abort drawing a figure.\n4. Press Ctrl key to draw squares or circles when drawing a rectangle or ellipse.\n");
	QString helptext2("5. Click on the edge of a figure to select.\n6. Rotate 15 degrees each time.\n7. Press Delete key or select Delete to remove a figure.\n");
	QString helptext3("8. Text cannot be modified after exiting edit mode\n9. Color and width change applied after unselected\n");
	QMessageBox box(QMessageBox::Information, "Help", helptext1 + helptext2 + helptext3, QMessageBox::Ok);
	box.exec();
}

/* * @brief    create a new file
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::new_file()
{
	//prompt the user to save the picture
	QMessageBox box(QMessageBox::Question, tr("Save"), tr("Do you want to save the picture?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

	switch (box.exec()) {
	case QMessageBox::Yes:
		if (saved) {
			//save the picture and clear the canvas
			emit select_function(SAVE, PIXMAP, filename);
			emit select_function(NEW);
		}
		else {
			this->filename = QFileDialog::getSaveFileName(this, tr("Save"), "untitled.png", tr("*.png;; *.bmp;; *.jpg"));
			if (!filename.isEmpty()) {
				emit select_function(SAVE, PIXMAP, filename);
				emit select_function(NEW);
			}
		}
		break;
	case QMessageBox::No:
		emit select_function(NEW);
		break;
	default:
		break;
	}
}

/* * @brief    open a file
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::open_file()
{
	this->filename2 = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Images (*.png *.jpg *.bmp)"));
	if (!filename2.isEmpty()) {
		//prompt the user to save the picture
		QMessageBox box(QMessageBox::Question, tr("Save"), tr("Do you want to save the picture?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		switch (box.exec()) {
		case QMessageBox::Yes:
			if (saved) {
				emit select_function(SAVE, PIXMAP, filename);
				this->filename = this->filename2;
				emit select_function(OPEN, PIXMAP, filename2);
			}
			else {
				this->filename = QFileDialog::getSaveFileName(this, tr("Save"), "untitled.png", tr("*.png;; *.bmp;; *.jpg"));
				if (!filename.isEmpty()) {
					emit select_function(SAVE, PIXMAP, filename);
					this->filename = this->filename2;
					emit select_function(OPEN, PIXMAP, filename2);
				}
			}
			break;
		case QMessageBox::No:
			this->filename = this->filename2;
			emit select_function(OPEN, PIXMAP, filename2);
			break;
		default:
			break;
		}
	}
}

/* * @brief    save current file
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::save_file()
{
	if (saved) {
		//if the user has selected the save path
		emit select_function(SAVE, PIXMAP, filename);
	}
	else {
		//if the user hasn't selected the path, prompt the user to choose a path
		this->filename = QFileDialog::getSaveFileName(this, tr("Save"), "untitled.png", tr("*.png;; *.bmp;; *.jpg"));
		if (!filename.isEmpty()) {
			emit select_function(SAVE, PIXMAP, filename);
			saved = true;
		}
	}
}

/* * @brief    save as another file
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::save_as()
{
	QString filename3 = QFileDialog::getSaveFileName(this, tr("Save"), "untitled.png", tr("*.png;; *.bmp;; *.jpg"));
	if (!filename3.isEmpty()) {
		emit select_function(SAVE, PIXMAP, filename3);
	}
}

/* * @brief    visualize linewidth change
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::visualize_LineWidthChange()
{
	pSliderWidth->setVisible(true);
	SpinBoxPainterWidth->setVisible(true);

	pSliderColorR->setVisible(false);
	SpinBoxPainterColorR->setVisible(false);
	pSliderColorG->setVisible(false);
	SpinBoxPainterColorG->setVisible(false);
	pSliderColorB->setVisible(false);
	SpinBoxPainterColorB->setVisible(false);
}

/* * @brief    visualize color change
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::visualize_ColorChange()
{
	pSliderWidth->setVisible(false);
	SpinBoxPainterWidth->setVisible(false);

	pSliderColorR->setVisible(true);
	SpinBoxPainterColorR->setVisible(true);
	pSliderColorG->setVisible(true);
	SpinBoxPainterColorG->setVisible(true);
	pSliderColorB->setVisible(true);
	SpinBoxPainterColorB->setVisible(true);
}

/* * @brief    actions when the user is closing the main window
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::closeEvent(QCloseEvent* event)
{
	//if the user is closing the main window
	//stop the closing action and prompt the user to save
	QMessageBox box(QMessageBox::Question, tr("Save"), tr("Do you want to save the picture?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

	switch (box.exec()) {
	case QMessageBox::Yes:
		if (saved) {
			emit select_function(SAVE, PIXMAP, filename);
		}
		else {
			this->filename = QFileDialog::getSaveFileName(this, tr("Save"), "untitled.png", tr("*.png;; *.bmp;; *.jpg"));
			if (!filename.isEmpty()) {
				emit select_function(SAVE, PIXMAP, filename);
			}
			else {
				event->ignore();
			}
		}
		break;
	case QMessageBox::No:
		event->accept();
		break;
	case QMessageBox::Cancel:
		event->ignore();
		break;
	default:
		event->ignore();
	}
}

/* * @brief    resize the window
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void MainWindow::windowResize(int w, int h)
{
	resize(w, h);
}


void MainWindow::RecieveTime(int val) {
	Transport(TIME, val*0.05);
}

void MainWindow::Generate_HeatView()
{
	connect(view, SIGNAL(SendTime(int)), this, SLOT(RecieveTime(int)));
	Updatewb();
	view->show();
	//InitTimer();
}


void MainWindow::Updatewb()
{
	const std::vector<Figure*>& figure_array = qt_gui_class->getFigureArray();
	if (figure_array.size() > 0) {
		std::vector<std::vector<point> > A;
		initial_condition.getPointMat(A);
		int size = initial_condition.getSize();
		int sedge = this->frameGeometry().width() / size;
		for (int pos = 0;pos < size*size;pos++) {
			A[pos%size][pos / size].setTemperature(0.0);
			A[pos%size][pos / size].setProperty(NORMAL);
			for (size_t i = 0; i < figure_array.size(); i++) {
				if (figure_array[i]->is_in_figure(QPoint((pos / size)*sedge, (pos%size)*sedge))) {
					A[pos%size][pos / size].setTemperature(figure_array[i]->get_temperature());
					A[pos%size][pos / size].setProperty(figure_array[i]->get_property());
				}
			}
		}
		initial_condition = A;
		Transport(INITIALCOND, 0.0);
	}

}

void MainWindow::set_CalcCommand(const std::shared_ptr<ICommandBase>& cmd) throw()
{
	m_cmdCalc = cmd;
}

std::shared_ptr<IPropertyNotification> MainWindow::get_PropertySink() throw()
{
	return std::static_pointer_cast<IPropertyNotification>(m_sinkProperty);
}

std::shared_ptr<ICommandNotification> MainWindow::get_CommandSink() throw()
{
	return std::static_pointer_cast<ICommandNotification>(m_sinkCommand);
}

void MainWindow::InitTimer()
{

	count = 0;
	m_timer->start(50);

}

void MainWindow::TimerTimeOut()
{
	if (count == 400) {
		m_timer->stop();
		return;
	}
	count++;

	Transport(TIME, count*0.05);

}

void MainWindow::Transport(CType type, double changeval) {
	std::any param(std::make_any<workboardPass>());
	workboardPass& wbp = std::any_cast<workboardPass&>(param);
	wbp.setChangeType(type);
	wbp.setChangeValue(changeval);
	wbp.setWorkBoard(initial_condition);
	
	m_cmdCalc->SetParameter(param);
	m_cmdCalc->Exec();
}
