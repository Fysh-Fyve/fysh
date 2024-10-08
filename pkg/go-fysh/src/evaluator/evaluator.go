package evaluator

import (
	"fmt"
	"math"

	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/ast"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/ast/binary"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/ast/unary"
	"github.com/Fysh-Fyve/fysh/pkg/go-fysh/src/object"
)

var (
	NULL  = &object.Null{}
	TRUE  = &object.Integer{Value: 1}
	FALSE = &object.Integer{Value: 0}
	BREAK = &object.Break{}
)

type UnknownBinaryOperator struct {
	lt string
	op string
	rt string
}

func (e UnknownBinaryOperator) Error() string {
	return fmt.Sprintf("unknown operator: %s %s %s", e.lt, e.op, e.rt)
}

func unknownBinaryOp(lt object.ObjectType, op binary.Op, rt object.ObjectType) *object.Error {
	return &object.Error{Error: UnknownBinaryOperator{lt: string(lt), op: op.String(), rt: string(rt)}}
}

func Eval(node ast.Node, env *object.Environment) object.Object {
	switch node := node.(type) {
	// Statements
	case *ast.Program:
		return evalProgram(node, env)

	case *ast.BlockStatement:
		return evalBlockStatement(node, env)

	case *ast.AnchorStatement:
		return evalAnchor(node, env)

	case *ast.ExpressionStatement:
		return Eval(node.Expr, env)

	case *ast.BreakStatement:
		return BREAK

	case *ast.ReturnStatement:
		val := Eval(node.Expr, env)
		if object.IsError(val) {
			return val
		}
		return &object.ReturnValue{Value: val}

	case *ast.AssignmentStatement:
		val := Eval(node.Right, env)
		if object.IsError(val) {
			return val
		}
		env.Set(node.Left.String(), val)

	// Expressions
	case *ast.Scales:
		return &object.Integer{Value: node.Value}

	case *ast.Bones:
		return &object.Float{Value: node.Value}

	case *ast.String:
		return &object.String{Value: string(node.Value)}

	// case *ast.Boolean:
	// 	return nativeBoolToBooleanObject(node.Value)

	case *ast.Unary:
		right := Eval(node.Right, env)
		if object.IsError(right) {
			return right
		}
		return evalUnary(node.Op, right)

	case *ast.Binary:
		left := Eval(node.Left, env)
		if object.IsError(left) {
			return left
		}

		right := Eval(node.Right, env)
		if object.IsError(right) {
			return right
		}

		return evalBinary(node.Op, left, right)

	case *ast.Grilled:
		return &object.Integer{Value: int64(env.RandomNum())}

	case *ast.IfStatement:
		return evalIf(node, env)

	case *ast.LoopStatement:
		return evalLoop(node, env)

	case *ast.Identifier:
		return evalIdent(node, env)

	case *ast.SUBRoutine:
		params := node.Parameters
		body := node.Body
		sub := &object.Function{Parameters: params, Env: env, Body: body}
		env.Set(string(node.Name), sub)
		return sub

	case *ast.Call:
		function := Eval(&ast.Identifier{Name: node.Callee}, env)
		if object.IsError(function) {
			return function
		}

		args := evalExprs(node.Args, env)
		if len(args) == 1 && object.IsError(args[0]) {
			return args[0]
		}

		return applyFunction(function, args)

	case *ast.Aquarium:
		elements := evalExprs(node.Elems, env)
		if len(elements) == 1 && object.IsError(elements[0]) {
			return elements[0]
		}
		return &object.Array{Elements: elements}

	case *ast.IncrementStatement:
		return evalUpdate(node.Expr, env, TRUE)

	case *ast.DecrementStatement:
		return evalUpdate(node.Expr, env, evalNeg(TRUE))

	case *ast.Index:
		left := Eval(node.Left, env)
		if object.IsError(left) {
			return left
		}
		index := Eval(node.Index, env)
		if object.IsError(index) {
			return index
		}
		return evalIndexExpression(left, index)

	case *ast.SeaHash:
		return evalHashLiteral(node, env)

	default:
		return newError("unhandled node type: %T", node)
	}
	return nil
}

func evalAnchor(anc *ast.AnchorStatement,
	env *object.Environment) object.Object {
	if anc.Op != binary.AnchorOut {
		return newError("unimplemented anchor: %s", anc.Op)
	}
	val := Eval(anc.Right, env)
	if object.IsError(val) {
		return val
	}
	env.Print(val.Inspect())
	return NULL
}

func evalUpdate(expr ast.Expression,
	env *object.Environment, add object.Object) object.Object {
	id, ok := expr.(*ast.Identifier)
	if !ok {
		return newError("not an identifier")
	}
	ident := Eval(&ast.Identifier{Name: id.Name}, env)
	if object.IsError(ident) {
		return ident
	}
	res := evalBinary(binary.Add, ident, add)
	if object.IsError(res) {
		return res
	}
	env.Set(string(id.Name), res)
	return res
}

func evalProgram(program *ast.Program, env *object.Environment) object.Object {
	var result object.Object

	for _, statement := range program.TopLevels {
		result = Eval(statement, env)

		switch result := result.(type) {
		case *object.ReturnValue:
			return result.Value
		case *object.Error:
			return result
		}
	}

	return result
}

func evalBlockStatement(
	block *ast.BlockStatement,
	env *object.Environment,
) object.Object {
	var result object.Object

	for _, statement := range block.Statements {
		result = Eval(statement, env)

		if result != nil {
			rt := result.Type()
			if rt == object.RET || rt == object.ERR || rt == object.BRK {
				return result
			}
		}
	}

	return result
}

func evalUnary(op unary.Op, right object.Object) object.Object {
	switch op {
	case unary.LogicalNot:
		return evalBang(right)
	case unary.Neg:
		return evalNeg(right)
	case unary.BitwiseNot:
		return evalNot(right)
	default:
		return newError("unknown operator: %s%s", op, right.Type())
	}
}

func evalBinary(op binary.Op, left, right object.Object) object.Object {
	switch lt, rt := left.Type(), right.Type(); {
	case (lt == object.INT || lt == object.FLOAT) && (rt == object.INT || rt == object.FLOAT):
		return evalNumBinary(op, left, right)
	case lt == object.STR && rt == object.STR:
		return evalStrBinary(op, left, right)
	default:
		return unknownBinaryOp(lt, op, rt)
	}
}

func evalBang(right object.Object) object.Object {
	switch right {
	case TRUE:
		return FALSE
	case FALSE:
		return TRUE
	case NULL:
		return TRUE
	default:
		if i, ok := right.(*object.Integer); ok && i.Value == 0 {
			return TRUE
		} else {
			return FALSE
		}
	}
}

func evalNot(right object.Object) object.Object {
	if right.Type() != object.INT {
		return newError("unknown operator: ~%s", right.Type())
	}

	if r, ok := right.(*object.Integer); !ok {
		return newError("%s is not an integer!", right.Inspect())
	} else {
		value := r.Value
		return &object.Integer{Value: ^value}
	}
}

func evalNeg(right object.Object) object.Object {
	if right.Type() != object.INT {
		return newError("unknown operator: -%s", right.Type())
	}

	if r, ok := right.(*object.Integer); !ok {
		return newError("%s is not an integer!", right.Inspect())
	} else {
		value := r.Value
		return &object.Integer{Value: -value}
	}
}

func toBool(input bool) *object.Integer {
	if input {
		return TRUE
	}
	return FALSE
}

// checks if a float is a whole number, if it is, it returns an integer object
func intOrFloat(num float64) object.Object {
	if num == math.Trunc(num) {
		return &object.Integer{Value: int64(num)}
	}
	return &object.Float{Value: num}
}

// shift operations for floats
func shiftRight(f float64, shift int64) float64 {
	return f / float64(int64(1)<<shift)
}

func shiftLeft(f float64, shift int64) float64 {
	return f * float64(int64(1)<<shift)
}

func bitWiseEval(op binary.Op, left, right object.Object) object.Object {
	if right.Type() != object.INT {
		return unknownBinaryOp(left.Type(), op, right.Type())
	}
	rv, ok := right.(*object.Integer)
	if !ok {
		return newError("%s is not an integer object!", right.Inspect())
	}
	rval := rv.Value
	if left.Type() == object.INT {
		lv, ok := left.(*object.Integer)
		if !ok {
			return newError("%s is not an integer object!", left.Inspect())
		}
		lval := lv.Value
		switch op {
		case binary.BitwiseOr:
			return &object.Integer{Value: lval | rval}
		case binary.BitwiseAnd:
			return &object.Integer{Value: lval & rval}
		case binary.BitwiseXor:
			return &object.Integer{Value: lval ^ rval}
		case binary.ShiftLeft:
			return &object.Integer{Value: lval << rval}
		case binary.ShiftRight:
			return &object.Integer{Value: lval >> rval}
		default:
			return unknownBinaryOp(left.Type(), op, right.Type())
		}
	}
	lv, ok := left.(*object.Float)
	if !ok {
		return newError("%s is not a float object!", left.Inspect())
	}
	lval := lv.Value
	switch op {
	case binary.ShiftLeft:
		return &object.Float{Value: shiftLeft(lval, rval)}
	case binary.ShiftRight:
		return &object.Float{Value: shiftRight(lval, rval)}
	default:
		return unknownBinaryOp(left.Type(), op, right.Type())
	}
}

func evalNumBinary(op binary.Op, left, right object.Object) object.Object {
	var leftVal, rightVal float64
	if integer, ok := left.(*object.Integer); ok {
		leftVal = float64(integer.Value)
	} else if float, ok := left.(*object.Float); ok {
		leftVal = float.Value
	} else {
		return newError("evalNumBinary was called with non-numeric object %s", left)
	}
	if integer, ok := right.(*object.Integer); ok {
		rightVal = float64(integer.Value)
	} else if float, ok := right.(*object.Float); ok {
		rightVal = float.Value
	} else {
		return newError("evalNumBinary was called with non-numeric object %s", right)
	}

	switch op {
	case binary.Add:
		return intOrFloat(leftVal + rightVal)
	case binary.Mul:
		return intOrFloat(leftVal * rightVal)
	case binary.Div:
		return intOrFloat(leftVal / rightVal)
	case binary.BitwiseOr,
		binary.BitwiseAnd,
		binary.BitwiseXor,
		binary.ShiftLeft,
		binary.ShiftRight:
		return bitWiseEval(op, left, right)
	case binary.LT:
		return toBool(leftVal < rightVal)
	case binary.LTE:
		return toBool(leftVal <= rightVal)
	case binary.GT:
		return toBool(leftVal > rightVal)
	case binary.GTE:
		return toBool(leftVal >= rightVal)
	case binary.Equal:
		return toBool(leftVal == rightVal)
	case binary.NotEqual:
		return toBool(leftVal != rightVal)
	case binary.LogicalAnd:
		return toBool(leftVal != 0 && rightVal != 0)
	case binary.LogicalOr:
		return toBool(leftVal != 0 || rightVal != 0)
	default:
		return unknownBinaryOp(left.Type(), op, right.Type())
	}
}

func evalStrBinary(op binary.Op, left, right object.Object) object.Object {
	if op != binary.Add {
		return unknownBinaryOp(left.Type(), op, right.Type())
	}

	if lv, ok := left.(*object.String); !ok {
		return newError("%s is not a string!", left.Inspect())
	} else if rv, ok := right.(*object.String); !ok {
		return newError("%s is not a string!", right.Inspect())
	} else {
		return &object.String{Value: lv.Value + rv.Value}
	}
}

func evalLoop(ie *ast.LoopStatement, env *object.Environment) object.Object {
	condition := Eval(ie.Cond, env)
	if object.IsError(condition) {
		return condition
	}

	var value object.Object = NULL

	for isTruthy(condition) {
		value = Eval(ie.Body, env)
		if object.IsError(value) {
			return value
		}
		if value == BREAK {
			return nil
		}
		condition = Eval(ie.Cond, env)
		if object.IsError(condition) {
			return condition
		}
	}

	return value
}

func evalIf(ie *ast.IfStatement, env *object.Environment) object.Object {
	condition := Eval(ie.Cond, env)
	if object.IsError(condition) {
		return condition
	}

	if isTruthy(condition) {
		return Eval(ie.Then, env)
	} else if ie.Else != nil {
		return Eval(ie.Else, env)
	} else {
		return NULL
	}
}

func evalIdent(node *ast.Identifier, env *object.Environment) object.Object {
	name := string(node.Name)
	if val, ok := env.Get(name); ok {
		return val
	}

	if builtin, ok := builtins[name]; ok {
		return builtin
	}

	return newError("identifier not found: " + name)
}

func isTruthy(obj object.Object) bool {
	switch obj {
	case NULL:
		return false
	case TRUE:
		return true
	case FALSE:
		return false
	default:
		if i, ok := obj.(*object.Integer); ok {
			return i.Value != 0
		} else {
			return true
		}
	}
}

func newError(format string, a ...interface{}) *object.Error {
	return &object.Error{Message: fmt.Sprintf(format, a...)}
}

func evalExprs(es []ast.Expression, env *object.Environment) []object.Object {
	var result []object.Object

	for _, e := range es {
		evaluated := Eval(e, env)
		if object.IsError(evaluated) {
			return []object.Object{evaluated}
		}
		result = append(result, evaluated)
	}

	return result
}

func applyFunction(fn object.Object, args []object.Object) object.Object {
	switch fn := fn.(type) {

	case *object.Function:
		extendedEnv := extendFunctionEnv(fn, args)
		evaluated := Eval(fn.Body, extendedEnv)
		return unwrapReturnValue(evaluated)

	case *object.Builtin:
		return fn.Fn(args...)

	default:
		return newError("not a function: %s", fn.Type())
	}
}

func extendFunctionEnv(
	fn *object.Function,
	args []object.Object,
) *object.Environment {
	env := object.NewEnclosedEnvironment(fn.Env)

	for paramIdx, param := range fn.Parameters {
		env.Set(string(param.Name), args[paramIdx])
	}

	return env
}

func unwrapReturnValue(obj object.Object) object.Object {
	if returnValue, ok := obj.(*object.ReturnValue); ok {
		return returnValue.Value
	}

	return obj
}

func evalIndexExpression(left, index object.Object) object.Object {
	switch {
	case left.Type() == object.ARR && index.Type() == object.INT:
		return evalArrayIndexExpression(left, index)
	case left.Type() == object.MAP:
		return evalHashIndexExpression(left, index)
	default:
		return newError("index operator not supported: %s", left.Type())
	}
}

func evalArrayIndexExpression(array, index object.Object) object.Object {
	arrayObject, ok := array.(*object.Array)
	if !ok {
		return newError("%s is not an array object!", array.Inspect())
	}
	idx, ok := index.(*object.Integer)
	if !ok {
		return newError("%s is not an integer object!", idx.Inspect())
	}
	max := int64(len(arrayObject.Elements) - 1)

	if idx.Value < 0 || idx.Value > max {
		return NULL
	}

	return arrayObject.Elements[idx.Value]
}

func evalHashLiteral(
	node *ast.SeaHash,
	env *object.Environment,
) object.Object {
	pairs := make(map[object.HashKey]object.HashPair)

	for keyNode, valueNode := range node.Pairs {
		key := Eval(keyNode, env)
		if object.IsError(key) {
			return key
		}

		hashKey, ok := key.(object.Hashable)
		if !ok {
			return newError("unusable as hash key: %s", key.Type())
		}

		value := Eval(valueNode, env)
		if object.IsError(value) {
			return value
		}

		hashed := hashKey.HashKey()
		pairs[hashed] = object.HashPair{Key: key, Value: value}
	}

	return &object.Hash{Pairs: pairs}
}

func evalHashIndexExpression(hash, index object.Object) object.Object {
	hashObject, ok := hash.(*object.Hash)
	if !ok {
		return newError("%s is not a hash object!", hash.Inspect())
	}

	key, ok := index.(object.Hashable)
	if !ok {
		return newError("unusable as hash key: %s", index.Type())
	}

	pair, ok := hashObject.Pairs[key.HashKey()]
	if !ok {
		return NULL
	}

	return pair.Value
}
