import os
import unittest

from relsa_serializer.serialize_modules.formats_converter import transfer_to_another_format

from test_files.class_file import ClassForTest
from test_files.class_file import take_globals as tg1

from test_files.funct_file import f
from test_files.funct_file import take_globals as tg2

from relsa_serializer.serialize_modules.serialize_factory import SerializeFactory
from relsa_serializer.tools_modules.convert_to_universal_format import serialize_to_dict
from relsa_serializer.tools_modules.return_to_normal_form import deserialize_from_dict

test_list = ['1', '2', '3']
test_tuple = ('1', '2', '3')
test_dict = {'1': 1, '2': 2, '3': 3}


class TestClass(unittest.TestCase):

    def setUp(self):
        self.to_toml_serializer = SerializeFactory.create_serializer('toml')
        self.to_yaml_serializer = SerializeFactory.create_serializer('yaml')
        self.to_json_serializer = SerializeFactory.create_serializer('json')

    def test_serialization_class(self):
        serialized = serialize_to_dict(ClassForTest, tg1())
        restored = deserialize_from_dict(serialized, tg1())
        instance_tmp1 = ClassForTest("aboba", 228)
        instance_tmp2 = restored

        self.assertEqual(instance_tmp1, instance_tmp2)

        tmp1 = instance_tmp1.funct1()
        tmp2 = instance_tmp2.funct1()

        self.assertEqual(tmp1, tmp2)

    def test_serialization_class_object(self):
        serialized = serialize_to_dict(ClassForTest("aboba", 228), tg1())
        restored = deserialize_from_dict(serialized, tg1())
        self.assertEqual(ClassForTest("aboba", 228), restored)

    def test_serialization_function(self):
        serialized = serialize_to_dict(f, tg2())
        deserialized = deserialize_from_dict(serialized, tg2())
        self.assertEqual(f(5), deserialized(5))

    def test_formats_serializer_class(self):
        self.to_toml_serializer.dump(ClassForTest, "results/ForClass.toml", tg1())
        restored_class_toml = self.to_toml_serializer.load("results/ForClass.toml", tg1())

        self.to_yaml_serializer.dump(ClassForTest, "results/ForClass.yaml", tg1())
        restored_class_yaml = self.to_yaml_serializer.load("results/ForClass.yaml", tg1())

        self.to_json_serializer.dump(ClassForTest, "results/ForClass.json", tg1())
        restored_class_json = self.to_json_serializer.load("results/ForClass.json", tg1())

        restored_class_object_from_class_toml = restored_class_toml()
        intial_class_object_toml = ClassForTest("aboba", 228)

        tmp_toml1 = restored_class_object_from_class_toml.funct1()
        tmp_toml2 = intial_class_object_toml.funct1()

        restored_class_object_from_class_yaml = restored_class_yaml()
        intial_class_object_yaml = ClassForTest("aboba", 228)

        tmp_yaml1 = restored_class_object_from_class_yaml.funct1()
        tmp_yaml2 = intial_class_object_yaml.funct1()

        restored_class_object_from_class_json = restored_class_json()
        intial_class_object_json = ClassForTest("aboba", 228)

        tmp_json1 = restored_class_object_from_class_json.funct1()
        tmp_json2 = intial_class_object_json.funct1()

        self.assertEqual(tmp_toml2, tmp_toml1)
        self.assertEqual(tmp_yaml2, tmp_yaml1)
        self.assertEqual(tmp_json2, tmp_json1)

    def test_formats_serializer_class_object(self):
        self.to_toml_serializer.dump(ClassForTest("aboba", 228), "results/ForObject.toml", tg1())
        restored_class_object_toml = self.to_toml_serializer.load("results/ForObject.toml", tg1())

        self.to_yaml_serializer.dump(ClassForTest("aboba", 228), "results/ForObject.yaml", tg1())
        restored_class_object_yaml = self.to_yaml_serializer.load("results/ForObject.yaml", tg1())

        self.to_json_serializer.dump(ClassForTest("aboba", 228), "results/ForObject.json", tg1())
        restored_class_object_json = self.to_json_serializer.load("results/ForObject.json", tg1())

        self.assertEqual(ClassForTest("aboba", 228), restored_class_object_toml)
        self.assertEqual(ClassForTest("aboba", 228), restored_class_object_yaml)
        self.assertEqual(ClassForTest("aboba", 228), restored_class_object_json)

    def test_formats_serializer_function(self):
        self.to_toml_serializer.dump(f, "results/ForFunct.toml", tg2())
        restored_function_toml = self.to_toml_serializer.load("results/ForFunct.toml", tg2())

        self.to_yaml_serializer.dump(f, "results/ForFunct.yaml", tg2())
        restored_function_yaml = self.to_yaml_serializer.load("results/ForFunct.yaml", tg2())

        self.to_json_serializer.dump(f, "results/ForFunct.json", tg2())
        restored_function_json = self.to_json_serializer.load("results/ForFunct.json", tg2())

        self.assertEqual(restored_function_toml(5), f(5))
        self.assertEqual(restored_function_yaml(5), f(5))
        self.assertEqual(restored_function_json(5), f(5))

    def test_formats_serializer_dict(self):
        self.to_toml_serializer.dump(test_dict, "results/ForDict.toml", globals())
        restored_test_dict_toml = self.to_toml_serializer.load("results/ForDict.toml", globals())

        self.to_yaml_serializer.dump(test_dict, "results/ForDict.yaml", globals())
        restored_test_dict_yaml = self.to_yaml_serializer.load("results/ForDict.yaml", globals())

        self.to_json_serializer.dump(test_dict, "results/ForDict.json", globals())
        restored_test_dict_json = self.to_json_serializer.load("results/ForDict.json", globals())

        self.assertEqual(restored_test_dict_toml, test_dict)
        self.assertEqual(restored_test_dict_yaml, test_dict)
        self.assertEqual(restored_test_dict_json, test_dict)

    def test_formats_serializer_list(self):
        self.to_toml_serializer.dump(test_list, "results/ForList.toml", globals())
        restored_test_list_toml = self.to_toml_serializer.load("results/ForList.toml", globals())

        self.to_yaml_serializer.dump(test_list, "results/ForList.yaml", globals())
        restored_test_list_yaml = self.to_yaml_serializer.load("results/ForList.yaml", globals())

        self.to_json_serializer.dump(test_list, "results/ForList.json", globals())
        restored_test_list_json = self.to_json_serializer.load("results/ForList.json", globals())

        self.assertEqual(restored_test_list_toml, test_list)
        self.assertEqual(restored_test_list_yaml, test_list)
        self.assertEqual(restored_test_list_json, test_list)

    def test_formats_serializer_tuple(self):
        self.to_toml_serializer.dump(test_tuple, "results/ForTuple.toml", globals())
        restored_test_tuple_toml = self.to_toml_serializer.load("results/ForTuple.toml", globals())

        self.to_yaml_serializer.dump(test_tuple, "results/ForTuple.yaml", globals())
        restored_test_tuple_yaml = self.to_yaml_serializer.load("results/ForTuple.yaml", globals())

        self.to_json_serializer.dump(test_tuple, "results/ForTuple.json", globals())
        restored_test_tuple_json = self.to_json_serializer.load("results/ForTuple.json", globals())

        self.assertEqual(restored_test_tuple_toml, test_tuple)
        self.assertEqual(restored_test_tuple_yaml, test_tuple)
        self.assertEqual(restored_test_tuple_json, test_tuple)

    def test_change_formats(self):
        self.assertTrue(transfer_to_another_format("results/ForObject.toml", "toml", "results/transfer/ObjectTomlYaml", "yaml"))
        self.assertTrue(transfer_to_another_format("results/ForObject.json", "json", "results/transfer/ObjectJsonYaml", "yaml"))
        self.assertTrue(transfer_to_another_format("results/ForObject.yaml", "yaml", "results/transfer/ObjectYamlYaml", "yaml"))

        self.assertTrue(transfer_to_another_format("results/ForObject.yaml", "yaml", "results/transfer/ObjectYamlToml", "toml"))
        self.assertTrue(transfer_to_another_format("results/ForObject.json", "json", "results/transfer/ObjectJsonToml", "toml"))
        self.assertTrue(transfer_to_another_format("results/ForObject.toml", "toml", "results/transfer/ObjectTomlToml", "toml"))

        self.assertTrue(transfer_to_another_format("results/ForObject.yaml", "yaml", "results/transfer/ObjectYamlJson", "json"))
        self.assertTrue(transfer_to_another_format("results/ForObject.toml", "toml", "results/transfer/ObjectTomlJson", "json"))
        self.assertTrue(transfer_to_another_format("results/ForObject.json", "json", "results/transfer/ObjectJsonJson", "json"))
