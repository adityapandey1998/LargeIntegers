//Creates the string containing the large integer.
void* largeInt_create(const char* str);

//Frees the memory allocated to the large integer.
void largeInt_destroy(void* largeInt);

//Converts largeInt to a string of decimal digits for display purposes.
char* largeInt2str(void* largeInt);

//Increments the integer by one and returns the incremented largeInt.
void* largeInt_increment(void* largeInt);

//Decrements the integer by one and returns the decremented largeInt.
void* largeInt_decrement(void* largeInt);

//Adds two largeInts and returns their sum.
void* largeInt_add(void* largeInt1, void* largeInt2);

//Returns the difference of two largeInts.
void* largeInt_diff(void* largeInt1, void* largeInt2);

//Multiplies two largeInts and returns the product.
void* largeInt_multiply(void* largeInt1, void* largeInt2);

//Returns the integer part of the quotient of largeInt1/largeInt2.
void* largeInt_divide(void* largeInt1, void* largeInt2);

//Returns 0 when both are equal, +ve when largeInt1 is greater, and -ve when largeInt2 is greater.
int largeInt_compare(void* largeInt1, void* largeInt2);

//Returns largeInt1^largeInt2.
void* largeInt_pow(void* largeInt1, void* largeInt2);
