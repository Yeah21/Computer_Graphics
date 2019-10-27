#include<iostream> 
using namespace std;
class DrawLine{
public:
	void DDAline(int x0,int y0,int x1,int y1,int color);
	void MidLine(int x0,int y0,int x1,int y1,int color);
	void BreLine(int x0,int y0,int x1,int y1,int color);
};
void DrawLine::DDAline(int x0,int y0,int x1,int y1,int color){
	cout << "DrawLine" << endl;
	int x;
	float dx,dy,k,y;
	dx = x1 - x0;
	dy = y1 - y0;
	k = dy/dx;
	y = y0;
	for (x = x0; x <= x1; x++){
		cout << x << " " << int(y + 0.5)<<endl;
		y = y+k;
	}
}

void DrawLine::MidLine(int x0,int y0,int x1,int y1,int color){
	cout << "MidLine" << endl;
	int a,b,delta1,delta2,d,x,y;
	a = y0 - y1; 
	b =  x1 - x0;
	d = 2 * a +b;
	delta1 = 2 * a;
	delta2 = 2 * (a + b);
	x = x0;
	y = y0;
	cout << x << " " << y<<endl;
	while (x  < x1){
		if(d < 0){
			x++;y++;
			d += delta2;
		}else{
			x++;
			d += delta1;
		}
	    cout << x << " " << y<<endl;		
	}
}

void  DrawLine::BreLine(int x0,int y0,int x1,int y1,int color){
	cout <<"BresenhamLine" <<endl;
	int x,y,dx,dy; float e; 
	dx = x1-x0; dy = y1-y0;
	e = 2*dy-dx; x=x0; y=y0; 
	cout << x <<" "<< y <<endl;
	for( int i=1; i<=dx; i++){
	   x++; 
	   if(e > 0) {
	        e = e-2*dx;
			y++;} 
	   cout << x <<" "<< y <<endl; 
	   e=e+2*dy; 
   }
}

int main(){
	DrawLine l;  
	l.DDAline(0,0,5,4,1);
	l.MidLine(0,0,5,4,1);
	l.BreLine(0,0,5,4,1);
	return 0;
}
