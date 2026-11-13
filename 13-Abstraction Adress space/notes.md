# Chapter 13: The Abstraction – Address Spaces

## 1. Multiprogramming

**Main Goal: Increase CPU Utilization.**

- Multiple processes can reside in RAM at the same time.
- When one process waits for an I/O operation, the OS can switch to another ready process.
- This reduces CPU idle time and improves CPU utilization.

**Example:**
- Process A
- Process B
- Process C

All three processes can be loaded into RAM simultaneously, while the CPU executes one process at a time (assuming a single-core CPU).

## 2. Time Sharing

**Main Goal: Interactivity and Fast Response Time for Users.**

- The CPU gives each process a small amount of execution time called a Time Slice (Time Quantum).
- The OS switches between processes quickly.
- Users can interact with multiple programs and receive fast responses.

**Key Difference:**

- Multiprogramming = CPU Utilization.
- Time Sharing = Interactivity + Response Time.

## 3. Address Space

**Definition:**

The address space is the running program's view of memory in the system.

Each process has its own virtual address space, which makes it appear as if it has private memory.

### Main Components of Address Space

**A. Code Segment**
- Contains the program's instructions (machine code).

**B. Heap**
- Stores dynamically allocated memory.
- Used for dynamic memory allocation.
- Examples: `malloc()` in C and `new` in C++.
- Typically grows toward higher addresses in the illustrated layout.

**C. Stack**
- Used for function calls.
- Contains local variables, function arguments, return addresses, and stack frames.
- Typically grows toward lower addresses in the illustrated layout.

## 4. Virtual Address vs Physical Address

**Virtual Address:**
- The address used and seen by a running program.

**Physical Address:**
- The actual location in physical memory (RAM).

The OS and hardware provide address translation to map virtual addresses to physical addresses.

**Important:** An address printed by a normal user-level program is a virtual address, not a physical address.

## 5. Memory Protection and Isolation

- Each process should be protected from other processes.
- A process must not access another process's memory without permission.
- The OS must also be protected from user processes.

**Isolation:** Preventing one process from affecting the memory of another process.

## 6. Goals of Virtual Memory

Virtual Memory has three main goals:

1. **Transparency:** Virtualization should be invisible to the running program.
2. **Efficiency:** Minimize time and space overhead.
3. **Protection:** Protect processes from one another and protect the OS from processes.

### Efficiency Includes:
- Time Efficiency: Minimize performance overhead.
- Space Efficiency: Minimize memory overhead.
- Hardware support such as TLBs helps improve efficiency.

---

## 7. Important Concepts to Remember

| Concept | Main Idea |
|---|---|
| Multiprogramming | Improve CPU Utilization |
| Time Sharing | Improve Interactivity and Response Time |
| Address Space | Program's View of Memory |
| Code | Program Instructions |
| Heap | Dynamic Memory Allocation |
| Stack | Function Calls and Local Variables |
| Virtual Address | Address Seen by the Program |
| Physical Address | Actual RAM Location |
| Isolation | Protect Processes from Each Other |
| Transparency | Hide Virtualization Details |
| Efficiency | Minimize Time and Space Overhead |
| Protection | Prevent Unauthorized Memory Access |

## 8. Chapter 13 – Key Takeaway

The Operating System provides each process with its own virtual address space, translates virtual addresses into physical addresses, and ensures memory protection, isolation, and efficient memory usage.