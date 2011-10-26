var assert = require('assert');

var tests = {
	module: function (addonis) {
		console.log("\nTesting and inspecting module");
		assert.notStrictEqual(addonis, undefined);
		console.log(addonis);
	},
	fields: function (addonis) {
		console.log("Testing and inspecting fields");
		// nullField
		assert.equal(addonis.nullField, null);
		addonis.nullField = [];
		assert.notEqual(addonis.nullField, null);
		console.log(addonis.nullField);
		// boolField
		assert.equal(addonis.boolField, true);
		addonis.boolField = false;
		assert.equal(addonis.boolField, false);
		console.log(addonis.boolField);
		// uintField
		assert.equal(addonis.uintField, 0);
		addonis.uintField = 4;
		assert.equal(addonis.uintField, 4);
		console.log(addonis.uintField);
		// intField
		assert.equal(addonis.intField, -1);
		addonis.intField = 4;
		assert.equal(addonis.intField, 4);
		console.log(addonis.intField);
		// doubleField
		assert.equal(addonis.doubleField, 1.5);
		addonis.doubleField = 3.3;
		assert.equal(addonis.doubleField, 3.3);
		console.log(addonis.doubleField);
		// strField
		assert.equal(addonis.strField, 'test');
		addonis.strField = 'abc';
		assert.equal(addonis.strField, 'abc');
		console.log(addonis.strField);
	},
	constants: function (addonis) {
		console.log("Testing and inspecting constants");
		// NULL_CONST
		assert.strictEqual(addonis.NULL_CONST, null);
		addonis.NULL_CONST = [];
		assert.strictEqual(addonis.NULL_CONST, null);
		console.log(addonis.NULL_CONST);
		// BOOL_CONST
		assert.strictEqual(addonis.BOOL_CONST, false);
		addonis.BOOL_CONST = true;
		assert.strictEqual(addonis.BOOL_CONST, false);
		console.log(addonis.BOOL_CONST);
		// UINT_CONST
		assert.strictEqual(addonis.UINT_CONST, 0);
		addonis.UINT_CONST = 4;
		assert.strictEqual(addonis.UINT_CONST, 0);
		console.log(addonis.UINT_CONST);
		// INT_CONST
		assert.strictEqual(addonis.INT_CONST, -1);
		addonis.INT_CONST = 4;
		assert.strictEqual(addonis.INT_CONST, -1);
		console.log(addonis.INT_CONST);
		// DBL_CONST
		assert.strictEqual(addonis.DBL_CONST, 3.14);
		addonis.DBL_CONST = 2.5;
		assert.strictEqual(addonis.DBL_CONST, 3.14);
		console.log(addonis.DBL_CONST);
		// STR_CONST
		assert.strictEqual(addonis.STR_CONST, 'testing');
		addonis.STR_CONST = 'attention';
		assert.strictEqual(addonis.STR_CONST, 'testing');
		console.log(addonis.STR_CONST);
	},
	arrays: function (addonis) {
		console.log("Testing and inspecting arrays");
		assert.notStrictEqual(addonis.sampleArray, undefined);
		console.log(addonis.sampleArray);
		assert.equal(addonis.sampleArray.length, 9);
	},
	objects: function (addonis) {
		console.log("Testing and inspecting objects");
		assert.notStrictEqual(addonis.information, undefined);
		console.log(addonis.information);
		assert.notStrictEqual(addonis.information.version, undefined);
		console.log(addonis.information.version);
	},
	function_calls: function (addonis) {
		console.log("Testing and inspecting functions calls");
		assert.strictEqual(addonis.evalThis("1 + 1"), "2");
		console.log(addonis.evalThis("1 + 1"));
		assert.strictEqual(addonis.getSomething(), "getSomething");
		console.log(addonis.getSomething());
		assert.strictEqual(addonis.getAddonis(), "Addonis");
		console.log(addonis.getAddonis());
		assert.strictEqual(addonis.isDifficult(), false);
		console.log(addonis.isDifficult());
		assert.strictEqual(addonis.isUseful(), true);
		console.log(addonis.isUseful());
		assert.strictEqual(addonis.getNegativeOne(), -1);
		console.log(addonis.getNegativeOne());
		assert.strictEqual(addonis.getNegative2(), -2);
		console.log(addonis.getNegative2());
		assert.strictEqual(addonis.get42(), 42);
		console.log(addonis.get42());
		assert.strictEqual(addonis.getOneTwoThree(), 123);
		console.log(addonis.getOneTwoThree());
		assert.strictEqual(addonis.getPI(), 3.14);
		console.log(addonis.getPI());
		assert.strictEqual(addonis.getPHI(), 1.618);
		console.log(addonis.getPHI());
	},
	procedure_calls: function (addonis) {
		console.log("Testing and inspecting procedure calls");
		addonis.doNothing();
		console.log("doNothing has been called");
		addonis.print();
		addonis.print(null);
		addonis.print(-1);
		addonis.print(1);
		addonis.print(1.5);
		addonis.print(true);
		addonis.print("hello world");
		addonis.print([1,2,3]);
		addonis.print({ hello: "world" });
		addonis.print(addonis.print);
	}
}

exports.test = function (addonis) {
	console.log("Addonis tests");
	tests.module(addonis);
	console.log("\n");
	tests.fields(addonis);
	console.log("\n");
	tests.constants(addonis);
	console.log("\n");
	tests.arrays(addonis);
	console.log("\n");
	tests.objects(addonis);
	console.log("\n");
	tests.function_calls(addonis);
	console.log("\n");
	tests.procedure_calls(addonis);
}
