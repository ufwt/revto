#ifndef MULTICOLUMN_H
#define MULTICOLUMN_H

#include <stdint.h>
#include <stdio.h>

#define MULTICOLUMN_DEFAULT_SIZE 		12
#define MULTICOLUMN_DEFAULT_SEPARATOR 	" | "
#define MULTICOLUMN_DEFAULT_TYPE		MULTICOLUMN_TYPE_STRING
#define MULTICOLUMN_STRING_MAX_SIZE		256

enum multiColumnType{
	MULTICOLUMN_TYPE_STRING			= 0,
	MULTICOLUMN_TYPE_INT8 			= 1,
	MULTICOLUMN_TYPE_INT32 			= 2,
	MULTICOLUMN_TYPE_UINT32 		= 3,
	MULTICOLUMN_TYPE_DOUBLE 		= 4,
	MULTICOLUMN_TYPE_HEX_32			= 5,
	MULTICOLUMN_TYPE_HEX_64 		= 6,
	MULTICOLUMN_TYPE_UNBOUND_STRING = 7,
	MULTICOLUMN_TYPE_BOOL 			= 8
};

#define MULTICOLUMN_TYPE_IS_VALID(type) ((type) <= MULTICOLUMN_TYPE_BOOL)

struct multiColumnColumn{
	uint32_t 					size;
	char 						title[MULTICOLUMN_STRING_MAX_SIZE];
	enum multiColumnType 		type;
};

struct multiColumnPrinter{
	FILE* 						file;
	uint32_t 					nb_column;
	char 						separator[MULTICOLUMN_STRING_MAX_SIZE];
	uint32_t 					auto_header;
	struct multiColumnColumn 	columns[1];
};

struct multiColumnPrinter* multiColumnPrinter_create(FILE* file, uint32_t nb_column, uint32_t* sizes, enum multiColumnType* types, char* separator);
void multiColumnPrinter_set_column_size(struct multiColumnPrinter* printer, uint32_t column, uint32_t size);
void multiColumnPrinter_set_column_type(struct multiColumnPrinter* printer, uint32_t column, enum multiColumnType);
void multiColumnPrinter_set_title(struct multiColumnPrinter* printer, uint32_t column, const char* title);
void multiColumnPrinter_print_header(struct multiColumnPrinter* printer);
void multiColumnPrinter_print_horizontal_separator(struct multiColumnPrinter* printer);
void multiColumnPrinter_print(struct multiColumnPrinter* printer, ...);
void multiColumnPrinter_print_string_line(struct multiColumnPrinter* printer, char* string, uint32_t string_size);

#define multiColumnPrinter_delete(printer) free(printer)

#endif
