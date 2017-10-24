
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
	// ����� ��������� ������� (���������� �� x � y)
	int m_size;
	// ��������� �� ������������ ������ ������
	PAR* m_data;

public:
	// ������ ����������� ��������
	explicit Sample();
	// ������ �����������
	// size - ���������� ���������, ���������� �� x � y (size*size)
	Sample(int size);
	// ����������
	virtual ~Sample();

	// ������ �������
	int GetSize() const;
	// �������� ��������� �������� �������� � ������� i,j
	PAR& operator()(int i, int j);
	// �������� ��������� const �������� �������� � ������� i,j
	const PAR& operator()(int i, int j) const;

	// ��������� ��������� �� ������ ������
	PAR* GetPointer();

	// ������������� ���� ��������� ������� ���������� ��������� value
	void SetValue(PAR value);

	// �������� � �������� � ������
	// �������� ���� ��������� ������� � �����
	Sample<PAR>& operator+=(PAR value);
	// ��������� ���� ��������� ������� �� �����
	Sample<PAR>& operator*=(PAR value);
	// ������� ���� ��������� ������� �� �����
	Sample<PAR>& operator/=(PAR value);

	// �������� � ����� ���������
	// ������������
	Sample<PAR>& operator= (const Sample<PAR> &temp);
	// ������������ �������� ���� �������
	Sample<PAR>& operator+=(const Sample<PAR> &temp);
	// ������������ ������������ ���� �������
	Sample<PAR>& operator*=(const Sample<PAR> &temp);

	// ���������� ��������� ������ ������� � ����
	friend ostream& operator<< (ostream& out, const Sample& other);

	// ���������� �������� ���������� ����� � ������������ i
	// (������� ����������, ������� ���������� ����� �������)
	// i - ����� �����
	// dx - ��� �� �������
	double CalcCoord(int i, double dx = 1.) const;
};
//-------------------------------------------------------------------------------------------------
// ������ �����������
template <class PAR>
Sample<PAR>::Sample(int size)
{
	m_size = size;
	m_data = new PAR[m_size*m_size];
}
//-------------------------------------------------------------------------------------------------
// ����������
template <class PAR>
Sample<PAR>::~Sample()
{
	delete[] m_data;
}
//-------------------------------------------------------------------------------------------------
// ������ �������
template <class PAR>
int Sample<PAR>::GetSize() const
{
	return(m_size);
}
//-------------------------------------------------------------------------------------------------
// �������� ��������� �������� �������� � ������� i,j
template <class PAR>
PAR& Sample<PAR>::operator()(int i, int j)
{
	return (m_data[i*m_size + j]);
}
//-------------------------------------------------------------------------------------------------
// �������� ��������� const �������� �������� � ������� i,j
template <class PAR>
const PAR& Sample<PAR>::operator()(int i, int j) const
{
	return (m_data[i*m_size + j]);
}
//-------------------------------------------------------------------------------------------------
// ��������� ��������� 
template <class PAR>
PAR* Sample<PAR>::GetPointer()
{
	return m_data;
}
//-------------------------------------------------------------------------------------------------
// ������������� ���� ��������� ������� ���������� ���������
template <class PAR>
void Sample<PAR>::SetValue(PAR value)
{
	for (int i = 0; i<m_size*m_size; i++)
	{
		m_data[i] = value;
	}
}
//-------------------------------------------------------------------------------------------------
// �������� ���� ��������� ������� � �����
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
// ��������� ���� ��������� ������� �� �����
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
// ������� ���� ��������� ������� �� �����
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
// ������������
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
// ������������ �������� ���� �������
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
// ������������ ������������ ���� �������
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
// ���������� �������� ���������� �����
// i - ����� �����
// dx - ��� �� �������
template <class PAR>
double Sample<PAR>::CalcCoord(int i, double dx) const
{
	return (i - m_size / 2. + 0.5)*dx;
}
//-------------------------------------------------------------------------------------------------
// ���������� ��������� ������ ������� � ����
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