#ifndef _LEITURA_H_
#define _LEITURA_H_

#include "tipos.h"
#include <stdio.h>

u1 u1Read(FILE *fd);
u2 u2Read(FILE *fd);
u4 u4Read(FILE *fd);
void imprime_constant_utf_value(constant cp);
int nome_u1_igual_string(u1* vetor,char* str,int length);
u1* le_vetor_u1(u2 length,FILE *fp);
u2* le_vetor_u2(u2 length,FILE *fp);
exception* le_exception_table(u2 length,FILE *fp);
class* le_classes_table(u2 length, FILE *fp);
line_number* le_line_number_table(u2 length, FILE* fp);
local_variable* le_local_variable_table(u2 length, FILE* fp);
attribute_info* le_attributes(constant* constantPool,u2 attributes_count,FILE *fp);
void leConstantPool(ClassFile *cf,FILE *fp);
method_info* le_methods(constant* constantPool,u2 length,FILE *fp);
field_info* le_fields(constant* constantPool,u2 length,FILE *fp);
ClassFile* le_class_file (char* arquivo_name) ;

#endif
