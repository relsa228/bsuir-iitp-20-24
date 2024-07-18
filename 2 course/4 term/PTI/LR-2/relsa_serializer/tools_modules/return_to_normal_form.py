from relsa_serializer.tools_modules.work_with_function_module.dic_to_ast_module import unparse_ast_str
from relsa_serializer.tools_modules.work_with_function_module.unserialize_funct_module import return_compiled_function
from relsa_serializer.tools_modules.work_with_function_module.unserialize_funct_module import unparsed_funct


def deserialize_from_dict(incoming_dict: dict, globals_from_main) -> object:
    """
    Возвращает объект из универсального словаря
    """
    if 'type' in incoming_dict and incoming_dict['type'] == 'class':
        return class_deserialize(incoming_dict, globals_from_main)

    elif 'type' in incoming_dict and incoming_dict['type'] == 'instance':
        return instance_deserialize(incoming_dict, globals_from_main)

    elif "<class 'function'>" in incoming_dict:
        return function_deserialize(incoming_dict, globals_from_main)

    if 'type' in incoming_dict and incoming_dict['type'] == 'list':
        return list_deserialize(incoming_dict)

    elif 'type' in incoming_dict and incoming_dict['type'] == 'tuple':
        return tuple_deserialize(incoming_dict)

    else:
        else_dict = dict()

        for item in incoming_dict.items():
            if type(item[1]) == dict and 'value' in item[1]:
                else_dict[item[0]] = item[1]['value']

        return else_dict


def class_deserialize(incoming_dict: dict, globals_from_main):
    dict_as_obj = dict()
    for item in incoming_dict.items():
        if type(item[1]) == dict and "<class 'function'>" in item[1]:
            unparsed_funct(unparse_ast_str(item[1]["<class 'function'>"]))
            unprs_fnct = return_compiled_function(unparse_ast_str(item[1]["<class 'function'>"]), globals_from_main)
            dict_as_obj[item[0]] = unprs_fnct

    constructed_class = type(f'{incoming_dict["class_name"]}', (object,), dict_as_obj)

    return constructed_class


def instance_deserialize(incoming_dict: dict, globals_from_main):
    class_deserialized = deserialize_from_dict(incoming_dict['class'], globals_from_main)

    params_dict = dict()
    for item in incoming_dict.items():
        if type(item[1]) == dict and 'value' in item[1]:
            params_dict[item[0]] = item[1]['value']
        elif type(item[1]) == dict and 'type' in item[1] and item[1]['type'] == 'instance' and len(
                params_dict) != 0:
            if class_deserialized:
                for item_in_included in item[1].items():
                    if type(item_in_included) == tuple and 'value' in item_in_included[1]:
                        params_dict[item_in_included[0]] = item_in_included[1]['value']

    constructed_instance = class_deserialized(**params_dict)
    return constructed_instance


def function_deserialize(incoming_dict: dict, globals_from_main):
    unparsed_funct(unparse_ast_str(incoming_dict["<class 'function'>"]))
    unprs_fnct = return_compiled_function(unparse_ast_str(incoming_dict["<class 'function'>"]), globals_from_main)
    return unprs_fnct


def list_deserialize(incoming_dict: dict):
    out_list = list()

    for item in incoming_dict.items():
        if 'value' in item[1]:
            out_list.append(type(item[1]['type'])(item[1]['value']))

    return out_list


def tuple_deserialize(incoming_dict: dict):
    out_tuple = tuple()

    for item in incoming_dict.items():
        if 'value' in item[1]:
            out_tuple = list(out_tuple)
            out_tuple.append(type(item[1]['type'])(item[1]['value']))
            out_tuple = tuple(out_tuple)

    return out_tuple
