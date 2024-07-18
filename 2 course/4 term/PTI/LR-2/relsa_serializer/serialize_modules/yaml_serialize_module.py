import yaml

from relsa_serializer.serialize_modules.abstractserializer import AbstractSerializer
from relsa_serializer.tools_modules.convert_to_universal_format import serialize_to_dict
from relsa_serializer.tools_modules.return_to_normal_form import deserialize_from_dict


class YamlSerializer(AbstractSerializer):
    def dump(self, target_item, file_path: str, globals_from_main: dict) -> None:
        """
        Сериализация объекта в файл
        """
        with open(file_path, 'w+') as file:
            file.write(yaml.dump(serialize_to_dict(target_item, globals_from_main)))
            file.close()

    def dumps(self, target_item, globals_from_main: dict) -> str:
        """
        Сериализация объекта в строку
        """
        return yaml.safe_dump(serialize_to_dict(target_item, globals_from_main))

    def load(self, file_path: str, globals_from_main) -> all:
        """
        Возвращает объект из файла
        """
        with open(file_path, 'r+') as file:
            wrk_str = file.read()
            wrk_str = yaml.safe_load(wrk_str)
            file.close()
        return deserialize_from_dict(wrk_str, globals_from_main)

    def loads(self, target_str, globals_from_main) -> all:
        """
        Возвращает объект из строки
        """
        wrk_str = yaml.safe_load(target_str)
        return deserialize_from_dict(wrk_str, globals_from_main)
