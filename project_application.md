# Lab 11 - Project Application

## E1 - Original collection and borrowed pointers
- **Storage:** The `orders` array permanently stores the actual `OrderPreview` records in their initial operational sequence.
- **Borrowed Pointers:** The `view` array stores memory addresses (`OrderPreview*`) pointing directly to specific elements inside the `orders` array. This allows us to build temporary reports without duplicating objects or violating data ownership.

## E2 - Implemented view and test
- **Dummy Cases:** Tested with 4 orders: Order 101 (Active DELIVERY), Order 102 (Active DINE_IN), Order 103 (Active DELIVERY), and Order 104 (Completed PICKUP).
- **Selected IDs:** The filtered view successfully captured only IDs `101` and `103`.
- **Preservation Check:** Printing the `orders` array before and after building the view verified that no data fields or storage positions were altered.

## E3 - Sorting criterion and next integration step
- **Comparison Rules:** 
  1. Building name in alphabetical order.
  2. Priority in descending order (higher priority values first) if buildings match.
  3. Order ID in ascending order for exact ties.
- **Next Integration:** Connect this pointer-array view logic with `mergeSortView` to sort active delivery reports dynamically for the cafeteria project.

## E4 - Lab evidence
- **Source file:** delivery_view_practice.cpp
- **Test output:** delivery_view_output.txt
- **Explanation:** This technique separates temporary display requirements from operational queues (such as FIFO preparation), keeping core backend order management intact.