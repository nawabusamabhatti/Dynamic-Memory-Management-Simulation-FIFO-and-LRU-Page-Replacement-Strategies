

References for Two Algoriths:
https://www.geeksforgeeks.org/page-replacement-algorithms-in-operating-systems/
https://www.geeksforgeeks.org/program-for-least-recently-used-lru-page-replacement-algorithm/


Linked List:
https://www.geeksforgeeks.org/data-structures/linked-list/



linked list is used to store and manage page frames in memory for both the First-In, First-Out (FIFO) and Least Recently Used (LRU) page replacement algorithms. A linked list is chosen in this case for its dynamic nature, allowing for easy insertion and deletion of elements without the need for reallocation, unlike arrays.

Why LinkedList is Used:
Linked lists offer several advantages over arrays:

They can be easily resized during runtime.
Insertion and deletion of elements can be done with constant time complexity.
Memory allocation for the elements is non-contiguous, allowing for more efficient use of memory.
What Two Algorithms are Doing:
Both algorithms are used to simulate page replacement strategies in an operating system's memory management subsystem.

FIFO Algorithm: This algorithm replaces the oldest page in memory (i.e., the one that was loaded first) when a new page needs to be loaded, and no empty frames are available. It is a simple and easy-to-implement algorithm but can suffer from poor performance in certain situations.

LRU Algorithm: This algorithm replaces the least recently used page in memory when a new page needs to be loaded, and no empty frames are available. It works under the assumption that pages accessed recently are more likely to be accessed again soon. It generally provides better performance than the FIFO algorithm, but it can be more complex to implement.

Flow of the Code:
The read_trace_file function reads a trace file containing a sequence of memory access operations and stores them in an array of TraceEntry structures.
The create_frame_list function creates a linked list of PageFrameNode structures representing the available memory frames.
The fifo_algorithm function iterates over the trace entries and, for each entry, checks if the corresponding page is already in memory. If not, the oldest page is replaced with the new one following the FIFO strategy. It also updates the dirty flag if a write operation is performed and counts the number of reads and writes.
The lru_algorithm function follows a similar process but replaces the least recently used page instead of the oldest one. It also updates the lastUsed field for each page frame to track the recency of access.
The main function reads the trace file, executes both algorithms, and prints the contents of the page frames and the number of reads and writes for each algorithm.
Both algorithms use a linked list to manage the memory frames, allowing for efficient insertion, deletion, and traversal of the frames while simulating the page replacement strategies.