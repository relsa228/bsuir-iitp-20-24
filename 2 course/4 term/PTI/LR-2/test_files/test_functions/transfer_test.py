from relsa_serializer.serialize_modules.formats_converter import transfer_to_another_format
from relsa_serializer.serialize_modules.serialize_factory import SerializeFactory
from test_files.class_file import take_globals as tg1

json_ser = SerializeFactory.create_serializer("json")
toml_ser = SerializeFactory.create_serializer("toml")
yaml_ser = SerializeFactory.create_serializer("yaml")


def transfer_test_for_json():
    transfer_to_another_format("results/ForObject.json", "json", "results/transfer/ObjectJsonToml", "toml")
    transfer_to_another_format("results/ForObject.json", "json", "results/transfer/ObjectJsonYaml", "yaml")
    transfer_to_another_format("results/ForObject.json", "json", "results/transfer/ObjectJsonJson", "json")

    json_obj = json_ser.load("results/ForObject.json", tg1())
    json_toml = toml_ser.load("results/transfer/ObjectJsonToml.toml", tg1())
    json_yaml = yaml_ser.load("results/transfer/ObjectJsonYaml.yaml", tg1())

    print("\n1) Transfer test for JSON for class object:")
    print("\t• Object serialize input: ", json_obj)
    print("\t\t— Result of funct1:", json_obj.funct1())
    print("\t\t— Result of funct2:", json_obj.funct2())

    print("\n\t• Object TOML: ", json_toml)
    print("\t\t— Result of funct1:", json_toml.funct1())
    print("\t\t— Result of funct2:", json_toml.funct2())

    print("\n\t• Object YAML: ", json_yaml)
    print("\t\t— Result of funct1:", json_yaml.funct1())
    print("\t\t— Result of funct2:", json_yaml.funct2())


def transfer_test_for_toml():
    transfer_to_another_format("results/ForObject.toml", "toml", "results/transfer/ObjectTomlJson", "json")
    transfer_to_another_format("results/ForObject.toml", "toml", "results/transfer/ObjectTomlYaml", "yaml")
    transfer_to_another_format("results/ForObject.toml", "toml", "results/transfer/ObjectTomlToml", "toml")

    toml_obj = toml_ser.load("results/ForObject.toml", tg1())
    toml_json = json_ser.load("results/transfer/ObjectTomlJson.json", tg1())
    toml_yaml = yaml_ser.load("results/transfer/ObjectTomlYaml.yaml", tg1())

    print("\n2) Transfer test for TOML for class object:")
    print("\t• Object serialize input: ", toml_obj)
    print("\t\t— Result of funct1:", toml_obj.funct1())
    print("\t\t— Result of funct2:", toml_obj.funct2())

    print("\n\t• Object JSON: ", toml_json)
    print("\t\t— Result of funct1:", toml_json.funct1())
    print("\t\t— Result of funct2:", toml_json.funct2())

    print("\n\t• Object YAML: ", toml_yaml)
    print("\t\t— Result of funct1:", toml_yaml.funct1())
    print("\t\t— Result of funct2:", toml_yaml.funct2())


def transfer_test_for_yaml():
    transfer_to_another_format("results/ForObject.yaml", "yaml", "results/transfer/ObjectYamlJson", "json")
    transfer_to_another_format("results/ForObject.yaml", "yaml", "results/transfer/ObjectYamlToml", "toml")
    transfer_to_another_format("results/ForObject.yaml", "yaml", "results/transfer/ObjectYamlYaml", "yaml")

    yaml_obj = yaml_ser.load("results/ForObject.yaml", tg1())
    yaml_json = json_ser.load("results/transfer/ObjectYamlJson.json", tg1())
    yaml_toml = toml_ser.load("results/transfer/ObjectYamlToml.toml", tg1())

    print("\n3) Transfer test for YAML for class object:")
    print("\t• Object serialize input: ", yaml_obj)
    print("\t\t— Result of funct1:", yaml_obj.funct1())
    print("\t\t— Result of funct2:", yaml_obj.funct2())

    print("\n\t• Object JSON: ", yaml_json)
    print("\t\t— Result of funct1:", yaml_json.funct1())
    print("\t\t— Result of funct2:", yaml_json.funct2())

    print("\n\t• Object TOML: ", yaml_toml)
    print("\t\t— Result of funct1:", yaml_toml.funct1())
    print("\t\t— Result of funct2:", yaml_toml.funct2())
