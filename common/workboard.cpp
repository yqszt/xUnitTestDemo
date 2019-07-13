#include "workboard.h"
#include <iostream>


point::point():temperature(0),propertyID(0) {
	;
}

point::point(double T) : temperature(T), propertyID(0) {
	;
}

point::point(double T, int PID) : temperature(T), propertyID(PID) {
	;
}

double point::getTemperature() const {
	return temperature;
}

int point::getProperty() const {
	return propertyID;
}

void point::setTemperature(double T) {
	temperature = T;
}

void point::setProperty(int PID) {
	propertyID = PID;
}

point::~point() {
	;
}

workboard::workboard():size(MAT_SIZE),t_matrix() {
	t_matrix.resize(size);
	for (int i = 0; i < size; i++) {
		t_matrix[i].resize(size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			t_matrix[i][j] = 0;
		}
	}
}

workboard::~workboard() {
	;
}

void workboard::__show() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << t_matrix[i][j].getTemperature() << " ";
		}
		std::cout << std::endl;
	}
}

workboard& workboard::operator= (const workboard& s) {
	//DONOT CHECK whether size is fitable or not
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			t_matrix[i][j] = s.t_matrix[i][j];
		}
	}
	return *this;
}

void workboard::getPointMat(std::vector<std::vector<point> >& ret) const {
	ret.resize(size);
	for (int i = 0; i < size; i++) {
		ret[i].resize(size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			ret[i][j] = t_matrix[i][j];
		}
	}
}

int workboard::getSize() const {
	return size;
}

workboard& workboard::operator= (const std::vector<std::vector<point> >& mat) {
	if (mat.size() != size) {
		std::cout << "Size not fit" << std::endl;
	}
	else {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				t_matrix[i][j] = mat[i][j];
			}
		}
	}
	return *this;
}


workboardPass::workboardPass():wb(),changeType(NOCHANGE) {
	;
}

workboardPass::workboardPass(const workboard& w):wb(w),changeType(NOCHANGE) {
	;
}

CType workboardPass::getChangeType()  const {
	return changeType;
}

void workboardPass::setChangeType(CType c) {
	changeType = c;
}

double workboardPass::getChangeValue()  const {
	return changeValue;
}

void workboardPass::setChangeValue(double val) {
	changeValue = val;
}

workboard workboardPass::getWorkBoard()  const {
	return wb;
}

void workboardPass::setWorkBoard(const workboard& w) {
	wb = w;
}

workboardPass::~workboardPass() {
	;
}