package support

import protocol "github.com/tliron/glsp/protocol_3_16"

var strTokenTypes []string
var mapTokenTypes map[protocol.SemanticTokenType]uint32
var strTokenModifiers []string
var mapTokenModifiers map[protocol.SemanticTokenModifier]uint32

func create[T ~string](
	orig []T,
	arr *[]string,
	m *map[T]uint32,
) ([]string, map[T]uint32) {
	if len(*arr) == 0 {
		*m = make(map[T]uint32, len(orig))
		*arr = make([]string, len(orig))
		for i, t := range orig {
			(*m)[t] = uint32(i)
			(*arr)[i] = string(t)
		}
	}
	return *arr, *m
}

func GetTokenTypes() ([]string, map[protocol.SemanticTokenType]uint32) {
	return create(TokenTypes[:], &strTokenTypes, &mapTokenTypes)
}

func GetTokenModifiers() ([]string, map[protocol.SemanticTokenModifier]uint32) {
	return create(TokenModifiers[:], &strTokenModifiers, &mapTokenModifiers)
}

var TokenTypes = [...]protocol.SemanticTokenType{
	protocol.SemanticTokenTypeNamespace,
	protocol.SemanticTokenTypeType,
	protocol.SemanticTokenTypeClass,
	protocol.SemanticTokenTypeEnum,
	protocol.SemanticTokenTypeInterface,
	protocol.SemanticTokenTypeStruct,
	protocol.SemanticTokenTypeTypeParameter,
	protocol.SemanticTokenTypeParameter,
	protocol.SemanticTokenTypeVariable,
	protocol.SemanticTokenTypeProperty,
	protocol.SemanticTokenTypeEnumMember,
	protocol.SemanticTokenTypeEvent,
	protocol.SemanticTokenTypeFunction,
	protocol.SemanticTokenTypeMethod,
	protocol.SemanticTokenTypeMacro,
	protocol.SemanticTokenTypeKeyword,
	protocol.SemanticTokenTypeModifier,
	protocol.SemanticTokenTypeComment,
	protocol.SemanticTokenTypeString,
	protocol.SemanticTokenTypeNumber,
	protocol.SemanticTokenTypeRegexp,
	protocol.SemanticTokenTypeOperator,
}

var TokenModifiers = [...]protocol.SemanticTokenModifier{
	protocol.SemanticTokenModifierDeclaration,
	protocol.SemanticTokenModifierDefinition,
	protocol.SemanticTokenModifierReadonly,
	protocol.SemanticTokenModifierStatic,
	protocol.SemanticTokenModifierDeprecated,
	protocol.SemanticTokenModifierAbstract,
	protocol.SemanticTokenModifierAsync,
	protocol.SemanticTokenModifierModification,
	protocol.SemanticTokenModifierDocumentation,
	protocol.SemanticTokenModifierDefaultLibrary,
}
