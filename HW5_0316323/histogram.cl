__kernel void hist(__global int *A, __global int *C)                                         
    {                                                                  
        int idx = get_global_id(0);                                    
        atomic_inc(&C[(idx % 3) * 256 + A[idx]]);                      
    }                                                                  
