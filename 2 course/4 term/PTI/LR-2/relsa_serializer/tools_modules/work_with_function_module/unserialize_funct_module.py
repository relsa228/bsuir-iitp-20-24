import ast
import types


def get_function_name(unparse_str: str) -> str:
    """
    Получение названия функции
    """
    result = ""
    for i in range(4, len(unparse_str)):
        if unparse_str[i] == '(':
            return result
        result += unparse_str[i]


def unparsed_funct(inpt_ast: str):
    """
    Перевод разименованной ast-строки в дерево
    """
    ss = eval(inpt_ast)
    ast.fix_missing_locations(ss)
    unparse_ast = ast.unparse(ss)
    return unparse_ast


def return_compiled_function(new_str: str, globals_main):
    """
    Возвращает рабочую функцию
    """
    unparse = unparsed_funct(new_str)
    ast_node = ast.parse(unparse)
    code = compile(ast_node, '<ast>', mode="exec")
    f_code = next(c for c in code.co_consts if isinstance(c, types.CodeType))
    compiled_function = types.FunctionType(f_code, globals_main)
    return compiled_function
