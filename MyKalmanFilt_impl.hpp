/****************************************************************************************
 Author      : Hasan Tafish
 email:		 : htafish@hra.com
 Date        : Nov,2016
 Build       : -std=c++11

		- Implelemntation of MyKalmanFilt functionality
 ***************************************************************************************/
#ifndef MYKALMANFILT_IMPL_HPP_
#define MYKALMANFILT_IMPL_HPP_

#include "MyMatrix.hpp"


void MyKalmanFilt::initFilter(const int& stateNo, const int& measNo, const int& stateNoiseSize, const int& measureNoiseSize){
	setStateVarNum(stateNo);
	setMeasVarNum(measNo);	
	setV_size(measureNoiseSize);
	setW_size(stateNoiseSize);

	X = MyMatrix<double>(stateVarNum, 1, 0);
	Y = MyMatrix<double>(measVarNum, 1, 0);
	A = MyMatrix<double>(stateVarNum, stateVarNum, 0);
	C = MyMatrix<double>(measVarNum, stateVarNum, 0);
	R = MyMatrix<double>(W_size, W_size, 0);
	Q = MyMatrix<double>(measVarNum, measVarNum, 0);
	P = identity<double>(stateVarNum) * 1000;
	W = MyMatrix<double>(stateVarNum,W_size,0);
	V = MyMatrix<double>(measVarNum,V_size,0);
	
	filter_initialized = true;
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

void MyKalmanFilt::setTimeStep(const double& t){
	T = t;
}

MyMatrix<double> MyKalmanFilt::getP() {
	return P;
}

void MyKalmanFilt::initStateAndCov(const MyMatrix<double>& X_,
		const MyMatrix<double>& P_) {
	X = X_;
	P = P_;
}

void MyKalmanFilt::setStateVarNum(const int& n){
	stateVarNum = n;
}

void MyKalmanFilt::setMeasVarNum(const int& n){
	measVarNum = n;
}

void MyKalmanFilt::setV_size(const int& n){
	V_size = n;
}


void MyKalmanFilt::setW_size(const int& n){
	W_size = n;
}


void MyKalmanFilt::motionUpdate(const MyMatrix<double>& motion_) {
	if(!filter_initialized)
		throw "Initialize filter first by calling initFilter!";
	else
	{
		motion = motion_;
		setA();
		setW();
		setR();
		R = W*R*W.transpose();
		X = A*X + motion;
		P = A * P * A.transpose() + R;

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
}

void MyKalmanFilt::sensorUpdate(const MyMatrix<double>& measure_) {	
	if(!filter_initialized)
		throw "Initialize filter first by calling initFilter!";
	else
	{
		measure = measure_;
		MyMatrix<double>g(2,1,0);
		g(0,0) = X(0,0);
		g(1,0) = X(3,0);
		setC();
		setV();
		setQ();
		Q = V*Q*V.transpose();
		MyMatrix<double> S = C * P * C.transpose() + Q;
		MyMatrix<double> K = P * C.transpose() * S.InverseHermitian();
		Y = measure - g;
		X = X + (K * Y);

		MyMatrix<double> I = identity<double>(stateVarNum);
		P = (I - (K * C)) * P;

		if(debug)
		{
			logger("", V, "V");
			logger("", Q, "Q");
			logger("", S, "S");
			logger("", S.UpperCholesky(), "chol(s)");
			logger("", S.InverseHermitian(), "S^-1");
			logger("", K, "K");
			logger("", X, "X");
			logger("", P, "P");
		}
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
