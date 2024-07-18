from setuptools import setup

long_description = '''Simple Python module to serialize objects to json, toml or yaml'''

setup(
    name="relsa_serializer",
    packages=["relsa_serializer", "relsa_serializer.serialize_modules", "relsa_serializer.tools_modules",
              "relsa_serializer.tools_modules.work_with_function_module"],
    version="1.0.0",
    author="_relsa",
)
