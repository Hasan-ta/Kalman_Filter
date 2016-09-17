/*
 * MyMatrix.hpp
 *
 *  Created on: Jun 24, 2016
 *      Author: hasan
 */

#ifndef MYMATRIX_HPP_
#define MYMATRIX_HPP_


#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

template <typename T> class MyMatrix{
private:
	int rows,cols;
	std::vector<T> elements;

public:
	MyMatrix();

	MyMatrix(const unsigned int&, const unsigned int&, const T&);

	MyMatrix(const MyMatrix<T>&);

	MyMatrix(MyMatrix<T>&&);

//	~MyMatrix();

	int numOfRaws() const;

	int numOfCols() const;

	int numOfRaws();

	int numOfCols();

	int set(const int&, const int&, const T&);

	T get(const int&, const int&);

	T get(const int&, const int&) const;

	void print();

	T& operator() (const int&, const int&);

	const T& operator() (const int&, const int&) const;

	MyMatrix<T>& operator= (const MyMatrix&);

	MyMatrix<T>& operator= (MyMatrix&&);

	MyMatrix<T>& operator+= (const T&);

	MyMatrix<T>& operator+= (const MyMatrix&);

	MyMatrix<T> operator+ (const T&);

	MyMatrix<T> operator+ (const MyMatrix&);

	MyMatrix<T>& operator-= (const T&);

	MyMatrix<T>& operator-= (const MyMatrix&);

	MyMatrix<T> operator- (const T&);

	MyMatrix<T> operator- (const MyMatrix&) const;

	MyMatrix<T>& operator/= (const T&);

	MyMatrix<T>& operator/= (const MyMatrix&);

	MyMatrix<T> operator/ (const T&);

	MyMatrix<T> operator/ (const MyMatrix&);

	MyMatrix<T> operator* (const T&);

	MyMatrix<T>& operator*= (const T&);

	MyMatrix<T>& operator*= (const MyMatrix&);

	MyMatrix<T> operator* (const MyMatrix&);

	MyMatrix<T> transpose();

	MyMatrix<T> UpperCholesky();

	MyMatrix<T> InverseHermitian();
};

template <typename T> MyMatrix<T> identity(int dim);

#include "MyMatrix_impl.hpp"


#endif /* MYMATRIX_HPP_ */
