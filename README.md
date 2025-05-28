# 🛒 ShoppingApp-C

A command-line shopping application written in the **C programming language**, designed to simulate a marketplace with user and admin roles. This project was developed for an academic final machine problem. Strictly terminal-based; no GUI.

## 👩‍💻 Developer
**Reina Althea Garcia**

---

## 📌 Features

### 👤 User Features
- **User Registration & Login**  
  Register with personal details and securely log in.
- **Sell Products**  
  Add new items with unique product IDs, descriptions, prices, and quantities.
- **View My Products**  
  See the list of items the user is selling.
- **Edit & Manage Products**  
  Update product information and stock levels.
- **Buy Products**  
  Browse products by seller, name, or category and add items to cart.
- **Cart & Checkout**  
  Edit cart contents and proceed to checkout with transaction summaries.

### 🔐 Admin Features
- **Secure Admin Login**  
  Password protected access to admin tools.
- **View All Users**  
  List all registered users sorted by user ID.
- **View All Sellers**  
  Display users who have posted products for sale.
- **View Sales Reports**  
  Generate reports on total sales, seller earnings, and shopaholics based on a date range.

### 🧾 File Handling
- Automatically updates `Users.txt`, `Items.txt`, and generates `transactions.dat` during runtime.
- Handles empty or non-existent transaction files.

---

## 🖥️ How to Run
```bash
gcc ShoppingApp15d.c -o main.exe
main
```
