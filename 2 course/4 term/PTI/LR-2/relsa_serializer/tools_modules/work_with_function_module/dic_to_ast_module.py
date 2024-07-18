list_of_asts = ["Module", "Interactive", "Expression", "FunctionType", "FunctionDef", "AsyncFunctionDef",
                "ClassDef", "Return", "Delete", "Assign", "AugAssign", "AnnAssign", "For", "AsyncFor", "While",
                "If", "With", "AsyncWith", "Match", "Raise", "Try", "Assert", "Import", "ImportFrom", "Global",
                "Nonlocal", "Expr", "Pass", "Break", "Continue", "BoolOp", "NamedExpr", "BinOp", "UnaryOp",
                "Lambda", "IfExp", "Dict", "Set", "ListComp", "SetComp", "DictComp", "GeneratorExp", "Await",
                "Yield", "YieldFrom", "Compare", "Call", "FormattedValue", "JoinedStr", "Constant", "Attribute",
                "Subscript", "Starred", "Name", "List", "Tuple", "Slice", "Load", "Store", "Del", "And", "Or",
                "Add", "Sub", "Mult", "MatMult", "Div", "Mod", "Pow", "LShift", "RShift", "BitOr", "BitXor",
                "BitAnd", "FloorDiv", "Invert", "Not", "UAdd", "USub", "Eq", "NotEq", "Lt", "LtE", "Gt", "GtE",
                "Is", "IsNot", "In", "NotIn", "ExceptHandler", "MatchValue", "MatchSingleton", "MatchSequence",
                "MatchMapping", "MatchClass", "MatchStar", "MatchAs", "MatchOr", "TypeIgnore", "arguments", "arg"]


def unparse_ast_str(unparse_ast: str):
    """
    Перевод ast-словаря в форму, пригодную для инициализации заполнения узла
    """
    result_str = unparse_ast.replace(":", "=")
    result_str = result_str[2:]
    result_str = result_str[:len(result_str) - 1]

    for i in range(0, len(result_str)):
        if i == len(result_str):
            break

        if result_str[i] == "'" and result_str[i + 1] == "=":
            result_str = result_str[:i] + result_str[i + 1:]
            for j in range(i, 0, -1):
                if result_str[j] == "'":
                    result_str = result_str[:j] + result_str[j + 1:]
                    break

    for i in range(0, len(result_str)):
        if i == len(result_str):
            break

        flag = 0
        if result_str[i] == "=":
            for j in range(i - 1, -1, -1):
                d = result_str[j]
                if not result_str[j].isalpha():
                    break
                if not result_str[j].islower():
                    flag = 1
                    break

        if flag == 1:
            result_str = result_str[:i] + result_str[i + 1:]

    result_str = result_str.replace("={}", "=[]")
    wrk_list_of_asts = set(list_of_asts)
    for i in wrk_list_of_asts:
        str_1 = i + "{"
        str_2 = i + "("
        result_str = result_str.replace(str_1, str_2)

        str_3 = i + "={"
        result_str = result_str.replace(str_3, str_2)

    result_str = close_all_brekets(result_str)
    result_str = del_figure_braket(result_str)
    result_str = set_dot_ast(result_str)

    result_str = result_str.replace("}", "]")
    result_str = result_str.replace("{", "[")
    return result_str


def set_dot_ast(unparse_ast: str):
    """
    Добавляет 'ast.' перед узлами дерева
    """
    wrk_list_of_asts = set(list_of_asts)
    unparse_ast = "ast." + unparse_ast
    for i in wrk_list_of_asts:
        unparse_ast = unparse_ast.replace(f"{i}(", f"ast.{i}(")

    return unparse_ast[4:]


def close_all_brekets(inpt_str: str):
    """
    Закрывает скобки
    """
    start_index = 0
    for _ in range(0, inpt_str.count('(')):
        current_index = inpt_str.find('(', start_index)
        wrk_ind = current_index
        count = 0
        while True:
            if inpt_str[wrk_ind] == '(' or inpt_str[wrk_ind] == '{':
                count += 1
            elif inpt_str[wrk_ind] == ')' or inpt_str[wrk_ind] == '}':
                count -= 1

            if count == 0:
                inpt_str = inpt_str[:wrk_ind] + ')' + inpt_str[wrk_ind + 1:]
                break
            wrk_ind += 1

        start_index = current_index + 1

    return inpt_str


def del_figure_braket(inpt_str: str):
    """
    Удаление остатков фигурных скобок из строки
    """
    start_index = 0
    for _ in range(0, inpt_str.count('{')):
        current_index = inpt_str.find('{', start_index)
        start_index = current_index + 1
        if inpt_str[current_index - 2] == 'y' and inpt_str[current_index - 3] == 'd' and \
                inpt_str[current_index - 4] == 'o' and inpt_str[current_index - 5] == 'b':
            continue
        elif inpt_str[current_index - 2] == 's' and inpt_str[current_index - 3] == 'g' and \
                inpt_str[current_index - 4] == 'r' and inpt_str[current_index - 5] == 'a' and \
                inpt_str[current_index + 4] != 'u':
            continue
        elif inpt_str[current_index - 2] == 's' and inpt_str[current_index - 3] == 't' and \
                inpt_str[current_index - 4] == 'e' and inpt_str[current_index - 5] == 'g' and \
                inpt_str[current_index - 6] == 'r' and inpt_str[current_index - 7] == 'a' and \
                inpt_str[current_index - 8] == 't':
            continue
        else:
            wrk_index = current_index
            while True:
                if inpt_str[wrk_index] == '(':
                    break
                wrk_index += 1

            count = 0
            while True:
                if inpt_str[wrk_index] == '(':
                    count += 1
                elif inpt_str[wrk_index] == ')':
                    count -= 1

                if count == 0:
                    if not inpt_str[wrk_index + 1] == ',':
                        inpt_str = inpt_str[:current_index] + inpt_str[current_index + 1:]
                        inpt_str = inpt_str[:wrk_index] + inpt_str[wrk_index + 1:]
                    break
                wrk_index += 1

    return inpt_str
