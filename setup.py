from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext



ext_modules = [
    Pybind11Extension(
        "dbscan",
        ["dbscan.cpp"],  # El nombre de tu archivo C++
    ),
]

setup(
    name="dbscan",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)

