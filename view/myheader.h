#pragma once

#include <QPen>
#include <QPainter>
#include <QTextEdit>
#include <QWidget>

#define PI 3.1415926

enum _TYPE {
	LINE = 0,        //draw line status
	RECTANGLE,  //draw rectangle status
	ELLIPSE,         //draw ellipse status
	POLYGON,    //draw polygon status
	PIXMAP,       //load external image
	RANDOM,    //arbitrary lines
	ERASE,         //draw white lines to erase drawn figures
	TEXT            //draw texts
};

enum _FUNCTION {
	DEFAULT = 10,  //single click selection state
	SELECTING,       //selecting figures using a frame
	WAIT,                //wait to draw a figure
	DRAWING,        //drawing a figure
	TEXTING,          //writing texts
	DELETEIT,             //delete status
	MOVE,              //wait to move
	MOVING,          //moving a figure
	ROTATE_LEFT,   //rotate selected figures counterclockwise
	ROTATE_RIGHT,//rotate selected figures clockwise
	ROTATING,       //rotating figures, unfinished
	AMPLIFY,          //amplify
	SHRINK,            //shrink
	SAVE,                //save the picture
	NEW,                //create a new blank picture
	OPEN                //open an existing picture
};

enum _PROPERTY{
	HEATINSULATION = -1,
	NORMAL = 0,
	HEATSOURCE
};
/* * @brief   calculate the length of a vector
	* @param [in]  QPoint &: end point of a vector
	* @return  double: length of the vector
	*/
inline const double vectorLength(const QPoint &point)
{
	return sqrt(point.x()*point.x() + point.y()*point.y());
}

/* * @brief       prensent figure 
	* @exception   no
	* @note        this class is the parent class of concrete figure class(Line, Rectangle, Ellipse and so on).
				   Only its child class is meaningful to use.
	* @author       
*/
class Figure
{
public:
	Figure();
	Figure(const QPen &pen, const int &type);
	Figure(const int &type);

	virtual ~Figure() {}
	virtual void DrawFigure(QPainter &painter, const QPen *pen = NULL) const = 0;
	virtual bool selected(const QPoint &point) const = 0;
	virtual bool is_in_it(const QPoint &start_point_, const QPoint &end_point_) const = 0;
	virtual void clear_move_point() = 0;
	virtual void Amplify() = 0;
	virtual void Shrink() = 0;
	virtual bool is_in_figure(const QPoint &point) { return false; }

	//update move_point
	void set_move_point(const QPoint &start_point_, const QPoint &end_point_);
	//set color
	void set_color(const QColor &color);
	//set width
	void set_size(const int width);
	//rotateL
	void RotateL();
	//rotateR
	void RotateR();
	//set property
	void set_property(_PROPERTY p);
	//get property
	_PROPERTY get_property();
	//set temperature
	void set_temperature(double T);
	//get temperature
	double get_temperature();

	QPen pen;             //store information of pen, such as color and width
	int type;                //store the type of this figure
	bool is_selected;   //whether selected. True means yes, and False means no.
	int rotate;             //rotating angle in degrees
	QPoint move_p;   //move_point
	_PROPERTY _property;
	double temperature;
};

/* * @brief       represent lines
	* @exception   child class of class Figure
	* @author
*/
class Line : public Figure
{
public:
	Line();
	Line(const QPoint &start, const QPoint &end, QPen &pen);
	~Line();

	/* * @brief   draw the line
		* @param [in]  QPainter &painter : painter
		* @param [in]  const QPen *pen   : pen
		* @param [out] void
		* @return      void
	*/
	void DrawFigure(QPainter &painter, const QPen *pen) const;

	/* * @brief   determine whether is selected(used for click selection)
		* @param [in]  Point &point : click point
		* @param [out] void
		* @return      bool : true for selected, false for not selected
    */
	bool selected(const QPoint &point) const;

	/* * @brief   determine whether is selected(used for frame selection)
		* @param [in]  QPoint &start_point_ : the start point of frame
		* @param [in]  QPoint &end_point_   : the end point of frame
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	bool is_in_it(const QPoint &start_point_, const QPoint &end_point_) const;
	bool is_in_figure(const QPoint &point);
	/* * @brief   clear move point
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	void clear_move_point();

	/* * @brief   amplify
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	inline void Amplify() {
		//end = (end - start)*1.1 + start;
		start *= 1.1;
		end *= 1.1;
	}

	/* * @brief   shrink
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	inline void Shrink() {
		//end = (end - start)*0.9 + start;
		end *= 0.9;
		start *= 0.9;
	}

private:
	QPoint start, end;  //the start point and end point of line
	QPoint mid;           //the mid point of the line
};

/* * @brief       represent rectangles
	* @exception   child class of class Figure
	* @author
*/
class Rectangle : public Figure
{
public:
	Rectangle();
	Rectangle(int start_x, int start_y, int width, int height, const QPen &pen);
	~Rectangle();

	/* * @brief   draw the rectangle
		* @param [in]  QPainter &painter : painter
		* @param [in]  const QPen *pen   : pen
		* @param [out] void
		* @return      void
	*/
	void DrawFigure(QPainter &painter, const QPen *pen) const;

	/* * @brief   determine whether is selected(used for click selection)
		* @param [in]  Point &point : click point
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	bool selected(const QPoint &point) const;

	/* * @brief   determine whether is selected(used for frame selection)
		* @param [in]  QPoint &start_point_ : the start point of frame
		* @param [in]  QPoint &end_point_   : the end point of frame
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	bool is_in_it(const QPoint &start_point_, const QPoint &end_point_) const;
	bool is_in_figure(const QPoint &point);
	/* * @brief   clear move point
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	void clear_move_point();

	/* * @brief   amplify
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	inline void Amplify() {
		width *= 1.1;
		height *= 1.1;
	}

	/* * @brief   shrink
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	inline void Shrink() {
		width *= 0.9;
		height *= 0.9;
	}

private:
	int start_x, start_y, width, height;
};

/* * @brief       represent ellipses
	* @exception   child class of class Figure
	* @author
*/
class Ellipse : public Figure
{
public:
	Ellipse();
	Ellipse(const QPoint &center, int major, int minor, const QPen pen);
	~Ellipse();

	/* * @brief   draw the ellipse
		* @param [in]  QPainter &painter : painter
		* @param [in]  const QPen *pen   : pen
		* @param [out] void
		* @return      void
	*/
	void DrawFigure(QPainter &painter, const QPen *pen) const;

	/* * @brief   determine whether is selected(used for click selection)
		* @param [in]  Point &point : click point
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	bool selected(const QPoint &point) const;

	/* * @brief   determine whether is selected(used for frame selection)
		* @param [in]  QPoint &start_point_ : the start point of frame
		* @param [in]  QPoint &end_point_   : the end point of frame
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	bool is_in_it(const QPoint &start_point_, const QPoint &end_point_) const;
	bool is_in_figure(const QPoint &point);
	/* * @brief   clear move point
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	void clear_move_point();

	/* * @brief   amplify
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	inline void Amplify() {
		semi_major *= 1.1;
		semi_minor *= 1.1;
	}

	/* * @brief   shrink
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	inline void Shrink() {
		semi_major *= 0.9;
		semi_minor *= 0.9;
	}

private:
	QPoint center;         //central point
	int semi_major, semi_minor;      //long half axis and short half axis
};

/* * @brief       represent polygons
	* @exception   child class of class Figure
	* @author
*/
class Polygon : public Figure
{
public:
	Polygon();
	Polygon(const std::vector<QPoint*> &list, const int length, const QPen &pen);
	~Polygon();

	/* * @brief   draw the polygon
		* @param [in]  QPainter &painter : painter
		* @param [in]  const QPen *pen   : pen
		* @param [out] void
		* @return      void
	*/
	virtual void DrawFigure(QPainter &painter, const QPen *pen) const;

	/* * @brief   determine whether is selected(used for click selection)
		* @param [in]  Point &point : click point
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	virtual bool selected(const QPoint &point) const;

	/* * @brief   determine whether is selected(used for frame selection)
		* @param [in]  QPoint &start_point_ : the start point of frame
		* @param [in]  QPoint &end_point_   : the end point of frame
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	bool is_in_it(const QPoint &start_point, const QPoint &end_point) const;

	/* * @brief   clear move point
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	void clear_move_point();

	/* * @brief   amplify
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	void Amplify();

	/* * @brief   shrink
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	void Shrink();

protected:
	QPoint *start;   //store the points of polygon
	QPoint centroid;  //geometry center of polygon
	int size;            //number of points
};

/* * @brief       represent pictures
	* @exception   child class of class Figure
	* @author
*/
class Pixmap : public Figure
{
public:
	Pixmap();
	Pixmap(const QPixmap *pixmap, int &start_x, int &start_y);
	~Pixmap();

	/* * @brief   draw the external picture
		* @param [in]  QPainter &painter : painter
		* @param [in]  const QPen *pen   : pen
		* @param [out] void
		* @return      void
	*/
	void DrawFigure(QPainter &painter, const QPen *pen) const;

	/* * @brief   determine whether is selected(used for click selection)
		* @param [in]  Point &point : click point
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	bool selected(const QPoint &point) const;

	/* * @brief   determine whether is selected(used for frame selection)
		* @param [in]  QPoint &start_point_ : the start point of frame
		* @param [in]  QPoint &end_point_   : the end point of frame
		* @param [out] void
		* @return      bool : true for selected, false for not selected
	*/
	bool is_in_it(const QPoint &start_point, const QPoint &end_point) const;

	/* * @brief   clear move point
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	void clear_move_point();

	/* * @brief   amplify
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	inline void Amplify() {
		pixmap->scaledToWidth(1.1);
	}

	/* * @brief   shrink
		* @param [in]  void
		* @param [out] void
		* @return      void
	*/
	inline void Shrink() {
		pixmap->scaledToWidth(0.9);
	}

private:
	const QPixmap *pixmap;        //the picture
	int start_x, start_y;       //position of picture(upper left corner)
};

/* * @brief       represent random lines
	* @exception   child class of class Polygon
	* @author
*/
class Random : public Polygon
{
public:
	Random();
	Random(const std::vector<QPoint*> &list, const int length, const QPen &pen);
	void DrawFigure(QPainter &painter, const QPen *pen) const;
	bool selected(const QPoint &point) const;
	bool is_in_figure(const QPoint &point);
};

/* * @brief       represent text boxes
	* @exception   child class of class Figure
	* @author
*/
class Text : public Figure
{
public:
	Text();
	Text(QTextEdit *newtext);
	~Text();
	void DrawFigure(QPainter &painter, const QPen *pen = NULL) const {}
	bool selected(const QPoint &point) const;
	bool is_in_it(const QPoint &start_point_, const QPoint &end_point_) const;
	void clear_move_point();
	void Amplify() {}
	void Shrink() {}
	QTextEdit *line;
	int old_x, old_y;
private:
	QPoint center;
};

/* * @brief       represent erase lines
	* @exception   child class of class Polygon
	* @author
*/
class Erase : public Polygon
{
public:
	Erase();
	Erase(const std::vector<QPoint*> &list, const int length, const QPen &pen);
	void DrawFigure(QPainter &painter, const QPen *ownpen) const;
	bool selected(const QPoint &point) const;
private:
	QPen ownpen;
};