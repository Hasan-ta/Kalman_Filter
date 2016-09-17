/*
 * MyMatrix_impl.hpp
 *
 *  Created on: Jun 24, 2016
 *      Author: hasan
 */

#ifndef MYMATRIX_IMPL_HPP_
#define MYMATRIX_IMPL_HPP_


template<typename T> MyMatrix<T>::MyMatrix()
{
	rows = 1; cols = 1;
	elements = std::vector<T>(rows*cols,0);
}

template<typename T> MyMatrix<T>::MyMatrix(const unsigned int& n, const unsigned int& m, const T& init)
{
	if((n > 0) && (m > 0))
	{
		rows = n; cols = m;
		elements = std::vector<T>(rows*cols,T(init));
	}
	else
        throw "Invalid matrix size";
}

template<typename T> MyMatrix<T>::MyMatrix(const MyMatrix<T>& a)
{
	rows = a.numOfRaws(); cols = a.numOfCols();
	elements = a.elements;

}


template<typename T> MyMatrix<T>::MyMatrix(MyMatrix<T>&& a)
{
	rows = a.numOfRaws(); cols = a.numOfCols();
	elements = a.elements;
}

/*
template<typename T> MyMatrix<T>::~MyMatrix() {
}
*/

template<typename T> inline int MyMatrix<T>:: numOfRaws() const
{
	return rows;
}

template<typename T> inline int MyMatrix<T>:: numOfCols() const
{
	return cols;
}

template<typename T> inline int MyMatrix<T>:: numOfRaws()
{
	return rows;
}

template<typename T> inline int MyMatrix<T>:: numOfCols()
{
	return cols;
}

template<typename T> inline int MyMatrix<T>:: set(const int& row, const int& col, const T& value)
{
	if((row >= rows) || (row < 0) || (col >= cols) || (col < 0))
	{
		throw "Invalid indix! can't set element out of borders";
		//return -1;
	}
	else
		elements[row*cols+col] = T(value);
	return 0;
}

template<typename T> inline T MyMatrix<T>:: get(const int& row, const int& col){
	if((row >= rows) || (row < 0) || (col >= cols) || (col < 0))
	{
		throw "Invalid indix! can't get element out of borders";
		//return -1;
	}
	else
		return elements[row*cols+col];
}

template<typename T> inline T MyMatrix<T>:: get(const int& row, const int& col) const
{
	if((row >= rows) || (row < 0) || (col >= cols) || (col < 0))
	{
		throw "Invalid indix! can't get element out of borders";
		//return -1;
	}
	else
		return elements[row*cols+col];
}


template<typename T> inline void MyMatrix<T>:: print()
{
	for (int i = 0; i< rows; ++i)
	{
		for (int j = 0; j<cols; ++j)
		{
			std::cout << std::setprecision(15) <<elements[i*cols+j] <<'\t';
		}
		std::cout<<std::endl;
	}
}

template<typename T> inline T& MyMatrix<T>:: operator() (const int& a, const int& b)
{
    /*
    typename std::vector<T>::iterator it = (elements.begin() + a*cols + b);
    return *it;
    */
	return elements[a*cols+b];
}

template<typename T> const inline T& MyMatrix<T>:: operator() (const int& a, const int& b) const
{
    /*
    typename std::vector<T>::const_iterator it = (elements.begin() + a*cols + b);
    return *it;
    */
	return elements[a*cols+b];
}


template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator= (const MyMatrix& a)
{
	rows = a.numOfRaws(); cols = a.numOfCols();
	elements = std::vector<T>(rows*cols,0);
	for (int i = 0; i< rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			this->set(i,j,T(a.get(i,j)));
	}
	return *this;
}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator= (MyMatrix&& a)
{
	rows = a.numOfRaws(); cols = a.numOfCols();
	elements = a.elements;
	return *this;
}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator+= (const T& scaler)
{

	for (int i = 0; i< rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			this->set(i,j,this->get(i,j) + scaler);
	}
	return *this;
}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator+= (const MyMatrix& a)
{
	if((a.numOfRaws() == rows) && (a.numOfCols() == cols))
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
					this->set(i,j,this->operator()(i,j) + T(a.get(i,j)));
			}
		return *this;
	}
	else
	{
		throw "Matrix Dimensions should be equivalent";
	}
}

template<typename T> inline MyMatrix<T> MyMatrix<T>:: operator+ (const T& scaler)
{
	MyMatrix<T> result(rows,cols,0);
	for (int i = 0; i< rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
				result.set(i,j,this->get(i,j) + scaler);
		}
	return result;
}

template<typename T> inline MyMatrix<T> MyMatrix<T>:: operator+ (const MyMatrix& a)
{
	MyMatrix<T> result(rows,cols,0);
	if((a.numOfRaws() == rows) && (a.numOfCols() == cols))
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
					result.set(i,j,this->operator()(i,j) + T(a.get(i,j)));
			}
		return result;
	}
	else
	{
		throw "Matrix Dimensions should be equivalent";
	}
}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator-= (const T& scaler)
{
	for (int i = 0; i< rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
				this->set(i,j,this->operator()(i,j) - scaler);
		}
	return *this;

}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator-= (const MyMatrix& a)
{
	if((a.numOfRaws() == rows) && (a.numOfCols() == cols))
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
					this->set(i,j,this->operator()(i,j) - T(a.get(i,j)));
			}
		return *this;
	}
	else
	{
		throw "Matrix Dimensions should be equivalent";
	}
}

template<typename T> inline MyMatrix<T> MyMatrix<T>:: operator- (const T& scaler)
{
	MyMatrix<T> result(rows,cols,0);
	for (int i = 0; i< rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
				result.set(i,j,this->get(i,j) - scaler);
		}
	return result;
}

template<typename T> inline MyMatrix<T> MyMatrix<T>:: operator- (const MyMatrix& a) const
{
	MyMatrix<T> result(rows,cols,0);
	if((a.numOfRaws() == rows) && (a.numOfCols() == cols))
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
                    double t1 = T(a.get(i,j));
                    double t2 = this->get(i,j);
					result.set(i,j,this->get(i,j) - T(a.get(i,j)));
                }
			}
		return result;
	}
	else
	{
		throw "Matrix Dimensions should be equivalent";
	}
}

template<typename T> inline MyMatrix<T> MyMatrix<T>:: operator/ (const T& scaler)
{
	MyMatrix<T> result(rows,cols,0);
	if(scaler != 0)
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
					result.set(i,j,this->get(i,j) / scaler);
			}
		return result;
	}
	else
		throw "Division by zero";
}

template<typename T> inline MyMatrix<T> MyMatrix<T>:: operator/ (const MyMatrix& a)
{
	MyMatrix<T> result(rows,cols,0);
	if((a.numOfRaws() == rows) && (a.numOfCols() == cols))
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					if(a.get(i,j)!=0)
						result.set(i,j,this->operator()(i,j) / T(a.get(i,j)));
					else
						throw "Division by zero!";
				}
			}
		return result;
	}
	else
	{
		throw "Matrix Dimensions should be equivalent";
	}
}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator/= (const T& scaler)
{
	if(scaler != 0)
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
					this->set(i,j,this->get(i,j) / scaler);
			}
		return *this;
	}
	else

		throw "Division by zero";
}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator/= (const MyMatrix& a)
{
	if((a.numOfRaws() == rows) && (a.numOfCols() == cols))
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					if(a.get(i,j)!=0)
						this->set(i,j,this->operator()(i,j) / T(a.get(i,j)));
					else
						throw "Division by zero!";
				}
			}
		return *this;
	}
	else
	{
		throw "Matrix Dimensions should be equivalent";
	}
}

template<typename T> inline MyMatrix<T> MyMatrix<T>:: operator* (const T& scaler)
{
	MyMatrix<T> result(rows,cols,0);
	for (int i = 0; i< rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
				result.set(i,j,this->get(i,j) * scaler);
		}
	return result;
}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator*= (const T& scaler)
{
	for (int i = 0; i< rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			this->set(i,j,this->get(i,j) * scaler);
	}
	return *this;
}

template<typename T> inline MyMatrix<T>& MyMatrix<T>:: operator*= (const MyMatrix& a)
{
	if((a.numOfRaws() == rows) && (a.numOfCols() == cols))
	{
		for (int i = 0; i< rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
					this->set(i,j,this->operator()(i,j) * T(a.get(i,j)));
			}
		return *this;
	}
	else
	{
		throw "Matrix Dimensions should be equivalent";
	}
}

template<typename T> inline MyMatrix<T> MyMatrix<T>:: operator* (const MyMatrix& a)
{
	if(this->cols == a.numOfRaws())
	{
		MyMatrix<T> result(this->rows,a.cols,0);
		for(int i=0; i<this->rows; ++i)
			for(int j=0; j<a.numOfCols(); ++j)
				for(int k=0; k<this->cols; ++k)
				{
					result.set(i,j,result(i,j) + this->get(i,k)*a.get(k,j));
				}
		return result;
	}
	else
		throw "Matrix Dimensions should be equivalent";
}

template<typename T> inline MyMatrix<T> MyMatrix<T>::transpose()
{
	MyMatrix<T> result(this->cols, this->rows,0);
	for (int i =0; i<result.numOfRaws(); ++i)
	{
		for (int j = 0; j<result.numOfCols(); ++j)
			result.set(i,j,this->get(j,i));
	}
	return result;
}

template<typename T> inline MyMatrix<T> MyMatrix<T>::UpperCholesky()
{
	MyMatrix<T> result(this->rows,this->cols,0);
	if(rows == cols)
	{
		for (int j = 0; j < cols; ++j)
		{
			for (int i = 0; i <= j; ++i)
			{
				T sum1 = 0, sum2 = 0;
				for (int k = 0; k < i; ++k)
				{
					sum1 = sum1 + T(result(k,i) * result(k,i));
					sum2 = sum2 + T(result(k,i) * result(k,j));
				}

				T beta = result(i,i);
				if(i == j)
					result(i,j) = T(sqrtf(this->get(i,j)-sum1));
				else
					result(i,j)=T((this->get(i,j)-sum2)/beta);
			}
		}
		return result;
	}
	else
		throw "Matrix Should Be Square to get upper triangular Matrix";
}
template<typename T> inline MyMatrix<T> MyMatrix<T>::InverseHermitian()
{
	MyMatrix<T> R(this->rows,this->cols,0);
	MyMatrix<T> result(this->rows,this->cols,0);
	R = this->UpperCholesky();
	for (int j = cols-1; j>= 0; --j)
	{
		for(int i = j; i>=0; --i)
		{
			if(i == j)
				result(i,j) = 1/R(i,j);
			else
			{
				T sum = 0;
				for (int k =i+1; k <= j; ++k)
					sum += R(i,k)*result(k,j);
				result(i,j) = -sum/R(i,i);
			}
		}
	}
	//result *= result.transpose(); // Fix Mult;
	result = result * result.transpose();
	return result;
}

template <typename T> inline MyMatrix<T> identity(int dim)
{
	MyMatrix<T> result(dim,dim,0);
	for (int i = 0; i < dim; ++i)
	{
		result(i,i) = T(1.0);
	}
	return result;
}



#endif /* MYMATRIX_IMPL_HPP_ */
