import sys
from consolemenu import *
from consolemenu.items import *

# Create the menu
menu = ConsoleMenu("Mesterseges inteligencia", "Hazi1")

# Create some items

# MenuItem is the base class for all items, it doesn't do anything when selected
menu_item = MenuItem("Menu Item")

# A FunctionItem runs a Python function when selected
nyers_backtracking = FunctionItem("Nyers backtracking", input, ["Enter an input"])

# A FunctionItem runs a Python function when selected
backtracking_mvr_forward = FunctionItem("Backtracking + MVR + forward checking", input, ["Enter an input"])

# A FunctionItem runs a Python function when selected
backtracking_mvr_ac3 = FunctionItem("Backtracking + MVR + AC-3", input, ["Enter an input"])
# Once we're done creating them, we just add the items to the menu

menu.append_item(menu_item)
menu.append_item(nyers_backtracking)
menu.append_item(backtracking_mvr_forward)
menu.append_item(backtracking_mvr_ac3)

# Finally, we call show to show the menu and allow the user to interact
menu.show()

