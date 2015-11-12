/////////////////////////////////////////////////////////////////////
// File: MyBoundingObjectClass.cpp
// DSA2 A10_BoundingObjectManager
// Authors:
//      Ilan Isakov
//		Marty Kurtz
//		Mary Spencer
//
// Description:
//
/////////////////////////////////////////////////////////////////////


#include "MyBoundingObjectClass.h"
//  MyBoundingObjectClass
void MyBoundingObjectClass::Init(void)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
	m_v3HalfWidth = vector3(0.0f);

	bAABBVisible = true;
	bBOVisible = true;
	v3BOColor = REWHITE;

}
void MyBoundingObjectClass::Swap(MyBoundingObjectClass& other)
{
	std::swap(m_m4ToWorld, other.m_m4ToWorld);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	std::swap(m_v3HalfWidth, other.m_v3HalfWidth);
}
void MyBoundingObjectClass::Release(void)
{

}
//The big 3
MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> a_lVectorList,String name)
{
	//Init the default values
	Init();
	sName = name;

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth.x = glm::distance(vector3(m_v3Min.x, 0.0f, 0.0f), vector3(m_v3Max.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidth.y = glm::distance(vector3(0.0f, m_v3Min.y, 0.0f), vector3(0.0f, m_v3Max.y, 0.0f)) / 2.0f;
	m_v3HalfWidth.z = glm::distance(vector3(0.0f, 0.0f, m_v3Min.z), vector3(0.0f, 0.0f, m_v3Max.z)) / 2.0f;
	
	radius = glm::distance(m_v3Center, m_v3Max);
}
MyBoundingObjectClass::MyBoundingObjectClass(MyBoundingObjectClass const& other)
{
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3HalfWidth = other.m_v3HalfWidth;
}
MyBoundingObjectClass& MyBoundingObjectClass::operator=(MyBoundingObjectClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyBoundingObjectClass temp(other);
		Swap(temp);
	}
	return *this;
}
MyBoundingObjectClass::~MyBoundingObjectClass(){ Release(); };
//Accessors
void MyBoundingObjectClass::SetModelMatrix(matrix4 a_m4ToWorld)
{ 
	m_m4ToWorld = a_m4ToWorld;

	//compute aligned box points
	vector3 boxVec[8];
	boxVec[0] = m_v3Min;
	boxVec[1] = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	boxVec[2] = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	boxVec[3] = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	boxVec[4] = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	boxVec[5] = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	boxVec[6] = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);
	boxVec[7] = m_v3Max;

	//Change to WOrld Coords
	for (int i = 0; i < 8; i++)
	{
		//printf("BOX_I[%d] X[%.3f] Y[%.3f] Z[%.3f]\n", i,boxVec[i].x,boxVec[i].y,boxVec[i].z);
		boxVec[i] = vector3(m_m4ToWorld * vector4(boxVec[i], 1.0f));
		//printf("BOXNEW_I[%d] X[%.3f] Y[%.3f] Z[%.3f]\n", i, boxVec[i].x, boxVec[i].y, boxVec[i].z);
	}

	m_v3MinNEW = m_v3MaxNEW = boxVec[0];

	//Get the max and min out of the list
	for (uint i = 0; i < 8; i++)
	{
		if (m_v3MinNEW.x > boxVec[i].x) //If min is larger than current
			m_v3MinNEW.x = boxVec[i].x;
		else if (m_v3MaxNEW.x < boxVec[i].x)//if max is smaller than current
			m_v3MaxNEW.x = boxVec[i].x;

		if (m_v3MinNEW.y > boxVec[i].y) //If min is larger than current
			m_v3MinNEW.y = boxVec[i].y;
		else if (m_v3MaxNEW.y < boxVec[i].y)//if max is smaller than current
			m_v3MaxNEW.y = boxVec[i].y;

		if (m_v3MinNEW.z > boxVec[i].z) //If min is larger than current
			m_v3MinNEW.z = boxVec[i].z;
		else if (m_v3MaxNEW.z < boxVec[i].z)//if max is smaller than current
			m_v3MaxNEW.z = boxVec[i].z;
	}

	//Center is the same
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;
	//Update halfWidth for new box
	m_v3HalfWidthNEW.x = glm::distance(vector3(m_v3MinNEW.x, 0.0f, 0.0f), vector3(m_v3MaxNEW.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidthNEW.y = glm::distance(vector3(0.0f, m_v3MinNEW.y, 0.0f), vector3(0.0f, m_v3MaxNEW.y, 0.0f)) / 2.0f;
	m_v3HalfWidthNEW.z = glm::distance(vector3(0.0f, 0.0f, m_v3MinNEW.z), vector3(0.0f, 0.0f, m_v3MaxNEW.z)) / 2.0f;

	radius = glm::distance(m_v3Center, m_v3Center + m_v3HalfWidthNEW);

}

//accessors
matrix4 MyBoundingObjectClass::GetModelMatrix(void){ return m_m4ToWorld; }
vector3 MyBoundingObjectClass::GetCenterLocal(void){ return m_v3Center; }
vector3 MyBoundingObjectClass::GetCenterGlobal(void){ return vector3(m_m4ToWorld * vector4(m_v3Center,1.0f)); }
float MyBoundingObjectClass::GetRadius(void){ return radius; }
vector3 MyBoundingObjectClass::GetHalfWidth(bool aligned)
{
	if (aligned)
		return m_v3HalfWidthNEW;
	else
		return m_v3HalfWidth;
}

/////////////////////////////////////////////////////////////////
// SetAABBVisible()
/////////////////////////////////////////////////////////////////
void MyBoundingObjectClass::SetAABBVisible(bool visible)
{
	bAABBVisible = visible;
}

/////////////////////////////////////////////////////////////////
// SetBOColor()
/////////////////////////////////////////////////////////////////
void MyBoundingObjectClass::SetBOColor(vector3 v3color)
{
	v3BOColor = v3color;
}

/////////////////////////////////////////////////////////////////
// SetBOVisible()
/////////////////////////////////////////////////////////////////
void MyBoundingObjectClass::SetBOVisible(bool visible)
{
	bBOVisible = visible;
}

/////////////////////////////////////////////////////////////////
// Render()
/////////////////////////////////////////////////////////////////
void MyBoundingObjectClass::UpdateRender()
{
	//print out info (directions only once)
	/*if (sName == "Creeper"){
		m_pMeshMngr->PrintLine("V:toggle bounding sphere B: toggle bounding box ", REYELLOW);
	}*/
	/*m_pMeshMngr->Print(sName + " Max:", RERED);
	m_pMeshMngr->Print("(" + std::to_string(GetMax(true).x) + "," + std::to_string(GetMax(true).y) + "," + std::to_string(GetMax(true).z) + ")\n");
	m_pMeshMngr->Print(sName + " Min:", REBLUE);
	m_pMeshMngr->Print("(" + std::to_string(GetMin(true).x) + "," + std::to_string(GetMin(true).y) + "," + std::to_string(GetMin(true).z) + ")\n");

	m_pMeshMngr->PrintLine(sName + " centroid: (" + std::to_string(GetCenterGlobal().x) + "," + std::to_string(GetCenterGlobal().y) + "," + std::to_string(GetCenterGlobal().z) + ")", REBLACK);*/

	if (bBOVisible)
	{
		//Axis Oriented Bounding box
		m_pMeshMngr->AddCubeToQueue(GetModelMatrix() *
			glm::translate(IDENTITY_M4, GetCenterLocal()) *
			glm::scale(GetHalfWidth(false) *2.0f), v3BOColor, WIRE);

		if (bAABBVisible)
		{
			//Axis Re-aligned bounding box
			m_pMeshMngr->AddCubeToQueue(glm::translate(GetCenterGlobal()) *
				glm::scale(GetHalfWidth(true) *2.0f), v3BOColor, WIRE);

			////Sphere Around AABB
			//m_pMeshMngr->AddSphereToQueue(
			//	glm::translate(IDENTITY_M4, GetCenterGlobal()) *
			//	glm::scale(vector3(GetRadius()) *2.0f), v3BOColor, WIRE);
		}
	}
}

//--- Non Standard Singleton Methods
bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass* const a_pOther)
{
	//NO precheck sphere collisions
	//vector3 v3MyCenter = GetCenterGlobal();
	//vector3 v3OtherCenter = a_pOther->GetCenterGlobal();
	//float dist = glm::distance(v3MyCenter, v3OtherCenter);
	//if (dist >= (GetRadius() + a_pOther->GetRadius()))
	//{
	//	return false;
	//}


	//Pre-check AABB collision

	//New box is already is global space
	vector3 v3Min = m_v3MinNEW;
	vector3 v3Max = m_v3MaxNEW;
	vector3 v3MinO = a_pOther->m_v3MinNEW;
	vector3 v3MaxO = a_pOther->m_v3MaxNEW;

	//Are they colliding?
	//For boxes we will assume they are colliding, unless at least 
	//one of the following conditions is not met
	bool bColliding = true;
	//Check for X
	if (v3Max.x < v3MinO.x)
		bColliding = false;
	if (v3Min.x > v3MaxO.x)
		bColliding = false;
	//Check for Y
	if (v3Max.y < v3MinO.y)
		bColliding = false;
	if (v3Min.y > v3MaxO.y)
		bColliding = false;
	//Check for Z
	if (v3Max.z < v3MinO.z)
		bColliding = false;
	if (v3Min.z > v3MaxO.z)
		bColliding = false;

	if (!bColliding)
		return bColliding;

	//Else AABB is colliding, continue with Spanning Axis Test

	//Form rotational matrix representing b in a's coord ref
	matrix3 R, RAbs;
	//Represent A's local Axis
	//std::vector<vector4> Aaxis = { vector4(1.0f, 0.0f, 0.0f, 0.0f) /* this->GetModelMatrix()*/,
	//	                           vector4(0.0f, 1.0f, 0.0f, 0.0f) /* this->GetModelMatrix()*/, 
	//	                           vector4(0.0f, 0.0f, 1.0f, 0.0f) /* this->GetModelMatrix()*/ };

	//std::vector<vector3> Aaxis = { vector3(1.0f, 0.0f, 0.0f) * matrix3(this->GetModelMatrix()),
	//	                           vector3(0.0f, 1.0f, 0.0f) * matrix3(this->GetModelMatrix()), 
	//	                           vector3(0.0f, 0.0f, 1.0f) * matrix3(this->GetModelMatrix()) };
	std::vector<vector3> Aaxis = { vector3(1.0f, 0.0f, 0.0f),
		                           vector3(0.0f, 1.0f, 0.0f),
		                           vector3(0.0f, 0.0f, 1.0f) };

	//Represent B's local Axis in global space?
	//std::vector<vector4> Baxis = { vector4(1.0f, 0.0f, 0.0f, 0.0f) * (a_pOther->GetModelMatrix() *glm::inverse(this->GetModelMatrix())),
	//	vector4(0.0f, 1.0f, 0.0f, 0.0f) * (a_pOther->GetModelMatrix() * glm::inverse(this->GetModelMatrix())),
	//	vector4(0.0f, 0.0f, 1.0f, 0.0f) * (a_pOther->GetModelMatrix() *  glm::inverse(this->GetModelMatrix())) };
	//std::vector<vector4> Baxis = { vector4(1.0f, 0.0f, 0.0f, 0.0f) * (a_pOther->GetModelMatrix()),
	//	vector4(0.0f, 1.0f, 0.0f, 0.0f) * (a_pOther->GetModelMatrix() ),
	//	vector4(0.0f, 0.0f, 1.0f, 0.0f) * (a_pOther->GetModelMatrix() ) };
	std::vector<vector3> Baxis = { vector3(1.0f, 0.0f, 0.0f) * matrix3(a_pOther->GetModelMatrix()),
		                           vector3(0.0f, 1.0f, 0.0f) * matrix3(a_pOther->GetModelMatrix()),
		                           vector3(0.0f, 0.0f, 1.0f) * matrix3(a_pOther->GetModelMatrix()) };

    //Form the rotation matrix by dotting the axiis with each other
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			R[i][j] = glm::dot(Aaxis[i], Baxis[j]);
		}
	}


	//Get T is A's coordinate frame
	vector3 T = vector3(a_pOther->GetCenterGlobal() - this->GetCenterGlobal());
	T = vector3(glm::dot(T, Aaxis[0]), glm::dot(T, Aaxis[1]), glm::dot(T, Aaxis[2]));

	//Compute Abs... to simplify computations
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			RAbs[i][j] = glm::abs(R[i][j]);
		}
	}

	float rA, rB;
	//Get A's local half width
	vector3 hwA = this->GetHalfWidth(false);

	//Get B's half width in global coord space?
	//vector3 hwB = a_pOther->GetHalfWidth(false);
	vector3 hwB = a_pOther->GetHalfWidth(false) * matrix3(a_pOther->GetModelMatrix());

	//debugging
	/*printf("hwA x[%f]y[%f]z[%f]  \n", hwA[0], hwA[1], hwA[2]);
	printf("hwB x[%f]y[%f]z[%f]  \n", hwB.x, hwB.y, hwB.z);
	std::cout << "A:" << this->sName << "  B:" << a_pOther->sName << std::endl;
	printf("Tx[%f] Ty[%f] Tz[%f]\n", T[0], T[1], T[2]);*/

	//Test A's 3 axiis (Ax, Ay, Az)
	for (int i = 0; i < 3; i++)
	{
		rA = hwA[i];
		rB = ((hwB[0] * RAbs[i][0]) + (hwB[1] * RAbs[i][1]) + (hwB[2] * RAbs[i][2]));

		//printf("hwA x[%f]y[%f]z[%f]  \n", hwA[0], hwA[1], hwA[2]);
		//printf("hwB x[%f]y[%f]z[%f]  \n", (hwB[0] * RAbs[i][0]), (hwB[1] * RAbs[i][1]), (hwB[2] * RAbs[i][2])
		//	);
		//printf("\n\t A_AXII RA%d[%f] RB%d[%f]", i, rA, i, rB);

		bool check = (glm::abs(T[i]) >(rA + rB));
		if (check){
			return false;
			//printf(" T>a+b =Plane\n");
		}
		else{
			printf(" T>a+b =none\n");
		}
	}

	//Test B's 3 axiis (Bx, By, Bz)
	for (int i = 0; i < 3; i++)
	{
		rA = ((hwA[0] * RAbs[0][i]) + (hwA[1] * RAbs[1][i]) + (hwA[2] * RAbs[2][i]));
		rB = hwB[i];
		float td = glm::abs(T[0] * R[0][i] + T[1] * R[1][i] + T[2] * R[2][i]);
		//printf("\n\t B_AXII RA%d[%f] RB%d[%f]", i, rA, i, rB);

		bool check = (td >(rA + rB));
		if (check){
			return false;
		}
		//printf(" T>a+b =Plane\n");
		else{
			printf(" T>a+b =none\n");
		}
	}
	printf(" Before 0");

	//Check for the other axiis by applying crossproduct between the axiis

	// Ax X Bx
	rA = hwA[1] * RAbs[2][0] + hwA[2] * RAbs[1][0];
	rB = hwB[1] * RAbs[0][2] + hwB[2] * RAbs[0][1];
	if (!glm::abs(T[2] * R[1][0] - T[1] * R[2][0]) > (rA + rB)) 
		return true;
	printf("1");

	// Ax X By
	rA = hwA[1] * RAbs[2][1] + hwA[2] * RAbs[1][1];
	rB = hwB[0] * RAbs[0][2] + hwB[2] * RAbs[0][0];
    if (!glm::abs(T[2] * R[1][1] - T[1] * R[2][1]) > (rA + rB))
		return true;
	printf("2");

	// Ax X Bz
	rA = hwA[1] * RAbs[2][2] + hwA[2] * RAbs[1][2];
	rB = hwB[0] * RAbs[0][1] + hwB[1] * RAbs[0][0];
	if (!glm::abs(T[2] * R[1][2] - T[1] * R[2][2]) > (rA + rB))
		return true;
	printf("3");

	// Ay X Bx
	rA = hwA[0] * RAbs[2][0] + hwA[2] * RAbs[0][0];
	rB = hwB[1] * RAbs[1][2] + hwB[2] * RAbs[1][1];
	if (!glm::abs(T[0] * R[2][0] - T[2] * R[0][0]) > (rA + rB))
		return true;
	printf("4");

	// Ay X By
	rA = hwA[0] * RAbs[2][1] + hwA[2] * RAbs[0][1];
	rB = hwB[0] * RAbs[1][2] + hwB[2] * RAbs[1][0];
	if (!glm::abs(T[0] * R[2][1] - T[2] * R[0][1]) > (rA + rB))
		return true;
	printf("5");

	// Ay X Bz
	rA = hwA[0] * RAbs[2][2] + hwA[2] * RAbs[0][2];
	rB = hwB[0] * RAbs[1][1] + hwB[1] * RAbs[1][0];
	if (!glm::abs(T[0] * R[2][2] - T[2] * R[0][2]) > (rA + rB))
		return true;
	printf("6");

	// Az X Bx
	rA = hwA[0] * RAbs[1][0] + hwA[1] * RAbs[0][0];
	rB = hwB[1] * RAbs[2][2] + hwB[2] * RAbs[2][1];
	if (!glm::abs(T[1] * R[0][0] - T[0] * R[1][0]) > (rA + rB))
		return true;
	printf("7");

	// Az X Bx
	rA = hwA[0] * RAbs[1][1] + hwA[1] * RAbs[0][1];
	rB = hwB[0] * RAbs[2][2] + hwB[2] * RAbs[2][0];
	if (!glm::abs(T[1] * R[0][1] - T[0] * R[1][1]) > (rA + rB))
		return true;
	printf("8");

	// Az X Bz
	rA = hwA[0] * RAbs[1][2] + hwA[1] * RAbs[0][2];
	rB = hwB[0] * RAbs[2][1] + hwB[1] * RAbs[2][0];
	if (!glm::abs(T[1] * R[0][2] - T[0] * R[1][2]) > (rA + rB))
		return true;
	printf("9");


	//Other attemps to slove the Spanning Axis Test..
    /*//float rA, rB; //the projection of radii on axis
	//Convert matrix B into matrix A coordinates (WtoA * BtoW)
	matrix4 WtoA = glm::inverse(this->GetModelMatrix());
	matrix4 WtoB = glm::inverse(a_pOther->GetModelMatrix());
	matrix4 AtoB = this->GetModelMatrix() * WtoB;
	matrix4 BtoA = a_pOther->GetModelMatrix() * WtoA;
	//Compute T translatoin vector
	vector3 t3, t3a, t3b;
	t3b = a_pOther->GetCenterGlobal();
	t3a = this->GetCenterGlobal();
	//vector4 T = vector4((t3b[0] - t3a[0]),(t3b[1] - t3a[1]),(t3b[2] - t3a[2]),0.0f);
	//Convert to A's coords
	//T = T * WtoA;
	std::cout << "A:" << this->sName << "  B:" << a_pOther->sName << std::endl;
	printf("Tx[%f] Ty[%f] Tz[%f]", T[0], T[1], T[2]);

	//Test A's x, y, z axis  (L = A0,A1,A2)
	vector4 bHalfWidthInA = vector4(a_pOther->m_v3HalfWidth, 0.0f) * BtoA;
	vector4 bHalfWidthInG = vector4(a_pOther->m_v3HalfWidth, 0.0f) * a_pOther->GetModelMatrix();
	vector4 aHalfWidth = vector4(this->m_v3HalfWidth, 0.0f) * this->GetModelMatrix();
	for (int i = 0; i < 3; i++)
	{
		rA = this->m_v3HalfWidth[i];
		rB = bHalfWidthInA[i];
		//radiusA = the hlaf width on this axis
		rA = aHalfWidth[i];
		//radiusB = the halfwidth of B in A coords
		rB = bHalfWidthInG[i];

		printf("\n\t A_AXII RA%d[%f] RB%d[%f]", i, rA, i, rB);

		bool check = (glm::abs(T[i]) >(glm::abs(rA) + glm::abs(rB)));
		if (check){
			return false;
			printf(" T>a+b =Plane\n");
		}
		else{
			printf(" T>a+b =none\n");
		}
	}
	//Test B's x,y,z axis (L = B0,B1,B2)
	vector4 aHalfWidthInB = vector4(this->m_v3HalfWidth, 0.0f) * AtoB;
	for (int i = 0; i < 3; i++)
	{
		rB = a_pOther->m_v3HalfWidth[i];
		rA = aHalfWidthInB[i];
		printf("\n\t B_AXII RA%d[%f] RB%d[%f]", i, rA, i, rB);

		bool check = (glm::abs(T[i]) >(rA + rB));
		if (check){
			printf(" T>a+b =[N]");
			return false;
		}
		else{
			printf(" T>a+b =[Y]");
		}
	}*/


	//Otherwise they must be intersecting
	return true;
}


vector3 MyBoundingObjectClass::GetMax(bool global){
	std::cout << m_v3MaxNEW.x;
	return m_v3MaxNEW;
}

vector3 MyBoundingObjectClass::GetMin(bool global){
	return m_v3MinNEW;
}