# Railway Management System in C

A complete console-based Railway Management System developed in **C language** using **structures, file handling, modular programming, and validation logic**.

This project simulates real-world railway enquiry and management operations with separate **Admin** and **User** functionalities.

---

# Features

## Admin Module

* Secure admin login authentication
* Add new train records
* Modify existing train information
* Manage:

  * Train routes
  * Intermediate stations
  * Arrival & departure timings
  * Running days

## User Module

* Search trains using train number
* Find trains between source and destination
* Date-based train availability checking
* View complete route and timing details

---

# File Handling

The project uses text files for persistent data storage.

### Files Used

* `admin_record.txt` → Stores admin credentials
* `train_record.txt` → Stores train information
* `temp.txt` → Temporary file used while updating records

---

# Validation & Error Handling

The system includes multiple validations and safety checks:

* Invalid login detection
* Invalid menu choice handling
* Date validation with leap year support
* Time validation with AM/PM checking
* Prevention of same source and destination input
* Train not found handling
* File opening error handling
* Prevention of overwriting occupied records
* Safe file updating using temporary files

---

# Concepts Used

* Structures
* Arrays & Strings
* File Handling
* Modular Programming
* Input Validation
* String Parsing
* Case-Insensitive Comparison
* Console-Based UI Design
* Date & Time Logic

---

# Technologies Used

* C Language
* GCC Compiler
* Standard C Libraries

---

# How to Run

## Compile the Program

```bash
gcc railway_management_system.c -o railway
```

## Run the Program

```bash
./railway
```

---

# Functionalities Included

* Admin Authentication
* Train Record Management
* Route & Station Management
* Search by Train Number
* Search by Source & Destination
* Running Day Validation
* Progress Bar Animation
* Interactive Console Interface
* Error Handling & Recovery

---
# Developed By

## Rahul Gupta

B.Tech 1st Year Student

---

# Project Overview

This project was created as a learning-based implementation of a real-world Railway Management System. It helped in understanding practical applications of C programming concepts including file handling, structures, validation logic, and modular program design.
