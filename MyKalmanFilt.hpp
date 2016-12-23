
/****************************************************************************************
 Author      : Hasan Tafish
 email:		 : htafish@hra.com
 Date        : Nov,2016
 Build       : -std=c++11

		- My Kalman Filter class definition
 ***************************************************************************************/
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

	bool filter_initialized = false;

	std::ofstream logFile;

public:

	MyMatrix<double> X;

	MyMatrix<double> P;

	MyKalmanFilt(){};

	void initFilter(const int&, const int&, const int&, const int&);

	virtual ~MyKalmanFilt();

	virtual void setA();

	virtual void setC();

	virtual void setR();

	virtual void setQ();

	virtual void setV();

	virtual void setW();
	
	void setStateVarNum(const int&);

	void setMeasVarNum(const int&);

	void setV_size(const int&);

	void setW_size(const int&);

	void setTimeStep(const double&);

	MyMatrix<double> getP();

	void initStateAndCov(const MyMatrix<double>&, const MyMatrix<double>&);

	virtual void motionUpdate(const MyMatrix<double>&);

	virtual void sensorUpdate(const MyMatrix<double>&);

	void step(const MyMatrix<double>&, const MyMatrix<double>&);

	void logger(const std::string&, const MyMatrix<double>&, const std::string&);
};

double angle_norm(const double&);

#include "MyKalmanFilt_impl.hpp"



#endif /* MYKALMANFILT_HPP_ */
