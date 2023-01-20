# Item Inventory
A simple inventory made in c++ created for EA's Software Engineering Virtual Intern Program.

## Purpose
Inventory system that allows a user to add, sell, edit, and view items stored in an inventory. When items are sold, the user can check how much money is left in their wallet.

## How to View and Run
Clone this repository and run Inentory.cpp from an IDE

## Features Added
- Item::enter_data() - merged add_data and edit_data into one function
- Item::check_for_less_than_greater_than_zero() - function that's used
		with enter_data to make sure that a negative number or zero is not
		entered when adding or editing an item (data)
- Item::get_name() - function that returns an item's name - used for
		printing an item's name
- Changed items from array to a vector
- Initialized the size of the items vector to 20 in the Inventory
		constuctor to keep consistent with the original array[20]
- Inventory::sell_items() - condition put in to prevent a negative
		number from being inserted in the quantity so that you can't sell
		a negative quantity of items.
- Inventory::remove_item() - function that removes the item from the
		inventory by erasing the index and the data inside from the items
		vector
- Inventory::check_for_empty() - function that checks if the total
		item_count (the current size of the vector) is equal to 0, outputting
		that the inventory is empty, and then returning a boolean
- Inventory::check_wallet() - function that prints out the total_money
- Option 6. added to "Check wallet"
- XML comments on each new added function