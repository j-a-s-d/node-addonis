/**

 NodeJS Addonis               http://coderesearchlabs.com/nodejsaddonis
 by Javier Santo Domingo                   j-a-s-d@coderesearchlabs.com
 ----------------------------------------------------------------------
 implementation

**/

// Node Addonis user initialize function forward declaration

void initialize();

// v8 related

#include <v8.h>
using namespace v8;

// local uses

#include <string>
#include <stack>
#include <vector>

Handle<Object> _module;
std::stack<Handle<Object>> _constructionStack;

// node.js stuff

#pragma comment(lib, "node")
#include <node.h>

extern "C" void NODE_EXTERN init (Handle<Object> target)
{
	_module = target;
	_constructionStack.push(_module);
	initialize();
	while (!_constructionStack.empty()) {
      _constructionStack.pop();
    }
}

// general

bool isModuleSelected()
{
	return _constructionStack.top() == _module;
}

bool hasMember(const char *name)
{
	return _constructionStack.top()->Has(String::New(name));
}

bool deleteMember(const char *name)
{
	return _constructionStack.top()->Delete(String::New(name));
}

std::string _lastEvaluation = "";

const char* evaluateScript(const char *script)
{
    String::Utf8Value str(Script::Compile(String::New(script))->Run()->ToString());
	_lastEvaluation = (*str ? *str : "<string conversion failed>");
	return _lastEvaluation.c_str();
}

// fields

void _newField(Handle<String> name, Handle<Value> value)
{
	_constructionStack.top()->Set(name, value);
}

void newNullField(const char *name)
{
	_newField(String::NewSymbol(name), Null());
}

void newBooleanField(const char *name, bool value)
{
	_newField(String::NewSymbol(name), Boolean::New(value));
}

void newUnsignedIntegerField(const char *name, unsigned int value)
{
	_newField(String::NewSymbol(name), Uint32::New(value));
}

void newIntegerField(const char *name, int value)
{
	_newField(String::NewSymbol(name), Int32::New(value));
}

void newDoubleField(const char *name, double value)
{
	_newField(String::NewSymbol(name), Number::New(value));
}

void newStringField(const char *name, const char *value)
{
	_newField(String::NewSymbol(name), String::New(value));
}

// constants

void _newConstant(Handle<String> name, Handle<Value> value)
{
	_constructionStack.top()->Set(name, value, static_cast<PropertyAttribute>(ReadOnly|DontDelete));
}

void newNullConstant(const char *name)
{
	_newConstant(String::NewSymbol(name), Null());
}

void newBooleanConstant(const char *name, bool value)
{
	_newConstant(String::NewSymbol(name), Boolean::New(value));
}

void newUnsignedIntegerConstant(const char *name, unsigned int value)
{
	_newConstant(String::NewSymbol(name), Uint32::New(value));
}

void newIntegerConstant(const char *name, int value)
{
	_newConstant(String::NewSymbol(name), Int32::New(value));
}

void newDoubleConstant(const char *name, double value)
{
	_newConstant(String::NewSymbol(name), Number::New(value));
}

void newStringConstant(const char *name, const char *value)
{
	_newConstant(String::NewSymbol(name), String::New(value));
}

// function arguments

struct argumentsStruct {
    Handle<Value>* arguments;
	int count;
};
argumentsStruct _currentArgs;
std::string _lastArgument = "";

void _enterArgumentsUsageSection(const Arguments& args)
{
	_currentArgs.count = args.Length();
	_currentArgs.arguments = new Handle<Value>[_currentArgs.count];
	for (int i = 0; i < _currentArgs.count; ++i) {
		_currentArgs.arguments[i] = args[i];
	}
}

void _leaveArgumentsUsageSection()
{
	delete[] _currentArgs.arguments;
	_currentArgs.count = 0;
}

int getArgumentsCount()
{
	return _currentArgs.count;
}

bool isNullArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsNull();
	} else {
		return false;
	}
}

bool isBooleanArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsBoolean();
	} else {
		return false;
	}
}

bool getBooleanArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->BooleanValue();
	} else {
		return false;
	}
}

bool isUnsignedIntegerArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsUint32();
	} else {
		return false;
	}
}

unsigned int getUnsignedIntegerArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->Uint32Value();
	} else {
		return false;
	}
}

int64_t get64BitsIntegerArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IntegerValue();
	} else {
		return false;
	}
}

bool isIntegerArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsInt32();
	} else {
		return false;
	}
}

int getIntegerArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->Int32Value();
	} else {
		return false;
	}
}

bool isDoubleArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsNumber();
	} else {
		return false;
	}
}

double getDoubleArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->NumberValue();
	} else {
		return false;
	}
}

bool isStringArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsString();
	} else {
		return false;
	}
}

const char* getStringArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		String::Utf8Value str(_currentArgs.arguments[argumentNumber]);
		_lastArgument = (*str ? *str : "<string conversion failed>");
		return _lastArgument.c_str();
	} else {
		return "";
	}
}

bool isArrayArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsArray();
	} else {
		return false;
	}
}

bool isObjectArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsObject();
	} else {
		return false;
	}
}

bool isFunctionArgument(int argumentNumber)
{
	if (_currentArgs.count > argumentNumber) {
		return _currentArgs.arguments[argumentNumber]->IsFunction();
	} else {
		return false;
	}
}

// functions

struct callbackStruct {
	std::string name;
};
std::string _lastCallbackName = "";

const char* _getCallbackName(Handle<Function> callee)
{
	String::Utf8Value str(callee->GetName());
	_lastCallbackName = (*str ? *str : "<string conversion failed>");
	return _lastCallbackName.c_str();
}

void _newFunction(Handle<String> name, InvocationCallback callback)
{
    Handle<Function> f = FunctionTemplate::New(callback)->GetFunction();
    f->SetName(name);
    _constructionStack.top()->Set(name, f);
}

struct voidCallbackStruct : callbackStruct {
	void (*callback)();
};
std::vector<voidCallbackStruct> _voidCallbacks;

Handle<Value> handleVoidFunction(const Arguments& args) {
  HandleScope scope;
  _enterArgumentsUsageSection(args);
  const char* callbackName = _getCallbackName(args.Callee());

  Handle<Primitive> result = Undefined();
  for (unsigned int i = 0; i <= _voidCallbacks.size(); i++) {
    if (_voidCallbacks[i].name.size() > 0) {
      if (strcmp(callbackName, _voidCallbacks[i].name.c_str()) == 0) {
        _voidCallbacks[i].callback();
        break;
      }
    }
  }

  _leaveArgumentsUsageSection();
  return scope.Close(result);
}

void newVoidFunction(const char *name, void callback())
{
    voidCallbackStruct _callbackStruct;

    _callbackStruct.name = name;
    _callbackStruct.callback = callback;
    _voidCallbacks.resize(_voidCallbacks.size() + 1);
    _voidCallbacks.push_back(_callbackStruct);

    _newFunction(String::New(name), handleVoidFunction);
}

struct boolCallbackStruct : callbackStruct {
	bool (*callback)();
};
std::vector<boolCallbackStruct> _boolCallbacks;

Handle<Value> handleBooleanFunction(const Arguments& args) {
  HandleScope scope;
  _enterArgumentsUsageSection(args);
  const char* callbackName = _getCallbackName(args.Callee());

  Handle<Boolean> result = Boolean::New(false);
  for (unsigned int i = 0; i <= _boolCallbacks.size(); i++) {
    if (_boolCallbacks[i].name.size() > 0) {
      if (strcmp(callbackName, _boolCallbacks[i].name.c_str()) == 0) {
        result = Boolean::New(_boolCallbacks[i].callback());
        break;
      }
    }
  }

  _leaveArgumentsUsageSection();
  return scope.Close(result);
}

void newBooleanFunction(const char *name, bool callback())
{
    boolCallbackStruct _callbackStruct;

    _callbackStruct.name = name;
    _callbackStruct.callback = callback;
    _boolCallbacks.resize(_boolCallbacks.size() + 1);
    _boolCallbacks.push_back(_callbackStruct);

    _newFunction(String::New(name), handleBooleanFunction);
}

struct uintCallbackStruct : callbackStruct {
	unsigned int (*callback)();
};
std::vector<uintCallbackStruct> _uintCallbacks;

Handle<Value> handleUnsignedIntegerFunction(const Arguments& args) {
  HandleScope scope;
  _enterArgumentsUsageSection(args);
  const char* callbackName = _getCallbackName(args.Callee());

  Handle<Integer> result = Uint32::New(0);
  for (unsigned int i = 0; i <= _uintCallbacks.size(); i++) {
    if (_uintCallbacks[i].name.size() > 0) {
      if (strcmp(callbackName, _uintCallbacks[i].name.c_str()) == 0) {
        result = Uint32::New(_uintCallbacks[i].callback());
        break;
      }
    }
  }

  _leaveArgumentsUsageSection();
  return scope.Close(result);
}

void newUnsignedIntegerFunction(const char *name, unsigned int callback())
{
    uintCallbackStruct _callbackStruct;

	_callbackStruct.name = name;
    _callbackStruct.callback = callback;
    _uintCallbacks.resize(_uintCallbacks.size() + 1);
    _uintCallbacks.push_back(_callbackStruct);

	_newFunction(String::New(name), handleUnsignedIntegerFunction);
}

struct intCallbackStruct : callbackStruct {
	int (*callback)();
};
std::vector<intCallbackStruct> _intCallbacks;

Handle<Value> handleIntegerFunction(const Arguments& args) {
  HandleScope scope;
  _enterArgumentsUsageSection(args);
  const char* callbackName = _getCallbackName(args.Callee());

  Handle<Integer> result = Int32::New(0);
  for (unsigned int i = 0; i <= _intCallbacks.size(); i++) {
    if (_intCallbacks[i].name.size() > 0) {
      if (strcmp(callbackName, _intCallbacks[i].name.c_str()) == 0) {
        result = Int32::New(_intCallbacks[i].callback());
        break;
      }
    }
  }

  _leaveArgumentsUsageSection();
  return scope.Close(result);
}

void newIntegerFunction(const char *name, int callback())
{
    intCallbackStruct _callbackStruct;

	_callbackStruct.name = name;
    _callbackStruct.callback = callback;
    _intCallbacks.resize(_intCallbacks.size() + 1);
    _intCallbacks.push_back(_callbackStruct);

	_newFunction(String::New(name), handleIntegerFunction);
}

struct dblCallbackStruct : callbackStruct {
	double (*callback)();
};
std::vector<dblCallbackStruct> _dblCallbacks;

Handle<Value> handleDoubleFunction(const Arguments& args) {
  HandleScope scope;
  _enterArgumentsUsageSection(args);
  const char* callbackName = _getCallbackName(args.Callee());

  Handle<Number> result = Number::New(0.0);
  for (unsigned int i = 0; i <= _dblCallbacks.size(); i++) {
    if (_dblCallbacks[i].name.size() > 0) {
      if (strcmp(callbackName, _dblCallbacks[i].name.c_str()) == 0) {
        result = Number::New(_dblCallbacks[i].callback());
        break;
      }
    }
  }

  _leaveArgumentsUsageSection();
  return scope.Close(result);
}

void newDoubleFunction(const char *name, double callback())
{
    dblCallbackStruct _callbackStruct;

	_callbackStruct.name = name;
	_callbackStruct.callback = callback;
    _dblCallbacks.resize(_dblCallbacks.size() + 1);
    _dblCallbacks.push_back(_callbackStruct);

	_newFunction(String::New(name), handleDoubleFunction);
}

struct strCallbackStruct : callbackStruct {
	const char* (*callback)();
};
std::vector<strCallbackStruct> _strCallbacks;

Handle<Value> handleStringFunction(const Arguments& args) {
  HandleScope scope;
  _enterArgumentsUsageSection(args);
  const char* callbackName = _getCallbackName(args.Callee());

  Handle<String> result = String::New("");
  for (unsigned int i = 0; i <= _strCallbacks.size(); i++) {
    if (_strCallbacks[i].name.size() > 0) {
      if (strcmp(callbackName, _strCallbacks[i].name.c_str()) == 0) {
        result = String::New(_strCallbacks[i].callback());
        break;
      }
    }
  }

  _leaveArgumentsUsageSection();
  return scope.Close(result);
}

void newStringFunction(const char *name, const char* callback())
{
    strCallbackStruct _callbackStruct;

    _callbackStruct.name.assign(name);
    _callbackStruct.callback = callback;
    _strCallbacks.resize(_strCallbacks.size() + 1);
    _strCallbacks.push_back(_callbackStruct);

    _newFunction(String::New(name), handleStringFunction);
}

// objects

Handle<Object> _newObject()
{
  HandleScope scope;
  return scope.Close(Object::New());
}

void newObject(const char *name)
{
	Handle<Object> obj = _newObject();
	_constructionStack.top()->Set(String::New(name), obj);
	_constructionStack.push(obj);
}

bool hasObject(const char *name)
{
	Handle<Value> target = _constructionStack.top()->Get(String::New(name));
	return target->IsObject();
}

bool selectObject(const char *name)
{
	Handle<Value> target = _constructionStack.top()->Get(String::New(name));
	bool result = target->IsObject();
	if (result) {
		Handle<Object> obj = Handle<Object>::Cast(target);
		_constructionStack.push(obj);
	}
	return result;
}

bool isObjectSelected()
{
	return _constructionStack.top()->IsObject();
}

void closeObject()
{
	_constructionStack.pop();
}

// arrays

Handle<Array> _newArray()
{
  HandleScope scope;
  return scope.Close(Array::New());
}

void newArray(const char *name)
{
	Handle<Array> arr = _newArray();
	_constructionStack.top()->Set(String::New(name), arr);
	_constructionStack.push(arr);
}

bool hasArray(const char *name)
{
	Handle<Value> target = _constructionStack.top()->Get(String::New(name));
	return target->IsArray();
}

bool selectArray(const char *name)
{
	Handle<Value> target = _constructionStack.top()->Get(String::New(name));
	bool result = target->IsArray();
	if (result) {
		Handle<Array> arr = Handle<Array>::Cast(target);
		_constructionStack.push(arr);
	}
	return result;
}

bool isArraySelected()
{
	return _constructionStack.top()->IsArray();
}

void closeArray()
{
	_constructionStack.pop();
}

// array values

void _newArrayValue(Handle<Value> value)
{
	Handle<Value> target = _constructionStack.top();
	if (target->IsArray()) {
		Handle<Array> arr = Handle<Array>::Cast(target);
		arr->Set(arr->Length(), value);
	}
}

void newNullArrayValue()
{
	_newArrayValue(Null());
}

void newBooleanArrayValue(bool value)
{
	_newArrayValue(Boolean::New(value));
}

void newUnsignedIntegerArrayValue(unsigned int value)
{
	_newArrayValue(Uint32::New(value));
}

void newIntegerArrayValue(int value)
{
	_newArrayValue(Int32::New(value));
}

void newDoubleArrayValue(double value)
{
	_newArrayValue(Number::New(value));
}

void newStringArrayValue(const char *value)
{
	_newArrayValue(String::New(value));
}

void newNullArrayValues(int count)
{
	for (int index = 0; index < count; index++) {
		_newArrayValue(Null());
	}
}

void newBooleanArrayValues(bool values[], int count)
{
	for (int index = 0; index < count; index++) {
		_newArrayValue(Boolean::New(values[index]));
	}
}

void newUnsignedIntegerArrayValues(unsigned int values[], int count)
{
	for (int index = 0; index < count; index++) {
		_newArrayValue(Uint32::New(values[index]));
	}
}

void newIntegerArrayValues(int values[], int count)
{
	for (int index = 0; index < count; index++) {
		_newArrayValue(Int32::New(values[index]));
	}
}

void newDoubleArrayValues(double values[], int count)
{
	for (int index = 0; index < count; index++) {
		_newArrayValue(Number::New(values[index]));
	}
}

void newStringArrayValues(const char *values[], int count)
{
	for (int index = 0; index < count; index++) {
		_newArrayValue(String::New(values[index]));
	}
}