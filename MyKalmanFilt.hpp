/*
 * MyKalmanFilt.hpp
 *
 *  Created on: Jun 24, 2016
 *      Author: hasan
 */

#ifndef MYKALMANFILT_HPP_
#define MYKALMANFILT_HPP_


#include "MyMatrix.hpp"
#include <math.h>
#include <iostream>
#include <fstream>


class MyKalmanFilt{
protected:
	MyMatrix<double> A;
	MyMatrix<double> B;
	MyMatrix<double> C;
	MyMatrix<double> Y;
	MyMatrix<double> R;
	MyMatrix<double> Q;
	MyMatrix<double> V;
	MyMatrix<double> W;

    MyMatrix<double> motion;
    MyMatrix<double> measure;

	int stateVarNum;
	int measVarNum;
	int V_size;
	int W_size;

	double T;

	bool debug = false;

	std::ofstream logFile;

public:

	MyMatrix<double> X;

	MyMatrix<double> P;

	MyKalmanFilt();

	MyKalmanFilt(const double&, const int&, const int&, const int&, const int&, bool);

	virtual ~MyKalmanFilt();

	virtual void setA();

	virtual void setC();

	virtual void setR();

	virtual void setQ();

	virtual void setV();

	virtual void setW();

	MyMatrix<double> getP();

	virtual void init(const MyMatrix<double>&, const MyMatrix<double>&);

	void motionUpdate(const MyMatrix<double>&);

	void sensorUpdate(const MyMatrix<double>&);

	void step(const MyMatrix<double>&, const MyMatrix<double>&);

	void logger(const std::string&, const MyMatrix<double>&, const std::string&);
};

double angle_norm(const double&);

#include "MyKalmanFilt_impl.hpp"



#endif /* MYKALMANFILT_HPP_ */
