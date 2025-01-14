#include "Utilities.h"
#include "../Basis_Structs/Tuple.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* Allocate_and_Copy_Str(const char* source){
  char* New_String=(char*)malloc(sizeof(char)*(strlen(source)+1));
  strcpy(New_String,source);
  return New_String;
}

static void Check_if_empty(FILE* File_ptr){
  fseek(File_ptr,0,SEEK_END);
  size_t size = ftell(File_ptr);
  if(0==size){
    printf("File is empty");
    exit(-1);
  }
  fseek(File_ptr,0,SEEK_SET);
}

int Open_File_for_Read(FILE** File_Ptr,const char* File_Name){
  if(((*File_Ptr)=fopen(File_Name,"r"))!=NULL){
    Check_if_empty(*File_Ptr);
    return 1;
  }
  printf("Error at file opening\n");
  exit(-1);
}

int Open_File_for_Write(FILE** File_Ptr,const char* File_Name){
  if(((*File_Ptr)=fopen(File_Name,"w"))!=NULL)
    return 1;
  printf("Error at file opening\n");
  perror("Error");
  exit(-1);
}

Tuple_Ptr Allocate_Array(int Array_elements){

  if(Array_elements==0)
    return NULL;

  Tuple_Ptr New_Array = (Tuple_Ptr) malloc(Array_elements* sizeof(struct Tuple));

  if(New_Array==NULL){
    printf("Memory Allocation Failed\n");
    return NULL;
  }
  return New_Array;
}

int Free_Array(Tuple_Ptr Array) {

  if(Array==NULL)
    return 0;

  free(Array);
  return 1;

}

int generic_swap(void* value_1, void* value_2, int size){
  void* temp;

   if((temp=malloc(size))==NULL)
    return -1;

  memcpy(temp,value_1,size);
  memcpy(value_1,value_2,size);
  memcpy(value_2,temp,size);
  free(temp);
  return 0;
}
