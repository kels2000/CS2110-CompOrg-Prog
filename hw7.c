/**
 * @file hw7.c
 * @author Kelsi Fulton
 * @brief structs, pointers, pointer arithmetic, arrays, strings, and macros
 * @date 2021-06-xx
 */

// DO NOT MODIFY THE INCLUDE(S) LIST
#include <stdio.h>
#include "hw7.h"
#include "my_string.h"

// Global array of student structs
struct hogwarts_student class[MAX_CLASS_SIZE];

int size = 0;

/** addStudent
 *
 * @brief creates a new hogwarts_student struct and adds it to the array of hogwarts_student structs, "class"
 *
 *
 * @param "name" name of the student being created and added
 *               NOTE: if the length of name (including the null terminating character)
 *               is above MAX_NAME_SIZE, truncate name to MAX_NAME_SIZE. If the length
 *               is below MIN_NAME_SIZE, return FAILURE.  
 *               
 * @param "age" age of the student being created and added
 * @param "housePoints" gpa of the student being created and added
 * @param "house" Hogwarts house of the student being created and added
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "name" is less than MIN_NAME_SIZE
 *         (2) a student with the name "name" already exits in the array "class"
 *         (3) adding the new student would cause the size of the array "class" to
 *             exceed MAX_CLASS_SIZE
 */
int addStudent(const char *name, int age, double housePoints, const char *house)
{
  if (size > MAX_CLASS_SIZE-1) { return FAILURE;}
  if (my_strlen(name) < MIN_NAME_SIZE) {
    return FAILURE;
  }
  if (my_strlen(house) < MIN_HOUSE_SIZE) {
    return FAILURE;
  }

  for (int i=0; i<size; i++){
    if (my_strncmp(class[i].name, name, MAX_NAME_SIZE) == 0){
      return FAILURE;
    }
  }


  if (my_strlen(name) >= MAX_NAME_SIZE) {
    my_strncpy(class[size].name, name, MAX_NAME_SIZE-1);
  }
  else{
    my_strncpy(class[size].name, name, MAX_NAME_SIZE);
    }
  my_strncpy(class[size].house, house, MAX_HOUSE_SIZE);
  class[size].age = age;
  class[size].housePoints = housePoints;
  size++;
  

  return SUCCESS;
}

/** updateStudentName
 *
 * @brief updates the name of an existing hogwarts_student in the array of hogwarts_student structs, "class"
 *
 * @param "s" hogwarts_student struct that exists in the array "class"
 * @param "name" new name of hogwarts_student "s"
 *               NOTE: if the length of name (including the null terminating character)
 *               is above MAX_NAME_SIZE, truncate name to MAX_NAME_SIZE
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the hogwarts_student struct "s" can not be found in the array "class"
 */
int updateStudentName(struct hogwarts_student s, const char *name)
{
  int i=0;
  while (i < size) {
    if (*s.name == *class[i].name){
      if (my_strlen(name)> MAX_NAME_SIZE){
        my_strncpy(class[i].name, name, MAX_NAME_SIZE-1);
      }
      else {my_strncpy(class[i].name, name, MAX_NAME_SIZE);}
      
      return SUCCESS;
    }
    i++;
  
  }
  return FAILURE;
 

}

/** swapStudents
 *
 * @brief swaps the position of two hogwarts_student structs in the array of hogwarts_student structs, "class"
 *
 * @param "index1" index of the first hogwarts_student struct in the array "class"
 * @param "index2" index of the second hogwarts_student struct in the array "class"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "index1" and/or "index2" are negative numbers
 *         (2) "index1" and/or "index2" are out of bounds of the array "class"
 */
int swapStudents(int index1, int index2)
{
  if (size == 0) return FAILURE;
  if (index1 < 0){
    return FAILURE;
  } 
  else if (index2 < 0){
    return FAILURE;
  } 
  else if (index1 > size-1){
    return FAILURE;
  }
  else if (index2 > size-1){
    return FAILURE;
  }
  else if (index1 > MAX_CLASS_SIZE-1){
  return FAILURE;
  }
  else if (index2 > MAX_CLASS_SIZE-1){
    return FAILURE;
  }
  
  struct hogwarts_student s1 = class[index1];
  struct hogwarts_student s2 = class[index2];
  
  for (int i = 0; i<size; i++){
    if (i == index1){
      class[index1] = s2;
    }
    if (i == index2){
      class[index2] = s1;
    }
  }
  return SUCCESS;


  
}

/** removeStudent
 *
 * @brief removes student in the array of hogwarts_student structs, "class", that has the same name
 *
 * @param "s" hogwarts_student struct that exists in the array "class"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the student struct "s" can not be found in the array "class"
 */
int removeStudent(struct hogwarts_student s)
{
  // size_t currentSize = size;
  if (size == 0) {
    return FAILURE;}
  int index;
  for (int i = 0; i<size;i++){
    if (my_strncmp(class[i].name, s.name, MAX_NAME_SIZE) == 0){
    for (index=i; index<size-1; index++){
      swapStudents(index,index+1);
    }
    size--;
    return SUCCESS;
    }
  }
  

  // if((index >= 0) & (index !=(size-1))){
  //   class[index] = class[size-1];
  // }

//   for(int i = 0, i < varorArraySize, i++){
// if(varunummerToLookFor == varorArray[i].varunummer){
// for (i = pos; i <  varorArraySize - 1; i++)
//             {
//             varorArray[i] = varorArray[i + 1];

return FAILURE;
}


/** compareStudentName
 *
 * @brief using ASCII, compares the last three characters (not including the NULL
 * terminating character) of two students' names
 *
 * @param "s1" hogwarts_student struct that exists in the array "class"
 * @param "s2" hogwarts_student struct that exists in the array "class"
 * @return negative number if s1 is less than s2, positive number if s1 is greater
 *         than s2, and 0 if s1 is equal to s2
 */
int compareStudentName(struct hogwarts_student s1, struct hogwarts_student s2)
{
  int len1 = my_strlen(s1.name);
  int len2 = my_strlen(s2.name);
  const char *last_four1 = &s1.name[len1-3];
  const char *last_four2 = &s2.name[len2-3];
  printf("%s", last_four1);
  return my_strncmp(last_four1, last_four2, 4);
}



/** sortStudents
 *
 * @brief using the compareStudentID function, sort the students in the array of
 * student structs, "class," by the last three characters of their student IDs
 *
 * @param void
 * @return void
 */
void sortStudents(void)
{
   int i, j;
   struct hogwarts_student tmp;
   for(i=0; i<size; i++)
    {
        for(j=i+1; j<size; j++)
        {
            if(compareStudentName(class[j], class[i]) == -1)
            {
                tmp = class[i];
                class[i] = class[j];
                class[j] = tmp;
            }
        }
    }
}
