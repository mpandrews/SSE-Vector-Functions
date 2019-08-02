#ifndef SSE_WIDTH
#define SSE_WIDTH 4
#endif

void SSE_Vec_Mul (float* a, float* b, float* c, int len)
{
	long width = SSE_WIDTH;
	long length = len;
	__asm
	(
		".att_syntax\n\t"
		"xor %%rdx, %%rdx\n\t" //Zero rdx
		"divq %4\n\t" //Divide the array size by SSE width.
		"movq %%rax, %%rcx\n\t" //Move the result into rcx for looping
		"test %%rcx, %%rcx\n\t"
		"je babyloop1\n\t" //If we have less than one SSE_WIDTH
		"multloop1:\n\t"
		"movups (%1), %%xmm0\n\t" //Load floats from a
		"movups (%2), %%xmm1\n\t" //Load floats from b
		"mulps %%xmm1, %%xmm0\n\t" //Multiply
		"movups %%xmm0, (%3)\n\t" //Store in c
		"add $16, %1\n\t"
		"add $16, %2\n\t"
		"add $16, %3\n\t"
		"loop multloop1\n\t"	//Loop.
		"babyloop1:\n\t"
		"movq %%rdx, %%rcx\n\t"  //The number of residue floats to
					 //process.
		"test %%rcx, %%rcx\n\t"
		"je bypass1\n\t"
		"residueloop1:\n\t"
		"movss (%1), %%xmm0\n\t"
		"movss (%2), %%xmm1\n\t"
		"mulss %%xmm1, %%xmm0\n\t"
		"movss %%xmm0, (%3)\n\t"
		"addq $4, %1\n\t"
		"addq $4, %2\n\t"
		"addq $4, %3\n\t"
		"loop residueloop1\n\t"
		"bypass1:\n\t"


		 : "+a" (length), "+r" (a), "+r" (b), "+r" (c)
		 : "m" (width)
		 : "cc", "rdx", "rcx", "memory"
	);
}

float SSE_Vec_MulSum (float* a, float* b, int len)
{
	float sum[4] = {0., 0., 0., 0.};
	long width = SSE_WIDTH;
	long length = len;
	__asm
	(
	 	".att_syntax\n\t"
		"pxor %%xmm2, %%xmm2\n\t" //Zero the result register.
		"xor %%rdx, %%rdx\n\t" //Empty rdx.
		"divq %7\n\t" //Divide length by SSE width.
		"movq %%rax, %%rcx\n\t" //Store length/width in rcx.
		"test %%rcx, %%rcx\n\t"
		"je babyloop\n\t" //If we have less than one SSE_WIDTH
		"multloop:\n\t"
		"movups (%2), %%xmm0\n\t" //Load first set of floats.
		"movups (%3), %%xmm1\n\t" //Load second set.
		"mulps %%xmm1, %%xmm0\n\t" //Multiply!
		"addps %%xmm0, %%xmm2\n\t" //Add!
		"addq $16, %2\n\t"
		"addq $16, %3\n\t"
		"loop multloop\n\t"	//Once more from the top, this time
					 //with feeling.
		"babyloop:\n\t"
		"movq %%rdx, %%rcx\n\t" //Load the remainder of our earlier
					 //division operation into rcx.  If we
					 //have an array size that isn't a
					 //multiple of SSE_WIDTH, this is the
					 //number of leftovers.
		"test %%rcx, %%rcx\n\t"
		"je bypass\n\t"		//We need to manually jump past this
					 //section if there's no residue,
					 //or the loop instruction will under
					 //flow and we'll be here for a long,
					 //long while.
		"residueloop:\n\t"
		"movss (%2), %%xmm0\n\t" //Load one value into xmm0.
		"movss (%3),  %%xmm1\n\t"  //Ditto xmm1.
		"mulss %%xmm1, %%xmm0\n\t" //Multiply the two.
		"addss %%xmm0, %%xmm2\n\t" //Add it to xmm2's low slot.
		"addq $4, %2\n\t"
		"addq $4, %3\n\t"
		"loop residueloop\n\t"
		"bypass:\n\t"
		"movups %%xmm2, %0\n\t"

		: "=m" (sum), "=a" (length), "=r"(a), "=r" (b) //Outputs
		: "1" (length), "2" (a), "3" (b), "m" (width) //Inputs
		: "cc", "memory", "rdx", "rcx"  //The clobber list.

	);
	return sum[0] + sum[1] + sum[2] + sum[3];
}
