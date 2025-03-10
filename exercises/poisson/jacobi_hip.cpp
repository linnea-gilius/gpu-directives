#include "jacobi_hip.h"
#include "jacobi.h"

void compute_jacobi(field_t * phi_new, field_t * phi_old, field_t * rho, int nFields)
{

    for(int iField=0 ; iField < nFields ; iField++ )
    {
        auto field_phi_new=phi_new[iField].get_data();
        auto field_phi_old=phi_old[iField].get_data();
        auto field_rho=rho[iField].get_data();
        auto g = phi_new[iField].get_grid();
        auto nx = g->n[0];
        auto ny = g->n[1];

        dim3 blockSize(8,8,1);
        dim3 gridSize((nx+1)/8,(ny+1)/8,1);
        
        {
            launch_compute_jacobi_hip(field_phi_new,field_phi_old,field_rho,g,nx,ny);
        }

    }
}
