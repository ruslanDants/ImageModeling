
#if !defined  SAMPLE_H
#define SAMPLE_H

#include <ostream>
#include <iostream>
#include <fstream>
using namespace std;
//-------------------------------------------------------------------------------------------------
template <class PAR>
class Sample
{
protected:
	// число элементов выборки (одинаковое по x и y)
	int m_size;
	// указатель на динамический массив данных
	PAR* m_data;

public:
	// пустой конструктор запрещен
	explicit Sample();
	// полный конструктор
	// size - количество элементов, одинаковое по x и y (size*size)
	Sample(int size);
	// деструктор
	virtual ~Sample();

	// размер выборки
	int GetSize() const;
	// оператор получения значения элемента с номером i,j
	PAR& operator()(int i, int j);
	// оператор получения const значения элемента с номером i,j
	const PAR& operator()(int i, int j) const;

	// получение указателя на массив данных
	PAR* GetPointer();

	// инициализация всех элементов выборки одинаковым значением value
	void SetValue(PAR value);

	// операции с выборкой и числом
	// сложение всех элементов выборки и числа
	Sample<PAR>& operator+=(PAR value);
	// умножение всех элементов выборки на число
	Sample<PAR>& operator*=(PAR value);
	// деление всех элементов выборки на число
	Sample<PAR>& operator/=(PAR value);

	// операции с двумя выборками
	// присваивание
	Sample<PAR>& operator= (const Sample<PAR> &temp);
	// поэлементное сложение двух выборок
	Sample<PAR>& operator+=(const Sample<PAR> &temp);
	// поэлементное перемножение двух выборок
	Sample<PAR>& operator*=(const Sample<PAR> &temp);

	// перегрузка оператора вывода выборки в файл
	friend ostream& operator<< (ostream& out, const Sample& other);

	// вычисление реальной координаты точки с координатами i
	// (выборка квадратная, поэтому достаточно одной функции)
	// i - номер точки
	// dx - шаг по выборке
	double CalcCoord(int i, double dx = 1.) const;
};
//-------------------------------------------------------------------------------------------------
// полный конструктор
template <class PAR>
Sample<PAR>::Sample(int size)
{
	m_size = size;
	m_data = new PAR[m_size*m_size];
}
//-------------------------------------------------------------------------------------------------
// деструктор
template <class PAR>
Sample<PAR>::~Sample()
{
	delete[] m_data;
}
//-------------------------------------------------------------------------------------------------
// размер выборки
template <class PAR>
int Sample<PAR>::GetSize() const
{
	return(m_size);
}
//-------------------------------------------------------------------------------------------------
// оператор получения значения элемента с номером i,j
template <class PAR>
PAR& Sample<PAR>::operator()(int i, int j)
{
	return (m_data[i*m_size + j]);
}
//-------------------------------------------------------------------------------------------------
// оператор получения const значения элемента с номером i,j
template <class PAR>
const PAR& Sample<PAR>::operator()(int i, int j) const
{
	return (m_data[i*m_size + j]);
}
//-------------------------------------------------------------------------------------------------
// получение указателя 
template <class PAR>
PAR* Sample<PAR>::GetPointer()
{
	return m_data;
}
//-------------------------------------------------------------------------------------------------
// инициализация всех элементов выборки одинаковым значением
template <class PAR>
void Sample<PAR>::SetValue(PAR value)
{
	for (int i = 0; i<m_size*m_size; i++)
	{
		m_data[i] = value;
	}
}
//-------------------------------------------------------------------------------------------------
// сложение всех элементов выборки и числа
template <class PAR>
Sample<PAR>& Sample<PAR>::operator+=(PAR value)
{
	for (int i = 0; i<m_size*m_size; i++)
	{
		m_data[i] += value;
	}
	return *this;
}
//-------------------------------------------------------------------------------------------------
// умножение всех элементов выборки на число
template <class PAR>
Sample<PAR>& Sample<PAR>::operator*=(PAR value)
{
	for (int i = 0; i<m_size*m_size; i++)
	{
		m_data[i] *= value;
	}
	return *this;
}
//-------------------------------------------------------------------------------------------------
// деление всех элементов выборки на число
template <class PAR>
Sample<PAR>& Sample<PAR>::operator/=(PAR value)
{
	for (int i = 0; i<m_size*m_size; i++)
	{
		m_data[i] /= value;
	}
	return *this;
}
//-------------------------------------------------------------------------------------------------
// присваивание
template <class PAR>
Sample<PAR>& Sample<PAR>::operator=(const Sample<PAR> &temp)
{
	m_size = temp.m_size;
	delete[] m_data;
	m_data = new PAR[m_size*m_size];

	for (int i = 0; i<m_size*m_size; i++)
	{
		m_data[i] = temp.m_data[i];
	}
	return *this;
}

//-------------------------------------------------------------------------------------------------
// поэлементное сложение двух выборок
template <class PAR>
Sample<PAR>& Sample<PAR>::operator+=(const Sample<PAR> &temp)
{
	if (m_size != temp.m_size)
		throw("Sample::operator+= - samples sizes not valid");

	for (int i = 0; i<m_size*m_size; i++)
	{
		m_data[i] += temp.m_data[i];
	}
	return *this;
}
//-------------------------------------------------------------------------------------------------
// поэлементное перемножение двух выборок
template <class PAR>
Sample<PAR>& Sample<PAR>::operator*=(const Sample<PAR> &temp)
{
	if (m_size != temp.m_size)
		throw("Sample::operator+= - samples sizes not valid");

	for (int i = 0; i<m_size*m_size; i++)
	{
		m_data[i] *= temp.m_data[i];
	}
	return *this;
}
//-------------------------------------------------------------------------------------------------
// вычисление реальной координаты точки
// i - номер точки
// dx - шаг по выборке
template <class PAR>
double Sample<PAR>::CalcCoord(int i, double dx) const
{
	return (i - m_size / 2. + 0.5)*dx;
}
//-------------------------------------------------------------------------------------------------
// перегрузка оператора вывода выборки в файл
template <class PAR>
ostream& operator<<(ofstream& out, const Sample<PAR> &other)
{
	for (int i = 0; i<other.GetSize(); i++)
	{
		for (int j = 0; j<other.GetSize(); j++)
		{
			out << other(i, j) << " ";
		}
		out << endl;
	}
	return out;
}
//-------------------------------------------------------------------------------------------------
#endif //defined SAMPLE_H