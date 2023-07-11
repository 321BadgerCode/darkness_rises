//badger
using namespace std;

template<typename T=int>struct vector{
	T x,y,z;

	vector():x(0),y(0),z(0){}
	vector(T x,T y,T z):x(x),y(y),z(z){}
	operator string() const {
		return 	"("+
			to_string(x)+","+
			to_string(y)+","+
			to_string(z)+")";
	}
	vector operator+(const vector& other) const {
		return vector(x+other.x,y+other.y,z+other.z);
	}
	vector operator-(const vector& other) const {
		return vector(x-other.x,y-other.y,z-other.z);
	}
	vector operator*(T scalar) const {
		return vector(x*scalar,y*scalar,z*scalar);
	}
	vector operator/(T scalar) const {
		return vector(x/scalar,y/scalar,z/scalar);
	}
	vector& operator+=(const vector& other){
		x+=other.x;
		y+=other.y;
		z+=other.z;
		return *this;
	}
	vector& operator-=(const vector& other){
		x-=other.x;
		y-=other.y;
		z-=other.z;
		return *this;
	}
	vector& operator*=(T scalar){
		x*=scalar;
		y*=scalar;
		z*=scalar;
		return *this;
	}
	vector& operator/=(T scalar){
		x/=scalar;
		y/=scalar;
		z/=scalar;
		return *this;
	}
};