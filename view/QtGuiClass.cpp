#include "QtGuiClass.h"

/* * @brief   initialize the QtGui class
	* @param [in]  QWidget *parent
	* @param [out] void
	* @return      void
*/
QtGuiClass::QtGuiClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//we don't draw anything at the beginning
	is_equal = false;
	encap = false;
	figure_array.clear();
	polygon_vertice.clear();
	draw_shape = LINE;
	function_state = DEFAULT;
	_property = NORMAL;
	Temperature = 20.0;
	setMouseTracking(true);
	setPalette(QPalette(Qt::white));
	setAutoFillBackground(true);

	/*
		initialize pen
		color: black
		width: 3
	*/
	pen = new QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin);
	//make sure keyboard actions are recorded
	this->grabKeyboard();
}

QtGuiClass::~QtGuiClass()
{
	for (size_t i = 0; i < polygon_vertice.size(); i++)
	{
		if (polygon_vertice[i])
		{
			delete polygon_vertice[i];
			polygon_vertice[i] = NULL;
		}
	}
	for (size_t i = 0; i < figure_array.size(); i++)
	{
		if (figure_array[i])
		{
			delete figure_array[i];
			figure_array[i] = NULL;
		}
	}
	delete pen;
}

/* * @brief   change the draw_shape
	* @param [in]  int shape: the shape waiting to draw
	* @param [in]  char* path: the path of external picture. used only when shape equals to PIXMAP
	* @param [out] void
	* @return      void
*/
void QtGuiClass::changeState(int function, int shape, QString path)
{
	function_state = function;
	switch (function) {
	case DEFAULT:
		break;
	case WAIT:
		draw_shape = shape;
		break;
	case DRAWING:
		draw_shape = shape;
		if (shape == PIXMAP) {
			pix = new QPixmap;
			pix->load(path);
		}
		break;
	case ROTATE_LEFT:
		RotateL_selected();
		break;
	case ROTATE_RIGHT:
		RotateR_selected();
		break;
	case DELETEIT:
		Delete_selected();
		break;
	case AMPLIFY:
		Amplify_selected();
		break;
	case SHRINK:
		Shrink_selected();
		break;
	case SAVE:
		//changed
	{
		for (int i = 0; i < figure_array.size(); i++) {
			figure_array[i]->is_selected = false;
		}
		update();
		QPixmap pic = this->grab(QRect(0, 0, this->width(), this->height()));
		pic.save(path);
	}
	break;
	case NEW:
		for (int i = 0; i < figure_array.size(); i++) {
			delete figure_array[i];
		}
		figure_array.clear();
		polygon_vertice.clear();
		emit resizeWindow(1024, 768);
		break;
	case OPEN:
		for (int i = 0; i < figure_array.size(); i++) {
			delete figure_array[i];
		}
		figure_array.clear();
		polygon_vertice.clear();
		pix = new QPixmap;
		pix->load(path);
		function_state = DEFAULT;
		emit resizeWindow(pix->width(), pix->height() + 75);
		saveCurrentFigure(PIXMAP, QPoint(0, 0), QPoint(0, 0));
		update();
		break;
	}
}

/* * @brief   set global pen color
	* @param [in]  const QColor &color: new color
	* @param [out] void
	* @return      void
*/
void QtGuiClass::setPenColor(const QColor &color)
{
	pen->setColor(color);
}

/* * @brief   set global pen size
	* @param [in]  const int width: new width
	* @param [out] void
	* @return      void
*/
void QtGuiClass::setPenSize(const int width)
{
	pen->setWidth(width);
}

void QtGuiClass::setProperty(_PROPERTY p) {
	_property = p;
}

void QtGuiClass::setTemperature(double T) {
	Temperature = T;
}

/* * @brief   to deal with mouse press event
	* @param [in]  QMouseEvent *event: mouse event
	* @param [out] void
	* @return      void
*/
void QtGuiClass::mousePressEvent(QMouseEvent *event)
{
	switch (event->button()) {
	case Qt::LeftButton:
		switch (function_state) {
		case WAIT:
			//waiting to draw
			start_point = end_point = event->pos();
			function_state = DRAWING;
			if (draw_shape == POLYGON || draw_shape == RANDOM || draw_shape == ERASE) {
				temp = new QPoint(event->pos());
				polygon_vertice.push_back(temp);
			}
			else if (draw_shape == TEXT) {
				edit = new QTextEdit(this);
				edit->setGeometry(event->x(), event->y(), 200, 50);
				QPalette pl = edit->palette();
				pl.setBrush(QPalette::Base, QBrush(QColor(255, 255, 255, 0)));
				edit->setPalette(pl);
				edit->show();
				edit->setFocus();
				edit->grabKeyboard();
				function_state = TEXTING;
			}
			break;
		case DEFAULT:
		{
			bool selected = false;
			if (!figure_array.empty()) {
				//click to select one figure
				//initialize, reset selected status
				for (int i = 0; i < figure_array.size(); i++) {
					figure_array[i]->is_selected = false;
				}
				int i = 0;
				while (i < figure_array.size()) {
					if (figure_array[i]->selected(event->pos())) {
						//find the selected figure
						figure_array[i]->is_selected = true;
						selected = true;
						break;
					}
					i++;
				}
			}
			if (!selected) {
				start_point = end_point = event->pos();
				function_state = SELECTING;
			}
		}
		break;
		case DRAWING:
			//is drawing, and click second time to finish the drawing
			switch (draw_shape) {
			case RECTANGLE:
				//reset function state to DEFAULT to stop continuing drawing
				function_state = DEFAULT;
				//save completed figure
				saveCurrentFigure(draw_shape, start_point, end_point);
				break;
			case ELLIPSE:
				//reset function state to DEFAULT to stop continuing drawing
				function_state = DEFAULT;
				//save completed figure
				saveCurrentFigure(draw_shape, start_point, end_point);
				break;
			case LINE:
				//save completed figure
				saveCurrentFigure(draw_shape, start_point, end_point);
				start_point = end_point = event->pos();
				break;
			case POLYGON:
				if (encap) {
					//the last point meets the first
					//reset function state to DEFAULT to stop continuing drawing
					function_state = DEFAULT;
					//save completed figure
					saveCurrentFigure(draw_shape, start_point, end_point);
				}
				else {
					//continue drawing the next edge
					temp = new QPoint(event->pos());
					polygon_vertice.push_back(temp);
					start_point = end_point = event->pos();
				}
				break;
			case PIXMAP:
				//reset function state to DEFAULT to stop continuing drawing
				function_state = DEFAULT;
				//save completed figure
				saveCurrentFigure(draw_shape, event->pos(), event->pos());
				break;
			}
			break;
		case MOVE:
			start_point = end_point = event->pos();
			function_state = MOVING;
			break;
		case TEXTING:
			if (event->x() < edit->x() || event->x() > edit->x() + edit->width() || event->y() > edit->y() + edit->height() || event->y() < edit->y()) {
				edit->clearFocus();
				edit->setStyleSheet(tr("border: none"));
				edit->setReadOnly(true);
				edit->releaseKeyboard();
				edit->releaseMouse();
				Figure *figure = new Text(edit);
				figure_array.push_back(figure);
				function_state = DEFAULT;
			}
			break;
		}
		break;
	case Qt::RightButton:
		switch (function_state) {
		case DRAWING:
			//reset function state to DEFAULT to stop continuing drawing
			function_state = DEFAULT;
			//to release the space storing polygon
			if (draw_shape == POLYGON) {
				for (size_t i = 0; i < polygon_vertice.size(); i++) {
					if (polygon_vertice[i])
						delete polygon_vertice[i];
				}
				polygon_vertice.clear();
			}
			break;
		}
		break;
	default:
		break;
	}
	update();
}

/* * @brief   to deal with mouse move event
	* @param [in]  QMouseEvent *event: mouse event
	* @param [out] void
	* @return      void
*/
void QtGuiClass::mouseMoveEvent(QMouseEvent *event)
{
	end_point = event->pos();
	switch (function_state) {
	case DRAWING:
		if (draw_shape == POLYGON) {
			QPoint vec(*(polygon_vertice[0]) - event->pos());
			double dist = vectorLength(vec);
			//to judge whether joint head and tail
			if (dist < 8.0)
				encap = true;
			else
				encap = false;
		}
		else if (draw_shape == RANDOM || draw_shape == ERASE) {
			temp = new QPoint(event->pos());
			polygon_vertice.push_back(temp);
			start_point = end_point = event->pos();
		}
		update();
		break;
	case MOVING:
		for (size_t i = 0; i < figure_array.size(); i++) {
			if (figure_array[i]->is_selected) {
				//update moving param
				if (figure_array[i]->type == TEXT) {
					Text *t = dynamic_cast<Text*>(figure_array[i]);
					t->line->setGeometry(t->old_x + event->x() - start_point.x(), t->old_y + event->y() - start_point.y(), t->line->width(), t->line->height());
					figure_array[i]->set_move_point(start_point, end_point);
				}
				else
					figure_array[i]->set_move_point(start_point, end_point);
			}
		}
		update();
		break;
	case SELECTING:
	{
		//initialize
		for (int i = 0; i < figure_array.size(); i++) {
			figure_array[i]->is_selected = false;
		}
		//judge every figure
		for (int i = 0; i < figure_array.size(); i++) {
			figure_array[i]->is_selected = figure_array[i]->is_in_it(start_point, end_point);
		}
		update();
	}
	break;
	}
}

/* * @brief   to deal with mouse release event
	* @param [in]  QMouseEvent *event: mouse event
	* @param [out] void
	* @return      void
*/
void QtGuiClass::mouseReleaseEvent(QMouseEvent *event)
{
	switch (event->button()) {
	case Qt::LeftButton:
		switch (function_state) {
		case SELECTING:
			//reset function state to DEFAULT to stop frame selection
			function_state = DEFAULT;
			break;
		case MOVING:
			//finish moving and update position of moved figures
			for (int i = 0; i < figure_array.size(); i++) {
				figure_array[i]->clear_move_point();
			}
			function_state = DEFAULT;
			break;
		case DRAWING:
			if (draw_shape == RANDOM || draw_shape == ERASE) {
				saveCurrentFigure(draw_shape, start_point, end_point);
				function_state = WAIT;
			}
			break;
		}
	}
	update();
}

/* * @brief   to deal with keyboard press event
	* @param [in]  QKeyEvent *event: keyboard event
	* @param [out] void
	* @return      void
*/
void QtGuiClass::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Control:
		//rectangle -> square, ellipse   -> circle
		is_equal = true;
		break;
	case Qt::Key_Delete:
		Delete_selected();
		break;
	case Qt::Key_Escape:
		switch (function_state) {
		case MOVING:
			//finish moving and update position of moved figures
			for (int i = 0; i < figure_array.size(); i++) {
				figure_array[i]->clear_move_point();
			}
			function_state = DEFAULT;
			break;
		}
	}
	update();
}

/* * @brief   to deal with keyboard release event
	* @param [in]  QKeyEvent *event: keyboard event
	* @param [out] void
	* @return      void
*/
void QtGuiClass::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Control:
		is_equal = false;
		break;
	}
	update();
}

/* * @brief   draw current figure
	* @param [in]  QPainter &painter: painter
	* @param [in]  QPoint &start	: start point of mouse
	* @param [in]  QPoint &end      : end point of mouse
	* @param [out] void
	* @return      void
*/
void QtGuiClass::drawCurrentFigure(QPainter &painter, QPoint &start, QPoint &end)
{
	switch (draw_shape) {
	case LINE:
		//draw current line
		painter.drawLine(start_point, end_point);
		break;
	case RECTANGLE:
		if (is_equal)
			//draw current square
			painter.drawRect(start_point.rx(), start_point.ry(), end_point.rx() - start_point.rx(), end_point.rx() - start_point.rx());
		else
			//draw current rectangle
			painter.drawRect(start_point.rx(), start_point.ry(), end_point.rx() - start_point.rx(), end_point.ry() - start_point.ry());
		break;
	case ELLIPSE:
		if (is_equal)
			//draw current circle
			painter.drawEllipse(start_point, end_point.rx() - start_point.rx(), end_point.rx() - start_point.rx());
		else
			//draw current ellipse
			painter.drawEllipse(start_point, end_point.rx() - start_point.rx(), end_point.ry() - start_point.ry());
		break;
	case POLYGON:
		//draw current polygon
		//connect every vertice
		for (size_t i = 0; i < polygon_vertice.size() - 1; i++) {
			painter.drawLine(*(polygon_vertice[i]), *(polygon_vertice[i + 1]));
		}
		//connect the last point and mouse position
		painter.drawLine(*(polygon_vertice.back()), end_point);

		if (encap) {
			painter.setPen(QPen(Qt::blue, 1));
			painter.drawEllipse(*(polygon_vertice[0]), 10, 10);
		}
		break;
	case PIXMAP:
		//draw current pixmap
		painter.drawPixmap(end, *pix);
		break;
	case RANDOM:
		for (size_t i = 0; i < polygon_vertice.size() - 1; i++) {
			painter.drawLine(*(polygon_vertice[i]), *(polygon_vertice[i + 1]));
		}
		break;
	case ERASE:
		painter.setPen(QPen(Qt::white, pen->width()));
		for (size_t i = 0; i < polygon_vertice.size() - 1; i++) {
			painter.drawLine(*(polygon_vertice[i]), *(polygon_vertice[i + 1]));
		}
		break;
	}
}

/* * @brief   push current figure to figure_array
	* @param [in]  const int shape  : shape of current figure
	* @param [in]  QPoint &start	: start point of mouse
	* @param [in]  QPoint &end      : end point of mouse
	* @param [out] void
	* @return      void
*/
void QtGuiClass::saveCurrentFigure(const int shape, const QPoint &start, const QPoint &end)
{
	Figure *figure = NULL;
	switch (shape) {
	case LINE:
		//new a line
		figure = new Line(start_point, end_point, *pen);
		break;
	case RECTANGLE:
		if (is_equal)
			//new a square
			figure = new Rectangle(start_point.rx(), start_point.ry(), end_point.rx() - start_point.rx(), end_point.rx() - start_point.rx(), *pen);
		else
			//new a rectangle
			figure = new Rectangle(start_point.rx(), start_point.ry(), end_point.rx() - start_point.rx(), end_point.ry() - start_point.ry(), *pen);
		break;
	case ELLIPSE:
		if (is_equal)
			//new a circle
			figure = new Ellipse(start_point, end_point.rx() - start_point.rx(), end_point.rx() - start_point.rx(), *pen);
		else
			//new a ellipse
			figure = new Ellipse(start_point, end_point.rx() - start_point.rx(), end_point.ry() - start_point.ry(), *pen);
		break;
	case POLYGON:
		if (polygon_vertice.size() >= 3)
			//new a polygon of which edge number is more than 3
			figure = new Polygon(polygon_vertice, polygon_vertice.size(), *pen);
		for (size_t i = 0; i < polygon_vertice.size(); i++) {
			delete polygon_vertice[i];
		}
		polygon_vertice.clear();
		break;
	case PIXMAP:
		//new a pixmap(external picture)
	{
		int ax = start.x();
		int ay = start.y();
		figure = new Pixmap(pix, ax, ay);
	}
	break;
	case RANDOM:
		if (polygon_vertice.size() >= 3)
			//new a polygon of which edge number is more than 3
			figure = new Random(polygon_vertice, polygon_vertice.size(), *pen);
		for (size_t i = 0; i < polygon_vertice.size(); i++) {
			delete polygon_vertice[i];
		}
		polygon_vertice.clear();
		break;
	case ERASE:
		if (polygon_vertice.size() >= 3)
			//new a polygon of which edge number is more than 3
			figure = new Erase(polygon_vertice, polygon_vertice.size(), *pen);
		for (size_t i = 0; i < polygon_vertice.size(); i++) {
			delete polygon_vertice[i];
		}
		polygon_vertice.clear();
		break;
	}
	//push figure back to figure_array
	if (figure)
	{
		figure->set_property(_property);
		figure->set_temperature(Temperature);
		figure_array.push_back(figure);
	}
		
}

/* * @brief   draw all the figure in figure_array
	* @param [in]  QPainter &painter: painter
	* @param [in]  const std::vector<Figure*> &figure_array: store the figures needed painting
	* @param [out] void
	* @return      void
*/
void QtGuiClass::drawAllFigure(QPainter &painter, const std::vector<Figure*> &figure_array)
{
	if (figure_array.size() > 0) {
		for (size_t i = 0; i < figure_array.size(); i++)
		{
			//highlight the selected figure
			if (figure_array[i]->is_selected) {
				//highlight_figure(figure_array[i]);
				if (figure_array[i]->type == PIXMAP) {
					QPen p(QColor(255, 0, 0), 5);
					figure_array[i]->DrawFigure(painter, &p);
				}
				else if (figure_array[i]->type == TEXT) {
					Text *t = dynamic_cast<Text*>(figure_array[i]);
					painter.setPen(QPen(QColor(255, 0, 0), 5));
					painter.drawRect(t->line->x() - 2, t->line->y() - 2, t->line->width() + 4, t->line->height() + 4);
				}
				else {
					QPen p(QColor(255, 0, 0), 5);
					figure_array[i]->DrawFigure(painter, &p);
				}

			}
			//draw figures
			else {
				if (figure_array[i]->type == PIXMAP)
					figure_array[i]->DrawFigure(painter);
				else
					figure_array[i]->DrawFigure(painter, &(figure_array[i]->pen));
			}
		}
	}
}

/* * @brief   paint things neeeded on screen
	* @param [in]  QPainter *
	* @param [out] void
	* @return      void
*/
void QtGuiClass::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	drawAllFigure(painter, figure_array);

	switch (function_state) {
	case SELECTING:
	{
		//draw the selecting frame
		QVector<qreal> dashes;
		QPen pen2;
		//set the space of dashes
		qreal space = 3;
		dashes << 5 << space << 5 << space;
		pen2.setDashPattern(dashes);
		pen2.setWidth(1);
		pen2.setColor(QColor(0, 0, 0));//set black color
		painter.setPen(pen2);
		//draw selecting frame
		painter.drawRect(start_point.rx(), start_point.ry(), end_point.rx() - start_point.rx(), end_point.ry() - start_point.ry());
	}
	break;
	case DRAWING:
		//draw current figure
		painter.setPen(*pen);
		drawCurrentFigure(painter, start_point, end_point);
		break;
	}

	painter.end();
}

/* * @brief   rotateL selected figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void QtGuiClass::RotateL_selected() {
	for (int i = 0; i < figure_array.size(); i++) {
		if (figure_array[i]->is_selected) {
			//rotateL
			figure_array[i]->RotateL();
		}
	}
	function_state = DEFAULT;
	update();
}

/* * @brief   rotateR selected figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void QtGuiClass::RotateR_selected() {
	for (int i = 0; i < figure_array.size(); i++) {
		if (figure_array[i]->is_selected) {
			//rotateR
			figure_array[i]->RotateR();
		}
	}
	function_state = DEFAULT;
	update();
}

/* * @brief   delete selected figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void QtGuiClass::Delete_selected() {
	if (!figure_array.empty()) {
		for (int i = figure_array.size() - 1; i >= 0; i--) {
			if (figure_array[i]->is_selected) {
				delete figure_array[i];
				figure_array.erase(figure_array.begin() + i);
			}
		}
	}
	function_state = DEFAULT;
	update();
}

/* * @brief   zoom in selected figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void QtGuiClass::Amplify_selected() {
	for (int i = 0; i < figure_array.size(); i++) {
		if (figure_array[i]->is_selected) {
			//amplify
			figure_array[i]->Amplify();
		}
	}
	function_state = DEFAULT;
	update();
}

/* * @brief   zoom out selected figures
	* @param [in]  void
	* @param [out] void
	* @return      void
*/
void QtGuiClass::Shrink_selected() {
	for (int i = 0; i < figure_array.size(); i++) {
		if (figure_array[i]->is_selected) {
			//shrink
			figure_array[i]->Shrink();
		}
	}
	function_state = DEFAULT;
	update();
}

/* * @brief   set color of selected figures
	* @param [in]  const QColor &color : new color
	* @param [out] void
	* @return      void
*/
void QtGuiClass::set_selected_color(const QColor &color) {
	for (int i = 0;i < figure_array.size();i++) {
		if (figure_array[i]->is_selected) {
			//set color
			figure_array[i]->set_color(color);
		}
	}
	update();
}

/* * @brief   set width of selected figures
	* @param [in]  const int width : new width
	* @param [out] void
	* @return      void
*/
void QtGuiClass::set_selected_size(const int width) {
	for (int i = 0;i < figure_array.size();i++) {
		if (figure_array[i]->is_selected) {
			//set width
			figure_array[i]->set_size(width);
		}
	}
	update();
}

void QtGuiClass::set_selected_property(_PROPERTY p) {
	for (int i = 0;i < figure_array.size();i++) {
		if (figure_array[i]->is_selected) {
			//set property
			figure_array[i]->set_property(p);
		}
	}
	update();
}

void QtGuiClass::set_selected_temperature(double T) {
	for (int i = 0;i < figure_array.size();i++) {
		if (figure_array[i]->is_selected) {
			//set temperature
			figure_array[i]->set_temperature(T);
		}
	}
	update();
}

const std::vector<Figure*>& QtGuiClass::getFigureArray(void) {
	return figure_array;
}