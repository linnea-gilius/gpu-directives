#include "jacobi_hip.h"
#include "jacobi.h"

void compute_jacobi(field_t * phi_new, field_t * phi_old, field_t * rho, int nFields,grid_t * g)
{

    for(int iField=0 ; iField < nFields ; iField++ )
    {
        auto field_phi_new=phi_new[iField].get_data();
        auto field_phi_old=phi_old[iField].get_data();
        auto field_rho=rho[iField].get_data();
        auto nx = g->n[0];
        auto ny = g->n[1];
        
        #pragma omp target data use_device_addr(field_phi_new[0:g->get_size()],field_phi_old[0:g->get_size()],field_rho[0:g->get_size()],g[0:1])
        {
            launch_compute_jacobi_hip(field_phi_new,field_phi_old,field_rho,g,nx,ny);
        }

    }
}
