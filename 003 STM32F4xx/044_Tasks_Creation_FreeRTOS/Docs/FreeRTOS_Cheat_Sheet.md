# FreeRTOS API Cheat Sheet

## 🧵 Task Management
- **xTaskCreate()**
  - Parameters: TaskFunction, Name, StackDepth, Parameters, Priority, TaskHandle  
  - Creates a new task and adds it to the scheduler.
- **vTaskDelete()**
  - Parameters: TaskHandle  
  - Deletes a task and frees its resources.
- **vTaskDelay()**
  - Parameters: TickCount  
  - Blocks the task for a given number of ticks.
- **vTaskSuspend()**
  - Parameters: TaskHandle  
  - Suspends a task until resumed.
- **vTaskResume()**
  - Parameters: TaskHandle  
  - Resumes a previously suspended task.

---

## 📦 Queues
- **xQueueCreate()**
  - Parameters: QueueLength, ItemSize  
  - Creates a queue to hold fixed-size items.
- **xQueueSend() / xQueueSendToBack() / xQueueSendToFront()**
  - Parameters: QueueHandle, Item, TicksToWait  
  - Sends an item to a queue (back or front).
- **xQueueReceive()**
  - Parameters: QueueHandle, Buffer, TicksToWait  
  - Receives an item from a queue.

---

## 🔒 Semaphores & Mutexes
- **xSemaphoreCreateBinary()**
  - Creates a binary semaphore (lock/unlock).
- **xSemaphoreCreateCounting()**
  - Parameters: MaxCount, InitialCount  
  - Creates a counting semaphore for multiple resources.
- **xSemaphoreCreateMutex()**
  - Creates a mutex for mutual exclusion.
- **xSemaphoreTake()**
  - Parameters: SemaphoreHandle, TicksToWait  
  - Attempts to take (lock) a semaphore/mutex.
- **xSemaphoreGive()**
  - Parameters: SemaphoreHandle  
  - Releases (unlocks) a semaphore/mutex.

---

## ⏱️ Timers
- **xTimerCreate()**
  - Parameters: Name, PeriodTicks, AutoReload, TimerID, Callback  
  - Creates a software timer with a callback function.
- **xTimerStart()**
  - Parameters: TimerHandle, TicksToWait  
  - Starts a timer running.
- **xTimerStop()**
  - Parameters: TimerHandle, TicksToWait  
  - Stops a running timer.

---

## ⚡ Event Groups
- **xEventGroupCreate()**
  - Creates an event group for bit-based synchronization.
- **xEventGroupSetBits()**
  - Parameters: EventGroupHandle, BitsToSet  
  - Sets one or more event bits.
- **xEventGroupClearBits()**
  - Parameters: EventGroupHandle, BitsToClear  
  - Clears one or more event bits.
- **xEventGroupWaitBits()**
  - Parameters: EventGroupHandle, BitsToWaitFor, ClearOnExit, WaitForAllBits, TicksToWait  
  - Waits until specified event bits are set.
