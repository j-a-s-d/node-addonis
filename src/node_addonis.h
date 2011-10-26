/**

 NodeJS Addonis               http://coderesearchlabs.com/nodejsaddonis
 by Javier Santo Domingo                   j-a-s-d@coderesearchlabs.com
 ----------------------------------------------------------------------
 interface

**/

// general
bool isModuleSelected();
bool hasMember(const char *name);
bool deleteMember(const char *name);
const char* evaluateScript(const char *script);

// fields
void newNullField(const char *name);
void newBooleanField(const char *name, bool value);
void newUnsignedIntegerField(const char *name, unsigned int value);
void newIntegerField(const char *name, int value);
void newDoubleField(const char *name, double value);
void newStringField(const char *name, const char *value);

// constants
void newNullConstant(const char *name);
void newBooleanConstant(const char *name, bool value);
void newUnsignedIntegerConstant(const char *name, unsigned int value);
void newIntegerConstant(const char *name, int value);
void newDoubleConstant(const char *name, double value);
void newStringConstant(const char *name, const char *value);

// arrays
void newArray(const char *name);
bool hasArray(const char *name);
bool selectArray(const char *name);
bool isArraySelected();
void closeArray();

// array values
void newNullArrayValue();
void newBooleanArrayValue(bool value);
void newUnsignedIntegerArrayValue(unsigned int value);
void newIntegerArrayValue(int value);
void newDoubleArrayValue(double value);
void newStringArrayValue(const char *value);

void newNullArrayValues(int count);
void newBooleanArrayValues(bool values[], int count);
void newUnsignedIntegerArrayValues(unsigned int values[], int count);
void newIntegerArrayValues(int values[], int count);
void newDoubleArrayValues(double values[], int count);
void newStringArrayValues(const char *values[], int count);

// objects
void newObject(const char *name);
bool hasObject(const char *name);
bool selectObject(const char *name);
bool isObjectSelected();
void closeObject();

// functions
void newVoidFunction(const char *name, void callback());
void newBooleanFunction(const char *name, bool callback());
void newUnsignedIntegerFunction(const char *name, unsigned int callback());
void newIntegerFunction(const char *name, int callback());
void newDoubleFunction(const char *name, double callback());
void newStringFunction(const char *name, const char* callback());

// function arguments
int getArgumentsCount();

bool isNullArgument(int argumentNumber);
bool isBooleanArgument(int argumentNumber);
bool isUnsignedIntegerArgument(int argumentNumber);
bool isIntegerArgument(int argumentNumber);
bool isDoubleArgument(int argumentNumber);
bool isStringArgument(int argumentNumber);
bool isArrayArgument(int argumentNumber);
bool isObjectArgument(int argumentNumber);
bool isFunctionArgument(int argumentNumber);

bool getBooleanArgument(int argumentNumber);
unsigned int getUnsignedIntegerArgument(int argumentNumber);
int getIntegerArgument(int argumentNumber);
double getDoubleArgument(int argumentNumber);
const char* getStringArgument(int argumentNumber);
