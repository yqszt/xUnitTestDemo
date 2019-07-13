#include "parameter.h"

timeParameters::timeParameters() {
	flameNo = 0;
}

timeParameters::timeParameters(const timeParameters& src) {
	flameNo = src.flameNo;
}

timeParameters::timeParameters(timeParameters&& src) noexcept
{
	flameNo = src.flameNo;
}

timeParameters& timeParameters::operator=(const timeParameters& src) {
	flameNo = src.flameNo;
	return *this;
}

timeParameters& timeParameters::operator=(timeParameters&& src) noexcept
{
	flameNo = src.flameNo;
	return *this;
}

int timeParameters::get() const{
	return flameNo;
}

void timeParameters::setPara(int t) {
	if (t < 0) t = 0;
	flameNo = t;
}

timeParameters::~timeParameters() {
	;
}

pointParameters::pointParameters() :x(0), y(0) {
	;
}

pointParameters::pointParameters(const pointParameters& src) {
	x = src.x;
	y = src.y;
}

pointParameters::pointParameters(pointParameters&& src) noexcept{
	x = src.x;
	y = src.y;
}

pointParameters::pointParameters(int x, int y) {
	this->x = x;
	this->y = y;
}

pointParameters::~pointParameters() {
	;
}

pointParameters& pointParameters::operator= (const pointParameters& src) {
	this->x = src.x;
	this->y = src.y;
	return *this;
}

pointParameters& pointParameters::operator= (pointParameters&& src) noexcept{
	this->x = src.x;
	this->y = src.y;
	return *this;
}

int pointParameters::getX() const {
	return x;
}

int pointParameters::getY() const {
	return y;
}

std::pair<int, int> pointParameters::getPair() const{
	std::pair<int, int> ret(x, y);
	return ret;
}

void pointParameters::setX(int x) {
	this->x = x;
}

void pointParameters::setY(int y) {
	this->y = y;
}

void pointParameters::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}
