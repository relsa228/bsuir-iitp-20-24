import ast

import toml
import yaml


def transfer_to_another_format(input_file: str, input_file_format: str, output_file_name: str,
                               output_file_format: str) -> bool:
    """
    Конвертирует один формат сериализации в другой
    """
    if output_file_format.lower() == 'yaml':
        if input_file_format.lower() == 'toml' and 'toml' in input_file:
            restored_class_toml = toml.load(input_file)
            with open(f"{output_file_name}.yaml", 'w+') as out_file:
                yaml.dump(restored_class_toml, out_file)
            return True

        elif input_file_format.lower() == 'json' and 'json' in input_file:
            with open(input_file, 'r+') as file:
                restored_class_json = ast.literal_eval(file.read())
            with open(f"{output_file_name}.yaml", 'w+') as out_file:
                yaml.dump(restored_class_json, out_file)
            return True

        elif input_file_format.lower() == 'yaml' and 'yaml' in input_file:
            return True

        return False

    elif output_file_format.lower() == 'toml':
        if input_file_format.lower() == 'yaml' and 'yaml' in input_file:
            with open(input_file, 'r+') as in_file:
                restored_class_yaml = yaml.safe_load(in_file.read())
            with open(f"{output_file_name}.toml", 'w+') as out_file:
                toml.dump(restored_class_yaml, out_file)
            return True

        elif input_file_format.lower() == 'json' and 'json' in input_file:
            with open(input_file, 'r+') as file:
                restored_class_json = ast.literal_eval(file.read())
            with open(f"{output_file_name}.toml", 'w+') as out_file:
                toml.dump(restored_class_json, out_file)
            return True

        elif input_file_format.lower() == 'toml' and 'toml' in input_file:
            return True

        return False

    elif output_file_format.lower() == 'json':
        if input_file_format.lower() == 'toml' and 'toml' in input_file:
            restored_class_toml = toml.load(input_file)
            with open(f"{output_file_name}.json", 'w+') as file:
                file.write(str(restored_class_toml))
            return True

        elif input_file_format.lower() == 'yaml' and 'yaml' in input_file:
            with open(input_file, 'r+') as in_file:
                restored_class_yaml = yaml.safe_load(in_file.read())
            with open(f"{output_file_name}.json", 'w+') as file:
                file.write(str(restored_class_yaml))
            return True

        elif input_file_format.lower() == 'json' and 'json' in input_file:
            return True

        return False
