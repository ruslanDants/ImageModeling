#if !defined  OBJECT_H
#define OBJECT_H

#include "SampleComplex.h"
//-------------------------------------------------------------------------------------------------
class Object : public SampleComplex
{
private:
	// ��� �� �������� (�.�.)
	double m_dx;

public:
	// �����������
	// size - ���������� ���������, ���������� �� x � y (size*size)
	// dx - ��� �� �������� (�.�.)
	Object(int size, double dx);
	~Object();

	// �������� �������� � ���� �������� ������������� ������� 
	// period - ������ ������� (�.�.)
	// width  - ������ ����� (�.�.)
	void CreateLineAndSpace(double period, double width);
	// �������� �������� � ���� ����������� ������������� ������� 
	// period - ������ ������� (�.�.)
	// width  - ������ ����� (�.�.)
	void CreateLineAndSpaceAttenuaten(double period, double width);
	// �������� �������� � ���� ������������ ����������� ������������� ������� 
	// period - ������ ������� (�.�.)
	// width  - ������ ����� (�.�.)
	void CreateLineAndSpaceAlternating(double period, double width);

	// �������� �������� � ���� �������������
	void CreateHalfPlane();

	// �������� �������� � ���� ���������� ����
	// count - ���������� �������� (�����)
	void CreateTargetStar(int count);

private:
	// ������������� ������� �������� �������� � ���� ������������ ������������� ������� 
	// period - ������ ������� (�.�.)
	// width  - ������ ����� (�.�.)
	// ob_module_line, ob_phase_line - ������ � ���� "�����", �.�. ������������ ����� �������
	// ob_module_space, ob_phase_space - ������ � ���� "����������", �.�. ���������� ����� �������
	// ob_phase_space2 - ���� ������� "���������", ��� ������������ �������
	void CreateLineAndSpaceCommon(double period, double width,
		double ob_module_line = 1., double ob_phase_line = 0,
		double ob_module_space = 0., double ob_phase_space = 0,
		double ob_phase_space2 = 0);
};
//-------------------------------------------------------------------------------------------------
#endif // OBJECT_H