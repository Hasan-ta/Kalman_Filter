/*
 * MyKalmanFilt_impl.hpp
 *
 *  Created on: Jun 24, 2016
 *      Author: hasan
 */

#ifndef MYKALMANFILT_IMPL_HPP_
#define MYKALMANFILT_IMPL_HPP_

#include "MyMatrix.hpp"



MyKalmanFilt::MyKalmanFilt(const double& timeStep, const int& stateNum, const int& measNum, const int& size_W, const int& size_V, bool debug_on) {
    T = timeStep;
	stateVarNum = stateNum;
	measVarNum = measNum;
	V_size = size_V;
	W_size = size_W;
	X = MyMatrix<double>(stateVarNum, 1, 0);
	Y = MyMatrix<double>(measVarNum, 1, 0);
	A = MyMatrix<double>(stateVarNum, stateVarNum, 0);
	C = MyMatrix<double>(measVarNum, stateVarNum, 0);
	R = MyMatrix<double>(W_size, W_size, 0);
	Q = MyMatrix<double>(measVarNum, measVarNum, 0);
	P = identity<double>(stateVarNum) * 1000;
	W = MyMatrix<double>(stateVarNum,W_size,0);
	V = MyMatrix<double>(measVarNum,V_size,0);
	debug = debug_on;

	if(debug_on)
        std::ofstream file("KalmanFiltLog.log",std::ios::out | std::ios::trunc);
}

MyKalmanFilt::~MyKalmanFilt() {
    if(logFile.is_open())
        logFile.close();
}

void MyKalmanFilt::setA() {
}

void MyKalmanFilt::setC() {
}

void MyKalmanFilt::setR() {
}

void MyKalmanFilt::setQ() {
}

void MyKalmanFilt::setW() {
}

void MyKalmanFilt::setV() {
}

MyMatrix<double> MyKalmanFilt::getP() {
	return P;
}

void MyKalmanFilt::init(const MyMatrix<double>& X_,
		const MyMatrix<double>& P_) {
	X = X_;
	P = P_;
}

void MyKalmanFilt::motionUpdate(const MyMatrix<double>& motion_) {
    motion = motion_;
    setA();
    setW();
    setR();
    R = W*R*W.transpose();
    //std::cout << "R: \n";
    //R.print();
    //std::cout << "A: \n";
    //A.print();
    //std::cout << "motion: \n";
    //motion.print();
	X = A*X + motion;
	X(2,0) = angle_norm(X(2,0));
	//std::cout << "Before Motion Update: \n";
	//P.print();
	P = A * P * A.transpose() + R;
	//std::cout << "After Motion Update: \n";
	//P.print();

    if(debug)
	{
        std::string separator = "-------------------------------------------------------------------";
        logger(separator, motion, "motion");
        logger("", A, "A");
        logger("", W, "W");
        logger("", R, "R");
        logger("", X, "X");
        logger("", P, "P");
    }
}

void MyKalmanFilt::sensorUpdate(const MyMatrix<double>& measure_) {
    measure = measure_;
	setC();
	setV();
	setQ();
	Q = V*Q*V.transpose();
	MyMatrix<double> S = C * P * C.transpose() + Q;
	MyMatrix<double> K = P * C.transpose() * S.InverseHermitian();
	Y = measure - C * X;
	X = X + (K * Y);

	MyMatrix<double> I = identity<double>(stateVarNum);
	P = (I - (K * C)) * P;

	if(debug)
	{
        logger("", measure, "measure");
        logger("", C, "C");
        logger("", V, "V");
        logger("", Q, "Q");
        logger("", K, "K");
        logger("", Y, "Y");
        logger("", X, "X");
        logger("", P, "P");
    }
}

void MyKalmanFilt::step(const MyMatrix<double>& measure_,
		const MyMatrix<double>& motion_) {
	motionUpdate(motion_);
	sensorUpdate(measure_);
}

void MyKalmanFilt::logger(const std::string& pre, const MyMatrix<double>& logMatrix, const std::string& matName)
{
    if(~logFile.is_open())
        logFile.open("KalmanFiltLog.log",std::ios_base::app);

    logFile << pre << "\n" << matName << ":" << std::endl;
    for (int i = 0; i< logMatrix.numOfRaws(); ++i)
	{
		for (int j = 0; j<logMatrix.numOfCols(); ++j)
		{
			logFile << std::setprecision(15) <<logMatrix(i,j) <<'\t';
		}
		logFile <<std::endl;
	}
	logFile.close();
}

double angle_norm(const double& theta)
{
    double ret = theta; //- (int)(theta/(2*M_PI));
    if((ret > 2*M_PI) || (ret < 0))
    {
        if(ret > 2*M_PI)
            ret = ret - 2*M_PI;
        else if(ret < 0)
            ret = ret + 2*M_PI;
    }
    return ret;
}



#endif /* MYKALMANFILT_IMPL_HPP_ */
