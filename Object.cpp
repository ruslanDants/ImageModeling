#include "Object.h"


//-------------------------------------------------------------------------------------------------
Object::Object(int size, double dx)
	: SampleComplex(size)
	, m_dx(dx)
{
}
//-------------------------------------------------------------------------------------------------
Object::~Object()
{

}
//-------------------------------------------------------------------------------------------------
// �������� �������� � ���� �������������
void Object::CreateHalfPlane()
{
	for (int j = 0; j<m_size; j++)
	{
		for (int i = 0; i<m_size; i++)
		{
			if (i<m_size / 2)
				operator()(i, j) = complex<double>(0., 0.);
			else
				operator()(i, j) = complex<double>(1., 0.);
		}
	}
}
//-------------------------------------------------------------------------------------------------
// �������� �������� � ���� ���������� ����
void Object::CreateTargetStar(int count)
{
	double dStep = 180 / count;
	for (int j = 0; j<m_size; j++)
	{
		double y = CalcCoord(j, m_dx);
		for (int i = 0; i<m_size; i++)
		{
			double x = CalcCoord(i, m_dx);
			double dAngle = atan2(y, x) * 180 / PI + 180;// ���������� ���� � ��������� 0 - 360 ����.
			if (int(dAngle / dStep) % 2 != 0)
				operator()(i, j) = complex<double>(0., 0.);
			else
				operator()(i, j) = complex<double>(1., 0.);
		}
	}
}
//-------------------------------------------------------------------------------------------------
// �������� �������� � ���� �������� ������������� ������� 
void Object::CreateLineAndSpace(double period, double width)
{
	CreateLineAndSpaceCommon(period, width, 0., 0., 1., 0., 0.);
}
//-------------------------------------------------------------------------------------------------
// �������� �������� � ���� ����������� ������������� ������� 
void Object::CreateLineAndSpaceAttenuaten(double period, double width)
{
	CreateLineAndSpaceCommon(period, width, 0.06, PI, 1., 0., 0);
}
//-------------------------------------------------------------------------------------------------
// �������� �������� � ���� ������������ ����������� ������������� ������� 
void Object::CreateLineAndSpaceAlternating(double period, double width)
{
	CreateLineAndSpaceCommon(period, width, 0., 0., 1., 0., PI);
}
//-------------------------------------------------------------------------------------------------
// �������� �������� � ���� ������������� �������
// period - ������ ������� (�.�.)
// width - ������ ����� (�.�.)
void Object::CreateLineAndSpaceCommon(double period, double width,
	double ob_module_line, double ob_phase_line,
	double ob_module_space, double ob_phase_space, double ob_phase_space2)
{
	// ������ � ������ ������� � ���-�� ���������
	int i_period = period / m_dx;
	int i_width = width / m_dx;

	// �������� ��� ��s � sin ����� ������������ ����� (������������� �� ������� ������)
	// ��� ����� � �����������
	double ob_c_line = cos(ob_phase_line);
	double ob_s_line = sin(ob_phase_line);
	double ob_c_space = cos(ob_phase_space);
	double ob_s_space = sin(ob_phase_space);
	double ob_c_space2 = cos(ob_phase_space2);
	double ob_s_space2 = sin(ob_phase_space2);

	// ��� ������� ���-�� ��������� � ������� ������ ����� ������ ���� ������, ��� ��������� - ������
	if ((m_size % 2 == 0 && i_width % 2 != 0) || (m_size % 2 != 0 && i_width % 2 == 0))
		i_width++;
	// ������ ���������� � ���-�� ���������
	int i_space = i_period - i_width;
	// �����������, ��� ������ ���� �� ���� ������� - ����� ��� ����������
	bool bFirstline = false;
	int  i_first = (m_size / 2 - i_width / 2) / i_period;
	i_first = m_size / 2 - i_width / 2 - i_first*i_period;
	if (i_first - i_space > 0)
	{
		i_first -= i_space;
		bFirstline = true;
	}

	// ��������, ��� ����� ��������� - ����� ��� ����������, � ����� �� �������� ����
	bool bPhase = true, bLine = false;
	for (int j = 0; j<m_size; j++)
	{
		// ����������
		if ((bFirstline && (j >= (i_first + i_space) && j<(i_first + i_period) || j<i_first)) ||
			(!bFirstline && (j >= (i_first) && j<(i_first + i_width))))
		{
			if (bLine)
				bPhase = !bPhase;
			for (int i = 0; i<m_size; i++)
			{
				if (bPhase)
					operator()(i, j) = ob_module_space*complex<double>(ob_c_space, ob_s_space);
				else
					operator()(i, j) = ob_module_space*complex<double>(ob_c_space2, ob_s_space2);
			}
			bLine = false;
		}
		// �����
		else
		{
			for (int i = 0; i<m_size; i++)
			{
				operator()(i, j) = ob_module_line*complex<double>(ob_c_line, ob_s_line);
			}
			bLine = true;
		}
		if ((j + 1) >= i_first + i_period)
			i_first += i_period;
	}
}
//-------------------------------------------------------------------------------------------------