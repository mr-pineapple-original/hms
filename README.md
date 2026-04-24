# MediCore Hospital Management System

A comprehensive Hospital Management System built with C++ and Qt6/QML. The system manages patients, doctors, appointments, prescriptions, billing, and administrative functions with persistent data storage.

## Features

- **Patient Portal**: Book/cancel appointments, view medical records, pay bills, top up balance
- **Doctor Portal**: View today's appointments, mark completions, write prescriptions, view patient history
- **Admin Panel**: Manage doctors, view all records, unpaid bills, discharge patients, security logs, daily reports
- **Data Persistence**: All data stored in CSV files and survives program restarts
- **Secure Authentication**: Role-based login with failed attempt tracking

## GitHub Repository

**[https://github.com/yourusername/hospital-management-system](https://github.com/mr-pineapple-original/hms)**

## Prerequisites

- Qt6 Development Libraries
- CMake 3.16+
- C++17 Compatible Compiler

## Installation

### Linux

#### Fedora (dnf)
```bash
sudo dnf install qt6-qtbase-devel qt6-qtdeclarative-devel cmake gcc-c++
```

#### Debian (apt)
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-declarative-dev cmake g++
```

#### Arch (pacman)
```bash
sudo pacman -S qt6-base qt6-declarative cmake base-devel
```


#### Windows

> [!TIP]
>
> Don't use windows, linux is better - not an opinion, it is a fact. ~


##### Prerequisites

1. **Install Qt6**:
   - Download Qt Online Installer from [qt.io/download](https://www.qt.io/download)
   - Run installer and select:
     - Qt 6.x (latest stable)
     - Qt 6.x → Qt Declarative (QML module)
     - Developer and Designer Tools → CMake
     - Developer and Designer Tools → MinGW 11.x (or MSVC 2019/2022)

2. **Alternative - Install separately**:
   - **CMake**: Download from [cmake.org/download](https://cmake.org/download/)
     - Select "Add CMake to system PATH" during installation
   - **MinGW**: Download from [mingw-w64.org](http://mingw-w64.org)
   - **Qt6**: Download maintenance tool or use Qt Online Installer
