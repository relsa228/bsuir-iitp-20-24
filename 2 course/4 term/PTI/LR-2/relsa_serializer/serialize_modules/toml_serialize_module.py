import toml

from relsa_serializer.serialize_modules.abstractserializer import AbstractSerializer
from relsa_serializer.tools_modules.convert_to_universal_format import serialize_to_dict
from relsa_serializer.tools_modules.return_to_normal_form import deserialize_from_dict


class TomlSerializer(AbstractSerializer):
    def dump(self, target_item, file_path: str, globals_from_main: dict) -> None:
        """
        Сериализация объекта в файл
        """
        with open(file_path, 'w+') as file:
            toml.dump(serialize_to_dict(target_item, globals_from_main), file)
            file.close()

    def dumps(self, target_item, globals_from_main: dict) -> str:
        """
        Сериализация объекта в строку
        """
        return toml.dumps(serialize_to_dict(target_item, globals_from_main))

    def load(self, file_path: str, globals_from_main) -> all:
        """
        Возвращает объект из файла
        """
        with open(file_path, 'r+') as file:
            wrk_str = toml.load(file)
            file.close()
        return deserialize_from_dict(wrk_str, globals_from_main)

    def loads(self, target_str, globals_from_main) -> all:
        """
        Возвращает объект из строки
        """
        wrk_str = toml.loads(target_str)
        return deserialize_from_dict(wrk_str, globals_from_main)
