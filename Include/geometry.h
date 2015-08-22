//=================================================================================
//	geometry.h : RoboLogic

#ifndef _CAD_DEF_H_
#define _CAD_DEF_H_

#include <math.h>
#include <afxtempl.h>

#define CAD_ZERO		1.0E-6
#define NC_ZERO		1.0E-3
#define IS_ZERO(x)		(fabs(x)<=CAD_ZERO)
#define IS_NCZERO(x)		(fabs(x)<=NC_ZERO)
#define IS_BETWEEN(x,min,max) (x<=max && x>=min)
#define PI	3.1415926535

typedef struct tagPoint2D{
	float x;
	float y;
} POINT2D, *PPOINT2D;

typedef struct tagVector2D{
	float dx;
	float dy;
} VECTOR2D,*PVECTOR2D;

typedef struct tagPoint3D{
	float x;
	float y;
	float z;
} POINT3D, *PPOINT3D;

typedef struct tagVector3D{
	float dx;
	float dy;
	float dz;
} VECTOR3D,*PVECTOR3D;

typedef struct tagMatrix2D{
	float A[3][3];
} MATRIX2D, *PMATRIX2D;

typedef struct  tagMatrix3D{
	float A[4][4];
} MATRIX3D, *PMATRIX3D;

class CPoint2D;
class CPoint3D;
class CVector2D;
class CVector3D;
class CMatrix2D;
class CMatrix3D;

class AFX_EXT_CLASS CPoint2D :public POINT2D
{
public:
	CPoint2D();
	CPoint2D(float ix,float iy);
	CPoint2D(const float*);
	CPoint2D(POINT2D p);
	~CPoint2D();

public:
	//operators
	CPoint2D operator*(const MATRIX2D& matrix) const;
	void  operator*=(const MATRIX2D& matrix);

	//offsetting with vector
	CPoint2D operator+(VECTOR2D v) const;
	void operator+=(VECTOR2D v);
	CPoint2D operator-(VECTOR2D v) const;
	void operator-=(VECTOR2D v);

	//derived vector = this point - sp
	CVector2D operator-(POINT2D sp) const;
} ;

// Intersection Point structure
typedef struct tagInterPOINT2D{
	CPoint2D interPt;
	float t0;
	float t1;
} INTERPOINT2D,*PINTERPOINT2D;


class AFX_EXT_CLASS CVector2D : public VECTOR2D  
{
public:
	CVector2D();
	CVector2D(float ix,float iy=0.0);
	CVector2D(const float* pv);
	CVector2D(VECTOR2D v);
	virtual ~CVector2D();

public:
	//operators declaration
	CVector2D operator+(VECTOR2D v) const;
	CVector2D operator-(VECTOR2D v) const;
	void operator+=(VECTOR2D v);
	void operator-=(VECTOR2D v);
	CVector2D operator*(float d) const;
	void operator*=(float d);
	CVector2D operator/(float d) const;
	void operator/=(float d);

	// cross product
	CVector3D operator*(VECTOR2D v) const;
	
	// dot product
	float operator|(VECTOR2D v) const;

	//matrix transformation
    CVector2D operator*(const MATRIX2D& matrix ) const;
    void operator*=(const MATRIX2D& matrix );

	//methods declaration
	float GetLength()const;
	CVector2D GetNormal()const;
	void Normalize();
	BOOL   IsZeroLength() const;
};

class AFX_EXT_CLASS CPoint3D :public POINT3D
{
public:
	CPoint3D();
	CPoint3D(float ix,float iy,float iz=0.0);
	CPoint3D(const float*);
	CPoint3D(POINT3D p);
	~CPoint3D();

public:
	//operators
	CPoint3D operator*(const MATRIX3D& matrix) const;
	void  operator*=(const MATRIX3D& matrix);

	//offsetting with vector
	CPoint3D operator+(VECTOR3D v) const;
	void operator+=(VECTOR3D v);
	CPoint3D operator-(VECTOR3D v) const;
	void operator-=(VECTOR3D v);

	BOOL operator==(POINT3D pos) const;
	BOOL operator!=(POINT3D pos) const;

	//derived vector = this point - sp
	CVector3D operator-(POINT3D sp) const;
} ;

class AFX_EXT_CLASS CVector3D: public VECTOR3D
{
public:
	CVector3D();
	CVector3D(float dx,float dy,float dz=0);
	CVector3D(const float*);
	CVector3D(VECTOR3D v);
	virtual ~CVector3D();

	//operator
	CVector3D operator+(VECTOR3D v) const;
	void operator+=(VECTOR3D v);
	CVector3D operator-(VECTOR3D v) const;
	void operator-=(VECTOR3D v);

	CVector3D operator*(float d) const;
	void operator*=(float d);
	CVector3D operator/(float d) const;
	void operator/=(float d);

	//cross product
	CVector3D operator*(VECTOR3D v) const;
	
	//dot product
	float operator|(VECTOR3D v) const;

	CVector3D operator*(const MATRIX3D& matrix) const;
	void  operator*=(const MATRIX3D& matrix);

	//length
	float GetLength() const;
	float GetLengthXY() const;
	float GetLengthYZ() const;
	float GetLengthZX() const;
	
	CVector3D	GetNormal() const;
	void		Normalize();
	BOOL		IsZeroLength() const;
};


class AFX_EXT_CLASS CMatrix2D : public MATRIX2D
{
public:
	CMatrix2D();
	CMatrix2D(const MATRIX2D&);
	CMatrix2D(const float *);
	virtual ~CMatrix2D();

	//operators
	CMatrix2D operator*(const MATRIX2D&) const;
	void operator*=(const MATRIX2D&);

	//methods
	void	IdenticalMatrix();
	float	GetValue() const;
public:
	// static member functions
	static float GetValue(float a00, float a01,
						   float a10, float a11);
	static CMatrix2D CreateMirrorMatrix(VECTOR2D vect);
	static CMatrix2D CreateRotateMatrix(float angle);
	static CMatrix2D CreateScaleMatrix(float);
	static CMatrix2D CreateTransfMatrix(VECTOR2D vect);
} ; 

class AFX_EXT_CLASS CMatrix3D : public MATRIX3D
{
public:
	CMatrix3D();
	CMatrix3D(const MATRIX3D&);
	CMatrix3D(const float *);
	virtual ~CMatrix3D();
public:
	//operators
	CMatrix3D operator*(const MATRIX3D& matrix)const;
	void operator*=(const MATRIX3D& matrix);

	//methods
	void   IdenticalMatrix();
	float GetValue() const;

public:
	// static member functions
	static float GetValue(float a00, float a01, float a02,
						   float a10, float a11, float a12,
						   float a20, float a21, float a22);
	static CMatrix3D CreateMirrorMatrix(VECTOR3D plnNorm);
	static CMatrix3D CreateRotateMatrix(float da,VECTOR3D bv);
	static CMatrix3D CreateScaleMatrix(float);
	static CMatrix3D CreateTransfMatrix(VECTOR3D vec);
} ; 

//////////////////////////////////////////////////////////////////////////
//  (x0,y0): the left and bottom corner
//  (x1,y1): the right and top corner
//////////////////////////////////////////////////////////////////////////
typedef struct tagBox2D{
	float x0;
	float y0;
	float x1;
	float y1;
} BOX2D , *PBOX2D;

class AFX_EXT_CLASS CBox2D : public BOX2D
{

//constructor && destructor
public:
	CBox2D();
	CBox2D(float ix0,float iy0,float ix1,float iy1);
	CBox2D(POINT2D pt0,POINT2D pt1);
	CBox2D(BOX2D b);
	CBox2D(POINT2D p,VECTOR2D v);
	virtual ~CBox2D();

// operator
public:
//// get the union box of this and box b.
	CBox2D operator+(BOX2D b) const;
	void operator+=(BOX2D b);

//// get the intersect box of this and box b.
	CBox2D operator&(BOX2D b) const;
	void operator&=(BOX2D b);

// get attribs
public:
	BOOL   IsZero() const;
	float Width() const;		// Length of X direction
	float Height()const;		// Length of Y direction

// relationship culation
public:
	enum {enumSeparated,enumIntersected};
	UINT GetRelationWith(BOX2D b) const;
protected:
	void normalize();
};

//////////////////////////////////////////////////////////////////////////
//  (x0,y0): the left and bottom corner
//  (x1,y1): the right and top corner
//////////////////////////////////////////////////////////////////////////
typedef struct tagBox3D{
	float x0;
	float y0;
	float z0;
	float x1;
	float y1;
	float z1;
} BOX3D , *PBOX3D;

class AFX_EXT_CLASS CBox3D : public BOX3D
{

//constructor && destructor
public:
	CBox3D();
	CBox3D(float ix0,float iy0,float iz0, float ix1,float iy1, float iz1);
	CBox3D(POINT3D pt0,POINT3D pt1);
	CBox3D(BOX3D b);
	CBox3D(POINT3D p,VECTOR3D v);
	virtual ~CBox3D();

// operator
public:
//// get the union box of this and box b.
	CBox3D operator+(BOX3D b) const;
	void operator+=(BOX3D b);

//// get the intersect box of this and box b.
	CBox3D operator&(BOX3D b) const;
	void operator&=(BOX3D b);
	CBox3D operator*( float sc ) const;
	void operator*= ( float sc );
	CBox3D operator*( const MATRIX3D& matrix ) const;
	void operator*= ( const MATRIX3D& matrix );
	BOOL operator<< ( BOX3D b )const ;
	BOOL operator>> ( BOX3D b ) const;
	BOOL operator>> ( POINT3D p ) const;
	CBox3D operator|(BOX3D b) const;
	void operator|=(BOX3D b);

	CBox3D operator+(VECTOR3D vect) const;
	void operator+=(VECTOR3D vect);
	CBox3D operator-(VECTOR3D vect)const;
	void operator-=(VECTOR3D vect);

// get attribs
	BOOL	IsEmpty() const;
	float	Width() const;	 //// Length of X direction
	float	Height() const; //// Length of Z direction
	float	Length( )const; //// Length of Y direction

	enum {enumSeparated,enumIntersected};
	UINT GetRelationWith(BOX3D b) const;

protected:
	void normalize();
};

//====================================================================================

//===================================================================================

// exported API functions
float	AFX_EXT_API _AngleBetween(VECTOR2D v1,VECTOR2D v2);
float	AFX_EXT_API _AngleBetween(VECTOR3D v1,VECTOR3D v2);
float	AFX_EXT_API _DistOf(POINT2D pt0, POINT2D pt1);
float	AFX_EXT_API _DistOf(POINT3D pt0, POINT3D pt1);
BOOL	AFX_EXT_API _IsParallel(VECTOR2D v0,VECTOR2D v1);
BOOL	AFX_EXT_API _IsParallel(VECTOR3D v0,VECTOR3D v1);
BOOL	AFX_EXT_API _IsOrthogonal(VECTOR3D v0,VECTOR3D v1);
void	AFX_EXT_API HSV_TO_RGB( float h, float s, float v, float *r, float *g, float *b );
void	AFX_EXT_API RGB_TO_HSV( float r, float g, float b, float *h, float *s, float *v );
void	AFX_EXT_API MultVector( CVector2D &v1, CVector2D &v2, CVector2D &result );
void	AFX_EXT_API MultVector( CVector3D &v1, CVector3D &normal, CVector3D &result );
void	AFX_EXT_API CalcNormal(CPoint3D v[3], CVector3D &out);
void	AFX_EXT_API ReduceToUnit(float vector[3]);

#endif