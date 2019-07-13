#include "myheader.h"

//functions for class Figure
Figure::Figure() : pen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin), type(LINE), is_selected(false), rotate(0), move_p(QPoint(0, 0)),_property(NORMAL),temperature(0.0) {}

Figure::Figure(const QPen &pen, const int &type) : pen(pen), type(type), is_selected(false), _property(NORMAL), temperature(0.0) {
	rotate = 0;
	move_p = QPoint(0, 0);
}

Figure::Figure(const int &type) : pen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin), type(type), is_selected(false), _property(NORMAL), temperature(0.0) {
	rotate = 0;
	move_p = QPoint(0, 0);
}

void Figure::set_move_point(const QPoint &start_point_, const QPoint &end_point_) {
	move_p = end_point_ - start_point_;
}

void Figure::set_color(const QColor &color) {
	pen.setColor(color);
}

void Figure::set_size(const int width) {
	pen.setWidth(width);
}

void Figure::set_property(_PROPERTY p) {
	_property = p;
}

_PROPERTY Figure::get_property() {
	return _property;
}

void Figure::set_temperature(double T) {
	temperature = T;
}

double Figure::get_temperature() {
	return temperature;
}

void Figure::RotateL()
{
	rotate -= 15;
	while (rotate < 0) {
		rotate += 360;
	}
}

void Figure::RotateR()
{
	rotate += 15;
	while (rotate >= 360) {
		rotate -= 360;
	}
}

//functions for class Line
Line::Line() : Figure(LINE), start(QPoint(0, 0)), end(QPoint(0, 0)) {}

Line::Line(const QPoint &start, const QPoint &end, QPen &pen) : Figure(pen, LINE)//, start(start), end(end)
{
	mid = (start + end) / 2;
	this->start = start - mid;
	this->end = end - mid;
}

Line::~Line() {}

void Line::DrawFigure(QPainter &painter, const QPen *pen) const
{
	//set pen(color and width)
	painter.setPen(*pen);
	//save the current status of painter
	painter.save();
	//move zero point to the mid of line
	//painter.translate((start.x() + end.x()) / 2 + move_p.x(), (start.y() + end.y()) / 2 + move_p.y());
	painter.translate(mid + move_p);
	//rotate the painter
	painter.rotate(rotate);
	//draw the line
	//painter.drawLine((start.x() - end.x()) / 2, (start.y() - end.y()) / 2, (end.x() - start.x()) / 2, (end.y() - start.y()) / 2);
	painter.drawLine(start, end);
	//back to the status saved above
	painter.restore();
}

bool Line::selected(const QPoint &point) const
{
	//int x1 = ((start.x() + end.x()) / 2 - point.x())*cos(rotate*PI / 180) + ((start.y() + end.y()) / 2 - point.y())*sin(rotate*PI / 180);
	//int y1 = -((start.x() + end.x()) / 2 - point.x())*sin(rotate*PI / 180) + ((start.y() + end.y()) / 2 - point.y())*cos(rotate*PI / 180);
	//rotate the vector
	//QPoint start(x1 + (start.x() - end.x()) / 2, y1 + (start.y() - end.y()) / 2);
	//QPoint end(x1 - (start.x() - end.x()) / 2, y1 - (start.y() - end.y()) / 2);
	QPoint start_ = mid - point + start;
	QPoint end_ = mid - point + end;
	//return ((QPoint::dotProduct(start, end) / (vectorLength(start)*vectorLength(end))) < -0.996);
	//determine whether the point is close enough to the line
	if (vectorLength(start) + vectorLength(end) < 120.0) {
		//use a weaker criteria when the line is short
		return ((QPoint::dotProduct(start_, end_) / (vectorLength(start_)*vectorLength(end_))) < -0.94);
	}
	else {
		return ((QPoint::dotProduct(start_, end_) / (vectorLength(start_)*vectorLength(end_))) < -0.99);
	}
}

bool Line::is_in_it(const QPoint &start_point_, const QPoint &end_point_) const
{
	
	if (start_point_.x() < end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper left to lower right
		return (mid.x() >= start_point_.x() && mid.x() <= end_point_.x() && mid.y() >= start_point_.y() && mid.y() <= end_point_.y());
	}
	else if (start_point_.x() >= end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper right to lower left
		return (mid.x() <= start_point_.x() && mid.x() >= end_point_.x() && mid.y() >= start_point_.y() && mid.y() <= end_point_.y());
	}
	else if (start_point_.x() < end_point_.x() && start_point_.y() >= end_point_.y()) {
		//frame selection from lower left to upper right
		return (mid.x() >= start_point_.x() && mid.x() <= end_point_.x() && mid.y() <= start_point_.y() && mid.y() >= end_point_.y());
	}
	else{
		//frame selection from lower right to upper left
		return (mid.x() <= start_point_.x() && mid.x() >= end_point_.x() && mid.y() <= start_point_.y() && mid.y() >= end_point_.y());
	}
}

bool Line::is_in_figure(const QPoint &point) {
	return selected(point);
}

void Line::clear_move_point() {
	//update start and end
	mid += move_p;
	//start = start + move_p;
	//end = end + move_p;
	move_p = QPoint(0, 0);
}

//functions for class Rectangle
Rectangle::Rectangle() : Figure(RECTANGLE), start_x(0), start_y(0), width(0), height(0) {}

Rectangle::Rectangle(int start_x, int start_y, int width, int height, const QPen &pen) : Figure(pen, RECTANGLE), start_x(start_x), start_y(start_y), width(width), height(height) {}

Rectangle::~Rectangle() {}

void Rectangle::DrawFigure(QPainter &painter, const QPen *pen) const
{
	//set pen(color and width)
	painter.setPen(*pen);
	//save the current status of painter
	painter.save();
	//move zero point to the mid of line
	painter.translate(start_x + width / 2 + move_p.x(), start_y + height / 2 + move_p.y());
	//rotate the painter
	painter.rotate(rotate);
	//draw the rectangle
	painter.drawRect(-width / 2, -height / 2, width, height);
	//back to the status saved above
	painter.restore();
}

bool Rectangle::selected(const QPoint &point) const
{
	int rx = (point.x() - (start_x + width / 2))*cos(rotate*PI / 180) +
		(point.y() - (start_y + height / 2))*sin(rotate*PI / 180) + (start_x + width / 2);
	int ry = -(point.x() - (start_x + width / 2))*sin(rotate*PI / 180) +
		(point.y() - (start_y + height / 2))*cos(rotate*PI / 180) + (start_y + height / 2);

	QPoint A(start_x - rx, start_y - ry), B(start_x + width - rx, start_y - ry), C(start_x + width - rx, start_y + height - ry), D(start_x - rx, start_y + height - ry);
	double cosine1 = QPoint::dotProduct(A, B) / (vectorLength(A)*vectorLength(B));
	double cosine2 = QPoint::dotProduct(A, D) / (vectorLength(A)*vectorLength(D));
	double cosine3 = QPoint::dotProduct(C, D) / (vectorLength(C)*vectorLength(D));
	double cosine4 = QPoint::dotProduct(B, C) / (vectorLength(B)*vectorLength(C));

	return (cosine1 < -0.99 || cosine2 < -0.99 || cosine3 < -0.99 || cosine4 < -0.99);
}

bool Rectangle::is_in_it(const QPoint &start_point_, const QPoint &end_point_) const
{
	int mid_point_x_ = start_x + width / 2;
	int mid_point_y_ = start_y + height / 2;
	if (start_point_.x() < end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper left to lower right
		return (mid_point_x_ >= start_point_.x() && mid_point_x_ <= end_point_.x() && mid_point_y_ >= start_point_.y() && mid_point_y_ <= end_point_.y());
	}
	else if (start_point_.x() >= end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper right to lower left
		return (mid_point_x_ <= start_point_.x() && mid_point_x_ >= end_point_.x() && mid_point_y_ >= start_point_.y() && mid_point_y_ <= end_point_.y());
	}
	else if (start_point_.x() < end_point_.x() && start_point_.y() >= end_point_.y()) {
		//frame selection from lower left to upper right
		return (mid_point_x_ >= start_point_.x() && mid_point_x_ <= end_point_.x() && mid_point_y_ <= start_point_.y() && mid_point_y_ >= end_point_.y());
	}
	else {
		//frame selection from lower right to upper left
		return (mid_point_x_ <= start_point_.x() && mid_point_x_ >= end_point_.x() && mid_point_y_ <= start_point_.y() && mid_point_y_ >= end_point_.y());
	}
}

bool Rectangle::is_in_figure(const QPoint &point) {
	return (point.x() >= start_x) && (point.x() <= start_x + width) && (point.y() >= start_y) && (point.y() <= start_y + height);
}

void Rectangle::clear_move_point() {
	start_x = start_x + move_p.x();
	start_y = start_y + move_p.y();
	move_p = QPoint(0, 0);
}

//functions for class Ellipse
Ellipse::Ellipse() : Figure(ELLIPSE), center(QPoint(0, 0)), semi_major(0), semi_minor(0) {}

Ellipse::Ellipse(const QPoint &center, int major, int minor, const QPen pen) : Figure(pen, ELLIPSE), center(center), semi_major(major), semi_minor(minor) {}

Ellipse::~Ellipse() {}

void Ellipse::DrawFigure(QPainter &painter, const QPen *pen) const
{
	//set pen(color and width)
	painter.setPen(*pen);
	//save the current status of painter
	painter.save();
	//move zero point to the mid of line
	painter.translate(center.x() + move_p.x(), center.y() + move_p.y());
	//rotate the painter
	painter.rotate(rotate);
	//draw the ellipse
	painter.drawEllipse(QPoint(0, 0), semi_major, semi_minor);
	//back to the status saved above
	painter.restore();
}

bool Ellipse::selected(const QPoint &point) const
{
	QPoint A((point.x() - center.x())*cos(rotate*PI / 180) + (point.y() - center.y())*sin(rotate*PI / 180),
		-(point.x() - center.x())*sin(rotate*PI / 180) + (point.y() - center.y())*cos(rotate*PI / 180));
	double one = A.x()*A.x() / ((double)semi_major*semi_major) + A.y()*A.y() / ((double)semi_minor*semi_minor);
	return (one > 0.9 && one < 1.1);
}

bool Ellipse::is_in_it(const QPoint &start_point_, const QPoint &end_point_) const
{
	if (start_point_.x() < end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper left to lower right
		return (center.x() >= start_point_.x() && center.x() <= end_point_.x() && center.y() >= start_point_.y() && center.y() <= end_point_.y());
	}
	else if (start_point_.x() >= end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper right to lower left
		return (center.x() <= start_point_.x() && center.x() >= end_point_.x() && center.y() >= start_point_.y() && center.y() <= end_point_.y());
	}
	else if (start_point_.x() < end_point_.x() && start_point_.y() >= end_point_.y()) {
		//frame selection from lower left to upper right
		return (center.x() >= start_point_.x() && center.x() <= end_point_.x() && center.y() <= start_point_.y() && center.y() >= end_point_.y());
	}
	else {
		//frame selection from lower right to upper left
		return (center.x() <= start_point_.x() && center.x() >= end_point_.x() && center.y() <= start_point_.y() && center.y() >= end_point_.y());
	}
}

bool Ellipse::is_in_figure(const QPoint &point) {
	return (point.x() - center.x())*(point.x() - center.x())*1.0 / (semi_major*semi_major)
		+ (point.y() - center.y())*(point.y() - center.y())*1.0 / (semi_minor*semi_minor) - 1.0 <= 0.0;
}

void Ellipse::clear_move_point() {
	center = center + move_p;
	move_p = QPoint(0, 0);
}

//functions for class Polygon
Polygon::Polygon() : Figure(POLYGON), start(nullptr),size(0){}

Polygon::Polygon(const std::vector<QPoint*> &list, const int length, const QPen &pen) : Figure(pen, POLYGON), size(length), start(NULL)
{
	start = new QPoint[length];
	int x = 0;
	int y = 0;
	for (int i = 0; i < length; i++) {
		x += list[i]->x();
		y += list[i]->y();
	}
	centroid = QPoint(x / size, y / size);
	for (int i = 0; i < length; i++) {
		start[i] = *(list[i]) - centroid;
	}
}

Polygon::~Polygon()
{
	if (start)
		delete[] start;
}

void Polygon::DrawFigure(QPainter &painter, const QPen *pen) const
{
	//set pen(color and width)
	painter.setPen(*pen);
	//save the current status of painter
	painter.save();
	//move zero point to the mid of line
	painter.translate(centroid.x() + move_p.x(), centroid.y() + move_p.y());
	//rotate the painter
	painter.rotate(rotate);
	//draw the polygon
	painter.drawPolygon(start, size);
	//back to the status saved above
	painter.restore();
}

bool Polygon::selected(const QPoint &point) const
{
	if (start) {
		size_t i = 0;
		QPoint A, B;
		double cosine;
		while (i < size - 1) {
			A = centroid - point + start[i];
			B = centroid - point + start[i + 1];
			cosine = QPoint::dotProduct(A, B) / (vectorLength(A)*vectorLength(B));
			if (cosine < -0.99)
				return true;
			i++;
		}
		A = centroid - point + start[i];
		B = centroid - point + start[0];
		cosine = QPoint::dotProduct(A, B) / (vectorLength(A)*vectorLength(B));
		if (cosine < -0.99)
			return true;
	}
	return false;
}

bool Polygon::is_in_it(const QPoint &start_point_, const QPoint &end_point_) const
{
	if (start_point_.x() < end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper left to lower right
		return (centroid.x() >= start_point_.x() && centroid.x() <= end_point_.x() && centroid.y() >= start_point_.y() && centroid.y() <= end_point_.y());
	}
	else if (start_point_.x() >= end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper right to lower left
		return (centroid.x() <= start_point_.x() && centroid.x() >= end_point_.x() && centroid.y() >= start_point_.y() && centroid.y() <= end_point_.y());
	}
	else if (start_point_.x() < end_point_.x() && start_point_.y() >= end_point_.y()) {
		//frame selection from lower left to upper right
		return (centroid.x() >= start_point_.x() && centroid.x() <= end_point_.x() && centroid.y() <= start_point_.y() && centroid.y() >= end_point_.y());
	}
	else {
		//frame selection from lower right to upper left
		return (centroid.x() <= start_point_.x() && centroid.x() >= end_point_.x() && centroid.y() <= start_point_.y() && centroid.y() >= end_point_.y());
	}
}

void Polygon::clear_move_point() {
	centroid += move_p;
	move_p = QPoint(0, 0);
}

void Polygon::Amplify() {
	for (int i = 0; i < size; i++) {
		start[i] = start[i] * 1.1;
	}
}

void Polygon::Shrink() {
	for (int i = 0; i < size; i++) {
		start[i] = start[i] * 0.9;
	}
}

//functions for class Pixmap
Pixmap::Pixmap() : Figure(PIXMAP), pixmap(), start_x(0), start_y(0) {}

Pixmap::Pixmap(const QPixmap *pixmap, int &start_x, int &start_y) : Figure(PIXMAP), pixmap(pixmap), start_x(start_x), start_y(start_y) {}

Pixmap::~Pixmap() {
	delete pixmap;
}

void Pixmap::DrawFigure(QPainter &painter, const QPen *pen) const
{
	if (pen) {
		painter.setPen(*pen);
		painter.drawRect(start_x - 2, start_y - 2, pixmap->width() + 4, pixmap->height() + 4);
	}
	painter.drawPixmap(start_x, start_y, *pixmap);
}

bool Pixmap::selected(const QPoint &point) const
{
	return (point.x() >= start_x && point.x() <= start_x + pixmap->width() && point.y() >= start_y && point.y() <= start_y + pixmap->height());
}

bool Pixmap::is_in_it(const QPoint &start_point_, const QPoint &end_point_) const
{
	QPoint center(start_x + pixmap->width() / 2, start_y + pixmap->height() / 2);
	if (start_point_.x() < end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper left to lower right
		return (center.x() >= start_point_.x() && center.x() <= end_point_.x() && center.y() >= start_point_.y() && center.y() <= end_point_.y());
	}
	else if (start_point_.x() >= end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper right to lower left
		return (center.x() <= start_point_.x() && center.x() >= end_point_.x() && center.y() >= start_point_.y() && center.y() <= end_point_.y());
	}
	else if (start_point_.x() < end_point_.x() && start_point_.y() >= end_point_.y()) {
		//frame selection from lower left to upper right
		return (center.x() >= start_point_.x() && center.x() <= end_point_.x() && center.y() <= start_point_.y() && center.y() >= end_point_.y());
	}
	else {
		//frame selection from lower right to upper left
		return (center.x() <= start_point_.x() && center.x() >= end_point_.x() && center.y() <= start_point_.y() && center.y() >= end_point_.y());
	}
}

void Pixmap::clear_move_point() {
	start_x = start_x + move_p.x();
	start_y = start_y + move_p.y();
	move_p = QPoint(0, 0);
}

//functions for class Random
Random::Random() : Polygon() {
	Figure::type = RANDOM;
}

Random::Random(const std::vector<QPoint*> &list, const int length, const QPen &pen) : Polygon(list, length, pen) {
	Figure::type = RANDOM;
}

void Random::DrawFigure(QPainter &painter, const QPen *pen) const {
	//set pen(color and width)
	painter.setPen(*pen);
	//save the current status of painter
	painter.save();
	//move zero point to the mid of line
	painter.translate(centroid.x() + move_p.x(), centroid.y() + move_p.y());
	//rotate the painter
	painter.rotate(rotate);
	//draw the arbitrary line
	for (size_t i = 0; i < size - 1; i++) {
		painter.drawLine(start[i], start[i+1]);
	}
	//back to the status saved above
	painter.restore();
}

bool Random::selected(const QPoint &point) const
{
	QPoint A;
	A = centroid - point + start[0];
	double min_dist = vectorLength(A);
	for (size_t i = 0; i < size; i++) {
		A = centroid - point + start[i];
		double dist = vectorLength(A);
		if (dist < min_dist)
			min_dist = dist;
	}
	return (min_dist < 6.0);
}

bool Random::is_in_figure(const QPoint &point) {
	return selected(point);
}

//function for class Text
Text::Text() : Figure(TEXT) {}

Text::Text(QTextEdit *newline) : Figure(TEXT), line(newline), center(QPoint(line->x()+line->width()/2,line->y()+line->height()/2))
{
	old_x = line->x();
	old_y = line->y();
}

bool Text::selected(const QPoint &point) const
{
	return (point.x() >= line->x() - 10 && point.x() <= line->x() + line->width() + 10 && point.y() <= line->y() + line->height() + 10 && point.y() >= line->y() - 10);
}

bool Text::is_in_it(const QPoint &start_point_, const QPoint &end_point_) const
{
	if (start_point_.x() < end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper left to lower right
		return (center.x() >= start_point_.x() && center.x() <= end_point_.x() && center.y() >= start_point_.y() && center.y() <= end_point_.y());
	}
	else if (start_point_.x() >= end_point_.x() && start_point_.y() < end_point_.y()) {
		//frame selection from upper right to lower left
		return (center.x() <= start_point_.x() && center.x() >= end_point_.x() && center.y() >= start_point_.y() && center.y() <= end_point_.y());
	}
	else if (start_point_.x() < end_point_.x() && start_point_.y() >= end_point_.y()) {
		//frame selection from lower left to upper right
		return (center.x() >= start_point_.x() && center.x() <= end_point_.x() && center.y() <= start_point_.y() && center.y() >= end_point_.y());
	}
	else {
		//frame selection from lower right to upper left
		return (center.x() <= start_point_.x() && center.x() >= end_point_.x() && center.y() <= start_point_.y() && center.y() >= end_point_.y());
	}
}

void Text::clear_move_point() {
	center.setX(center.x() + move_p.x());
	center.setY(center.y() + move_p.y());
	old_x = line->x();
	old_y = line->y();
	move_p = QPoint(0, 0);
}

Text::~Text() {
	delete line;
}

//functions for class Erase
Erase::Erase() : Polygon() {
	Figure::type = ERASE;
}

Erase::Erase(const std::vector<QPoint*> &list, const int length, const QPen &pen) : Polygon(list, length, pen) {
	Figure::type = ERASE;
	ownpen = pen;
	ownpen.setColor(Qt::white);
}

void Erase::DrawFigure(QPainter &painter, const QPen *pen) const {
	//set pen(color and width)
	painter.setPen(ownpen);
	//save the current status of painter
	painter.save();
	//move zero point to the mid of line
	painter.translate(centroid.x() + move_p.x(), centroid.y() + move_p.y());
	//rotate the painter
	painter.rotate(rotate);
	//draw the erase
	for (size_t i = 0; i < size - 1; i++) {
		painter.drawLine(start[i], start[i + 1]);
	}
	//back to the status saved above
	painter.restore();
}

bool Erase::selected(const QPoint &point) const
{
	QPoint A;
	A = centroid - point + start[0];
	double min_dist = vectorLength(A);
	for (size_t i = 0; i < size; i++) {
		A = centroid - point + start[i];
		double dist = vectorLength(A);
		if (dist < min_dist)
			min_dist = dist;
	}
	return (min_dist < 6.0);
}