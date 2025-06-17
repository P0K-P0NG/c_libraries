# Coding Standard

## Naming Convention

### Local Variables 
`snake_case`

#### Pointer Variables
 - **No Prefix**: variable name describes the type. e.g. `char **string_array`
 - **No Prefix**: 1 level of indirection beyond the type the variable name describes. e.g. `int *number`
 - **p_<VAR_NAME>**: 2 levels of indirection beyond the type the variable name describes. e.g. `void **p_data`
 - **pp_<VAR_NAME>**: 3 levels of indirection beyond the type the variable name describes. e.g. `void ***pp_data`

### Constants
`ALL_CAPS`

### Structs
`PascalCase`

#### Struct Members
`snake_case`

#### Enums
`PascalCase`

#### Enum Members
`ALL_CAPS`

### Structs
`PascalCase`

#### Union Members
`snake_case` ending in `_u`

### General Functions & Macro Functions
`camelCase`

*Note*: any array containing a void * element will naturally refer to an array of void pointer. Such as `void **items` inferring an array of pointers to items. 

### Struct Specific Functions & Macro Functions
`PascalCase` with the struct name at the start
