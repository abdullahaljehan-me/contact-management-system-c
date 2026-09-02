# ☎️ Contact Management System (C)

A command-line contact manager written in C. Add, delete, list, and search contacts, with everything saved to a local text file so your data survives between runs.

## Features

- Add a contact (name, phone, email) — supports full names with spaces
- Delete a contact by exact name match
- List all saved contacts with a running total
- Search by name, phone, or email substring
- Loads from `contacts.txt` on startup, saves on every change and on exit
- Input handling that won't overflow buffers or choke on `scanf` leftovers

## Build and run

```bash
gcc contact_management.c -o contact_manager
./contact_manager
```

## Project structure

```
contact-management-system-c/
├── contact_management.c
├── README.md
└── .gitignore
```

## Notes

- Storage is a flat text file, three lines per contact (name/phone/email). It works, but it's not built for large contact lists or concurrent access — a proper database is the next step if this grows.
- Deleting requires an exact name match; there's no fuzzy matching or ID system yet.
- Field lengths are capped (name/email 50 chars, phone 20) and input longer than that gets truncated, not rejected.
