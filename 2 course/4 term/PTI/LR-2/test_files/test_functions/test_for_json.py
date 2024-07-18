from relsa_serializer.serialize_modules.serialize_factory import SerializeFactory


from test_files.class_file import ClassForTest
from test_files.class_file import take_globals as tg1

from test_files.funct_file import f
from test_files.funct_file import take_globals as tg2

test_list = ['1', '2', '3']
test_tuple = ('1', '2', '3')
test_dict = {'1': 1, '2': 2, '3': 3}


def test_for_json():
    json_s = SerializeFactory.create_serializer("json")
    test_item = ClassForTest("Strochka", 256)

    print("\n1. JSON tests:")
    print("\n1) For class:\n\t• Class serialize input: ", ClassForTest)
    json_s.dump(ClassForTest, "results/ForClass.json", tg1())
    print("\t• Class serialize output: " + str(json_s.load("results/ForClass.json", tg1())))

    print("\n2) For class object:\n\t• Object serialize input: ", test_item)
    print("\t\t— Result of funct1:", test_item.funct1())
    print("\t\t— Result of funct2:", test_item.funct2())
    json_s.dump(test_item, "results/ForObject.json", tg1())
    out_item = json_s.load("results/ForObject.json", tg1())
    print("\t• Object serialize output: ", out_item)
    print("\t\t— Result of funct1:", out_item.funct1())
    print("\t\t— Result of funct2:", out_item.funct2())

    print("\n3) For funct:\n\t• Funct serialize input: ", f)
    print("\t\t— Result for x = 5:", f(5))
    json_s.dump(f, "results/ForFunct.json", tg2())
    out_f = json_s.load("results/ForFunct.json", tg2())
    print("\t• Funct serialize output: ", out_f)
    print("\t\t— Result for x = 5:", out_f(5))

    print("\n4) For list:\n\t• List serialize input: ", test_list)
    json_s.dump(test_list, "results/ForList.json", globals())
    out_list = json_s.load("results/ForList.json", globals())
    print("\t• List serialize output: ", out_list)

    print("\n5) For tuple:\n\t• Tuple serialize input: ", test_tuple)
    json_s.dump(test_tuple, "results/ForTuple.json", globals())
    out_tuple = json_s.load("results/ForTuple.json", globals())
    print("\t• Tuple serialize output: ", out_tuple)

    print("\n6) For dict:\n\t• Dict serialize input: ", test_dict)
    json_s.dump(test_dict, "results/ForDict.json", globals())
    out_dict = json_s.load("results/ForDict.json", globals())
    print("\t• Dict serialize output: ", out_dict)
