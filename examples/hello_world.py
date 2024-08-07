#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

import pyPhysX as physx


def main():
    def error_callback(code: physx.PxErrorCode, message: str, file: str, line: int):
        print(str)

    foundation = physx.PxCreateFoundation(physx.ErrorCallback(error_callback))
    engine = physx.PxCreatePhysics(foundation, physx.PxTolerancesScale())


if __name__ == '__main__':
    main()
