# Chapter 6 — Limited Direct Execution

## Main Idea

How can OS:

→ make virtualization **fast**  
→ and still keep **control** over the CPU?

---

## Direct Execution

→ Program runs directly on CPU  
→ Very fast

Problem:

→ Program can do anything  
→ OS loses control

---

## Limited Direct Execution

→ Program runs directly on CPU  
→ Fast like Direct Execution  
→ But OS puts **limits** on what program can do  
→ OS still keeps control

### Main goals

→ Performance  
→ Control

---

# Problem #1 → Restricted Operations

If program can access everything:

→ Bug can damage system  
→ Malicious program can damage system  
→ Program can access hardware / memory directly

### Solution

Use:

```text
User Mode
Kernel Mode
```

### User Mode

→ Normal program runs here  
→ Restricted operations  
→ Cannot directly access important hardware/resources

### Kernel Mode

→ OS runs here  
→ Full access to system resources  
→ Can perform privileged operations

---

# System Call

If a program needs something from OS:

```text
User Program
     ↓
System Call
     ↓
Trap
     ↓
Kernel Mode
     ↓
OS handles request
     ↓
Return-from-Trap
     ↓
User Mode
```

Examples:

→ `open()`  
→ `read()`  
→ `write()`  
→ `fork()`  
→ `exec()`  
→ `exit()`

`open()` looks like a normal function call to the programmer, but internally it causes a **system call** to the OS.

---

# Trap

Trap is the mechanism that transfers control:

```text
User Mode → Kernel Mode
```

It allows the OS to handle:

→ System calls  
→ Some illegal operations  
→ Other exceptional events

The hardware saves some information about the current program so it can return later.

---

# Return-from-Trap

After the OS finishes:

```text
Kernel Mode
     ↓
Return-from-Trap
     ↓
User Mode
     ↓
Continue Program
```

So:

→ Trap = enter OS  
→ Return-from-Trap = leave OS and continue program

---

# Trap Table

The OS creates the **Trap Table** during boot.

→ Hardware needs to know where the handler for each trap is  
→ Trap Table tells hardware where the OS handlers are

Example:

```text
System Call → system-call handler
Timer       → timer-interrupt handler
Exception   → exception handler
```

---

# Full Flow

```text
OS Boot
   ↓
Initialize Trap Table
   ↓
Create Process
   ↓
Load Program
   ↓
User Mode
   ↓
Run main()
   ↓
System Call
   ↓
Trap
   ↓
Kernel Mode
   ↓
Handle System Call
   ↓
Return-from-Trap
   ↓
User Mode
   ↓
Continue Program
   ↓
exit()
   ↓
OS cleans Process
```

---

# Problem #2 → Switching Between Processes

Suppose we have:

```text
Process A
Process B
```

We want:

```text
A
B
A
B
A
B
```

How does OS get control of the CPU and switch between them?

---

## Cooperative Approach

→ Process gives CPU back voluntarily  
→ Usually by making a system call

Example:

```text
Process A
   ↓
System Call
   ↓
OS gets CPU
   ↓
OS can run Process B
```

### Problem

What if Process A does:

```cpp
while (true)
{
    // do something forever
}
```

and never makes a system call?

→ A keeps running  
→ OS does not get control  
→ B may never run

So cooperative approach is not enough.

---

# Non-Cooperative Approach

### Solution → Timer Interrupt

OS uses a hardware timer.

```text
Process A running
       ↓
Timer Interrupt
       ↓
CPU enters Kernel
       ↓
OS gets control
       ↓
Scheduler decides
       ↓
Switch to Process B
```

Important:

→ Process does NOT need to cooperate  
→ Even if A runs forever  
→ Timer Interrupt can give OS control

So:

> **Timer Interrupt allows the OS to regain control of the CPU even when a process does not cooperate.**

---

# If A and B are running

The OS can do:

```text
A running
   ↓
Timer Interrupt
   ↓
OS
   ↓
Context Switch
   ↓
B running
   ↓
Timer Interrupt
   ↓
OS
   ↓
Context Switch
   ↓
A running
```

---

# If Process A finishes

A process doesn't have to call a system call just to let B run.

If A finishes:

```text
A
↓
exit()
↓
OS cleans A
↓
Scheduler
↓
Choose B
↓
B runs
```

So `exit()` tells the OS:

→ This process is finished  
→ Clean its resources  
→ Choose another process

---

# Context

**Context is NOT the status of the process.**

Context = information needed to continue running the process.

Examples:

→ Registers  
→ Program Counter (PC)  
→ Stack Pointer  
→ Other CPU state

Example:

```text
Process A
   ↓
CPU registers
PC
Stack Pointer
...
```

The OS saves this information.

---

# Context Switch

Context Switch means:

→ Save context of current process  
→ Restore context of another process  
→ Continue running the new process

Example:

```text
Process A running
      ↓
Timer Interrupt
      ↓
Save A context
      ↓
Load B context
      ↓
Process B running
```

So:

```text
Context Switch
= Save A + Restore B
```

---

# Scheduler

After the OS gets control of CPU:

→ Scheduler decides which process should run next.

Example:

```text
A running
   ↓
Timer Interrupt
   ↓
OS
   ↓
Scheduler
   ↓
Choose B
   ↓
Context Switch
   ↓
B running
```

---

# Concurrency

Problem:

What happens if another interrupt happens while OS is already handling an interrupt?

Example:

```text
Interrupt A
    ↓
OS handling A
    ↓
Interrupt B happens
    ↓
OS is already handling A
```

This creates **concurrency problems**.

The OS has to carefully control what happens when multiple events can occur at the same time.

→ This is the topic of the next part of OSTEP.

---