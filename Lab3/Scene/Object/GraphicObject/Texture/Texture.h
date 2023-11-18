<<<<<<< HEAD
#pragma once
#include "../../General_Heading.h"


// ������������ ��� ����������� ������ ����������
enum class TextureFilter {
	POINT, // ��������
	BILINEAR, // ����������
	TRILINEAR, // �����������
	ANISOTROPIC // ������������
};
// ����� ��� ������ � ���������
class Texture
{
public:
	// �������� �������� �� �������� �����
	void load(std::string filename);

	// ���������� �������� (�������� � ����������� ����� � ��������� ����������)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// ���������� ��������������� ��� ���� ���������� ������
	static void disableAll();
private:
	// ������������� (������) ����������� �������
	GLuint texIndex;
=======
#pragma once
#include "../../General_Heading.h"


// ������������ ��� ����������� ������ ����������
enum class TextureFilter {
	POINT, // ��������
	BILINEAR, // ����������
	TRILINEAR, // �����������
	ANISOTROPIC // ������������
};
// ����� ��� ������ � ���������
class Texture
{
public:
	// �������� �������� �� �������� �����
	void load(std::string filename);

	// ���������� �������� (�������� � ����������� ����� � ��������� ����������)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// ���������� ��������������� ��� ���� ���������� ������
	static void disableAll();
private:
	// ������������� (������) ����������� �������
	GLuint texIndex;
>>>>>>> 1f562be79d16193a9746e34b908252d6844f6415
};