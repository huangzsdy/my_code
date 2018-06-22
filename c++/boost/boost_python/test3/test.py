import sys
import os

import test3
world = test3.World("3")
print(world.greet())
world.set('holw')
print(world.greet())
