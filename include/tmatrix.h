// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<class T> 
class TDynamicVector
{
protected:
    int sz;
    T* pMem;
    int startInd;
public:
    TDynamicVector(int size = 5, int stInd = 0);
    TDynamicVector(const TDynamicVector& v);
    TDynamicVector(TDynamicVector&& v) ;
    ~TDynamicVector();

    int size();
    int getStartInd();
    void fillVec(int num);

    TDynamicVector& operator=(const TDynamicVector& v);
    bool operator==(const TDynamicVector& v) const;
    bool operator!=(const TDynamicVector& v) const;

    TDynamicVector operator+(T val);
    TDynamicVector operator-(T val);
    TDynamicVector operator*(T val);

    TDynamicVector operator+(const TDynamicVector& v);
    TDynamicVector operator-(const TDynamicVector& v);
    T operator*(const TDynamicVector& v);

    T& operator[](int ind);
    friend istream& operator>>(istream& istr, TDynamicVector& v) 
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) 
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};

template<class T>
TDynamicVector<T>::TDynamicVector(int size,int stInd) : sz(size),startInd(stInd)
{
    if ((size <= 0) || (size > MAX_VECTOR_SIZE) || (stInd < 0) || (stInd > MAX_MATRIX_SIZE - 1)) 
    {
        throw out_of_range("Wrong Size or Startt Index");
    }
    pMem = new T[size]{};// {}; // У типа T д.б. констуктор по умолчанию
}
  template<class T>
  TDynamicVector<T>::TDynamicVector(const TDynamicVector<T>& v)
  {
      sz = v.sz;
      startInd = v.startInd;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) 
      {
          pMem[i] = v.pMem[i];
      }
  }
  template<class T>
  TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& v) 
  {
      sz = v.sz;
      startInd = v.startInd;
      pMem = v.pMem;
      v.sz = 0;
      v.startInd = 0;
      v.pMem = nullptr;
  }
  template<class T>
  TDynamicVector<T>::~TDynamicVector()
  {
      delete[]pMem;
  }
  template<class T>
  void TDynamicVector<T>::fillVec(int num)
  {
      for (int i = startInd; i < sz; i++) 
      {
          pMem[i] = num;
      }
  }
  template<class T>
  TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector& v)
  {
      if (this == &v) 
      {
          return *this;
      }
      if (sz != v.sz) 
      {
          delete[]pMem;
          T* vec = new T[v.sz];
          pMem = vec;
          sz = v.sz;
      }
      startInd = v.startInd;
      for (int i = 0; i < sz; i++) 
      {
          pMem[i] = v.pMem[i];
      }
      return *this;
  }
  template<class T>
  int  TDynamicVector<T>::size() 
  { 
      return sz;
  }
  template<class T>
  int TDynamicVector<T>::getStartInd()
  {
      return startInd;
  }

  // индексация
  template<class T>
  T& TDynamicVector<T>::operator[](int ind)
  {
      ind -= startInd;
      if ((ind < 0) || (ind >= sz)) 
      {
          throw string("Wrong Index");
      }
      return pMem[ind];
  }

  // сравнение
  template<class T>
  bool TDynamicVector<T>::operator==(const TDynamicVector& v) const 
  {
      if (this == &v) 
      {
          return true;
      }
      if (sz != v.sz) 
      {
          return false;
      }
      if (startInd != v.startInd) 
      {
          return false;
      }
      for (int i = 0; i < sz; i++) 
      {
          if (pMem[i] != v.pMem[i]) 
          {
              return false;
          }
      }
      return true;
  }
  template<class T>
  bool TDynamicVector<T>::operator!=(const TDynamicVector& v) const 
  {
      return !(*this == v);
         
  }

  // скалярные операции
  template<class T>
  TDynamicVector<T> TDynamicVector<T>::operator+(T val)
  {
      TDynamicVector<T> vec(sz,startInd);
      for (int i = 0; i < sz; i++) 
      {
          vec.pMem[i] = pMem[i] + val;
      }
      return vec;

  }
  template<class T>
  TDynamicVector<T> TDynamicVector<T>::operator-(T val)
  {
      TDynamicVector<T> vec(sz,startInd);
      for (int i = 0; i < sz; i++)
      {
          vec.pMem[i] = pMem[i] - val;
      }
      return vec;

  }
  template<class T>
  TDynamicVector<T> TDynamicVector<T>::operator*(T val)
  {
      TDynamicVector<T> vec(sz,startInd);
      for (int i = 0; i < sz; i++)
      {
          vec.pMem[i] = pMem[i] * val;
      }
      return vec;
  }

  // векторные операции
  template<class T>
  TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& v)
  {
      if ((sz != v.sz) ||(startInd!=v.startInd))
      {
          throw string("Different vectors sizes");
      }
      TDynamicVector<T> vec(sz,startInd);
      for (int i = 0; i < sz; i++) 
      {
          vec.pMem[i] = pMem[i] + v.pMem[i];
      }
      return vec;
  }
  template<class T>
  TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& v)
  {
      if ((sz != v.sz) || (startInd != v.startInd))
      {
          throw string("Different vectors sizes");
      }
      TDynamicVector<T> vec(sz,startInd);
      for (int i = 0; i < sz; i++)
      {
          vec.pMem[i] = pMem[i] - v.pMem[i];
      }
      return vec;
  }
  template<class T>
  T TDynamicVector<T>::operator*(const TDynamicVector<T>& v)
  {
      if ((sz != v.sz) || (startInd != v.startInd))
      {
          throw string("Different vectors sizes");
      }
      T sum = 0;
      for (int i = 0; i < sz; i++)
      {
          sum+= pMem[i] * v.pMem[i];
      }
      return sum;
  }



// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<class T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{

public:

    TDynamicMatrix(int size = 5);
    TDynamicMatrix(const TDynamicMatrix& m);
    TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& m);
    void fillMat(int num);

    bool operator==(const TDynamicMatrix& m) const;
    bool operator!=(const TDynamicMatrix& m) const;

    TDynamicMatrix& operator=(const TDynamicMatrix& m);
    TDynamicMatrix operator+(const TDynamicMatrix& m);
    TDynamicMatrix operator-(const TDynamicMatrix& m); 
    TDynamicMatrix operator*(const TDynamicMatrix& m);
    
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v) 
    {
        for (int i = 0; i < v.sz; i++)
        {
            istr >> v.pMem[i];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) 
    {
        for (int i = 0; i < v.sz; i++)
        {
            ostr << v.pMem[i] << endl;
        }
        return ostr;
    }

};
template<class T>
TDynamicMatrix<T>::TDynamicMatrix(int size) : TDynamicVector<TDynamicVector<T>>(size)
{
    if ((size <= 0) || (size > MAX_MATRIX_SIZE))
    {
        throw string("Wrong matrix size");
    }
    for (int i = 0; i < size; i++)
    {
        TDynamicVector<T> vec(size - i, i);
        this->pMem[i] = vec;
    }
}
template<class T>
void TDynamicMatrix<T>::fillMat(int num)
{
    for (int i = 0; i < sz; i++)
    {
        pMem[i].fillVec(num);
    }
}
template<class T>
TDynamicMatrix<T>::TDynamicMatrix(const TDynamicMatrix<T>& m) :
    TDynamicVector<TDynamicVector<T>>(m) {}
template<class T>
TDynamicMatrix<T>::TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& m) :
    TDynamicVector<TDynamicVector<T>>(m) {}

// сравнение
template<class T>
bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& m) const
{
    return TDynamicVector<TDynamicVector<T>>::operator==(m);
}
template<class T>
bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix<T>& m) const
{
    return !(*this == m);
}
template<class T>
TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(const TDynamicMatrix<T>& m)
{
    if (this == &m)
        return *this;
    if (this->sz != m.sz)
    {
        delete[] this->pMem;
        this->sz = m.sz;
        this->pMem = new TDynamicVector<T>[sz];
    }
    for (int i = 0; i < this->sz; i++) {
        this->pMem[i] = m.pMem[i];
    }
    return *this;
}
// матрично-матричные операции
template<class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m)
{
    return TDynamicVector<TDynamicVector<T>>::operator+(m);
}
template<class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m)
{
    return TDynamicVector<TDynamicVector<T>>::operator-(m);
}
template<class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m)
{
}


#endif
