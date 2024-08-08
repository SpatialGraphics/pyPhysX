#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

from utils import PhysicsEngineCPU
from pxr import Usd, UsdPhysics


def main():
    engine = PhysicsEngineCPU()
    material = engine.creator.createMaterial(0, 0, 0)

    source = "xxx.usd"
    stage = Usd.Stage.Open(source, Usd.Stage.LoadAll)

    for prim in stage.Traverse():
        type_name = str(prim.GetTypeName())
        # path = str(prim.GetPath())

        if type_name == "PhysicsMaterialAPI":
            try:
                material_scheme = UsdPhysics.MaterialAPI(prim)
                material.restitution = material_scheme.GetRestitutionAttr().Get()

            except Exception as e:
                print(f"Failed to parse physics scene: {e}")
