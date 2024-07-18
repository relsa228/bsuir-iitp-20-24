from relsa_serializer.serialize_modules.json_serialize_module import JsonSerializer
from relsa_serializer.serialize_modules.toml_serialize_module import TomlSerializer
from relsa_serializer.serialize_modules.yaml_serialize_module import YamlSerializer


class SerializeFactory:

    @staticmethod
    def create_serializer(name_of_serializer: str) -> object:
        """
        Возвращает сериализатор по имени формата
        """
        lw_name = name_of_serializer.lower()
        if lw_name == "json":
            return JsonSerializer()
        elif lw_name == "toml":
            return TomlSerializer()
        elif lw_name == "yaml":
            return YamlSerializer()
