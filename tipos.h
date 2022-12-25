#ifndef _TIPOS_H_
#define _TIPOS_H_


#define ARRAY_TYPE_BOOLEAN 4
#define ARRAY_TYPE_FLOAT 6
#define ARRAY_TYPE_BYTE 8
#define ARRAY_TYPE_INT 10
#define ARRAY_TYPE_CHAR 5
#define ARRAY_TYPE_DOUBLE 7
#define ARRAY_TYPE_SHORT 9
#define ARRAY_TYPE_LONG 11


#define CONSTANT_Class 7 
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;
typedef unsigned long u8;



typedef struct{
    u1 tag;
    union {
        struct{
            u2 name_index;
        } Class;

        struct {
            u2 class_index;
            u2 name_and_type_index;
        } Fieldref;        

        struct {
            u2 class_index;
            u2 name_and_type_index;
        } Methodref;

        struct {
            u2 class_index;
            u2 name_and_type_index;            
        } InterfaceMethodRef;

        struct {
            u2 name_index;
            u2 descriptor_index;
        } NameAndType;

        struct {
            u2 length;
            u1 *bytes;
        } Utf8;

        struct {
            u2 string_index;
        } String;

        struct {
            u4 bytes;
        } Integer;

        struct {
            u4 bytes;
        } Float;

        struct {
            u4 high_bytes;
            u4 low_bytes;
        } Long;

        struct {
            u4 high_bytes;
            u4 low_bytes;
        } Double;
    }u;
} constant;



// usado no attribute
typedef struct {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} exception;

// usado no attribute
typedef struct {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
} class;


// usado no attribute
typedef struct {
    u2 start_pc;
    u2 line_number;
} line_number;


// usado no attribute
typedef struct {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
} local_variable;


typedef struct attr_info attribute_info;

struct attr_info{
    u2 attribute_name_index; 
    u4 attribute_length;

    union {
        struct{
            u2 constantvalue_index;
        } ConstantValue;

        struct{
            u2 max_stack;
            u2 max_locals;
            u4 code_length;
            u1* code;
            u2 exception_table_length;
            exception* exception_table;
            u2 attributes_count;
            attribute_info* attributes;
        } Code;

        struct{
        } Deprecated;

        struct {
            u2 number_of_exceptions;
            u2* exception_index_table;
        } Exceptions;

        struct {
            u2 number_of_classes;
            class* classes;
        } InnerClasses;


        struct {
            u2 line_number_table_length;
            line_number* line_number_table;
        } LineNumberTable;

        struct {
            u2 local_variable_table_length;
            local_variable* local_variable_table;
        } LocalVariableTable;

        struct {
            u2 sourcefile_index;
        } SourceFile;

    }info;  
};



typedef struct  {
	u2 access_flags;   
	u2 name_index; 
	u2 descriptor_index; 
	u2 attributes_count;    
  	attribute_info *attributes;
}field_info;

typedef struct { 
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
}method_info;



typedef struct{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    constant *constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;
    u2 fields_count;
    field_info *fields;
    u2 methods_count;
    method_info* methods;
    u2 attributes_count;
    attribute_info* attributes;
} ClassFile;


typedef int funcao_exibidora(u1* code,int n, constant constant_pool[]);

#endif

