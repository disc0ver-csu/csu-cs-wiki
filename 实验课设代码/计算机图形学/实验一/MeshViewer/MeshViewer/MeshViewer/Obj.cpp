#include "Obj.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using std::min;
using std::max;

Vector3 operator + (const Vector3& one, const Vector3& two) //两个向量相加
{
	return Vector3(one.fX + two.fX, one.fY + two.fY, one.fZ + two.fZ);
}

Vector3 operator - (const Vector3& one, const Vector3& two) //两个向量相减
{
	return Vector3(one.fX - two.fX, one.fY - two.fY, one.fZ - two.fZ);
}

Vector3 operator * (const Vector3& one, double scale) //向量与数的乘操作
{
	return Vector3(one.fX * scale, one.fY * scale, one.fZ * scale);
}

Vector3 operator / (const Vector3& one, double scale) //向量与数的除操作
{
	return one * (1.0 / scale);
}

Vector3 Cross(Vector3& one, Vector3& two) 
{//计算两个向量的叉积
	Vector3 vCross;								

	vCross.fX = ((one.fY * two.fZ) - (one.fZ * two.fY));
	vCross.fY = ((one.fZ * two.fX) - (one.fX * two.fZ));
	vCross.fZ = ((one.fX * two.fY) - (one.fY * two.fX));

	return vCross;		
}

CObj::CObj(void)
{
}


CObj::~CObj(void)
{
}

bool CObj::ReadObjFile(const char* pcszFileName) 
{//读取模型文件

	FILE* fpFile = fopen(pcszFileName, "r"); //以只读方式打开文件
	if (fpFile == NULL)
	{
		return false;
	}

	m_pts.clear(); 
	m_faces.clear();

	//TODO：将模型文件中的点和面数据分别存入m_pts和m_faces中
	char strLine[1024];
	Point point;
	Face face;
	std::string s1;
	while (!feof(fpFile))
	{
		fgets(strLine, 1024, fpFile);
		if (strLine[0] == 'v')
		{
			if (strLine[1] == 'n')
			{//vn
				
			}
			else
			{//v 点
				std::istringstream sin(strLine);
				sin >> s1 >> point.pos.fX >> point.pos.fY >> point.pos.fZ;
				m_pts.push_back(point);
			}
		}
		else if (strLine[0] == 'f')
		{// 面
			std::istringstream sin(strLine);
			sin >> s1 >> face.pts[0] >> face.pts[1] >> face.pts[2];
			ComputeFaceNormal(face);
			m_faces.push_back(face);
		}
		printf("%s\n", strLine);
	}

	fclose(fpFile);

	UnifyModel(); //将模型归一化

	return true;
}

void CObj::UnifyModel()
{//为统一显示不同尺寸的模型，将模型归一化，将模型尺寸缩放到0.0-1.0之间
//原理：找出模型的边界最大和最小值，进而找出模型的中心
//以模型的中心点为基准对模型顶点进行缩放
//TODO:添加模型归一化代码

	Vector3 vec_max, vec_min(1e5, 1e5, 1e5), vec;
	for (int i = 0; i < m_pts.size(); i++)
	{
		vec_max.fX = std::max(vec_max.fX, m_pts[i].pos.fX);
		vec_max.fY = std::max(vec_max.fY, m_pts[i].pos.fY);
		vec_max.fZ = std::max(vec_max.fZ, m_pts[i].pos.fZ);

		vec_min.fX = std::min(vec_min.fX, m_pts[i].pos.fX);
		vec_min.fY = std::min(vec_min.fY, m_pts[i].pos.fY);
		vec_min.fZ = std::min(vec_min.fZ, m_pts[i].pos.fZ);
	}

	vec.fX = vec_max.fX - vec_min.fX;
	vec.fY = vec_max.fY - vec_min.fY;
	vec.fZ = vec_max.fZ - vec_min.fZ;

	for (int i = 0; i < m_pts.size(); i++)
	{
		m_pts[i].normal = m_pts[i].pos;
		m_pts[i].normal.fX = (m_pts[i].normal.fX - vec_min.fX) / vec.fX - 0.5f;
		m_pts[i].normal.fY = (m_pts[i].normal.fY - vec_min.fY) / vec.fY - 0.5f;
		m_pts[i].normal.fZ = (m_pts[i].normal.fZ - vec_min.fZ) / vec.fZ - 0.5f;
	}

	//m_pts.push_back(vec);
}

void CObj::ComputeFaceNormal(Face& f)
{//TODO:计算面f的法向量，并保存
	f.normal = Cross(m_pts[f.pts[1]-1].pos - m_pts[f.pts[0]-1].pos, m_pts[f.pts[2]-1].pos - m_pts[f.pts[1]-1].pos);
	f.normal.Normalize();
}