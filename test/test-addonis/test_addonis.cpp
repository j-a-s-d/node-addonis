/**

 NodeJS Addonis               http://coderesearchlabs.com/nodejsaddonis
 by Javier Santo Domingo                   j-a-s-d@coderesearchlabs.com
 ----------------------------------------------------------------------
 windows test

**/

// windows related

#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

// NJSA require

#include <node_addonis.h>

// local uses

#include <stdio.h>
#include <string>

// routines

void doNothing()
{
	//
}

void print()
{
  if (getArgumentsCount() > 0) {
    printf("print() invoked with parameters and the first of them is");
	if (isNullArgument(0)) {
		printf(": ");
	} else if (isBooleanArgument(0)) {
		printf(" a boolean: ");
	} else if (isUnsignedIntegerArgument(0)) {
		printf(" an unsigned integer: ");
	} else if (isIntegerArgument(0)) {
		printf(" an integer: ");
	} else if (isDoubleArgument(0)) {
		printf(" a double: ");
	} else if (isArrayArgument(0)) {
		printf(" an array: ");
	} else if (isFunctionArgument(0)) {
		printf(" a function: ");
	} else if (isObjectArgument(0)) {
		printf(" an object: ");
	} else if (isStringArgument(0)) {
		printf(" an string: ");
	}
	const char* cstr = getStringArgument(0);
	printf(cstr);
	printf("\n");
  } else {
	printf("print() invoked without parameters\n");
  }
  fflush(stdout);
}

int getNegative1()
{
	return -1;
}

int getNegative2()
{
	return -2;
}

unsigned int getFourtyTwo()
{
	return 42;
}

unsigned int getOneTwoThree()
{
	return 123;
}

double getPI()
{
	return 3.14;
}

double getPHI()
{
	return 1.618;
}

const char* getAddonis()
{
	return "Addonis";
}

const char* getSomething()
{
	return "getSomething";
}

const char* evalThis()
{
	std::string script;
	for (int i = 0; i < getArgumentsCount(); ++i) {
	  if (i > 0) {
        script.append(" ");
	  }
	  script.append(getStringArgument(i));
    }
	return evaluateScript(script.c_str());
}

bool isUseful()
{
	return true;
}

bool isDifficult()
{
	return false;
}

// user initialize function called by Addonis on startup

void initialize()
{
#ifdef _DEBUG
	evaluateScript("console.log('entering initialize()')");

	evaluateScript("console.log('.. fields related stuff')");
#endif
	newNullField("nullField");
	newBooleanField("boolField", true);
	newUnsignedIntegerField("uintField", 0);
	newIntegerField("intField", -1);
	newDoubleField("doubleField", 1.5);
	newStringField("strField", "test");

#ifdef _DEBUG
	evaluateScript("console.log('.. constants related stuff')");
#endif
	newNullConstant("NULL_CONST");
	newBooleanConstant("BOOL_CONST", false);
	newUnsignedIntegerConstant("UINT_CONST", 0);
	newIntegerConstant("INT_CONST", -1);
	newDoubleConstant("DBL_CONST", 3.14);
	newStringConstant("STR_CONST", "testing");

#ifdef _DEBUG
	evaluateScript("console.log('.. array related stuff')");
#endif
	newArray("sampleArray");
	if (isArraySelected()) {
		newUnsignedIntegerArrayValue(0);
		newDoubleArrayValue(1.1);
		newBooleanArrayValue(false);
			newIntegerConstant("MY_CONST", 3);
		newIntegerArrayValue(-5);
			newIntegerField("test", 10);
		newIntegerArrayValue(-15);
		newStringArrayValue("hello");
		newUnsignedIntegerArrayValue(25);
		newNullArrayValue();
	}
	closeArray();

	newArray("boolArray");
		bool bools[5] = {true, false, true, false, true};
		newBooleanArrayValues(bools, 5);
	closeArray();

	newArray("uintArray");
		unsigned int uints[5] = {1, 2, 3, 4, 5};
		newUnsignedIntegerArrayValues(uints, 5);
	closeArray();

	newArray("intArray");
		int ints[5] = {1, -2, 3, -4, 5};
		newIntegerArrayValues(ints, 5);
	closeArray();

	newArray("dblArray");
		double doubles[5] = {1.1, -2.2, 3.33, -4.4, 5.5};
		newDoubleArrayValues(doubles, 5);
	closeArray();

	newArray("strArray");
		const char *strings[5] = {"abc", "def", "ghi", "jkl", "mno"};
		newStringArrayValues(strings, 5);
	closeArray();

#ifdef _DEBUG
	evaluateScript("console.log('.. object related stuff')");
#endif
	newObject("information");
	if (isObjectSelected()) {
		newStringConstant("title", "Addonis");
		newStringConstant("description", "NodeJS Addon Framework");
		newObject("version");
			newIntegerConstant("MAJOR", 1);
			newIntegerConstant("MINOR", 0);
		closeObject();
	}
	closeObject();

#ifdef _DEBUG
	evaluateScript("console.log('.. array related stuff again')");
#endif
	if (hasArray("sampleArray")) {
		if (selectArray("sampleArray")) {
			newIntegerArrayValue(35);
			closeArray();
		}
	}

#ifdef _DEBUG
	evaluateScript("console.log('.. object related stuff again')");
#endif
	if (hasObject("information")) {
		if (selectObject("information")) {
			newStringConstant("author", "Javier Santo Domingo <j-a-s-d@coderesearchlabs.com>");
			closeObject();
		}
	}

#ifdef _DEBUG
	evaluateScript("console.log('.. functions related stuff')");
#endif
	if (isModuleSelected()) {
		newVoidFunction("doNothing", doNothing);
		newVoidFunction("print", print);

		newUnsignedIntegerFunction("get42", getFourtyTwo);
		newIntegerFunction("getNegativeOne", getNegative1);

		newUnsignedIntegerFunction("getOneTwoThree", getOneTwoThree);
		newIntegerFunction("getNegative2", getNegative2);

		newDoubleFunction("getPI", getPI);
		newDoubleFunction("getPHI", getPHI);

		newBooleanFunction("isUseful", isUseful);
		newBooleanFunction("isDifficult", isDifficult);

		newStringFunction("getAddonis", getAddonis);
		newStringFunction("getSomething", getSomething);

		newStringFunction("toBeRemoved", evalThis);
		if (deleteMember("toBeRemoved")) {
			if (!hasMember("evalThis")) {
				newStringFunction("evalThis", evalThis);
				if (!hasMember("evalThis") || !hasMember("nullField") || !hasMember("NULL_CONST")) {
					newStringFunction("neverAgain", evalThis);
				}
			}
		}
	}

#ifdef _DEBUG
	evaluateScript("console.log('leaving initialize()')");
	evaluateScript("console.log('')");
#endif
}
