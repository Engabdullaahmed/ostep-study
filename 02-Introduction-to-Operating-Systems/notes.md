# Chapter 2 — Introduction to Operating Systems

### 1. CPU Virtualization

At this chapter we talk about **virtualization**, that how we have really one physical CPU and deal with many tasks and programs by making them appear to have virtual CPUs.

The OS uses the CPU and switches between many processes very quickly, so they appear to run at the same time.

**Main question:**

> How can one CPU run many programs at once?

The OS virtualizes the CPU by rapidly switching the CPU among multiple processes, making them appear to run simultaneously.

There are two important concepts:

- **Policy:** decides what the CPU should do and which process should run.
- **Mechanism:** how the OS actually implements that decision.

---

### 2. Virtual Memory

There is also the concept of **virtual memory**.

Each process has its own **virtual address space**, so different processes can use the same virtual address without necessarily accessing the same physical memory.

For example, if I have more than one program and they use the same memory address, the OS virtualizes the memory so each process can have its own memory space.

Also, every process has a **PID (Process ID)**, which is a unique number used to identify the process.

---

### 3. Concurrency

**Concurrency** deals with more than one thing happening at the same time or overlapping in execution.

Multiple threads can access shared data concurrently, which can lead to incorrect results if access is not properly synchronized.

A **race condition** occurs when multiple threads access shared data concurrently and the result depends on the timing or order of execution.

Example:

```text
Thread 1 → counter++
Thread 2 → counter++
```

Both are accessing the same `counter`, so without synchronization the final result may be incorrect.

---

### 4. Persistence

**Persistence** means that data can be stored and remain available even after the program stops or the system loses power.

This is done using **persistent storage** such as:

- HDD
- SSD

The **file system** manages this storage and provides a simple way for applications to create, read, and write files.

> The file system provides a simple interface for applications while managing the complex details of storing data reliably on persistent storage.

---

### 5. Main Design Goals

The main design goal is **abstraction**, which makes dealing with the computer easier.

Instead of dealing directly with complicated hardware, the OS provides simple interfaces.

Other important goals:

- **Performance:** the OS should be fast and efficient.
- **Protection:** the OS should protect programs from each other and protect the OS itself.
- **Reliability:** the OS should work correctly for a long time without crashing.
- **Trade-offs:** sometimes we need to make a trade-off, for example more protection or more features can cause more overhead.

---

### 6. User Mode and Kernel Mode

**User Mode:**  
Normal programs run here with limited permissions.

**Kernel Mode:**  
The OS runs here and has access to the hardware and system resources.

When a program needs something that it cannot do directly, it uses a **system call** to request the OS to do it.

```text
User Mode
   ↓
System Call
   ↓
Kernel Mode
   ↓
OS handles the request
   ↓
User Mode
```

### Main idea of the chapter

```text
CPU        → Virtualization
Memory     → Virtualization
Concurrency → Multiple things running together
Storage    → Persistence
OS Goals   → Abstraction, Performance, Protection, Reliability
```
