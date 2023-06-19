#ifndef __VECTOR_H__
#define __VECTOR_H__


typedef struct vector vector_t;
   
/* description: creates a new vector 
   params: vector capacity, and element size
   return value: In case of success pointer to the new struct, Null in case of failure
   undefined behavior: in case of invalid element size */ 
vector_t *VectorCreate(size_t capacity, size_t element_size);
/* description: free given vector and the array it contains 
   params: vector pointer
   return value: none
   undefined behavior: in case of invalid vector pointer */ 
void VectorDestroy(vector_t *vector);
/* description: insert the element into the vector array 
   params: vector pointer, element to push address
   return value: 0 in case of success, 1 in case of failure
   undefined behavior: in case of invalid element */ 
int VectorPush(vector_t *vector, void *element_to_push);
/* description: remove the last element from the vector array 
   params: vector pointer
   return value: none
   undefined behavior: in case of invalid vector pointer */ 
void VectorPop(vector_t *vector);
/* description: test if the vector is empty
   params: vector pointer
   return value: 0 in case the vector is empty, number otherwise
   undefined behavior: in case of invalid vector pointer */ 
int VectorIsEmpty(vector_t *vector);
/* description: return the number of elements in vector array
   params: vector pointer
   return value: size_t of the number of elements
   undefined behavior: in case of invalid vector pointer */ 
size_t VectorSize(vector_t *vector);
/* description: return the capacity of the vector array
   params: vector pointer
   return value: size_t of the capacity
   undefined behavior: in case of invalid vector pointer */ 
size_t VectorCapacity(vector_t *vector);
/* description: get an access to an element in the vector array specified index
   params: vector pointer, index
   return value: the address of the element in given index
   undefined behavior: in case of invalid vector pointer or index out of bounds */ 
void *VectorGetAccess(vector_t *vector, int index);
/* description: shrink the vector size to the number of elements in the vector array
   params: vector pointer
   return value: 0 in case of success, number otherwise
   undefined behavior: in case of invalid vector pointer*/ 
int VectorShrinkToFit(vector_t *vector);
/* description: change vector size based on new capacity
   params: vector pointer, new_capacity
   return value: 0 in case of success, number otherwise
   undefined behavior: in case of invalid vector pointer or invalid/smaller size then the current capacity*/
int VectorReserve(vector_t *vector, size_t new_capacity);
#endif
