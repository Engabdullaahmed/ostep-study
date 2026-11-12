# Summary Dialogue on CPU Virtualization

### 1. Traps & Trap Handlers
- Transfer control from the running program to the OS.
- Allow the OS to handle privileged operations and system calls.

### 2. Timer Interrupts
- Allow the OS to regain control of the CPU after a certain period of time.
- Prevent a program from keeping the CPU forever.

### 3. Context Switching
- Save and restore the state of a process when switching between processes.
- Allow the CPU to execute multiple processes over time.

### 4. Hardware & OS Cooperation
- Hardware and the OS work together to achieve CPU virtualization.
- Hardware provides mechanisms, and the OS uses them to manage CPU execution.

### 5. Limited Direct Execution
- Allow programs to execute directly on the CPU for better performance.
- The OS maintains control using hardware mechanisms such as traps and timer interrupts.

### Key Takeaway
**The OS is not just a program runner; it is a resource manager.**


### 1. Shortest Job First (SJF)
- Run shorter jobs before longer jobs.
- Goal: Minimize Average Waiting Time.

### 2. Multi-Level Feedback Queue (MLFQ)
- Combines ideas from SJF and Round Robin.
- Uses multiple priority queues.
- Processes can move between queues based on their behavior.

### 3. Scheduler Design
- Building a good scheduler is difficult.
- Different scheduling policies have different trade-offs.
- No single policy is perfect for every workload.

### 4. Scheduling Metrics
- Turnaround Time: Time from job arrival to completion.
- Response Time: Time from job arrival to its first CPU execution.

Improving one metric may negatively affect another.

### 5. Engineering Pragmatism
- The goal is not always to find the perfect solution.
- Sometimes the goal is to avoid a bad solution or disaster.

### 6. Gaming the Scheduler
- Processes may try to manipulate scheduling policies.
- The OS should prevent processes from abusing CPU scheduling.

### Key Takeaway
**A good scheduler balances performance, fairness, and responsiveness.**