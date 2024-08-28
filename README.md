# Financial Transaction Tracker

## Overview

This project implements a transaction history manager for tracking financial transactions. It includes functionality for reading transaction data from a file, storing it in a linked list, sorting transactions by date, updating values, and computing capital gains and losses.

## Files

- `main.cpp` - Contains the main function to demonstrate the usage of the `History` and `Transaction` classes.
- `History.hpp` - Header file for the `History` class, which manages the linked list of transactions.
- `History_Transactions_definitions.cpp` - Definitions for the `History` and `Transaction` classes, including methods for insertion, sorting, and computations.
- `Transaction.hpp` - Header file for the `Transaction` class, which represents individual transactions.
- `project4.cpp` - Implementation of file handling and parsing functions.
- `project4.hpp` - Header file for file handling and parsing functions used in `project4.cpp`.

## Classes

### `Transaction`

- **Constructor**: Initializes a transaction with the given details.
- **Destructor**: Cleans up the transaction object.
- **Member Functions**:
  - Getters for various transaction details (e.g., symbol, date, shares).
  - Setters for updating values (e.g., ACB, CGL).
  - Print function to display transaction details.
  - Overloaded `<` operator for comparison based on date and ID.

### `History`

- **Constructor**: Initializes an empty history.
- **Destructor**: Cleans up the linked list of transactions.
- **Member Functions**:
  - `insert(Transaction *p_new_trans)`: Inserts a transaction into the linked list.
  - `read_history()`: Reads transaction history from a file.
  - `print()`: Prints all transactions in the history.
  - `sort_by_date()`: Sorts transactions by date using insertion sort.
  - `update_acb_cgl()`: Updates ACB (Adjusted Cost Base) and CGL (Capital Gains/Losses).
  - `compute_cgl(unsigned int year)`: Computes total CGL for a given year.

## File Handling Functions (in `project4.cpp`)

- `open_file()`: Opens the transaction history file for reading.
- `close_file()`: Closes the file.
- `next_trans_entry()`: Parses the next transaction entry from the file.
- Getters for accessing parsed transaction details.

## Compilation and Usage

1. **Compile the Project**:

   ```bash
   g++ -o transaction_manager main.cpp History_Transactions_definitions.cpp project4.cpp
   ```

2. **Prepare the Input File**:

   Use the file named `transaction_history.txt` in the same directory 

3. **Run the Program**:

   ```bash
   ./transaction_manager
   ```

   This will read the transactions from `transaction_history.txt`, print the initial history, sort transactions by date, update ACB and CGL values, and compute CGL for the years 2018 and 2019.

## Notes

- Ensure that the file `transaction_history.txt` is present and correctly formatted for the program to work.
- The `Transaction` class uses a static member `assigned_trans_id` to uniquely identify each transaction.
