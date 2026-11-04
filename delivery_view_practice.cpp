#include <iostream>
#include <string>

using namespace std;

struct OrderPreview {
    int orderId;
    string orderType;
    string status;
    string building;
    int priority;
};

void displayOrders(const OrderPreview orders[], int count) {
    for (int i = 0; i < count; ++i) {
        cout << "Order ID: " << orders[i].orderId
             << " | Type: " << orders[i].orderType
             << " | Status: " << orders[i].status
             << " | Building: " << orders[i].building
             << " | Priority: " << orders[i].priority << endl;
    }
}

void displayview(OrderPreview* view[], int count) {
    for (int i = 0; i < count; ++i) {
        cout << "Order ID: " << view[i]->orderId
             << " | Type: " << view[i]->orderType
             << " | Status: " << view[i]->status
             << " | Building: " << view[i]->building
             << " | Priority: " << view[i]->priority << endl;
    }
}

int main() {

    const int ORDER_COUNT = 4;

    OrderPreview orders[ORDER_COUNT] = {
        {101, "Delivery", "Pending", "Building A", 2},
        {102, "Pickup", "Completed", "Building B", 1},
        {103, "Delivery", "In Progress", "Building C", 3},
        {104, "Pickup", "Pending", "Building A", 2},
    };

    OrderPreview* view[ORDER_COUNT];
    int viewCount = 0;

    for (int i = 0; i < ORDER_COUNT; ++i) 
    {
        if (orders[i].orderType == "Delivery" && 
            (orders[i].status == "Pending" || orders[i].status == "In Progress"))
        {
            view[viewCount] = &orders[i];
            viewCount++;
        }
        
    }

    cout << boolalpha;
    cout << "Original arrival order:" << endl;
    displayOrders(orders, ORDER_COUNT);

    cout << "\nView of orders:" << endl;
    displayview(view, viewCount);

    return 0;
}