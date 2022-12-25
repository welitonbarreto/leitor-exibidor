#include "leitura.h"


u1 u1Read(FILE *fd){
	u1 toReturn = getc(fd);
	return toReturn;
}

u2 u2Read(FILE *fd) { 
  u2 toReturn = getc(fd); 
  toReturn = (toReturn << 8) | (getc(fd));
  return toReturn; 
} 

u4 u4Read(FILE *fd) {
	u4 toReturn = u2Read(fd);
	toReturn = (toReturn << 16) | u2Read(fd);
	return toReturn;
}


u1* le_vetor_u1(u2 length,FILE *fp){
	u1* pointer = (u1*) malloc(sizeof(u1)*length);
	u1 *aux;

	for(aux = pointer;aux < pointer + length;aux++) {
		*aux = u1Read(fp);
	}

	return pointer;
}

u2* le_vetor_u2(u2 length,FILE *fp) {
	u2* pointer = (u2*) malloc(sizeof(u2)*length);
	u2 *aux;

  for(aux = pointer;aux < pointer + length;aux++) {
    *aux = u2Read(fp);
  }

  return pointer;
}


exception* le_exception_table(u2 length,FILE *fp) {
	exception* exception_table = (exception *) malloc(sizeof(exception)*length);
	exception* e;

	for (e = exception_table; e < exception_table + length; e++){
		e->start_pc = u2Read(fp);
		e->end_pc = u2Read(fp);
		e->handler_pc = u2Read(fp);
		e->catch_type = u2Read(fp);
	}  

	return exception_table;

}

class* le_classes_table(u2 length, FILE *fp) {
	class* class_table = (class *) malloc(sizeof(class)*length);
	class* c;

	for (c = class_table; c < class_table + length; c++){
		c->inner_class_info_index = u2Read(fp);
    	c->outer_class_info_index = u2Read(fp);
    	c->inner_name_index = u2Read(fp);
    	c->inner_class_access_flags = u2Read(fp);
	}  

	return class_table;
}

line_number* le_line_number_table(u2 length, FILE* fp) {
	line_number* line_number_table = (line_number *) malloc(sizeof(line_number)*length);
	line_number* l;


	for (l = line_number_table; l < line_number_table + length; l++){
		l->start_pc = u2Read(fp);
    	l->line_number = u2Read(fp);
	}  

	return line_number_table;
}


local_variable* le_local_variable_table(u2 length, FILE* fp) {
	local_variable* local_variable_table = (local_variable *) malloc(sizeof(local_variable)*length);
	local_variable* l;

	for (l = local_variable_table; l < local_variable_table + length; l++){
		l->start_pc = u2Read(fp);
    	l->length = u2Read(fp);
    	l->name_index = u2Read(fp);
   		l->descriptor_index = u2Read(fp);
    	l->index = u2Read(fp);
	}  

	return local_variable_table;
}



attribute_info* le_attributes(constant* constantPool,u2 attributes_count,FILE *fp){
	attribute_info* attributes = (attribute_info *) malloc(sizeof(attribute_info)*attributes_count); 
	attribute_info* a;
	int i = 0;

	for (a = attributes; a < attributes + attributes_count;a++) {
		
		a->attribute_name_index = u2Read(fp);
		a->attribute_length = u4Read(fp);

		u1* name = constantPool[a->attribute_name_index-1].u.Utf8.bytes;
		u2 length = constantPool[a->attribute_name_index-1].u.Utf8.length;


		if (nome_u1_igual_string(name,"ConstantValue",length)){
			a->info.ConstantValue.constantvalue_index = u2Read(fp);
		}
		else if (nome_u1_igual_string(name,"Code",length)) {
			a->info.Code.max_stack = u2Read(fp);
			a->info.Code.max_locals = u2Read(fp);
			a->info.Code.code_length = u4Read(fp);
			a->info.Code.code = le_vetor_u1(a->info.Code.code_length,fp);
			a->info.Code.exception_table_length = u2Read(fp);
			a->info.Code.exception_table = le_exception_table(a->info.Code.exception_table_length,fp);
			a->info.Code.attributes_count = u2Read(fp);
			a->info.Code.attributes = le_attributes(constantPool,a->info.Code.attributes_count,fp);
		}
		else if (nome_u1_igual_string(name,"Exceptions",length)) {
			a->info.Exceptions.number_of_exceptions = u2Read(fp);
			a->info.Exceptions.exception_index_table = le_vetor_u2(a->info.Exceptions.number_of_exceptions,fp);
		}
		else if (nome_u1_igual_string(name,"InnerClasses",length)) {
			a->info.InnerClasses.number_of_classes = u2Read(fp);
			a->info.InnerClasses.classes = le_classes_table(a->info.InnerClasses.number_of_classes,fp);
		}
		else if (nome_u1_igual_string(name,"LineNumberTable",length)) {
			a->info.LineNumberTable.line_number_table_length = u2Read(fp);
			a->info.LineNumberTable.line_number_table = le_line_number_table(a->info.LineNumberTable.line_number_table_length,fp);
		}
		else if (nome_u1_igual_string(name,"LocalVariableTable",length)) {
			a->info.LocalVariableTable.local_variable_table_length = u2Read(fp);
			a->info.LocalVariableTable.local_variable_table  = le_local_variable_table(a->info.LocalVariableTable.local_variable_table_length ,fp);
		}
		else if (nome_u1_igual_string(name,"SourceFile",length)) {
			a->info.SourceFile.sourcefile_index = u2Read(fp);
		}
		else {
			le_vetor_u1(a->attribute_length,fp); // descartando valores desconhecidos;
		}

	}

	return attributes;
}


void leConstantPool(ClassFile *cf,FILE *fp) {

	constant *constantPool = (constant*) malloc(sizeof(constant)*(cf->constant_pool_count-1));
	constant *cp;

	int indice_invalido = 0;

	for (cp = constantPool; cp < constantPool + (cf->constant_pool_count-1); cp++){
		
		if (indice_invalido) {
			indice_invalido = 0;
			continue;
		}
		
		cp->tag = u1Read(fp);

		switch(cp->tag) {
			case CONSTANT_Class: 
          		cp->u.Class.name_index = u2Read(fp); 
          		break; 
       		case CONSTANT_Fieldref: 
          		cp->u.Fieldref.class_index = u2Read(fp);  
          		cp->u.Fieldref.name_and_type_index = u2Read(fp); 
        		break; 
        	case CONSTANT_Methodref:
        		cp->u.Methodref.class_index = u2Read(fp);
        		cp->u.Methodref.name_and_type_index = u2Read(fp);
        		break;
        	case CONSTANT_InterfaceMethodref:
        		cp->u.InterfaceMethodRef.class_index = u2Read(fp);
        		cp->u.InterfaceMethodRef.name_and_type_index = u2Read(fp);
        		break;
        	case CONSTANT_String:
        		cp->u.String.string_index = u2Read(fp);
        		break;
        	case CONSTANT_Integer:
        		cp->u.Integer.bytes = u4Read(fp);
        		break;
        	case CONSTANT_Float:
        		cp->u.Float.bytes = u4Read(fp);
				// printf("pego o float em %d",i);
        		break;
        	case CONSTANT_Long:
        		cp->u.Long.high_bytes = u4Read(fp);
        		cp->u.Long.low_bytes = u4Read(fp);
				indice_invalido = 1;
        		break;
        	case CONSTANT_Double:
        		cp->u.Double.high_bytes = u4Read(fp);
        		cp->u.Double.low_bytes = u4Read(fp);
				indice_invalido = 1;
        		break;
        	case CONSTANT_NameAndType:
        		cp->u.NameAndType.name_index = u2Read(fp);
        		cp->u.NameAndType.descriptor_index = u2Read(fp);
        		break;	
        	//Possível erro, talvez ler todo o os bytes do array;
        	case CONSTANT_Utf8:
        		cp->u.Utf8.length = u2Read(fp);
        		cp->u.Utf8.bytes = le_vetor_u1(cp->u.Utf8.length, fp);				
 				break;
			default:
				// printf("padrao %d\n",i+1);
				break;
		}
	}

	cf->constant_pool = constantPool;
}


method_info* le_methods(constant* constantPool,u2 length,FILE *fp) {

	method_info *methods = (method_info*) malloc(sizeof(method_info)*(length));
	method_info *m;

	for (m = methods; m < methods + length; m++){
		m->access_flags = u2Read(fp);
		m->name_index = u2Read(fp);
		m->descriptor_index = u2Read(fp);
		m->attributes_count = u2Read(fp);
		m->attributes = le_attributes(constantPool,m->attributes_count,fp);
	}

	return methods;

}

field_info* le_fields(constant* constantPool,u2 length,FILE *fp) {	

	field_info *fields = (field_info*) malloc(sizeof(field_info)*(length));
	field_info *f;

	for (f = fields; f < fields + length; f++){
		f->access_flags = u2Read(fp);
		f->name_index = u2Read(fp);
		f->descriptor_index = u2Read(fp);
		f->attributes_count = u2Read(fp);
		f->attributes = le_attributes(constantPool,f->attributes_count,fp);
	}

	return fields;

}


ClassFile* le_class_file (char* arquivo_name) {
	FILE *fp = fopen(arquivo_name,"rb");
	ClassFile *cf = (ClassFile *) malloc(sizeof(ClassFile)); 
	cf->magic = u4Read(fp);
	cf->minor_version = u2Read(fp);	
	cf->major_version = u2Read(fp);
	cf->constant_pool_count = u2Read(fp);
	leConstantPool(cf,fp);
	cf->access_flags = u2Read(fp);
	cf->this_class = u2Read(fp);
	cf->super_class = u2Read(fp);
	cf->interfaces_count = u2Read(fp);
	cf->interfaces = le_vetor_u2(cf->interfaces_count,fp);
	cf->fields_count = u2Read(fp);
	cf->fields = le_fields(cf->constant_pool,cf->fields_count,fp);
	cf->methods_count = u2Read(fp);
	cf->methods = le_methods(cf->constant_pool,cf->methods_count,fp);
	cf->attributes_count = u2Read(fp);
	cf->attributes = le_attributes(cf->constant_pool,cf->attributes_count,fp);
	fclose(fp);

	return cf;
}
