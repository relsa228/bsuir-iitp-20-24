import ast


def ast_to_dict(ast_node) -> str:
    """
    Переводит ast узел в словарь
    """
    wrk_str = ast.dump(ast_node)
    wrk_str = wrk_str.replace('=', ':')
    wrk_str = wrk_str.replace('(', ":{")
    wrk_str = wrk_str.replace(')', '}')
    wrk_str = wrk_str.replace('[', '{')
    wrk_str = wrk_str.replace(']', '}')
    wrk_str = "{" + wrk_str + "}"

    start_index = 0
    while True:
        current_index = wrk_str.find(':', start_index)
        if wrk_str[current_index + 1].isalpha():
            wrk_str = wrk_str[:current_index + 1] + '[' + wrk_str[current_index + 1:]

        if current_index == -1:
            break
        else:
            start_index = current_index + 1

    wrk_str = close_all_brekets(wrk_str)
    wrk_str = wrk_str.replace('[', '{')
    wrk_str = wrk_str.replace(']', '}')

    wrk_str = add_quotes(wrk_str)
    return wrk_str


def close_all_brekets(inpt_str: str) -> str:
    """
    Закрывает открытые скобки (для поиска списков)
    """
    start_index = 0
    for _ in range(0, inpt_str.count('[')):
        current_index = inpt_str.find('[', start_index)

        wrk_ind = current_index
        while True:
            if inpt_str[wrk_ind] == '{':
                break
            wrk_ind += 1

        count = 0
        while True:
            if inpt_str[wrk_ind] == '{':
                count += 1
            elif inpt_str[wrk_ind] == '}':
                count -= 1

            if count == 0:
                inpt_str = inpt_str[:wrk_ind + 1] + ']' + inpt_str[wrk_ind + 1:]
                break
            wrk_ind += 1

        start_index = current_index + 1

    return inpt_str


def add_quotes(inpt_str: str) -> str:
    """
    Названия ast полей берутся в кавычки
    """
    i = 0
    while True:
        if i == len(inpt_str):
            break
        if inpt_str[i].isalpha() and inpt_str[i - 1] != '\'':
            inpt_str = inpt_str[:i] + '\'' + inpt_str[i:]
            i += 1
            while inpt_str[i].isalpha() or inpt_str[i] == '_':
                i += 1
            inpt_str = inpt_str[:i] + '\'' + inpt_str[i:]
        elif inpt_str[i] != '\'':
            while inpt_str[i].isalpha() or inpt_str[i] == '_':
                i += 1
        i += 1
    return inpt_str
