# ☎️ Contact Management System (C)

A command-line contact manager written in C. Add, delete, list, search, and sort contacts, with everything saved to a local text file so your data survives between runs.

## Features

- Add a contact (name, phone, email) — supports full names with spaces
- Delete a contact by exact name match
- List all saved contacts with a running total
- Search by name, phone, or email substring
- **Sort contacts alphabetically by name (case-insensitive)**
- Loads from `contacts.txt` on startup, saves on every change and on exit
- Input handling that won't overflow buffers or choke on `scanf` leftovers

## Prerequisites

To compile and run this game, you need:
- A C compiler (like `gcc`, `clang`, or `MinGW`).
- A terminal or command prompt.

## Build and run

```bash
gcc contact_management.c -o contact_manager
./contact_manager
```
---

<div align="center">

<sub>© 2026 abdullahaljehan-me · Licensed under MIT</sub>

</div>
