
#include <cmath>
#include <assert.h>
#include <algorithm>

#include "Box.h"

using namespace std;

const double HUGE_DOUBLE = 1e100;

bool Box::intersectLocal( const ray& r, isect& i ) const
{

        Vec3d p = r.getPosition();
        Vec3d d = r.getDirection();

        int it;
        double x, y, t, bestT; 
        int mod0, mod1, mod2, bestIndex;

        bestT = HUGE_DOUBLE;
        bestIndex = -1;

        for(it=0; it<6; it++){ 
                mod0 = it%3;

                if(d[mod0] == 0){
                        continue;
                }
                
                t = ((it/3) - 0.5 - p[mod0]) / d[mod0];                 

                if(t < RAY_EPSILON || t > bestT){
                        continue;
                }

                mod1 = (it+1)%3;
                mod2 = (it+2)%3;
                x = p[mod1]+t*d[mod1];
                y = p[mod2]+t*d[mod2];
                
                if(     x<=0.5 && x>=-0.5 &&
                        y<=0.5 && y>=-0.5)
                {
                        if(bestT > t){
                                bestT = t;
                                bestIndex = it;
                        }
                }                       
                
        }

        if(bestIndex < 0) return false;
        
        i.setT(bestT);
        i.setObject(this);

		Vec3d intersect_point = r.at((float)i.t);

		int i1 = (bestIndex + 1) % 3;
		int i2 = (bestIndex + 2) % 3;

        if(bestIndex < 3)
		{
                i.setN(Vec3d(-double(bestIndex == 0), -double(bestIndex == 1), -double(bestIndex == 2)));
				i.setUVCoordinates( Vec2d(	0.5 - intersect_point[ min(i1, i2) ], 
											0.5 + intersect_point[ max(i1, i2) ] ) );
		}
        else
		{
                i.setN(Vec3d(double(bestIndex==3), double(bestIndex == 4), double(bestIndex == 5)));
				i.setUVCoordinates( Vec2d(	0.5 + intersect_point[ min(i1, i2) ],
											0.5 + intersect_point[ max(i1, i2) ] ) );

		}
        return true;

}
