#pragma once
#include <utility>
class timeParameters {
private:
	int flameNo;
public:
	timeParameters();
	timeParameters(const timeParameters& src);
	timeParameters(timeParameters&& src) noexcept;
	~timeParameters();

	timeParameters& operator= (const timeParameters& src);
	timeParameters& operator= (timeParameters&& src) noexcept;

	int get() const;
	void setPara(int t);
};

class pointParameters {
private:
	int x;
	int y;
public:
	pointParameters();
	pointParameters(const pointParameters& src);
	pointParameters(pointParameters&& src) noexcept;
	pointParameters(int x, int y);
	~pointParameters();

	pointParameters& operator= (const pointParameters& src);
	pointParameters& operator= (pointParameters&& src) noexcept;

	int getX() const;
	int getY() const;
	std::pair<int, int> getPair() const;

	void setX(int x);
	void setY(int y);
	void setXY(int x, int y);


};