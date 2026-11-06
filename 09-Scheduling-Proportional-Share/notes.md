# Chapter 9 - Scheduling: Proportional Share

## 9.1 Basic Concept: Tickets Represent Your Share

- Tickets represent a process's share of CPU time.
- More tickets → Higher chance of getting CPU.
- Fewer tickets → Lower chance of getting CPU.
- Scheduler picks a random winning ticket.
- The process that owns the winning ticket gets the CPU.

**Example:**

| Process | Tickets | CPU Share |
|---|---:|---:|
| A | 75 | 75% |
| B | 25 | 25% |

**Important:**
- Lottery Scheduling is probabilistic, not deterministic.
- CPU shares are expected over time, not guaranteed in every short interval.

## 9.2 Ticket Mechanisms

Lottery Scheduling has 3 mechanisms:

### 1. Ticket Currency
- Users distribute tickets among their own jobs.
- System converts local tickets into global tickets.
- Each user keeps their allocated global share.

### 2. Ticket Transfer
- A process temporarily gives its tickets to another process.
- Useful in client/server systems.
- Server returns the tickets after finishing the request.

### 3. Ticket Inflation
- A process temporarily increases its tickets.
- More tickets → Higher chance of getting CPU.
- Useful when processes cooperate.
- Can be abused in competitive environments.

## 9.3 Implementation

Lottery Scheduling implementation is simple.

**Steps:**
1. Calculate total number of tickets.
2. Generate a random winning ticket.
3. Start traversing the process list.
4. Add each process's tickets to a counter.
5. Stop when `counter > winner`.
6. The current process is the winner.

**Remember:**

One lottery → One winning process → Stop searching → Run that process.

## 9.4 Lottery Fairness

- Lottery Scheduling is random, so jobs may finish at different times.
- The book uses Unfairness (U) to measure the difference.

**Formula:**

`U = First Job Finish Time / Second Job Finish Time`

**Example:**
- Job A finishes at time 10.
- Job B finishes at time 20.
- U = 10 / 20 = 0.5

**Main Idea:**
- U close to 1 → Better fairness.
- Short jobs may have high unfairness.
- Longer jobs give the scheduler more lottery rounds.
- Over time, CPU share approaches the expected proportion.

## 9.5 How To Assign Tickets?

- The system needs a way to decide how many tickets each job should get.
- Users can distribute their tickets among their own jobs.
- There is no general solution for assigning tickets.
- Ticket assignment is still an open problem.

## 9.6 Why Not Deterministic?

Lottery Scheduling uses randomness, so it may not give exact CPU shares over short intervals.

### Stride Scheduling

- A deterministic alternative to Lottery Scheduling.
- Each process has a Stride and Pass value.

**Formula:**

`Stride = K / Tickets`

- More tickets → Smaller stride.
- Fewer tickets → Larger stride.

**Scheduling Steps:**
1. Select the process with the lowest Pass.
2. Run that process.
3. Update its Pass:

`Pass += Stride`

**Example:**

| Process | Tickets | Stride |
|---|---:|---:|
| A | 100 | 100 |
| B | 50 | 200 |
| C | 250 | 40 |

Execution order:

`A → B → C → C → C → A → C → C → A`

- More tickets → Smaller stride → More CPU time.

### Lottery vs Stride

| Lottery | Stride |
|---|---|
| Random | Deterministic |
| Uses tickets | Uses Pass and Stride |
| Probabilistic sharing | More precise sharing |
| Easier to add new processes | Has a global state problem when a new process joins |

**Important:**
- Lottery: easier to handle new processes.
- Stride: a new process needs a suitable initial Pass value.
- Setting its Pass to 0 may give it an unfair advantage.