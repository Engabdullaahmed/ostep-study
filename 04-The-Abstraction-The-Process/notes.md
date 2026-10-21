# The Abstraction: A Process

## Process

A process is a running program.

The program itself is on the disk, but when the OS runs it, it becomes a process.

---

## OS Virtualization

The OS gives each process a small amount of CPU time, then switches to another process.

This makes it look like many processes are running at the same time.

### Time Sharing

Each process shares some time from the CPU.

```text
P1 → P2 → P3 → P1 → ...
```

The OS switches between processes to share the CPU.

### Space Sharing

The same idea as time sharing, but sharing a resource by space.

For example, the disk is divided into different parts/blocks used by different files.

```text
Time Sharing → sharing over time
Space Sharing → sharing over space
```

---

## Context Switch

When the OS switches from one process to another, it uses a **context switch**.

The OS saves the current process state and loads the state of another process.

---

## Mechanism and Policy

The OS needs mechanisms to implement virtualization.

**Mechanism = How?**

How does the OS do something?

**Policy = Which one / What?**

What decision should the OS make?

For example:

- Mechanism → How to switch between processes.
- Policy → Which process should run next.

Separating them makes it easier to change the policy without changing the mechanism.

---

## Process API

The OS provides an API to work with processes.

### Create
Create a new process.

### Destroy
Destroy/kill a process.

### Wait
Wait for a process to finish.

### Miscellaneous Control
Other controls, such as stopping a process for a while and then continuing it.

### Status
Get information about a process, such as its state.

---

## Process Creation

Before a program can run, the OS must load the necessary parts of the program from disk into memory.

### Eager Loading

Load everything before execution.

### Lazy Loading

Load only what is needed during execution.

---

## Process States

There are three main states:

### Running

The process is currently running on the CPU.

### Ready

The process is ready to run but waiting for the CPU.

Usually, it waits in the ready queue.

### Blocked

The process is waiting for an event or an I/O operation.

Example:

```text
Running
   ↓
I/O request
   ↓
Blocked
   ↓
I/O done
   ↓
Ready
```

---

## Zombie State

A zombie process is a process that has finished running, but its parent process has not collected its exit status yet.

---

## Process Control Block (PCB)

The OS keeps information about each process.

It can include:

- Process state
- PID
- Memory information
- CPU context
- Parent process
- Open files

The PCB helps the OS manage and control processes.

---

## Context

The context contains the CPU register values needed to stop and resume a process.

When the OS switches between processes:

```text
Process 1
   ↓
Save context
   ↓
Process 2
   ↓
Restore Process 1 context
   ↓
Process 1 continues
```