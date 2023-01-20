#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<vector>

using namespace std;

class Item
{
public:
	Item()
	{
		name = new char[20];
		float price;
		float quantity;
	}
	void enter_data(string, bool);
	void update_quanity(int);
	void display_data();
	float get_price();
	void set_quantity(int);
	int get_quantity();
	string get_name();
	int is_match(char[]);

private:
	char* name;
	float price;
	int quantity;
	int check_for_less_than_greater_than_zero(int, string);
};


class Inventory
{
public:
	Inventory() { items.reserve(20); };
	void add_item();
	void sell_item();
	void sell_item(int);
	void remove_item(int, string);
	void find_item();
	void edit_item();
	void list_items();
	bool check_for_empty();
	void check_wallet();

private:
	vector<Item*> items;
	float total_money = 0.0f;
	int item_count = 0;
	char item_to_check[20];
};

/// <summary>
/// Prints the name, quantity, and price data associated with an item.
/// </summary>
/// <param name="word">A string to represent either " " for adding data
///  or " new " to edit data.</param>
/// <returns>Nothing</returns>
void Item::enter_data(string word, bool ignore)
{
	if (ignore) { cin.ignore(); }
	cout << "\nEnter" << word << "item name: "; cin.getline(name, 20);

	int temp_quantity, temp_price;
	cout << "Enter" << word << "quantity: "; cin >> temp_quantity;
	quantity = check_for_less_than_greater_than_zero(temp_quantity, word);

	cout << "Enter" << word << "price: "; cin >> temp_price;
	price = check_for_less_than_greater_than_zero(temp_price, word);
}

/// <summary>
/// Checks if the input is greater than 0 in order to prevent a 0 or negative
/// number from being passed.
/// </summary>
/// <param name="temp_quantity">Int that stores the input from the user.</param>
/// <param name="word">A string to represent either " " for adding data
///  or " new " to edit data.</param>
/// <returns>An int from an input that's greater than 0.</returns>
int Item::check_for_less_than_greater_than_zero(int temp_quantity, string word)
{
	while (temp_quantity <= 0)
	{
		cout << "\nCannot enter an amount that is 0 or negative. Try again.";
		cout << "\nEnter" << word << "quantity: "; cin >> temp_quantity;
	}

	return temp_quantity;
}

void Item::display_data()
{
	cout << "\nItem name: " << name;
	cout << "\nQuantity: " << quantity;
	cout << "\nPrice: " << price;
}

float Item::get_price()
{
	return price;
}

void Item::set_quantity(int new_quantity)
{
	quantity = new_quantity;
}

int Item::get_quantity()
{
	return quantity;
}

/// <summary>
/// Give's the item's name.
/// </summary>
/// <returns>Returns the item's name as a string. </returns>
string Item::get_name()
{
	return name;
}

int Item::is_match(char object_to_buy[20])
{
	if (strcmp(object_to_buy, name) == 0)
	{
		return 1;
	}
	return 0;
}

void Inventory::add_item()
{
	Item* item = new Item;
	item->enter_data(" ", true);
	items.push_back(item);
	item_count++;
}

void Inventory::sell_item()
{
	if (check_for_empty()) { return; }

	cin.ignore();
	cout << "\nEnter item name: "; cin.getline(item_to_check, 20);

	for (int i = 0; i < item_count; i++)
	{
		if (items[i]->is_match(item_to_check))
		{
			sell_item(i);
		}
	}
	cout << "\nThis item is not in your Inventory";
}

void Inventory::sell_item(int item_index)
{
	int input_quantity;
	Item* item = items[item_index];
	cout << "\nEnter number of items to sell: "; cin >> input_quantity;

	while (input_quantity < 0)
	{
		cout << "\nBad input. Enter a positive number of items to sell: "; cin >> input_quantity;
	}
	int quantity = item->get_quantity();
	if (input_quantity <= quantity)
	{
		float price = item->get_price();
		float money_earned = price * input_quantity;
		float updated_quantity = quantity - input_quantity;
		item->set_quantity(updated_quantity);
		cout << "\n" << input_quantity << " " << item->get_name() << " sold sucessfully";
		cout << "\nQuantity left: " << item->get_quantity();
		cout << "\nMoney received: " << money_earned;
		total_money += money_earned;

		if (updated_quantity <= 0)
		{
			remove_item(item_index, item->get_name());
		}
	}
	else
	{
		cout << "\nCannot sell more items than you have.";
	}
}

/// <summary>
/// Removes an element at the specified index from the vector, items.
/// </summary>
/// <param name="item_index">The index to specify which element should be removed from the vector, items.</param>
/// <param name="name">The name of the item.</param>
void Inventory::remove_item(int item_index, string name)
{
	items.erase(items.begin() + item_index);
	item_count--;
	cout << "\n" << name << " successfully removed from inventory";
}

void Inventory::find_item()
{
	if (check_for_empty()) { return; }

	cin.ignore();
	cout << "\nEnter item name: ";
	cin.getline(item_to_check, 20);

	for (int i = 0; i < item_count; i++)
	{
		if (items[i]->is_match(item_to_check))
		{
			cout << "\nItem found";
			items[i]->display_data();
			return;
		}
	}
	cout << "\nThis item is not in your Inventory";
}

void Inventory::edit_item()
{
	if (check_for_empty()) { return; }

	cin.ignore();
	cout << "\nEnter item name: ";
	cin.getline(item_to_check, 20);

	for (int i = 0; i < item_count; i++)
	{
		if (items[i]->is_match(item_to_check))
		{
			cout << "\nItem found";
			items[i]->enter_data(" new ", false);
			return;
		}
	}

	cout << "\nThis item is not in your Inventory";
}


void Inventory::list_items()
{
	if (check_for_empty()) { return; }

	for (int i = 0; i < item_count; i++)
	{
		items[i]->display_data();
		cout << "\n";
	}
}

/// <summary>
/// Checks if item_count is equal to 0.
/// </summary>
/// <returns><i>Returns a boolean comparing if item_count is equal to 0 or not.</i></returns>
bool Inventory::check_for_empty()
{
	if (item_count == 0)
	{
		cout << "\nInventory empty.";
	}
	return item_count == 0;
}

/// <summary>
/// Prints the total_money
/// </summary>
void Inventory::check_wallet()
{
	cout << total_money << " money availble.";
}

int main()
{
	int choice;
	Inventory inventory_system;

	while (1)
	{
		cout << "\n\nMENU"
			<< "\n1. Add new item"
			<< "\n2. Sell item"
			<< "\n3. Find item"
			<< "\n4. Edit item"
			<< "\n5. List items"
			<< "\n6. Check wallet"
			<< "\n7. Exit"
			<< "\n\nEnter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			inventory_system.add_item();
			break;

		case 2:
			inventory_system.sell_item();
			break;

		case 3:
			inventory_system.find_item();
			break;

		case 4:
			inventory_system.edit_item();
			break;

		case 5:
			inventory_system.list_items();
			break;

		case 6:
			inventory_system.check_wallet();
			break;

		case 7:
			exit(0);
			break;

		default:
			cout << "\nInvalid choice entered";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			break;
		}
	}
	return 0;
}