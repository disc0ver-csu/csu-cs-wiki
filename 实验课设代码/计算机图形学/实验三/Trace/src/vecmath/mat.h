#ifndef __MATRIX_HEADER__
#define __MATRIX_HEADER__

#include <iostream>

//==========[ Forward References ]=============================================

template <class T> class Vec;
template <class T> class Vec3;
template <class T> class Vec4;
template <class T> class Mat3;
template <class T> class Mat4;

template <class T> Vec3<T> operator * ( const Mat4<T>& a, const Vec3<T>& v );

template <class T> inline Mat3<T> operator -( const Mat3<T>& a );
template <class T> inline Mat3<T> operator +( const Mat3<T>& a, const Mat3<T>& b );
template <class T> inline Mat3<T> operator -( const Mat3<T>& a, const Mat3<T>& b);
template <class T> inline Mat3<T> operator *( const Mat3<T>& a, const Mat3<T>& b );
template <class T> inline Mat3<T> operator *( const Mat3<T>& a, const double d );
template <class T> inline Mat3<T> operator *( const double d, const Mat3<T>& a );
template <class T> inline Mat3<T> operator /( const Mat3<T>& a, const double d );
template <class T> inline bool operator ==( const Mat3<T>& a, const Mat3<T>& b );
template <class T> inline bool operator !=( const Mat3<T>& a, const Mat3<T>& b );
template <class T> inline std::ostream& operator <<( std::ostream& os, const Mat3<T>& m );
template <class T> inline std::istream& operator >>( std::istream& is, Mat3<T>& m );
template <class T> inline Mat4<T> operator -( const Mat4<T>& a );
template <class T> inline Mat4<T> operator +( const Mat4<T>& a, const Mat4<T>& b );
template <class T> inline Mat4<T> operator -( const Mat4<T>& a, const Mat4<T>& b );
template <class T> inline Mat4<T> operator *( const Mat4<T>& a, const Mat4<T>& b );
template <class T> inline Mat4<T> operator *( const Mat4<T>& a, const double d );
template <class T> inline Mat4<T> operator *( const double d, const Mat4<T>& a );
template <class T> inline Mat4<T> operator /( const Mat4<T>& a, const double d );
template <class T> inline bool operator ==( const Mat4<T>& a, const Mat4<T>& b );
template <class T> inline bool operator !=( const Mat4<T>& a, const Mat4<T>& b );
template <class T> inline std::ostream& operator <<( std::ostream& os, const Mat4<T>& m );
template <class T> inline std::istream& operator >>( std::istream& is, Mat4<T>& m );

//==========[ class Mat3 ]=====================================================

template <class T>
class Mat3 {

	//---[ Private Variable Declarations ]-----------------


public:

	// matrix elements in row major order
	T		n[9];

	//---[ Constructors ]----------------------------------

	Mat3()
		{ memset(n,0,9*sizeof(T)); n[0]=1; n[4]=1; n[8]=1; }
	Mat3( T n0, T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8 )
		{ n[0]=n0; n[1]=n1; n[2]=n2;
		  n[3]=n3; n[4]=n4; n[5]=n5;
		  n[6]=n6; n[7]=n7; n[8]=n8; }
	Mat3( const Mat3<T>& m )
		{ memcpy(n,m.n,9*sizeof(T)); }

	//---[ Equal Operators ]-------------------------------

	Mat3<T>& operator =( const Mat3<T>& m )
		{ memcpy(n,m.n,9*sizeof(T)); return *this; }
	Mat3<T>& operator +=( const Mat3<T>& m )
		{ n[0]+=m.n[0]; n[1]+=m.n[1]; n[2]+=m.n[2]; n[3]+=m.n[3]; n[4]+=m.n[4]; n[5]+=m.n[5]; n[6]+=m.n[6]; n[7]+=m.n[7]; n[8]+=m.n[8]; return *this; }
	Mat3<T>& operator -=( const Mat3<T>& m )
		{ n[0]-=m.n[0]; n[1]-=m.n[1]; n[2]-=m.n[2]; n[3]-=m.n[3]; n[4]-=m.n[4]; n[5]-=m.n[5]; n[6]-=m.n[6]; n[7]-=m.n[7]; n[8]-=m.n[8]; return *this; }
	Mat3<T>& operator *=( const T d )
		{ n[0]*=d; n[1]*=d; n[2]*=d; n[3]*=d; n[4]*=d; n[5]*=d; n[6]*=d; n[7]*=d; n[8]*=d; return *this; }
	Mat3<T>& operator /=( const T d )
		{ n[0]/=d; n[1]/=d; n[2]/=d; n[3]/=d; n[4]/=d; n[5]/=d; n[6]/=d; n[7]/=d; n[8]/=d; return *this; }

	//---[ Access Operators ]------------------------------

	T* operator []( int i )
		{ return &n[i*3]; }
	const T* operator []( int i ) const
		{ return &n[i*3]; }

	//---[ Ordering Methods ]------------------------------

	Mat3<T> transpose() const { return Mat3<T>(n[0],n[3],n[6],n[1],n[4],n[7],n[2],n[5],n[8]); }
	double trace() const { return n[0]+n[4]+n[8]; }
	
	//---[ GL Matrix ]-------------------------------------

	void getGLMatrix( T* mat ) const
	{ mat[0]=n[0]; mat[1]=n[3]; mat[2]=n[6];
	  mat[3]=n[1]; mat[4]=n[4]; mat[5]=n[7];
	  mat[6]=n[2]; mat[7]=n[5]; mat[8]=n[8]; }

	//---[ Transformation Matrices ]-----------------------

	static Mat3<T> createRotation( T angle, float x, float y );
	static Mat3<T> createTranslation( T x, T y );
	static Mat3<T> createScale( T sx, T sy );
	static Mat3<T> createShear( T shx, T shy );

	//---[ Inversion ]-------------------------------------

	Mat3<T> inverse() const {	    // Gauss-Jordan elimination with partial pivoting
		Mat3<T> a(*this);			// As a evolves from original mat into identity
		Mat3<T> b; 					// b evolves from identity into inverse(a)
		int	 i, j, i1;

		// Loop over cols of a from left to right, eliminating above and below diag
		for (j=0; j<3; j++) {		// Find largest pivot in column j among rows j..2
			i1 = j;					// Row with largest pivot candidate
			for (i=j+1; i<3; i++)
				if (fabs(a[i][j]) > fabs(a[i1][j]))
					i1 = i;

			// Swap rows i1 and j in a and b to put pivot on diagonal
			for (i=0; i < 3; i++) {
				std::swap(a[i1][i], a[j][i]);
				std::swap(b[i1][i], b[j][i]);
			}

			// Scale row j to have a unit diagonal
//			if (a[j][j]==0.)
//				throw SingularMatrixException();

			double scale = a[j][j];
			for (i=0; i < 3; i++) {
				b[j][i] /= scale;
				a[j][i] /= scale;
			}

			// Eliminate off-diagonal elems in col j of a, doing identical ops to b
			for (i=0; i<3; i++)
				if (i!=j) {
					scale = a[i][j];
					for (i1=0; i1 < 3; i1++) {
						b[i][i1] -= scale*b[j][i1];
						a[i][i1] -= scale*a[j][i1];
					}
				}
		}
		return b;
	}

	//---[ Friend Methods ]--------------------------------

#ifdef WIN32
	// VCC is non-standard
	template <class U> friend Mat3<T> operator -( const Mat3<T>& a );
	template <class U> friend Mat3<T> operator +( const Mat3<T>& a, const Mat3<T>& b );
	template <class U> friend Mat3<T> operator -( const Mat3<T>& a, const Mat3<T>& b );
	template <class U> friend Mat3<T> operator *( const Mat3<T>& a, const Mat3<T>& b );
	template <class U> friend Mat3<T> operator *( const Mat3<T>& a, const double d );
	template <class U> friend Mat3<T> operator *( const double d, const Mat3<T>& a );
	template <class U> friend Mat3<T> operator /( const Mat3<T>& a, const double d );
	template <class U> friend bool operator ==( const Mat3<T>& a, const Mat3<T>& b );
	template <class U> friend bool operator !=( const Mat3<T>& a, const Mat3<T>& b );
	template <class U> friend std::ostream& operator <<( std::ostream& os, const Mat3<T>& m );
	template <class U> friend std::istream& operator >>( std::istream& is, Mat3<T>& m );
#else
	friend Mat3<T> operator - <>( const Mat3<T>& a );
	friend Mat3<T> operator + <>( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator - <>( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator * <>( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator * <>( const Mat3<T>& a, const double d );
	friend Mat3<T> operator * <>( const double d, const Mat3<T>& a );
	friend Mat3<T> operator / <>( const Mat3<T>& a, const double d );
	friend bool operator == <>( const Mat3<T>& a, const Mat3<T>& b );
	friend bool operator != <>( const Mat3<T>& a, const Mat3<T>& b );
	friend std::ostream& operator << <>( std::ostream& os, const Mat3<T>& m );
	friend std::istream& operator >> <>( std::istream& is, Mat3<T>& m );
#endif
};

typedef Mat3<int> Mat3i;
typedef Mat3<float> Mat3f;
typedef Mat3<double> Mat3d;

//==========[ class Mat4 ]=====================================================

template <class T>
class Mat4 {

	//---[ Private Variable Declarations ]-----------------


public:
		// matrix elements in row-major order
	T		n[16];

	bool isZero() { return n[0]==0&&n[1]==0&&n[2]==0&&n[3]==0&&n[4]==0&&n[5]==0&&n[6]==0&&n[7]==0&&n[8]==0&&n[9]==0&&n[10]==0&&n[11]==0&&n[12]==0&&n[13]==0&&n[14]==0&&n[15]==0; }
	
	//---[ Constructors ]----------------------------------

	Mat4()
		{ memset(n,0,16*sizeof(T)); n[0]=1;n[5]=1;n[10]=1;n[15]=1; }
	Mat4( T n0, T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8, T n9, T n10, T n11, T n12, T n13, T n14, T n15 )
		{ n[ 0]=n0 ; n[ 1]=n1 ; n[ 2]=n2 ; n[ 3]=n3 ;
		  n[ 4]=n4 ; n[ 5]=n5 ; n[ 6]=n6 ; n[ 7]=n7 ;
		  n[ 8]=n8 ; n[ 9]=n9 ; n[10]=n10; n[11]=n11;
		  n[12]=n12; n[13]=n13; n[14]=n14; n[15]=n15; }	  
	Mat4( const Mat4<T>& m )
		{ memcpy(n,m.n,16*sizeof(T)); }
	Mat4( const Vec4<T>& v0, const Vec4<T>& v1, const Vec4<T>& v2, const Vec4<T>& v3 ) {
		n[ 0] = v0[0]; n[ 1] = v0[1]; n[ 2] = v0[2]; n[ 3] = v0[3];
		n[ 4] = v1[0]; n[ 5] = v1[1]; n[ 6] = v1[2]; n[ 7] = v1[3];
		n[ 8] = v2[0]; n[ 9] = v2[1]; n[10] = v2[2]; n[11] = v2[3];
		n[12] = v3[0]; n[13] = v3[1]; n[14] = v3[2]; n[15] = v3[3];
	}

	//---[ Equal Operators ]-------------------------------

	Mat4<T>& operator =( const Mat4<T>& m )
		{ memcpy(n,m.n,16*sizeof(T)); return *this; }
	Mat4<T>& operator +=( const Mat4<T>& m )
		{ n[ 0]+=m.n[ 0]; n[ 1]+=m.n[ 1]; n[ 2]+=m.n[ 2]; n[ 3]+=m.n[ 3];
		  n[ 4]+=m.n[ 4]; n[ 5]+=m.n[ 5]; n[ 6]+=m.n[ 6]; n[ 7]+=m.n[ 7];
		  n[ 8]+=m.n[ 8]; n[ 9]+=m.n[ 9]; n[10]+=m.n[10]; n[11]+=m.n[11];
		  n[12]+=m.n[12]; n[13]+=m.n[13]; n[14]+=m.n[14]; n[15]+=m.n[15]; 
		  return *this; }
	Mat4<T>& operator -=( const Mat4<T>& m )
		{ n[ 0]-=m.n[ 0]; n[ 1]-=m.n[ 1]; n[ 2]-=m.n[ 2]; n[ 3]-=m.n[ 3];
		  n[ 4]-=m.n[ 4]; n[ 5]-=m.n[ 5]; n[ 6]-=m.n[ 6]; n[ 7]-=m.n[ 7];
		  n[ 8]-=m.n[ 8]; n[ 9]-=m.n[ 9]; n[10]-=m.n[10]; n[11]-=m.n[11];
		  n[12]-=m.n[12]; n[13]-=m.n[13]; n[14]-=m.n[14]; n[15]-=m.n[15]; 
		  return *this; }
	Mat4<T>& operator *=( const T d )
		{ n[ 0]*=d; n[ 1]*=d; n[ 2]*=d; n[ 3]*=d;
		  n[ 4]*=d; n[ 5]*=d; n[ 6]*=d; n[ 7]*=d;
		  n[ 8]*=d; n[ 9]*=d; n[10]*=d; n[11]*=d;
		  n[12]*=d; n[13]*=d; n[14]*=d; n[15]*=d; 
		  return *this; }
	Mat4<T>& operator /=( const T d )
		{ n[ 0]/=d; n[ 1]/=d; n[ 2]/=d; n[ 3]/=d;
		  n[ 4]/=d; n[ 5]/=d; n[ 6]/=d; n[ 7]/=d;
		  n[ 8]/=d; n[ 9]/=d; n[10]/=d; n[11]/=d;
		  n[12]/=d; n[13]/=d; n[14]/=d; n[15]/=d; 
		  return *this; }

	//---[ Access Operators ]------------------------------

	T* operator []( int i )
		{ return &n[i*4]; }
	const T* operator []( int i ) const
		{ return &n[i*4]; }

	//---[ Ordering Methods ]------------------------------

	Mat4<T> transpose() const
		{ return Mat4<T>(n[ 0],n[ 4],n[ 8],n[12],
						 n[ 1],n[ 5],n[ 9],n[13],
						 n[ 2],n[ 6],n[10],n[14],
						 n[ 3],n[ 7],n[11],n[15]); }
	double trace() const { return n[0]+n[5]+n[10]+n[15]; }
	
	//---[ GL Matrix ]-------------------------------------

	void getGLMatrix( T* mat ) const
	{ mat[ 0]=n[ 0]; mat[ 1]=n[ 4]; mat[ 2]=n[ 8]; mat[ 3]=n[12];
	  mat[ 4]=n[ 1]; mat[ 5]=n[ 5]; mat[ 6]=n[ 9]; mat[ 7]=n[13];
	  mat[ 8]=n[ 2]; mat[ 9]=n[ 6]; mat[10]=n[10]; mat[11]=n[14];
	  mat[12]=n[ 3]; mat[13]=n[ 7]; mat[14]=n[11]; mat[15]=n[15]; }

	void getGLMatrixF( float* mat )
	{ mat[ 0]=n[ 0]; mat[ 1]=n[ 4]; mat[ 2]=n[ 8]; mat[ 3]=n[12];
	  mat[ 4]=n[ 1]; mat[ 5]=n[ 5]; mat[ 6]=n[ 9]; mat[ 7]=n[13];
	  mat[ 8]=n[ 2]; mat[ 9]=n[ 6]; mat[10]=n[10]; mat[11]=n[14];
	  mat[12]=n[ 3]; mat[13]=n[ 7]; mat[14]=n[11]; mat[15]=n[15]; }

	//---[ Transformation Matrices ]-----------------------

	static Mat4<T> createRotation( T angle, float x, float y, float z );
	static Mat4<T> createTranslation( T x, T y, T z );
	static Mat4<T> createScale( T sx, T sy, T sz );
	static Mat4<T> createShear( T shx, T shy, T shz );

	//---[ Conversion ]------------------------------------

	Mat3<T> upper33() {
		return Mat3<T>(
			n[0], n[1], n[2],
			n[4], n[5], n[6],
			n[8], n[9], n[10]);
	}

	//---[ Inversion ]-------------------------------------

	Mat4<T> inverse() const {	    // Gauss-Jordan elimination with partial pivoting
		Mat4<T> a(*this);			// As a evolves from original mat into identity
		Mat4<T> b; 					// b evolves from identity into inverse(a)
		int	 i, j, i1;

		// Loop over cols of a from left to right, eliminating above and below diag
		for (j=0; j<4; j++) {		// Find largest pivot in column j among rows j..2
			i1 = j;					// Row with largest pivot candidate
			for (i=j+1; i<4; i++)
				if (fabs(a[i][j]) > fabs(a[i1][j]))
					i1 = i;

			// Swap rows i1 and j in a and b to put pivot on diagonal
			for (i=0; i < 4; i++) {
				std::swap(a[i1][i], a[j][i]);
				std::swap(b[i1][i], b[j][i]);
			}

			// Scale row j to have a unit diagonal
//			if (a[j][j]==0.)
//				throw SingularMatrixException();

			double scale = a[j][j];
			for (i=0; i < 4; i++) {
				b[j][i] /= scale;
				a[j][i] /= scale;
			}

			// Eliminate off-diagonal elems in col j of a, doing identical ops to b
			for (i=0; i<4; i++)
				if (i!=j) {
					scale = a[i][j];
					for (i1=0; i1 < 4; i1++) {
						b[i][i1] -= scale*b[j][i1];
						a[i][i1] -= scale*a[j][i1];
					}
				}
		}
		return b;
	}

	//---[ Friend Methods ]--------------------------------

#ifdef WIN32
	// VCC is non-standard
	template <class U> friend Mat4<T> operator -( const Mat4<T>& a );
	template <class U> friend Mat4<T> operator +( const Mat4<T>& a, const Mat4<T>& b );
	template <class U> friend Mat4<T> operator -( const Mat4<T>& a, const Mat4<T>& b );
	template <class U> friend Mat4<T> operator *( const Mat4<T>& a, const Mat4<T>& b );
	template <class U> friend Mat4<T> operator *( const Mat4<T>& a, const double d );
	template <class U> friend Mat4<T> operator *( const double d, const Mat4<T>& a );
	template <class U> friend Vec3<T> operator *( const Mat4<T>& a, const Vec3<T>& b );
	template <class U> friend Mat4<T> operator /( const Mat4<T>& a, const double d );
	template <class U> friend bool operator ==( const Mat4<T>& a, const Mat4<T>& b );
	template <class U> friend bool operator !=( const Mat4<T>& a, const Mat4<T>& b );
	template <class U> friend std::ostream& operator <<( std::ostream& os, const Mat4<T>& m );
	template <class U> friend std::istream& operator >>( std::istream& is, Mat4<T>& m );
#else
	friend Mat4<T> operator - <>( const Mat4<T>& a );
	friend Mat4<T> operator + <>( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator - <>( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator * <>( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator * <>( const Mat4<T>& a, const double d );
	friend Mat4<T> operator * <>( const double d, const Mat4<T>& a );
	friend Vec3<T> operator * <>( const Mat4<T>& a, const Vec3<T>& b );
	friend Mat4<T> operator / <>( const Mat4<T>& a, const double d );
	friend bool operator == <>( const Mat4<T>& a, const Mat4<T>& b );
	friend bool operator != <>( const Mat4<T>& a, const Mat4<T>& b );
	friend std::ostream& operator << <>( std::ostream& os, const Mat4<T>& m );
	friend std::istream& operator >> <>( std::istream& is, Mat4<T>& m );
#endif
};

typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

//==========[ Inline Method Definitions (Matrix) ]=============================

template <class T>
inline Mat3<T> Mat3<T>::createRotation( T angle, float x, float y ) {
	Mat3<T> rot;
	std::cout << "unimplemented matrix command!" << std::endl;
	return rot;
}

template <class T>
inline Mat3<T> Mat3<T>::createTranslation( T x, T y ) {
	Mat3<T> trans;
	std::cout << "unimplemented matrix command!" << std::endl;
	return trans;
}

template <class T>
inline Mat3<T> Mat3<T>::createScale( T sx, T sy ) {
	Mat3<T> scale;
	std::cout << "unimplemented matrix command!" << std::endl;
	return scale;
}

template <class T>
inline Mat3<T> Mat3<T>::createShear( T shx, T shy ) {
	Mat3<T> shear;
	std::cout << "unimplemented matrix command!" << std::endl;
	return shear;
}

template <class T>
inline Mat3<T> operator -( const Mat3<T>& a ) {
	return Mat3<T>( -a.n[0], -a.n[1], -a.n[2],
					-a.n[3], -a.n[4], -a.n[5],
					-a.n[6], -a.n[7], -a.n[8] );
}

template <class T>
inline Mat3<T> operator +( const Mat3<T>& a, const Mat3<T>& b ) {
	return Mat3<T>( a.n[0]+b.n[0], a.n[1]+b.n[1], a.n[2]+b.n[2],
					a.n[3]+b.n[3], a.n[4]+b.n[4], a.n[5]+b.n[5],
					a.n[6]+b.n[6], a.n[7]+b.n[7], a.n[8]+b.n[8]);
}

template <class T>
inline Mat3<T> operator -( const Mat3<T>& a, const Mat3<T>& b) {
	return Mat3<T>( a.n[0]-b.n[0], a.n[1]-b.n[1], a.n[2]-b.n[2],
					a.n[3]-b.n[3], a.n[4]-b.n[4], a.n[5]-b.n[5],
					a.n[6]-b.n[6], a.n[7]-b.n[7], a.n[8]-b.n[8]);
}

template <class T>
inline Mat3<T> operator *( const Mat3<T>& a, const Mat3<T>& b ) {
	return Mat3<T>( a.n[0]*b.n[0]+a.n[1]*b.n[3]+a.n[2]*b.n[6],
					a.n[0]*b.n[1]+a.n[1]*b.n[4]+a.n[2]*b.n[7],
					a.n[0]*b.n[2]+a.n[1]*b.n[5]+a.n[2]*b.n[8],
					a.n[3]*b.n[0]+a.n[4]*b.n[3]+a.n[5]*b.n[6],
					a.n[3]*b.n[1]+a.n[4]*b.n[4]+a.n[5]*b.n[7],
					a.n[3]*b.n[2]+a.n[4]*b.n[5]+a.n[5]*b.n[8],
					a.n[6]*b.n[0]+a.n[7]*b.n[3]+a.n[8]*b.n[6],
					a.n[6]*b.n[1]+a.n[7]*b.n[4]+a.n[8]*b.n[7],
					a.n[6]*b.n[2]+a.n[7]*b.n[5]+a.n[8]*b.n[8] );
}

template <class T>
inline Mat3<T> operator *( const Mat3<T>& a, const double d ) {
	return Mat3<T>( a.n[0]*d, a.n[1]*d, a.n[2]*d,
					a.n[3]*d, a.n[4]*d, a.n[5]*d,
					a.n[6]*d, a.n[7]*d, a.n[8]*d );
}

template <class T>
inline Mat3<T> operator *( const double d, const Mat3<T>& a ) {
	return Mat3<T>( a.n[0]*d, a.n[1]*d, a.n[2]*d,
					a.n[3]*d, a.n[4]*d, a.n[5]*d,
					a.n[6]*d, a.n[7]*d, a.n[8]*d );
}

template <class T>
inline Mat3<T> operator /( const Mat3<T>& a, const double d ) {
	return Mat3<T>( a.n[0]/d, a.n[1]/d, a.n[2]/d,
					a.n[3]/d, a.n[4]/d, a.n[5]/d,
					a.n[6]/d, a.n[7]/d, a.n[8]/d );
}

template <class T>
inline bool operator ==( const Mat3<T>& a, const Mat3<T>& b ) {
	return !memcmp( a.n, b.n, 9*sizeof(T) );
}

template <class T>
inline bool operator !=( const Mat3<T>& a, const Mat3<T>& b ) {
	return memcmp( a.n, b.n, 9*sizeof(T) );
}

template <class T>
inline std::ostream& operator <<( std::ostream& os, const Mat3<T>& m ) {
	os << m.n[0] << " " << m.n[1] << " " << m.n[2];
	os << m.n[3] << " " << m.n[4] << " " << m.n[5];
	os << m.n[6] << " " << m.n[7] << " " << m.n[8];
}

template <class T>
inline std::istream& operator >>( std::istream& is, Mat3<T>& m ) {
	is >> m.n[0] >> m.n[1] >> m.n[2];
	is >> m.n[3] >> m.n[4] >> m.n[5];
	is >> m.n[6] >> m.n[7] >> m.n[8];
}

template <class T>
inline Mat4<T> Mat4<T>::createRotation( T angle, float x, float y, float z ) {
	double c = cos( angle );
	double s = sin( angle );
	double t = 1.0 - c;

	Vec3<T> a(x, y, z);
	a.normalize();
	return Mat4<T>(
		t*a[0]*a[0]+c, t*a[0]*a[1]-s*a[2], t*a[0]*a[2]+s*a[1], 0.0,
		t*a[0]*a[1]+s*a[2], t*a[1]*a[1]+c, t*a[1]*a[2]-s*a[0], 0.0,
		t*a[0]*a[2]-s*a[1], t*a[1]*a[2]+s*a[0], t*a[2]*a[2]+c, 0.0,
		0.0, 0.0, 0.0, 1.0);
}

template <class T>
inline Mat4<T> Mat4<T>::createTranslation( T x, T y, T z ) {
	Mat4<T> trans;

	trans[0][3] = x;
	trans[1][3] = y;
	trans[2][3] = z;

	return trans;
}

template <class T>
inline Mat4<T> Mat4<T>::createScale( T sx, T sy, T sz ) {
	Mat4<T> scale;
	scale[0][0] = sx;
	scale[1][1] = sy;
	scale[2][2] = sz;

	return scale;
}

template <class T>
inline Mat4<T> Mat4<T>::createShear( T shx, T shy, T shz ) {
	Mat4<T> shear;
	std::cout << "unimplemented matrix command!" << std::endl;
	return shear;
}

template <class T>
inline Mat4<T> operator -( const Mat4<T>& a ) {
	return Mat4<T>( -a.n[ 0], -a.n[ 1], -a.n[ 2], -a.n[ 3],
					-a.n[ 4], -a.n[ 5], -a.n[ 6], -a.n[ 7],
					-a.n[ 8], -a.n[ 9], -a.n[10], -a.n[11],
					-a.n[12], -a.n[13], -a.n[14], -a.n[15] );
}

template <class T>
inline Mat4<T> operator +( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]+b.n[ 0], a.n[ 1]+b.n[ 1], a.n[ 2]+b.n[ 2], a.n[ 3]+b.n[ 3],
					a.n[ 4]+b.n[ 4], a.n[ 5]+b.n[ 5], a.n[ 6]+b.n[ 6], a.n[ 7]+b.n[ 7],
					a.n[ 8]+b.n[ 8], a.n[ 9]+b.n[ 9], a.n[10]+b.n[10], a.n[11]+b.n[11],
					a.n[12]+b.n[12], a.n[13]+b.n[13], a.n[14]+b.n[14], a.n[15]+b.n[15] );
}

template <class T>
inline Mat4<T> operator -( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]-b.n[ 0], a.n[ 1]-b.n[ 1], a.n[ 2]-b.n[ 2], a.n[ 3]-b.n[ 3],
					a.n[ 4]-b.n[ 4], a.n[ 5]-b.n[ 5], a.n[ 6]-b.n[ 6], a.n[ 7]-b.n[ 7],
					a.n[ 8]-b.n[ 8], a.n[ 9]-b.n[ 9], a.n[10]-b.n[10], a.n[11]-b.n[11],
					a.n[12]-b.n[12], a.n[13]-b.n[13], a.n[14]-b.n[14], a.n[15]-b.n[15] );
}

template <class T>
inline Mat4<T> operator *( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]*b.n[ 0]+a.n[ 1]*b.n[ 4]+a.n[ 2]*b.n[ 8]+a.n[ 3]*b.n[12],
					a.n[ 0]*b.n[ 1]+a.n[ 1]*b.n[ 5]+a.n[ 2]*b.n[ 9]+a.n[ 3]*b.n[13],
					a.n[ 0]*b.n[ 2]+a.n[ 1]*b.n[ 6]+a.n[ 2]*b.n[10]+a.n[ 3]*b.n[14],
					a.n[ 0]*b.n[ 3]+a.n[ 1]*b.n[ 7]+a.n[ 2]*b.n[11]+a.n[ 3]*b.n[15],
					a.n[ 4]*b.n[ 0]+a.n[ 5]*b.n[ 4]+a.n[ 6]*b.n[ 8]+a.n[ 7]*b.n[12],
					a.n[ 4]*b.n[ 1]+a.n[ 5]*b.n[ 5]+a.n[ 6]*b.n[ 9]+a.n[ 7]*b.n[13],
					a.n[ 4]*b.n[ 2]+a.n[ 5]*b.n[ 6]+a.n[ 6]*b.n[10]+a.n[ 7]*b.n[14],
					a.n[ 4]*b.n[ 3]+a.n[ 5]*b.n[ 7]+a.n[ 6]*b.n[11]+a.n[ 7]*b.n[15],
					a.n[ 8]*b.n[ 0]+a.n[ 9]*b.n[ 4]+a.n[10]*b.n[ 8]+a.n[11]*b.n[12],
					a.n[ 8]*b.n[ 1]+a.n[ 9]*b.n[ 5]+a.n[10]*b.n[ 9]+a.n[11]*b.n[13],
					a.n[ 8]*b.n[ 2]+a.n[ 9]*b.n[ 6]+a.n[10]*b.n[10]+a.n[11]*b.n[14],
					a.n[ 8]*b.n[ 3]+a.n[ 9]*b.n[ 7]+a.n[10]*b.n[11]+a.n[11]*b.n[15],
					a.n[12]*b.n[ 0]+a.n[13]*b.n[ 4]+a.n[14]*b.n[ 8]+a.n[15]*b.n[12],
					a.n[12]*b.n[ 1]+a.n[13]*b.n[ 5]+a.n[14]*b.n[ 9]+a.n[15]*b.n[13],
					a.n[12]*b.n[ 2]+a.n[13]*b.n[ 6]+a.n[14]*b.n[10]+a.n[15]*b.n[14],
					a.n[12]*b.n[ 3]+a.n[13]*b.n[ 7]+a.n[14]*b.n[11]+a.n[15]*b.n[15] );
}

template <class T>
inline Mat4<T> operator *( const Mat4<T>& a, const double d ) {
	return Mat4<T>( a.n[ 0]*d, a.n[ 1]*d, a.n[ 2]*d, a.n[ 3]*d,
					a.n[ 4]*d, a.n[ 5]*d, a.n[ 6]*d, a.n[ 7]*d,
					a.n[ 8]*d, a.n[ 9]*d, a.n[10]*d, a.n[11]*d,
					a.n[12]*d, a.n[13]*d, a.n[14]*d, a.n[15]*d );
}

template <class T>
inline Mat4<T> operator *( const double d, const Mat4<T>& a ) {
	return Mat4<T>( a.n[ 0]*d, a.n[ 1]*d, a.n[ 2]*d, a.n[ 3]*d,
					a.n[ 4]*d, a.n[ 5]*d, a.n[ 6]*d, a.n[ 7]*d,
					a.n[ 8]*d, a.n[ 9]*d, a.n[10]*d, a.n[11]*d,
					a.n[12]*d, a.n[13]*d, a.n[14]*d, a.n[15]*d );
}

template <class T>
inline Mat4<T> operator /( const Mat4<T>& a, const double d ) {
	return Mat4<T>( a.n[ 0]/d, a.n[ 1]/d, a.n[ 2]/d, a.n[ 3]/d,
					a.n[ 4]/d, a.n[ 5]/d, a.n[ 6]/d, a.n[ 7]/d,
					a.n[ 8]/d, a.n[ 9]/d, a.n[10]/d, a.n[11]/d,
					a.n[12]/d, a.n[13]/d, a.n[14]/d, a.n[15]/d );
}

template <class T>
inline bool operator ==( const Mat4<T>& a, const Mat4<T>& b ) {
	return !memcmp(a.n,b.n,16*sizeof(T));
}

template <class T>
inline bool operator !=( const Mat4<T>& a, const Mat4<T>& b ) {
	return memcmp(a.n,b.n,16*sizeof(T));
}

template <class T>
inline std::ostream& operator <<( std::ostream& os, const Mat4<T>& m ) {
	return os << m.n[ 0] << " " << m.n[ 1] << " " << m.n[ 2] << " " << m.n[ 3] << std::endl <<
		m.n[ 4] << " " << m.n[ 5] << " " << m.n[ 6] << " " << m.n[ 7] << std::endl  <<
		m.n[ 8] << " " << m.n[ 9] << " " << m.n[10] << " " << m.n[11] << std::endl  <<
		m.n[12] << " " << m.n[13] << " " << m.n[14] << " " << m.n[15] << std::endl;
}

template <class T>
inline std::istream& operator >>( std::istream& is, Mat4<T>& m ) {
	is >> m.n[ 0] >> m.n[ 1] >> m.n[ 2] >> m.n[ 3];
	is >> m.n[ 4] >> m.n[ 5] >> m.n[ 6] >> m.n[ 7];
	is >> m.n[ 8] >> m.n[ 9] >> m.n[10] >> m.n[11];
	is >> m.n[12] >> m.n[13] >> m.n[14] >> m.n[15];
}

template <class T>
inline Vec3<T> clamp( const Vec3<T>& other ) {
	return maximum( Vec3<T>(), minimum( other, Vec3<T>( 1.0, 1.0, 1.0 ) ) );
}

// These are handy functions

template <class T>
inline void makeDiagonal( Mat4<T>& m, T k ) {
	m[0][0] =   k; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = 0.0;
	m[1][0] = 0.0; m[1][1] =   k; m[1][2] = 0.0; m[1][3] = 0.0;
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] =   k; m[2][3] = 0.0;
	m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] =   k;
}

template <class T>
inline void makeHScale( Mat4<T>& m, T sx, T sy, T sz ) {
	m[0][0] =  sx; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = 0.0;
	m[1][0] = 0.0; m[1][1] =  sy; m[1][2] = 0.0; m[1][3] = 0.0;
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] =  sz; m[2][3] = 0.0;
	m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHScale( Mat4<T>& m, const Vec3<T> &v) {
	makeHScale(m, v[0], v[1], v[2]);
}

template <class T>
inline void makeHTrans( Mat4<T>& m, T tx, T ty, T tz ) {
	m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] =  tx;
	m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] =  ty;
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] =  tz;
	m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHTrans( Mat4<T>& m, const Vec3<T> &v) {
	makeHTrans(m, v[0], v[1], v[2]);
}

template <class T>
inline void makeHRotX( Mat4<T>& m, T thetaX ) {
	T cosT = (T)cos(thetaX);
	T sinT = (T)sin(thetaX);

	m[0][0] = 1.0; m[0][1] =  0.0; m[0][2] =   0.0; m[0][3] = 0.0;
	m[1][0] = 0.0; m[1][1] = cosT; m[1][2] = -sinT; m[1][3] = 0.0;
	m[2][0] = 0.0; m[2][1] = sinT; m[2][2] =  cosT; m[2][3] = 0.0;
	m[3][0] = 0.0; m[3][1] =  0.0; m[3][2] =   0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHRotY( Mat4<T>& m, T thetaY ) {
	T cosT = (T)cos(thetaY);
	T sinT = (T)sin(thetaY);

	m[0][0] =  cosT; m[0][1] = 0.0; m[0][2] = sinT; m[0][3] = 0.0;
	m[1][0] =   0.0; m[1][1] = 1.0; m[1][2] =  0.0; m[1][3] = 0.0;
	m[2][0] = -sinT; m[2][1] = 0.0; m[2][2] = cosT; m[2][3] = 0.0;
	m[3][0] =   0.0; m[3][1] = 0.0; m[3][2] =  0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHRotZ( Mat4<T>& m, T thetaZ ) {
	T cosT = (T)cos(thetaZ);
	T sinT = (T)sin(thetaZ);

	m[0][0] = cosT; m[0][1] = -sinT; m[0][2] = 0.0; m[0][3] = 0.0;
	m[1][0] = sinT; m[1][1] =  cosT; m[1][2] = 0.0; m[1][3] = 0.0;
	m[2][0] =  0.0; m[2][1] =   0.0; m[2][2] = 1.0; m[2][3] = 0.0;
	m[3][0] =  0.0; m[3][1] =   0.0; m[3][2] = 0.0; m[3][3] = 1.0;
}

template <class T>
inline void makeHRot( Mat4<T>& m, T theta, Vec3<T>& axis)
{
	Mat4d S, U, I;

	axis /= axis.length();

	const double &x = axis[0];
	const double &y = axis[1];
	const double &z = axis[2];

	S[0][0] = 0; S[0][1] = -z; S[0][2] = y;  S[0][3] = 0;
	S[1][0] = z; S[1][1] =  0; S[1][2] = -x; S[1][3] = 0;
	S[2][0] = -y; S[2][1] = x; S[2][2] = 0; S[2][3] = 0;
	S[3][0] = 0; S[3][1] = 0; S[3][2] = 0;   S[3][3] = 0;

	U[0][0] = x*x; U[0][1] = x*y; U[0][2] = x*z; U[0][3] = 0;
	U[1][0] = x*y; U[1][1] = y*y; U[1][2] = y*z; U[1][3] = 0;
	U[2][0] = x*z; U[2][1] = y*z; U[2][2] = z*z; U[2][3] = 0;
	U[3][0] = 0;   U[2][1] = 0;   U[3][2] = 0;   U[3][3] = 0;

	m = U + cos(theta)*(I-U) + sin(theta)*S;
	m[3][3] = 1;
}

template <class T>
inline void makeHRot( Mat4<T>& m, T theta, T x, T y, T z)
{
    makeHRot(m, theta, Vec3<T>(x,y,z));
}



#endif
