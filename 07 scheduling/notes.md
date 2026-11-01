# Scheduling: Introduction

## Mechanism vs Policy

**Mechanism**
→ How to create a context switch?  
→ How the OS can switch from one process to another.

**Policy**
→ Which process should I choose next?

**Scheduler**
→ Makes the decision about which process will run next.

Example:

```text
P1 → P2 → P3

or

P2 → P3 → P1

or

P2 → P1 → P3
```

---

## Workload Assumptions

Before creating a scheduling policy, we make some assumptions about the workload.

For example:

- All jobs arrive at the same time.
- Jobs may have known run times.
- Jobs use the CPU only.
- A job runs until completion.

These are just assumptions to make the problem easier.

In real systems, these assumptions are not always true.

---

## Scheduling Metrics

A **scheduling metric** is something we use to measure the performance of a scheduling policy.

### Turnaround Time

```text
Turnaround Time
→ from Arrival to Finish
```

Formula:

```text
Turnaround Time = Completion Time - Arrival Time
```

### Response Time

```text
Response Time
→ from Arrival to First Run
```

Formula:

```text
Response Time = First Run - Arrival Time
```

---

# FIFO — First In, First Out

FIFO means:

```text
First job arrives
      ↓
First job runs
```

Example:

```text
P1 → P2 → P3
```

FIFO is very simple and easy to implement.

### Problem: Convoy Effect

If a long job comes first:

```text
P1 = 100
P2 = 10
P3 = 10
```

FIFO:

```text
P1 → P2 → P3
```

The short jobs have to wait for the long job.

```text
Long job first
      ↓
Short jobs wait
      ↓
Convoy Effect
      ↓
High Average Turnaround Time
```

FIFO is more suitable when jobs have similar lengths or when simplicity is more important.

---

# SJF — Shortest Job First

SJF:

```text
Choose the shortest job first
```

Example:

```text
P1 = 100
P2 = 10
P3 = 10
```

SJF:

```text
P2 → P3 → P1
```

This can greatly reduce **Average Turnaround Time**.

Under the assumptions we made, SJF gives the optimal average turnaround time.

But it has a problem when new jobs arrive while another job is already running.

---

# Preemptive vs Non-preemptive

## Non-preemptive

Once a process starts running:

```text
Process starts
      ↓
Process continues
      ↓
Process finishes
```

The scheduler does **not** stop it in the middle.

---

## Preemptive

The OS can stop a running process and give the CPU to another process.

```text
A running
   ↓
B arrives
   ↓
Stop A
   ↓
Run B
   ↓
A continues later
```

So:

```text
Non-preemptive → cannot forcefully stop the running job

Preemptive → can stop the running job
```

---

# STCF — Shortest Time-to-Completion First

STCF is the preemptive version of SJF.

It chooses the process with the **shortest remaining time**.

Example:

```text
A remaining = 90
B = 10
C = 10
```

STCF chooses:

```text
B or C
```

because they have less time remaining.

If a new short process arrives while a long process is running, STCF can preempt the long process.

---

# Round Robin

Round Robin gives each process a small amount of CPU time.

This amount is called:

```text
Time Slice
or
Time Quantum
```

Example:

```text
A → B → C → A → B → C
```

This gives good **Response Time**.

---

## Small Time Slice

```text
Small Time Slice
       ↓
Better Response Time
       ↓
More Context Switches
       ↓
More Overhead
```

## Large Time Slice

```text
Large Time Slice
       ↓
Fewer Context Switches
       ↓
Less Overhead
       ↓
Worse Response Time
```

This is a **trade-off**.

---

# Trade-off

We cannot optimize everything at the same time.

For example:

```text
Response Time = perfect
Turnaround Time = perfect
Context Switch Overhead = zero
```

We cannot usually get all of them at the same time.

```text
Improve X
   ↓
May hurt Y
```

---

# I/O and Overlap

A process does not always use the CPU.

It can do:

```text
CPU → I/O → CPU → I/O
```

When a process starts I/O:

```text
Process
   ↓
Blocked
   ↓
CPU becomes available
```

The OS should not leave the CPU idle.

It can run another process:

```text
CPU:
A A A | B B B B | A A A | B B
      ↑
      A is doing I/O
```

This is called **overlap**.

The CPU works on B while A is waiting for I/O.

Result:

```text
Better CPU Utilization
```

---

# Important Idea

Different scheduling policies optimize different things.

```text
SJF / STCF
     ↓
Good Turnaround Time

Round Robin
     ↓
Good Response Time
```

There is no perfect scheduler for everything.

---

# No More Oracle

SJF/STCF assumes that the OS knows how long a job will run.

But in reality:

```text
OS does NOT know the future
```

So the scheduler can use the process's **past behavior** to predict its future behavior.

This leads to:

```text
Past behavior
      ↓
Prediction
      ↓
Better scheduling
      ↓
MLFQ
```