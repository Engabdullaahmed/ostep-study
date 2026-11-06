# Chapter 8 — Scheduling: The Multi-Level Feedback Queue (MLFQ)

## 1. What is MLFQ?

MLFQ = Multi-Level Feedback Queue.

- Multi-Level → We have more than one queue.
- Feedback → OS learns from process behavior while it runs.
- Queue → Each queue has a different priority.

**Main Idea:**

→ Observe process behavior.  
→ Use past behavior to predict future behavior.  
→ Change process priority based on its behavior.

Predictions are not always correct, so the OS keeps observing processes.

---

## 2. The Problem: Why Do We Need MLFQ?

In the previous chapter, we learned about:

**SJF / STCF**

→ Need to know the job length or remaining time.  
→ But the OS doesn't know the future.  
→ It cannot know how long a process will run in advance.

**Round Robin**

→ Gives good Response Time.  
→ But may have poor Turnaround Time.

**Our Goals:**

- Minimize Turnaround Time.
- Minimize Response Time.
- We don't know the job length in advance.

**The Solution: MLFQ**

→ Observe how processes behave.  
→ Adjust their priorities.  
→ Try to achieve good Response Time and Turnaround Time.

---

## 3. Types of Processes

### Interactive Process

Example: A program that interacts with the user.

```text
CPU → I/O → CPU → I/O → CPU
```

- Uses short CPU bursts.
- Frequently performs I/O.
- Needs a fast response.

### CPU-intensive Process

Example: A program that performs heavy calculations.

```text
CPU → CPU → CPU → CPU
```

- Uses CPU for long periods.
- Does not perform I/O frequently.
- Needs more CPU time.

**MLFQ tries to distinguish between these two types by observing their behavior.**

---

## 4. MLFQ Queues

MLFQ contains multiple priority queues.

Example:

```text
Q2 → Highest Priority
Q1 → Medium Priority
Q0 → Lowest Priority
```

- Higher queue → Higher priority.
- Lower queue → Lower priority.

The scheduler always chooses a process from the highest-priority queue that has a READY process.

If multiple processes have the same priority, Round Robin is used.

---

## 5. Basic MLFQ Rules

### Rule 1: Higher Priority

If Priority(A) > Priority(B):

→ A runs.  
→ B waits.

```text
A = High Priority
B = Low Priority

Result:
A runs → B waits
```

### Rule 2: Same Priority

If Priority(A) = Priority(B):

→ A and B run using Round Robin.

```text
A → B → A → B → A → B
```

Each process gets a time slice.

### Rule 3: New Jobs

When a new job enters the system:

→ It is placed at the highest priority queue.

Example:

```text
New Process
     ↓
    Q2
```

Why?

→ We don't know if the process is short or long.  
→ We give it a chance to run with high priority.

---

## 6. How Does MLFQ Change Priority?

### Rule 4a: Uses the Full Time Slice

If a process uses its entire time slice:

→ Its priority is reduced.  
→ It moves down one queue.

Example:

```text
Process A starts in Q2

Uses full time slice
        ↓
Moves to Q1

Uses full time slice again
        ↓
Moves to Q0
```

This usually indicates a CPU-intensive process.

### Rule 4b: Gives Up CPU Early

In the initial rules:

If a process gives up the CPU before its time slice ends:

→ It keeps the same priority.

Example:

```text
A in Q2
   ↓
Uses CPU for 2ms
   ↓
Requests I/O
   ↓
Becomes Blocked
   ↓
Returns to Q2
```

Why?

→ Interactive processes frequently perform I/O.  
→ We don't want to reduce their priority just because they are waiting for I/O.

**Important:**

While A is waiting for I/O:

→ A becomes Blocked.  
→ CPU becomes available.  
→ Another process can run.

This allows CPU and I/O operations to overlap.

---

## 7. MLFQ Examples

### Example 1: A Single Long-Running Job

A new process enters the system.

```text
New Job
   ↓
Q2
   ↓
Uses full time slice
   ↓
Q1
   ↓
Uses full time slice again
   ↓
Q0
```

- The process starts at the highest priority.
- It keeps using the full time slice.
- Its priority decreases.
- Eventually, it reaches the lowest queue.

**Conclusion:**

→ MLFQ learns that this process is probably CPU-intensive.

### Example 2: A Short Job Arrives

We have two processes:

- A → Long-running process.
- B → Short-running process.

A is already running at low priority in Q0.

At T = 100, B arrives.

```text
B arrives
    ↓
Starts in Q2
    ↓
Higher priority than A
    ↓
B runs before A
```

If B is short:

→ It finishes before moving down through all queues.

If B is long:

→ It keeps using its time slices.  
→ Its priority gradually decreases.

**Conclusion:**

→ MLFQ approximates SJF without knowing job length in advance.

### Example 3: What About I/O?

We have:

- A → Long-running CPU-intensive process.
- B → Interactive process.

B needs only 1ms of CPU before performing I/O.

```text
B:
CPU (1ms)
   ↓
I/O
   ↓
CPU (1ms)
   ↓
I/O
   ↓
Repeat
```

According to the initial Rule 4b:

→ B gives up CPU before its time slice ends.  
→ B keeps the same priority.  
→ While B waits for I/O, A can use the CPU.  
→ When B returns, it can run again at its previous priority.

**Conclusion:**

→ Interactive jobs keep high priority.  
→ CPU-intensive jobs use the CPU while interactive jobs wait for I/O.

---

## 8. Problems With the Initial MLFQ

The initial rules have some problems.

### Problem 1: Starvation

Starvation means a process may wait for a very long time without getting CPU time.

Example:

```text
Q2: B → C → D → B → C → D
Q1:
Q0: A (waiting...)
```

If too many high-priority jobs keep arriving:

→ Low-priority processes may never get CPU time.

### Problem 2: Gaming the Scheduler

A process may try to trick the scheduler to keep its high priority.

Example:

```text
Time Slice = 10ms

Run for 9ms
     ↓
Give up CPU
     ↓
Run for 9ms
     ↓
Give up CPU
     ↓
Repeat
```

According to the initial Rule 4b:

→ The process keeps the same priority.  
→ It can use a lot of CPU without moving down.

This is called Gaming the Scheduler.

### Problem 3: Changing Behavior

A process may change its behavior over time.

Example:

```text
At first:
CPU → I/O → CPU → I/O
(Interactive)

Later:
CPU → CPU → CPU → CPU
(CPU-intensive)
```

The scheduler needs to handle this change.

---

## 9. Attempt #2: Priority Boost

To reduce starvation, MLFQ introduces Rule 5.

### Rule 5

After some time period S:

→ Move all jobs in the system to the highest-priority queue.

Example:

Before Boost:

```text
Q2: B, C
Q1: D
Q0: A
```

After Boost:

```text
Q2: A, B, C, D
Q1:
Q0:
```

**Benefits:**

- Reduce starvation.
- Give low-priority processes another chance.
- Handle changes in process behavior.
- Allow CPU-intensive processes to make progress.

**Important:**

Priority Boost does not mean one process runs alone.

→ All processes return to the highest queue.  
→ Processes with the same priority share CPU using Round Robin.

### Choosing S

The boost interval must be selected carefully.

- If S is too large → Starvation may happen for a long time.
- If S is too small → Processes keep returning to high priority too frequently.

---

## 10. Attempt #3: Better Accounting

We still have the Gaming problem.

The solution:

→ Track the total CPU time used by each process at each priority level.

Do not reset CPU usage just because the process gives up the CPU for I/O.

### Example

```text
Time Slice = 10ms

Run 3ms → I/O
Run 2ms → I/O
Run 5ms → I/O
```

Total CPU usage:

```text
3 + 2 + 5 = 10ms
```

The process has consumed its full time allocation.

→ Its priority is reduced.

### Final Rule 4

Once a job uses up its time allocation at a given priority level:

→ Its priority is reduced.  
→ It moves down one queue.

This happens regardless of how many times it gave up the CPU.

**Main Idea:**

→ Track cumulative CPU usage.  
→ I/O does not reset the CPU time counter.  
→ A process cannot avoid moving down just by giving up CPU early.

---

## 11. Tuning MLFQ and Other Issues

There are important parameters when designing an MLFQ scheduler.

### 1. Number of Queues

→ How many priority queues should we have?

Example:

```text
Q2
Q1
Q0
```

The number can differ between operating systems.

### 2. Time Slice for Each Queue

Different queues may have different time slices.

Example:

| Queue | Time Slice |
|---|---:|
| Q2 | 10ms |
| Q1 | 20ms |
| Q0 | 40ms |

**Why?**

High Priority:

→ Short time slice.  
→ Better Response Time for interactive jobs.

Low Priority:

→ Long time slice.  
→ Fewer context switches.  
→ Less relative context-switch overhead for CPU-intensive jobs.

### 3. Priority Boost Interval

→ How often should the scheduler boost all processes?

A suitable interval helps prevent starvation without making boosts too frequent.

### Avoid Voo-doo Constants (Ousterhout's Law)

→ Avoid choosing arbitrary values without a good reason.

Examples:

- Number of queues.
- Time slice lengths.
- Priority boost interval.

These values should be chosen carefully and based on the system's requirements and measurements.

---

## 12. Real Operating System Implementations

Different operating systems may implement MLFQ in different ways.

### Solaris

- Uses scheduling tables.
- The administrator can configure priorities.
- Can configure time slices.
- Can configure how priorities change.
- Can configure priority boosts.

### BSD Scheduler

- Can calculate process priority using CPU usage.
- CPU usage affects the priority.
- Some implementations reduce the effect of old CPU usage over time.

### Other Features

**Reserved Priorities**

→ Some important system processes can have reserved high priorities.

**User Priority Control**

→ Users may be allowed to increase or decrease the priority of some processes, depending on permissions.

**Adjustable Priorities**

→ The operating system may change priorities according to system requirements.

---

## 13. Use Advice Where Possible

The OS does not always know what is best for every process.

Users or administrators can provide hints to the OS.

Examples:

- Scheduler hints.
- Memory management hints.
- File system hints.

**Important:**

Advice ≠ Decision.

→ Users provide hints.  
→ The OS can consider these hints.  
→ But it does not have to follow them.

The OS still makes the final decision.

---

## 14. Final MLFQ Rules — Quick Review

| Rule | Description |
|---|---|
| Rule 1 | Higher priority process runs first. |
| Rule 2 | Same priority → Round Robin. |
| Rule 3 | New jobs enter at the highest priority. |
| Rule 4 | When CPU allocation is consumed, move down one queue. |
| Rule 5 | After period S, boost all jobs to the highest queue. |

---

## 15. Final Summary

**MLFQ = Multi-Level Feedback Queue**

Problem:

- SJF/STCF need to know job length.
- OS does not know the future.
- Round Robin gives good Response Time but may hurt Turnaround Time.

Solution:

→ Use multiple priority queues.  
→ Observe process behavior.  
→ Adjust priority based on history.

Main Behavior:

```text
New Process
     ↓
Highest Priority
     ↓
Observe Behavior
     |
     |-- Uses full CPU allocation
     |          ↓
     |     Lower Priority
     |
     |-- Gives up CPU for I/O
                ↓
          Keeps Priority
     
Priority Boost after S
     ↓
All jobs return to highest queue
```

Better Accounting:

→ Track total CPU time at each priority level.  
→ I/O does not reset CPU usage.  
→ Prevent Gaming the Scheduler.

**Main Idea:**

History is the guide.

→ Observe how processes behave over time.  
→ Use their past behavior to predict their future behavior.  
→ Adjust priorities to make better scheduling decisions.

**MLFQ Goals:**

- Good Response Time for interactive jobs.
- Good Turnaround Time for short jobs.
- Fair CPU access for long-running jobs.
- Avoid starvation and scheduler gaming.