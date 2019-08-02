#ifndef SSE_VEC
#define SSE_VEC

/* 
 * SSE_Vec_Mul
 * Performs SSE four-at-a-time pairwise vector multiplication on two arrays 
 * of floats.
 * 
 * Arguments: Two input arrays of floats, an output array, and the length of
 * the three arrays (which must be identical.)
 * 
 * Precondition: None, except that the arrays must contain valid floats. The
 * arrays should ideally be aligned on a cache-line boundary, but do not have
 * to be.  The array sizes do not need to be a multiple of four; if 
 * len % 4 != 0, the last 1-3 float pairs will be multiplied individually.
 * 
 * Postcondition: The third argument will be populated with the pairwise
 * products of the first two arrays.  No registers are clobbered.
 * 
 * Return: Nothing.
 */
void SSE_Vec_Mul (float* a, float* b, float* c, int len);

/*
 * SSE_Vec_MulSum
 * Performs SSE four-at-a-time pairwise multiplication on two arrays of 
 * floating point numbers, and returns the sum of the products.
 *
 * Arguments: The two arrays to be processed and their length.
 *
 * Preconditions: The arrays should contain valid floats, and should be the
 * same length.  They do not strictly need to be aligned, nor does the number
 * of elements need to be a multiple of four.
 *
 * Postcondition: Nothing is modified, no registers are clobbered.
 *
 * Return: The sum of the pairwise multiplication of the arrays, as a float.
 */
float SSE_Vec_MulSum (float* a, float* b, int len);

#endif
