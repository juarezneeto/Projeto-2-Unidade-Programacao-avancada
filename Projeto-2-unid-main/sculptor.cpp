#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <cmath>
#include <vector>
#include "sculptor.h"



using namespace std;
 
 sculptor::sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    lado = 0.5;
    r = g = b = a = 0.5;
  
  // Alocação dinâmica 
    v = new voxel**[nx];
     for (int i =0; i<nx; i++){
      v[i] = new voxel*[ny];

     for (int j =0; j<ny; j++){
       v[i][j]= new voxel[nz];
      }
    }
};



sculptor::~sculptor(){
    for(int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
               delete[] v[i][j];
            }
        }
        for (int i=0; i <nx; i++){
            delete[] v[i];
        }

        delete[] v;

        nx = 0;
        ny = 0;
        nz = 0;}




void sculptor::setColor(float _r, float _g, float _b, float _a){
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

void sculptor::cutVoxel(int x0, int y0, int z0){
    v[x0][y0][z0].isOn = false;
}

void sculptor::putVoxel(int x0, int y0, int z0){
    v[x0][y0][z0].isOn = true;
    v[x0][y0][z0].r = r;
    v[x0][y0][z0].g = g;
    v[x0][y0][z0].b = b;
    v[x0][y0][z0].a = a;

}

void sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i<x1; i++){
       for (int j = y0; j<y1; j++){
           for (int k = z0; k<z1; k++){
               v[i][j][k].isOn = true;
               v[i][j][k].r = r;
               v[i][j][k].g = g;
               v[i][j][k].b = b;
               v[i][j][k].a = a;
           }
       }
    }
    
}

void sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = x0; i<x1; i++){
       for (int j = y0; j<y1; j++){
           for (int k = z0; k<z1; k++){
               v[i][j][k].isOn = false;
            }
        }
    }
}

void sculptor::putSphere(int x0, int y0, int z0, int radius){
  for(int i = -radius; i<=radius; i++){
      for(int j = -radius; j<=radius; j++){
          for(int k = -radius; k<=radius; k++){
         
            if ((i*i+j*j+k*k) < radius*radius){
              putVoxel(i+x0,j+y0,k+z0);
            }
          }
      }
  }

}

void sculptor::cutSphere(int x0, int y0, int z0, int radius){
  for(int i = -radius; i<radius; i++){
      for(int j = -radius; j<radius; j++){
          for(int k = -radius; k<radius; k++){
            if((i*i+j*j+k*k) < radius*radius){
              cutVoxel(i+x0,j+y0,k+z0);
            }
          }
      }
  }
}

void sculptor::putEllipsoid(int x0, int y0, int z0, int rx, int ry, int rz){
   float newx, newy, newz;

    for (int x = 0; x < nx; x++){
        for (int y = 0; y < ny; y++){
            for (int z = 0; z < nz; z++){
            newx = ((float)(x-x0)*(float)(x-x0))/(rx * rx);
            newy = ((float)(y-y0)*(float)(y-y0))/(ry * ry);
            newz = ((float)(z-z0)*(float)(z-z0))/(rz * rz);

            if ((newx + newy + newz) < 1){
                putVoxel(x,y,z);
            }
            }
        }
    }
}

void sculptor::cutEllipsoid(int x0, int y0, int z0, int rx, int ry, int rz){
   double newx, newy, newz;

    for (int x = 0; x < nx; x++){
        for (int y = 0; y < ny; y++){
            for (int z = 0; z < nz; z++){
            newx = ((float)(x-x0)*(float)(x-x0))/(rx * rx);
            newy = ((float)(y-y0)*(float)(y-y0))/(ry * ry);
            newz = ((float)(z-z0)*(float)(z-z0))/(rz * rz);

            if ((newx + newy + newz) < 1){
                cutVoxel(x,y,z);
            }
            }
        }
    }
}



void sculptor::writeOFF(char *filename){
    int total, index;
    ofstream arq;
    total = 0;
    arq.open(filename);
    arq << "OFF\n";

    for (int i = 0; i < nx; i++){
      for (int j = 0; j <ny; j++){
           for (int k = 0; k <nz; k++){
                if(v[i][j][k].isOn == true){
                total++;
        }
            }
        }
    }

    arq << total * 8 << " " << total * 6 <<" "<< 0 << "\n";

    for (int i = 0; i < nx; i++){
      for (int j = 0; j < ny; j++){
           for (int k = 0; k < nz; k++){
                if(v[i][j][k].isOn == true){

        arq << i - lado << " " << j + lado << " " << k - lado << "\n" << flush;
        arq << i - lado << " " << j - lado << " " << k - lado << "\n" << flush;
        arq << i + lado << " " << j - lado << " " << k - lado << "\n" << flush;
        arq << i + lado << " " << j + lado << " " << k - lado << "\n" << flush;
        arq << i - lado << " " << j + lado << " " << k + lado << "\n" << flush;
        arq << i - lado << " " << j - lado << " " << k + lado << "\n" << flush;
        arq << i + lado << " " << j - lado << " " << k + lado << "\n" << flush;
        arq << i + lado << " " << j + lado << " " << k + lado << "\n" << flush;
        }
            }
        }
    }
    total = 0;

   
            for (int i= 0; i<nx; i++){
      for (int j = 0; j<ny; j++){
           for (int k= 0; k<nz; k++){
                if(v[i][j][k].isOn == true){
                index = total * 8;
                arq << fixed;

            arq<< 4 << " " << index + 0 << " " << index + 3 << " " << index + 2 << " " << index + 1 << " ";
            arq << setprecision(2) << v[i][j][k].r << " " << setprecision(2) << v[i][j][k].g << " " << setprecision(2) << v[i][j][k].b << " " <<setprecision(2) << v[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 4 << " " << index + 5 << " " << index + 6 << " " << index + 7 << " ";
            arq << setprecision(2) << v[i][j][k].r << " " << setprecision(2) << v[i][j][k].g << " " << setprecision(2) << v[i][j][k].b << " " << setprecision(2) << v[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 0 << " " << index + 1 << " " << index + 5 << " " << index + 4 << " ";
            arq<< setprecision(2) << v[i][j][k].r << " " << setprecision(2) << v[i][j][k].g << " " << setprecision(2) << v[i][j][k].b << " " << setprecision(2) << v[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 0 << " " << index + 4 << " " << index + 7 << " " << index + 3 << " ";
            arq<< setprecision(2) << v[i][j][k].r << " " << setprecision(2) << v[i][j][k].g << " " << setprecision(2) << v[i][j][k].b << " " << setprecision(2) << v[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 7 << " " << index + 6 << " " << index + 2 << " " << index + 3 << " ";
            arq<< setprecision(2) << v[i][j][k].r << " " <<setprecision(2) << v[i][j][k].g << " " << setprecision(2) << v[i][j][k].b << " " <<setprecision(2) << v[i][j][k].a << setprecision(2) << "\n";

            arq<< 4 << " " << index + 1 << " " << index + 2 << " " << index + 6 << " " << index + 5 << " ";
            arq<< setprecision(2) << v[i][j][k].r << " " << setprecision(2) << v[i][j][k].g << " " << setprecision(2) << v[i][j][k].b << " " << setprecision(2) << v[i][j][k].a << setprecision(2) << "\n";

            total++;
        }
            }
        }
    }
    arq.close();
}