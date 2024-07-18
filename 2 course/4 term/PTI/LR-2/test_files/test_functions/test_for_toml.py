from relsa_serializer.serialize_modules.serialize_factory import SerializeFactory

from test_files.class_file import ClassForTest
from test_files.class_file import take_globals as tg1

from test_files.funct_file import f
from test_files.funct_file import take_globals as tg2

test_list = ['1', '2', '3']
test_tuple = ('1', '2', '3')
test_dict = {'1': 1, '2': 2, '3': 3}


def test_for_toml():
    toml_s = SerializeFactory.create_serializer("toml")
    test_item = ClassForTest("Strochka", 256)

    print("\n2. TOML tests:")
    print("\n1) For class:\n\t• Class serialize input: ", ClassForTest)
    toml_s.dump(ClassForTest, "results/ForClass.toml", tg1())
    print("\t• Class serialize output: " + str(toml_s.load("results/ForClass.toml", tg1())))

    print("\n2) For class object:\n\t• Object serialize input: ", test_item)
    print("\t\t— Result of funct1:", test_item.funct1())
    print("\t\t— Result of funct2:", test_item.funct2())
    toml_s.dump(test_item, "results/ForObject.toml", tg1())
    out_item = toml_s.load("results/ForObject.toml", tg1())
    print("\t• Object serialize output: ", out_item)
    print("\t\t— Result of funct1:", out_item.funct1())
    print("\t\t— Result of funct2:", out_item.funct2())

    print("\n3) For funct:\n\t• Funct serialize input: ", f)
    print("\t\t— Result for x = 5:", f(5))
    toml_s.dump(f, "results/ForFunct.toml", tg2())
    out_f = toml_s.load("results/ForFunct.toml", tg2())
    print("\t• Funct serialize output: ", out_f)
    print("\t\t— Result for x = 5:", out_f(5))

    print("\n4) For list:\n\t• List serialize input: ", test_list)
    toml_s.dump(test_list, "results/ForList.toml", globals())
    out_list = toml_s.load("results/ForList.toml", globals())
    print("\t• List serialize output: ", out_list)

    print("\n5) For tuple:\n\t• Tuple serialize input: ", test_tuple)
    toml_s.dump(test_tuple, "results/ForTuple.toml", globals())
    out_tuple = toml_s.load("results/ForTuple.toml", globals())
    print("\t• Tuple serialize output: ", out_tuple)

    print("\n6) For dict:\n\t• Dict serialize input: ", test_dict)
    toml_s.dump(test_dict, "results/ForDict.toml", globals())
    out_dict = toml_s.load("results/ForDict.toml", globals())
    print("\t• Dict serialize output: ", out_dict)
