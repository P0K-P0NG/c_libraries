.SECONDEXPANSION:
.SILENT:

BLANK :=

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
INCLUDE_DIR := includes
SRC_SUB_DIR := srcs
OBJ_SUB_DIR := objs
LIBS := $(patsubst $(INCLUDE_DIR)/%,lib%.dll, $(wildcard $(INCLUDE_DIR)/*))
HEADER_LIST := $(wildcard $(INCLUDE_DIR)/*/*.h)
OBJ_LIST := $(patsubst %.h,%.o, $(join $(addsuffix $(OBJ_SUB_DIR)/, $(dir $(HEADER_LIST))), $(notdir $(HEADER_LIST))))

.PHONY: print
print: 
	# echo $(patsubst %.h,%.o, $(foreach HEADER, $(HEADER_LIST), $(OBJ_SUB_DIR)/$(HEADER))) > f2.txt
	echo $(HEADER_LIST)

all: $(LIBS)

libbasic_data_manipulation.dll : $$(filter $$(INCLUDE_DIR)/$$(patsubst lib%.dll,%, $$@)/%, $$(OBJ_LIST))
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^

libcuston_io.dll : $$(filter $$(INCLUDE_DIR)/$$(patsubst lib%.dll,%, $$@)/%, $$(OBJ_LIST))
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^

libdata_structure.dll : $$(filter $$(INCLUDE_DIR)/$$(patsubst lib%.dll,%, $$@)/%, $$(OBJ_LIST))
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^ -L"./" -lbasic_data_manipulation

libgeneral_purpose.dll : $$(filter $$(INCLUDE_DIR)/$$(patsubst lib%.dll,%, $$@)/%, $$(OBJ_LIST))
	$(CC) $(CFLAGS) -fpic -shared -o $@ $^

$(OBJ_LIST) : %.o : $$(subst $(OBJ_SUB_DIR),$(SRC_SUB_DIR), %.c) $$(subst $(OBJ_SUB_DIR)/,$(BLANK), %.h)
	$(CC) $(CFLAGS) -fpic -shared $(patsubst %,-I"%",$(wildcard $(INCLUDE_DIR)/*)) -c -o $@ $(filter %.c, $^)

echo : 
	echo  $(subst $(OBJ_SUB_DIR),$(SRC_SUB_DIR), $(OBJ_LIST))

clean : 
	del $(patsubst %,"%", $(subst /,\, $(OBJ_LIST) $(LIBS)))