from relsa_serializer.serialize_modules.serialize_factory import SerializeFactory

from test_files.class_file import ClassForTest
from test_files.class_file import take_globals as tg1

from test_files.funct_file import f
from test_files.funct_file import take_globals as tg2

test_list = ['1', '2', '3']
test_tuple = ('1', '2', '3')
test_dict = {'1': 1, '2': 2, '3': 3}


def test_for_yaml():
    yaml_s = SerializeFactory.create_serializer("yaml")
    test_item = ClassForTest("Strochka", 256)

    print("\n3. YAML tests:")
    print("\n1) For class:\n\t• Class serialize input: ", ClassForTest)
    yaml_s.dump(ClassForTest, "results/ForClass.yaml", tg1())
    print("\t• Class serialize output: " + str(yaml_s.load("results/ForClass.yaml", tg1())))

    print("\n2) For class object:\n\t• Object serialize input: ", test_item)
    print("\t\t— Result of funct1:", test_item.funct1())
    print("\t\t— Result of funct2:", test_item.funct2())
    yaml_s.dump(test_item, "results/ForObject.yaml", tg1())
    out_item = yaml_s.load("results/ForObject.yaml", tg1())
    print("\t• Object serialize output: ", out_item)
    print("\t\t— Result of funct1:", out_item.funct1())
    print("\t\t— Result of funct2:", out_item.funct2())

    print("\n3) For funct:\n\t• Funct serialize input: ", f)
    print("\t\t— Result for x = 5:", f(5))
    yaml_s.dump(f, "results/ForFunct.yaml", tg2())
    out_f = yaml_s.load("results/ForFunct.yaml", tg2())
    print("\t• Funct serialize output: ", out_f)
    print("\t\t— Result for x = 5:", out_f(5))

    print("\n4) For list:\n\t• List serialize input: ", test_list)
    yaml_s.dump(test_list, "results/ForList.yaml", globals())
    out_list = yaml_s.load("results/ForList.yaml", globals())
    print("\t• List serialize output: ", out_list)

    print("\n5) For tuple:\n\t• Tuple serialize input: ", test_tuple)
    yaml_s.dump(test_tuple, "results/ForTuple.yaml", globals())
    out_tuple = yaml_s.load("results/ForTuple.yaml", globals())
    print("\t• Tuple serialize output: ", out_tuple)

    print("\n6) For dict:\n\t• Dict serialize input: ", test_dict)
    yaml_s.dump(test_dict, "results/ForDict.yaml", globals())
    out_dict = yaml_s.load("results/ForDict.yaml", globals())
    print("\t• Dict serialize output: ", out_dict)
