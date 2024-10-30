#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct item {
    string name;
    double price;
};
struct address {
    string district, nagar, locality, fullAddress;
    int pinCode;
};
class shoppingCart {
private:
    vector<item> cart;
public:
    void addItem(const item& itm) {
        cart.push_back(itm);
        cout << itm.name << " has been added to your cart.\n";
    }
    void removeItem(int index) {
        if (index >= 0 && index < cart.size()) {
            cout << cart[index].name << " has been removed from your cart.\n";
            cart.erase(cart.begin() + index);
        } else {
            cout << "Invalid item index!\n";
        }
    }
    void displayCart() {
        if (cart.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }
        cout << "\nItems in your cart:\n";
        for (int i = 0; i < cart.size(); i++) {
            cout << i + 1 << ". " << cart[i].name << " - Rs. " << cart[i].price << "\n";
        }
    }
    void clearCart() {
        cart.clear();
        cout << "Your cart has been cleared.\n";
    }
    double getTotalCost() {
        double total = 0;
        for (const auto& itm : cart) {
            total += itm.price;
        }
        return total;
    }
};
void displayDistricts() {
    cout << "\nAvailable Districts in Maharashtra:\n1. Pune\n2. Mumbai\n3. Nagpur\n4. Nashik\nSelect your district: ";
}
string getDistrict(int choice) {
    switch (choice) {
        case 1: return "Pune";
        case 2: return "Mumbai";
        case 3: return "Nagpur";
        case 4: return "Nashik";
        default: return "Unknown";
    }
}
void displayNagars(int districtChoice) {
    cout << "\nAvailable Places (Nagars) in " << getDistrict(districtChoice) << ":\n";
    switch (districtChoice) {
        case 1: cout << "1. Shivaji Nagar\n2. Kothrud\n3. Hinjewadi\n4. Wakad\n"; break;
        case 2: cout << "1. Andheri\n2. Bandra\n3. Dadar\n4. Juhu\n"; break;
        case 3: cout << "1. Dharampeth\n2. Sitabuldi\n3. Sadar\n4. Wardha Road\n"; break;
        case 4: cout << "1. Gangapur Road\n2. Deolali\n3. Panchavati\n4. Satpur\n"; break;
        default: cout << "Unknown district.\n";
    }
    cout << "Select your place: ";
}
string getNagar(int districtChoice, int nagarChoice) {
    if (districtChoice == 1) {
        switch (nagarChoice) {
            case 1: return "Shivaji Nagar";
            case 2: return "Kothrud";
            case 3: return "Hinjewadi";
            case 4: return "Wakad";
        }
    } else if (districtChoice == 2) {
        switch (nagarChoice) {
            case 1: return "Andheri";
            case 2: return "Bandra";
            case 3: return "Dadar";
            case 4: return "Juhu";
        }
    } else if (districtChoice == 3) {
        switch (nagarChoice) {
            case 1: return "Dharampeth";
            case 2: return "Sitabuldi";
            case 3: return "Sadar";
            case 4: return "Wardha Road";
        }
    } else if (districtChoice == 4) {
        switch (nagarChoice) {
            case 1: return "Gangapur Road";
            case 2: return "Deolali";
            case 3: return "Panchavati";
            case 4: return "Satpur";
        }
    }
    return "Unknown";
}
address getAddress() {
    address addr;
    int districtChoice, nagarChoice;
    displayDistricts();
    cin >> districtChoice;
    addr.district = getDistrict(districtChoice);
    displayNagars(districtChoice);
    cin >> nagarChoice;
    addr.nagar = getNagar(districtChoice, nagarChoice);
    cout << "Enter PIN code: ";
    cin >> addr.pinCode;
    cout << "Enter locality: ";
    cin.ignore();
    getline(cin, addr.locality);
    cout << "Enter full address: ";
    getline(cin, addr.fullAddress);
    return addr;
}
int estimateDeliveryTime(const address& addr) {
    int time = 20;
    if (addr.district == "Pune" && addr.nagar == "Hinjewadi") time += 10;
    else if (addr.district == "Mumbai" && addr.nagar == "Andheri") time += 15;
    else if (addr.district == "Nagpur" && addr.nagar == "Sadar") time += 25;
    else time += 30;
    return time;
}
void displayCategories() {
    cout << "\nCategories:\n1. Food\n2. Electronics\n3. Games\nSelect a category (or 0 to finish): ";
}
int main() {
    cout << "Welcome to the Maharashtra Online Store!\n";
    address userAddress = getAddress();
    shoppingCart cart;
    while (true) {
        displayCategories();
        int categoryChoice;
        cin >> categoryChoice;
        if (categoryChoice == 0) {
            cout << "\nYou have chosen to exit categories.\n";
            cart.displayCart(); 
            cout << "\nDo you want to leave the categories section? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                cout << "Exiting categories. Proceeding to cart options.\n";
                break;
            } else {
                continue; 
            }
        }
        vector<item> items; 
        switch (categoryChoice) {
            case 1: items = {{"Bread", 50}, {"Pizza", 300}, {"Burger", 150}}; break;
            case 2: items = {{"Laptop", 55000}, {"Smartphone", 15000}, {"Headphones", 2000}}; break;
            case 3: items = {{"Chess", 500}, {"Monopoly", 700}, {"Video Game", 1500}}; break;
            default: cout << "Invalid category!\n"; continue;
        }
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].name << " - Rs. " << items[i].price << "\n";
        }
        cout << "Enter item number to add to cart (or 0 to return): ";
        int itemChoice;
        cin >> itemChoice;
        if (itemChoice == 0) continue;
        if (itemChoice > 0 && itemChoice <= items.size()) {
            cart.addItem(items[itemChoice - 1]);
            cout << "\nItems in your cart:\n";
            cart.displayCart();
        } else {
            cout << "Invalid item choice!\n";
        }
    }
    double totalCost; 
    int deliveryTime;
    while (true) {
        cout << "\nCart Options:\n1. View Cart\n2. Remove Item\n3. Clear Cart\n4. Add More Items\n5. Proceed to Checkout\n(0 to exit): ";
        int cartOption;
        cin >> cartOption;
        switch (cartOption) {
            case 0:
                cout << "Exiting cart options. Thank you for shopping!\n";
                return 0;
            case 1:
                cart.displayCart();
                break;
            case 2:
                cart.displayCart();
                cout << "Enter item number to remove: ";
                int removeIndex;
                cin >> removeIndex;
                cart.removeItem(removeIndex - 1);
                break;
            case 3:
                cart.clearCart();
                break;
            case 4: {
                vector<item> items;
                displayCategories();
                int categoryChoice;
                cin >> categoryChoice;
                if (categoryChoice == 0) continue;
                switch (categoryChoice) {
                    case 1: items = {{"Bread", 50}, {"Pizza", 300}, {"Burger", 150}}; break;
                    case 2: items = {{"Laptop", 55000}, {"Smartphone", 15000}, {"Headphones", 2000}}; break;
                    case 3: items = {{"Chess", 500}, {"Monopoly", 700}, {"Video Game", 1500}}; break;
                    default: cout << "Invalid category!\n"; continue;
                }
                for (int i = 0; i < items.size(); i++) {
                    cout << i + 1 << ". " << items[i].name << " - Rs. " << items[i].price << "\n";
                }
                cout << "Enter item number to add to cart (or 0 to return): ";
                int itemChoice;
                cin >> itemChoice;
                if (itemChoice == 0) continue;
                if (itemChoice > 0 && itemChoice <= items.size()) {
                    cart.addItem(items[itemChoice - 1]);
                } else {
                    cout << "Invalid item choice!\n";
                }
                break;
            }
            case 5:
                totalCost = cart.getTotalCost(); 
                deliveryTime = estimateDeliveryTime(userAddress);
                cout << "\nYour total cost: Rs. " << totalCost << " + 18%(GST) \n";
                cout << "Estimated delivery time: " << deliveryTime << " minutes.\n";
                cout << "Proceeding to payment...\n";
                cout << "Thank you for your purchase!\n";
                return 0;
            default:
                cout << "Invalid option! Please try again.\n";
        }
    }
    return 0;
}
